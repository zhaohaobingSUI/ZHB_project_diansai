# 2021电赛F题视觉分析+代码免费开源

> 最近好多小宝宝们要电赛题的源码，其他csdn营销号下载都需要会员或者钱，哥们先把视觉分析+代码开源，饿死营销号

视觉的一个任务是视觉上位机模块识别数字并进行滤波和判断处理，传指令给下位机；另一个任务是红线循迹。



不多bb，先上效果图：

K210数字识别效果：

![k210结果2](https://github.com/zhaohaobingSUI/ZHB_project_diansai/blob/master/images/k210%E7%BB%93%E6%9E%9C2.png)

（我媛哥的手真好看）

openmv红线循迹效果：

![openmv结果1](https://github.com/zhaohaobingSUI/ZHB_project_diansai/blob/master/images/openmv%E7%BB%93%E6%9E%9C1.png)



硬件工具：K210、openmv

软件工具：Maixpy IDE、OpenMV IDE

IDE可到官网下载：

https://www.sipeed.com/index.html

https://singtown.com/openmv/

![IDE](https://github.com/zhaohaobingSUI/ZHB_project_diansai/blob/master/images/IDE.png)

## 1、K210数字识别、滤噪、判断

正常操作是上位机是识别，给下位机传数据，处理放到下位机；假如你有个坑比队友，处理还是放上位机干吧；

经过算法优化，现在几乎不存在掉帧。

### 1.1 功能难点及对应函数实现分析

1、在小车行驶过程中，会存在数字不能完全进入视野中情况等存在有很多帧误识情况，要进行滤波处理

2、每一帧要做处理的同时每个目标值的矩形框进行处理，每个目标值的矩形框还要进行滤波

3、在上位机上不断的优化算法，减少掉帧

4、在Maixpy IDE中python 的numpy、pandas巴拉巴拉包都调不了

5、图中最多出现四个，但这里设了读六个矩形框，留两个容错，不然有误识别的直接死机

6、给下位机传送指令：

一开始初始化识别传送对应的数字

若为12，则后面不在传送指令

若为34，则后面路口处传"l"or"r"

若为5678，则后面两个路口传送两次"l"or“r”

7、设计思路

通过初始化函数识别一开始给入的数字并保存下来；

根据识别的情况进入不同的程序；

12号病房，识别完了以后是不用在路上在识别的，直接关掉程序；

34号病房，初始化识别完了，加两秒延迟，避免在开始的时候连续识别传指令，要在路上识别一次，要保证返回来的时候不识别不然又给32传指令了，还要保证初始化识别完了以后不会紧接着识别误认为是路上的标签给32传指令；

5678也一样，但是路上得识别两次穿两次指令；



### 1.2 YOLOV5神经网络模型训练

训练集：

![数据集1](https://github.com/zhaohaobingSUI/ZHB_project_diansai/blob/master/images/%E6%95%B0%E6%8D%AE%E9%9B%861.png)

测试集：

![数据集2](https://github.com/zhaohaobingSUI/ZHB_project_diansai/blob/master/images/%E6%95%B0%E6%8D%AE%E9%9B%862.png)

训练输出结果：

![输出结果](https://github.com/zhaohaobingSUI/ZHB_project_diansai/blob/master/images/%E8%BE%93%E5%87%BA%E7%BB%93%E6%9E%9C.png)



将通过拍摄3403张赛道数字照片，使用labellmg进行标签标定，制作数据集，yolov5训练

详细过程可看下面文章：

https://blog.csdn.net/zhaohaobingniu/article/details/120397185?spm=1001.2014.3001.5502

https://blog.csdn.net/zhaohaobingniu/article/details/120255571?spm=1001.2014.3001.5502

注意：这里yolov5得到的是.pt文件，需要进行模型转换，转化成可以加载在K210板上的.kmodel模型（后面细讲）



### 1.3 K210操作步骤

#### 1.3.1 下载K210的IDE

https://www.sipeed.com/index.html

#### 1.3.2 烧入最新固件库

官方教程：

https://wiki.sipeed.com/soft/maixpy/zh/get_started/upgrade_maixpy_firmware.html

更新固件库：

![固件库](https://github.com/zhaohaobingSUI/ZHB_project_diansai/blob/master/images/%E5%9B%BA%E4%BB%B6%E5%BA%93.png)

#### 1.3.3 将文件放入TF卡中

文件目录：

![文件目录](https://github.com/zhaohaobingSUI/ZHB_project_diansai/blob/master/images/%E6%96%87%E4%BB%B6%E7%9B%AE%E5%BD%95.png)

将上述文件全复制到tf卡中，tf卡插入k210

注意：tf卡先格式成FAT32格式，部分牌子的tf卡格式了也不能挂载到k210上，建议多换几张卡试试

#### 1.3.4 IED中查看效果

IDE中运行效果：

![ide效果图](https://github.com/zhaohaobingSUI/ZHB_project_diansai/blob/master/images/ide%E6%95%88%E6%9E%9C%E5%9B%BE.png)

#### 1.3.5 通过串口调试助手测试指令通信

引脚9是TX，引脚10是RX，波特率为115200

通过usb转ttl连接到电脑上

初始识别数字为6，两次转向是向左

![串口发送数据图](https://github.com/zhaohaobingSUI/ZHB_project_diansai/blob/master/images/%E4%B8%B2%E5%8F%A3%E5%8F%91%E9%80%81%E6%95%B0%E6%8D%AE%E5%9B%BE.png)



### 1.4 上代码含详细注释



第一版：

```python
import sensor,image,lcd,time
import KPU as kpu
from machine import UART
from fpioa_manager import fm

lcd.init(freq=15000000)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_hmirror(0)
sensor.run(1)
#加载yolov5模型
task = kpu.load("/sd/yolov5.kmodel")
f=open("anchors.txt","r")
anchor_txt=f.read()
L=[]
for i in anchor_txt.split(","):
    L.append(float(i))
anchor=tuple(L)
f.close()
f=open("lable.txt","r")
lable_txt=f.read()
lable = lable_txt.split(",")
f.close()
#设置RX、RT引脚
fm.register(9, fm.fpioa.UART1_TX, force=True)
fm.register(10, fm.fpioa.UART1_RX, force=True)
#设置串口通信
uart_A = UART(UART.UART1, 115200, 8, 1, 0, timeout=1000, read_buf_len=4096)
anchor = (0.1766, 0.1793, 0.4409, 0.3797, 0.6773, 0.5954, 1.0218, 0.9527, 2.158, 1.6841)
sensor.set_windowing((224, 224))
a = kpu.init_yolo2(task, 0.5, 0.3, 5, anchor)
classes=["9","1","4","2","3","8","5","6","7" ]

#全局变量，保存初始化识别的数字
intnum = 0
#初始化识别函数
def begin(intnum):
    TF = 1
    #得分序列，放1-8识别的次数，每一帧识别成哪个，对应的位置加一，1-8哪个先到10即最终识别为哪个
    List_score01 = [0]*8
    while(TF):
         img = sensor.snapshot()
         #code是yolov5返回的每个矩形框的参数
         #例图中出现两个目标区域的时候：[{"x":9, "y":99, "w":55, "h":82, "value":0.697979, "classid":8, "index":0, "objnum":2}, {"x":137, "y":105, "w":56, "h":67, "value":0.939132, "classid":4, "index":1, "objnum":2}]
         code = kpu.run_yolo2(task, img)
         #print(code)
         if code:
             for i in code:
                #画目标区域矩形框
                a = img.draw_rectangle(i.rect())
                a = lcd. display(img)
                list1=list(i.rect())
                #print(classes[i.classid()])
                #识别到的加1
                List_score01[int(classes[i.classid()])-1] += 1
                #print(List_score01)
                if(List_score01[0] >= 10):
                    intnum = 1
                    #给下位机通信传指令
                    uart_A.write('1')
                    #print(1)
                    #退出初始化循环
                    TF = 0
                if(List_score01[1] >= 10):
                    intnum = 2
                    uart_A.write('2')
                    #print(2)
                    TF = 0
                if(List_score01[2] >= 10):
                    intnum = 3
                    uart_A.write('3')
                    #print(3)
                    TF = 0
                if(List_score01[3] >= 10):
                    intnum = 4
                    uart_A.write('4')
                    #print(4)
                    TF = 0
                if(List_score01[4] >= 10):
                    intnum = 5
                    uart_A.write('5')
                    #print(5)
                    TF = 0
                if(List_score01[5] >= 10):
                    intnum = 6
                    uart_A.write('6')
                    #print(6)
                    TF = 0
                if(List_score01[6] >= 10):
                    intnum = 7
                    uart_A.write('7')
                    #print(7)
                    TF = 0
                if(List_score01[7] >= 10):
                    intnum = 8
                    uart_A.write('8')
                    print(8)
                    TF = 0
         else:
             a = lcd.display(img)
    return intnum

#34道路识别函数
def threefour(intnum):
    #设置二维矩阵，存放每一个矩形框中不同数字识别的次数
    List_score02 = [[0]*8] * 6
    intnum02 = [0]*6
    TF = 1
    while(TF):
         #加载一帧图像
         img = sensor.snapshot()
         code = kpu.run_yolo2(task, img)
         if code:
             int_i = 0
             for i in code:
                 int_i +=1
                 a=img.draw_rectangle(i.rect())
                 a = lcd. display(img)
                 list1=list(i.rect())
                 b=(list1[0]+list1[2])/2
                 #对应的矩阵值加一
                 List_score02[int_i][int(classes[i.classid()])-1] += 1
                 print(List_score02[int_i])
                 #该目标框逐个数字分析是否出现次数到达10，即为该目标区域中的数字
                 for ii in range(8):
                    if(List_score02[int_i][ii] >= 10):
                        intnum02[int_i] = ii+1
                 #该目标区域中的数字是否是初始化识别的数字
                 if(intnum == intnum02[int_i]):
                 #判断位置，从而判断先做向右转
                    if(b < 75):
                        uart_A.write("l")
                        print("l")
                        TF = 0
                    if(b > 75):
                        uart_A.write("r")
                        print("r")
                        TF = 0
         else:
             a = lcd.display(img)
    return 0

#5678道路识别函数
def fivesixseveneight(intnum):
    #设置二维矩阵，存放每一个矩形框中不同数字识别的次数，一帧中最多有四个目标区域，但这里设置六个，防止有误识别的造成有很多矩形框程序暴死
    List_score02 = [[0]*8] * 6
    intnum02 = [0]*6
    TF = 2
    #5678道路识别要识别两次，传两次指令，两次直接通过延时函数断开
    while(TF):
         img = sensor.snapshot()
         code = kpu.run_yolo2(task, img)
         if code:
             int_i = 0
             for i in code:
                 int_i +=1
                 a=img.draw_rectangle(i.rect())
                 a = lcd. display(img)
                 list1=list(i.rect())
                 b=(list1[0]+list1[2])/2
                 List_score02[int_i][int(classes[i.classid()]) -1] += 1
                 print(List_score02[int_i])
                 for ii in range(8):
                    if(List_score02[int_i][ii] >= 10):
                        intnum02[int_i] = ii+1
                 if(intnum == intnum02[int_i]):
                    if(b < 75):
                        uart_A.write("l")
                        print("l")
                        TF -= 1
                        List_score02 = [[0]*8] * 6
                        intnum02 = [0]*6
                        time.sleep(3)
                    if(b > 75):
                        uart_A.write("r")
                        print("r")
                        TF -= 1
                        List_score02 = [[0]*8] * 6
                        intnum02 = [0]*6
                        time.sleep(3)
         else:
             a = lcd.display(img)
    return 0

#执行程序
intnum = begin(intnum)
time.sleep(3)
if(intnum == 3 or intnum == 4):
    threefour(intnum)
if(intnum == 5 or intnum == 6 or intnum ==7 or intnum == 8):
    fivesixseveneight(intnum)
uart_A.deinit()
del uart_A
a = kpu.deinit(task)


```



第二版：

```python
import sensor,image,lcd,time
import KPU as kpu
from machine import UART
from fpioa_manager import fm

lcd.init(freq=15000000)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_hmirror(0)
sensor.run(1)
#加载yolov5模型
task = kpu.load("/sd/yolov5.kmodel")
f=open("anchors.txt","r")
anchor_txt=f.read()
L=[]
for i in anchor_txt.split(","):
    L.append(float(i))
anchor=tuple(L)
f.close()
f=open("lable.txt","r")
lable_txt=f.read()
lable = lable_txt.split(",")
f.close()
#设置RX、RT引脚
fm.register(9, fm.fpioa.UART1_TX, force=True)
fm.register(10, fm.fpioa.UART1_RX, force=True)
#设置串口通信
uart_A = UART(UART.UART1, 9600, 8, 1, 0, timeout=1000, read_buf_len=4096)
anchor = (0.1766, 0.1793, 0.4409, 0.3797, 0.6773, 0.5954, 1.0218, 0.9527, 2.158, 1.6841)
sensor.set_windowing((224, 224))
a = kpu.init_yolo2(task, 0.5, 0.3, 5, anchor)
classes=["9","1","4","2","3","8","5","6","7" ]

#全局变量，保存初始化识别的数字
intnum = 0
#初始化识别函数
def begin(intnum):
    TF = 1
    #得分序列，放1-8识别的次数，每一帧识别成哪个，对应的位置加一，1-8哪个先到10即最终识别为哪个
    List_score01 = [0]*8
    while(TF):
         img = sensor.snapshot()
         #code是yolov5返回的每个矩形框的参数
         #例图中出现两个目标区域的时候：[{"x":9, "y":99, "w":55, "h":82, "value":0.697979, "classid":8, "index":0, "objnum":2}, {"x":137, "y":105, "w":56, "h":67, "value":0.939132, "classid":4, "index":1, "objnum":2}]
         code = kpu.run_yolo2(task, img)
         #print(code)
         if code:
             for i in code:
                #画目标区域矩形框
                a = img.draw_rectangle(i.rect())
                a = lcd. display(img)
                list1=list(i.rect())
                #print(classes[i.classid()])
                #识别到的加1
                List_score01[int(classes[i.classid()])-1] += 1
                #print(List_score01)
                if(List_score01[0] >= 10):
                    intnum = 1
                    #给下位机通信传指令
                    uart_A.write('A')
                    print(1)
                    #退出初始化循环
                    TF = 0
                if(List_score01[1] >= 10):
                    intnum = 2
                    uart_A.write('B')
                    print(2)
                    TF = 0
                if(List_score01[2] >= 10):
                    intnum = 3
                    uart_A.write('C')
                    print(3)
                    TF = 0
                if(List_score01[3] >= 10):
                    intnum = 4
                    uart_A.write('D')
                    print(4)
                    TF = 0
                if(List_score01[4] >= 10):
                    intnum = 5
                    uart_A.write('E')
                    print(5)
                    TF = 0
                if(List_score01[5] >= 10):
                    intnum = 6
                    uart_A.write('F')
                    print(6)
                    TF = 0
                if(List_score01[6] >= 10):
                    intnum = 7
                    uart_A.write('G')
                    #print(7)
                    TF = 0
                if(List_score01[7] >= 10):
                    intnum = 8
                    uart_A.write('H')
                    print(8)
                    TF = 0
         else:
             a = lcd.display(img)
    return intnum


#道路识别函数
def then(intnum):
    while(1):
        #设置二维矩阵，存放每一个矩形框中不同数字识别的次数，一帧中最多有四个目标区域，但这里设置六个，防止有误识别的造成有很多矩形框程序暴死
        List_score02 = [[0]*8] * 6
        intnum02 = [0]*6
        TF = 1
        while(TF):
             img = sensor.snapshot()
             code = kpu.run_yolo2(task, img)
             if code:
                 int_i = -1
                 for i in code:
                     int_i +=1
                     a=img.draw_rectangle(i.rect())
                     a = lcd. display(img)
                     list1=list(i.rect())
                     b=(list1[0]+list1[2])/2
                     List_score02[int_i][int(classes[i.classid()]) -1] += 1
                     #print(int_i)
                     print(str(List_score02[int_i]) + str(int_i))
                     for ii in range(8):
                     #int_i是第几个框，ii是第几个框中的每个数字
                        if(List_score02[int_i][ii] == 10 and intnum == ii+1):
                            if(b < 75):
                                uart_A.write("L")
                                print("L")
                                TF = 0
                                List_score02 = [[0]*8] * 6
                                intnum02 = [0]*6
                            if(b > 75):
                                uart_A.write("R")
                                print("R")
                                TF = 0
                                List_score02 = [[0]*8] * 6
                                intnum02 = [0]*6
             else:
                 a = lcd.display(img)
                 TF = 0
                 List_score02 = [[0]*8] * 6
                 intnum02 = [0]*6
    return 0

#执行程序
time.sleep(3)
uart_A.write("E")
intnum = begin(intnum)
time.sleep(3)
then(intnum)
uart_A.deinit()
del uart_A
a = kpu.deinit(task)

```



## 2、OPENMV红线循迹

循迹测试：

![openmv结果1](images\openmv结果1.png)

测试结果：

![openmv结果2](images\openmv结果2.png)

用openmv红线循迹，这部分比较简单，就不多说了吧

用灰度传感器循迹也可以，不过调的不好容易走s形

