import sensor
import image
import time
import math
import pyb
from pyb import Pin, Timer,LED
from GeometryFeature import GeometryFeature
LED(4).on()
is_debug = True
DISTORTION_FACTOR = 1.5#畸变矫正因子
IMG_WIDTH  = 64#像素点宽度
IMG_HEIGHT = 64#像素点高度
def init_sensor():#初始化感光器
    sensor.reset()
    sensor.set_pixformat(sensor.GRAYSCALE)#设置为灰度图
    sensor.set_framesize(sensor.B64X64)  #设置像素大小
    sensor.skip_frames(time=2000)        #最大像素点个数
    sensor.set_auto_gain(False)          #颜色追踪关闭自动增益
    sensor.set_auto_whitebal(False)      #颜色追踪关闭自动白平衡
init_sensor()
INTERSERCT_ANGLE_THRESHOLD = (45,90)     #设置角度阈值
LINE_COLOR_THRESHOLD = [(0, 120)]        #设置巡线的颜色阈值
ROIS = {                                 #ROIS将镜头的画面分割为5个区域分别找寻色块
    'down': (0, 55, 64, 8),
    'middle': (0, 28, 64, 8),
    'up': (0, 0, 64, 8),
    'left': (0, 0, 8, 64),
    'right': (56, 0, 8, 64)
}
def find_blobs_in_rois(img):
    '''
    在ROIS中寻找色块，获取ROI中色块的中心区域与是否有色块的信息
    '''
    global ROIS
    global is_debug
    roi_blobs_result = {}
    for roi_direct in ROIS.keys():
        roi_blobs_result[roi_direct] = {
            'cx': -1,
            'cy': -1,
            'blob_flag': False
        }
    for roi_direct, roi in ROIS.items():
        blobs=img.find_blobs(LINE_COLOR_THRESHOLD, roi=roi, merge=True, pixels_area=10)
        if len(blobs) == 0:
            continue
        largest_blob = max(blobs, key=lambda b: b.pixels())
        x,y,width,height = largest_blob[:4]
        if not(width >=5 and width <= 15 and height >= 5 and height <= 15):
            continue
        roi_blobs_result[roi_direct]['cx'] = largest_blob.cx()
        roi_blobs_result[roi_direct]['cy'] = largest_blob.cy()
        roi_blobs_result[roi_direct]['blob_flag'] = True
        if is_debug:
            img.draw_rectangle((x,y,width, height), color=(127))
    return roi_blobs_result
def visualize_result(canvas, cx_mean, cx, cy, is_turn_left, is_turn_right, is_t, is_cross):
    '''
    可视化结果
    '''
    if not(is_turn_left or is_turn_right or is_t or is_cross):
        mid_x = int(canvas.width()/2)
        mid_y = int(canvas.height()/2)
        print("mid_x= %d,cx_mean= %d,mid_x-cx_mean =%dsd       ",mid_x,cx_mean,(mid_x-cx_mean)*2)
        canvas.draw_circle(int(cx_mean), mid_y, 5, color=(255))
        canvas.draw_circle(mid_x, mid_y, 8, color=(0))
        canvas.draw_line((mid_x, mid_y, int(cx_mean), mid_y), color=(255))

    turn_type = 'N'   #判断为直线
    if is_t or is_cross:
        canvas.draw_cross(int(cx), int(cy), size=10, color=(255))
        canvas.draw_circle(int(cx), int(cy), 5, color=(255))
    if is_t:
        turn_type = 'T'  #判断为T字路口
    elif is_cross:
        turn_type = 'C'  #判断为十字路口
    canvas.draw_string(0, 0, turn_type, color=(0))
last_cx = 0
last_cy = 0
while True:
    img = sensor.snapshot()     #拍取一张图片
    img.lens_corr(DISTORTION_FACTOR)  #进行镜头畸形矫正，里面的参数是进行鱼眼矫正的程度
    lines = img.find_lines(threshold=1000, theta_margin = 50, rho_margin = 50)
    intersect_pt = GeometryFeature.find_interserct_lines(lines, angle_threshold=(45,90), window_size=(IMG_WIDTH, IMG_HEIGHT))
    if intersect_pt is None:
        intersect_x = 0
        intersect_y = 0
    else:
        intersect_x, intersect_y = intersect_pt
    reslut = find_blobs_in_rois(img)
    is_turn_left = False
    is_turn_right = False
    if (not reslut['up']['blob_flag'] ) and reslut['down']['blob_flag']:
        if reslut['left']['blob_flag']:
            is_turn_left = True
        if reslut['right']['blob_flag']:
            is_turn_right = True
    is_t = False
    is_cross = False
    cnt = 0
    for roi_direct in ['up', 'down', 'left', 'right']:
        if reslut[roi_direct]['blob_flag']:
            cnt += 1
    is_t = cnt == 3
    is_cross = cnt == 4
    cx_mean = 0
    for roi_direct in ['up', 'down', 'middle']:
        if reslut[roi_direct]['blob_flag']:
            cx_mean += reslut[roi_direct]['cx']
        else:
            cx_mean += IMG_WIDTH / 2
    cx_mean /= 3  #表示为直线时区域的中心x坐标
    cx = 0        #cx,cy表示当测到为T型或者十字型的时候计算的交叉点的坐标
    cy = 0
    if is_cross or is_t:
        cnt = 0
        for roi_direct in ['up', 'down']:
            if reslut[roi_direct]['blob_flag']:
                cnt += 1
                cx += reslut[roi_direct]['cx']
        if cnt == 0:
            cx = last_cx
        else:
            cx /= cnt
        cnt = 0
        for roi_direct in ['left', 'right']:
            if reslut[roi_direct]['blob_flag']:
                cnt += 1
                cy += reslut[roi_direct]['cy']
        if cnt == 0:
            cy = last_cy
        else:
            cy /= cnt
    last_cx = cx
    last_cy = cy
    if is_debug:
        visualize_result(img, cx_mean, cx, cy, is_turn_left, is_turn_right, is_t, is_cross)
