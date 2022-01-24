#include "sys.h"

u8 res1;
int Test_Distance;
int record;
int num_record;//目标值
int YaoP;
u8 CheckYP;
u8 WXZFlag,BXZFlag;//修正标志位
u8 WJCFlag,BJCFlag;//是否开启检测的标志位
int num, num_1;
extern int circle_count,circle_count_1;
extern int F1,F2,F3,F4,F5,TotalF;
extern 	int Lef,Rig,Tot;
int test,testnum;
extern u8 res3;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
 	uart_init(9600);
	Usart3_Init(9600);
	OLED_Init();
	BEEP_Init();
	LED_init();
	Infrared_init();
	S305_init();
	TIM1_Init(249,7199);//25
	TIM2_PWM_Init(999,71);
	TIM3_Mode_Config();
	TIM4_Mode_Config();
	OLED_ShowString(0,0,"LELE");
	OLED_Display_On();
	test =0;
	circle_count = 0;
	circle_count_1 = 0;
	CheckYP = '1';
	Test_Distance = 3400;
	while(1)
	{
		ReadS305();
		OLED_ShowNum(0,0,F1,1,16);
		OLED_ShowNum(8,0,F2,1,16);
		OLED_ShowNum(16,0,F3,1,16);
		OLED_ShowNum(24,0,F4,1,16);
		OLED_ShowNum(32,0,F5,1,16);
		OLED_ShowNum(0,2,TotalF,1,16);
		ReadInf();
		OLED_ShowNum(0,4,Lef,1,16);
		OLED_ShowNum(8,4,Rig,1,16);
//		USART_Printf(USART1,"I1 LO\r\n");
//		USART_Printf(USART3,"I3 LO\r\n");
		delay_ms(200);
		
		if(res1 == 'T')
		{
			testnum = VisGO();
			USART_Printf(USART1,"test:%d\r\n",testnum);
			res1 = '0';
		}
		
		if(res1 == 'G')
		{
			printf("en");
			WXZFlag = '1';//开启修正
			WJCFlag = '1';//开启检测
			while(TotalF != 5)
			{
				Wforward(SetSpeed);
			}
			WXZFlag = '0';//开启修正
			WJCFlag = '0';//开启检测
			Brake();
			res1 = '0';
		}
		
		if(res1 == 'g')
		{
			printf("en");
			WXZFlag = '1';//开启修正
			WJCFlag = '1';//开启检测
			Distance(Test_Distance,SetSpeed);
			WXZFlag = '0';//开启修正
			WJCFlag = '0';//开启检测
			Brake();
			res1 = '0';
		}
		
		if(res1 == 'b')
		{

			Brake();
			delay_ms(10);
			res1 = '0';
		}
		
		if(res1 == '3')
		{
			BackFrom3();
			res1 = '0';
		}
		
		if(res1 == '4')
		{
			BackFrom4();
			res1 = '0';
		}
		
		if(res1 == '5')
		{
			BackFrom5();
			res1 = '0';
		}
		
		if(res1 == '6')
		{
			BackFrom6();
			res1 = '0';
		}
		
		if(res1 == '7')
		{
			BackFrom7();
			res1 = '0';
		}
		
		if(res1 == '8')
		{
			BackFrom8();
			res1 = '0';
		}
		
		if(res1 == 'a')
		{
			Test_Distance += 50;
			printf("distance：%d\r\n",Test_Distance);
			res1 = '0';
		}
		
		if(res1 == 'd')
		{
			Test_Distance -= 50;
			printf("distance：%d\r\n",Test_Distance);
			res1 = '0';
		}
		
		if(res1 == 'L')
		{
			WTurnLeft90();
			res1 = '0';
		}
		
		if(res1 == 'R')
		{
			WTurnRight90();
			res1 = '0';
		}
		
		if(res1 == 'A'||res3 == 'A')
		{	
			Goto1();
			res1 = '0';
			res3 = 'N';
		}
		
		if(res1 == 'B'||res3 == 'B')
		{		
			Goto2();
			res1 = '0';
			res3 = 'N';
		}

		if(res3 == 'E')
		{
			OLED_ShowString(0,6,"Connect");
			res1 = '0';
			res3 = 'N';
		}		
	}
}

void USART1_IRQHandler(void)   
{  
     if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)  
      {       
            res1= USART_ReceiveData(USART1); 	 
						USART_SendData(USART1,res1); 			
      }      
}

//定时器1中断服务程序
void TIM1_UP_IRQHandler(void)
{  	     
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//检查指定的TIM中断发生与否:TIM 中断源 
	{
		//应用代码编写区
		if(WXZFlag == '1')//如果开启修正标志位
		{
			ReadS305();
			if(TotalF > 2)
			{
				/*直接转向不修正*/
			}
			else
			{
				if(F1 == 1 && F5 == 0)
				{
					
					BLWcorect();
				}
				if(F2 == 1 && F4 == 0)
				{
//					printf("L");
					LWcorect();
				}
				if(F4 == 1 && F2 == 0)
				{
					RWcorect();
//					printf("R");
				}
				if(F5 == 1 && F1 == 0)
				{
					BRWcorect();
				}
				  Wforward(SetSpeed);
			}
			
		}	
		if(CheckYP == '1')
		{
			ReadInf();
			YaoP = Lef;			
		}	
		if(test == 50)
		{
			test = 0;
//			if(res1 != '0') res1 = '0';
//			USART_SendData(USART1,res1); 	
		}
		else 
		{
			test++;
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//清除TIMx的中断待处理位:TIM 中断源 
	}	     
}







/************************************************
速度测试代码
		Wforward(SetSpeed);
		num=TIM4->CNT;
		num_1=TIM3->CNT;
		OLED_ShowString(0,0,"circle:");
		OLED_ShowNum(56,0,circle_count,3,16);
		OLED_ShowString(0,2,"num:");
		OLED_ShowNum(32,2,num,4,16);
		OLED_ShowString(0,4,"circle:");
		OLED_ShowNum(56,4,circle_count_1,3,16);
		OLED_ShowString(0,6,"num:");
		OLED_ShowNum(32,6,num_1,4,16);
		delay_ms(20);
*************************************************/

/************************************************
LED测试代码
		R();
		delay_ms(1000);
		G();
		delay_ms(1000);
		Y();
		delay_ms(1000);
************************************************/

/***********************************************
灰度传感器测试代码
		ReadS307();
		OLED_ShowNum(0,0,D7_1,1,16);
		OLED_ShowNum(8,0,D7_2,1,16);
		OLED_ShowNum(16,0,D7_3,1,16);
		OLED_ShowNum(24,0,D7_4,1,16);
		OLED_ShowNum(32,0,D7_5,1,16);
		OLED_ShowNum(40,0,D7_6,1,16);
		OLED_ShowNum(48,0,D7_7,1,16);
		OLED_ShowNum(0,2,Total7,1,16);
		delay_ms(500);
************************************************/

/***********************************************
灰度传感器测试代码
		ReadS305();
		OLED_ShowNum(0,0,F1,1,16);
		OLED_ShowNum(8,0,F2,1,16);
		OLED_ShowNum(16,0,F3,1,16);
		OLED_ShowNum(24,0,F4,1,16);
		OLED_ShowNum(32,0,F5,1,16);
		OLED_ShowNum(0,2,TotalF,1,16);
		ReadInf();
		OLED_ShowNum(0,4,Lef,1,16);
		OLED_ShowNum(8,4,Rig,1,16);
		OLED_ShowNum(0,6,Tot,1,16);
		delay_ms(200);
************************************************/

