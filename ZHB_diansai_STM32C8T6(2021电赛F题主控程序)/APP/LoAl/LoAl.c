#include "LoAl.h"
#include "sys.h"
/*位置算法*/
extern int circle_count;
extern int circle_count_1;
extern int num,num_1;
extern int Test_Distance;
extern int record;
extern int num_record;//目标值
extern int F1,F2,F3,F4,F5,TotalF;
extern int YaoP;
extern u8 CheckYP;
extern u8 WXZFlag,BXZFlag;//修正标志位
extern u8 WJCFlag,BJCFlag;//是否开启检测的标志位

/************************************
  5					8

  7					6


		3			4


		1			2

************************************/


void Goto1(void)
{
		OLED_Clear();
		OLED_ShowString(0,0,"GET:1");
		YaoP = 0;
		CheckYP = '1';//开启检测药品
		while(YaoP == 0);//等待放药品 空
		R();
		CheckYP = '0';//关闭检测药品
		delay_ms(1000);
		WXZFlag = '1';//开启修正
		WJCFlag = '1';//开启检测
		delay_ms(500);
		TotalF = 0;
		while(TotalF < 3)//等待识别路口
		{Wforward(SetSpeed);}		
		WXZFlag = '0';//关闭修正
		Distance(ds,SetSpeed);//等待车身中心到达路口
		Brake();
		WTurnLeft90();//左转
		WXZFlag = '1';//开启修正
		delay_ms(200);
		Distance(3400,SetSpeed);//函数里关闭了修正		
		Brake();		
		CheckYP = '1';//开启检测药品
		YaoP = 1;
		delay_ms(500);//检测药品
		while( YaoP == 1);//等待药品移开
		CheckYP = '0';
		BEEP_ON();
		delay_ms(1000);
		BEEP_OFF();
		//调头
		WTurnLeft90();//左转
		delay_ms(450);
		WTurnLeft90();//左转		
		WXZFlag = '1';//开启修正
		delay_ms(500);
		while(TotalF < 3)//等待识别路口
		{Wforward(SetSpeed);}
		WXZFlag = '0';//关闭修正
		Distance(ds,SetSpeed);//等待车身中心到达路口
		delay_ms(200);
		WTurnRight90();//右转
		WXZFlag = '1';//开启修正
		delay_ms(200);
		Distance(4800,300);//函数里关闭了修正		
		Brake();
		G();
}

void Goto2(void)
{
	OLED_Clear();
	OLED_ShowString(0,0,"GET:2");
	YaoP = 0;
	CheckYP = '1';//开启检测药品
	while(YaoP == 0);//等待放药品
	R();
	CheckYP = '0';//关闭检测药品
	delay_ms(1000);
	WXZFlag = '1';//开启修正
	WJCFlag = '1';//开启检测
	delay_ms(500);
	TotalF = 0;
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';//关闭修正
	Distance(ds,SetSpeed);
	WTurnRight90();//右转
	WXZFlag = '1';//开启修正
	Distance(3400,SetSpeed);//函数里开启了修正
	Brake();
	CheckYP = '1';//开启检测药品
	YaoP = 1;
	delay_ms(500);
	while( YaoP == 1);//等待药品移开
	CheckYP = '0';
	BEEP_ON();
	delay_ms(1000);
	BEEP_OFF();
	//调头
	WTurnLeft90();//左转
	delay_ms(450);
	WTurnLeft90();//左转
	WXZFlag = '1';//开启修正
	delay_ms(500);
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';//关闭修正
	Distance(ds,SetSpeed);
	WTurnLeft90();//右转
	WXZFlag = '1';//开启修正		
	Distance(4800,SetSpeed);//函数里开启了修正		
	Brake();
	G();
}

void BackFrom3(void)
{
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(dds,SetSpeed);
	WTurnRight90();
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	Distance(5400,SetSpeed);//函数里开启了修正
	Brake();
	WXZFlag = '0';
	WJCFlag = '0';
}

void BackFrom4(void)
{
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(dds,SetSpeed);
	WTurnLeft90();
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	Distance(5400,SetSpeed);//函数里开启了修正
	Brake();
	WXZFlag = '0';
	WJCFlag = '0';
}

void BackFrom5(void)
{
	WXZFlag = '1';
	WJCFlag = '1';
	while(F1 == 0 || F2 == 0)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(dds,SetSpeed);
	WTurnLeft90();
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(F4 == 0 || F5 == 0)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(ddds,SetSpeed);
	WTurnRight90();
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(ds,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	Distance(5400,SetSpeed);//函数里开启了修正
	Brake();
	WXZFlag = '0';
	WJCFlag = '0';
}

void BackFrom6(void)
{
	WXZFlag = '1';
	WJCFlag = '1';
	while(F1 == 0 || F2 == 0)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(dds,SetSpeed);
	WTurnLeft90();
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(F1 == 0 || F2 == 0)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(ddds,SetSpeed);
	WTurnLeft90();
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(ds,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	Distance(5400,SetSpeed);//函数里开启了修正
	Brake();
	WXZFlag = '0';
	WJCFlag = '0';
}

void BackFrom7(void)
{
	WXZFlag = '1';
	WJCFlag = '1';
	while(F4 == 0 || F5 == 0)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(dds,SetSpeed);
	WTurnRight90();
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(F4 == 0 || F5 == 0)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(ddds,SetSpeed);
	WTurnRight90();
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(ds,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	Distance(5400,SetSpeed);//函数里开启了修正
	Brake();
	WXZFlag = '0';
	WJCFlag = '0';
}

void BackFrom8(void)
{
	WXZFlag = '1';
	WJCFlag = '1';
	while(F4 == 0 || F5 == 0)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(dds,SetSpeed);
	WTurnRight90();
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(F1 == 0 || F2 == 0)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(ddds,SetSpeed);
	WTurnLeft90();
	WXZFlag = '1';
	WJCFlag = '1';
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	WXZFlag = '0';
	WJCFlag = '0';
	Distance(ds,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	Wforward(SetSpeed);
	Distance(cs,SetSpeed);
	WXZFlag = '1';
	WJCFlag = '1';
	while(TotalF < 3)//等待识别路口
	{
		Wforward(SetSpeed);
	}
	Distance(5400,SetSpeed);//函数里开启了修正
	Brake();
	WXZFlag = '0';
	WJCFlag = '0';
}

/*控制功能函数*/
void WTurnLeft90(void)
{
	int cont;
	Brake();
	delay_ms(300);
	num=TIM4->CNT;
	cont = num - 880;
	if(cont < 0)
	{
		cont = cont + 1560;
	}
//	printf("%d",cont);
	WTurnLeft();
	delay_ms(20);
	while(num < cont - 5 || num >cont + 5)
	{
		num=TIM4->CNT;
	}
//	printf("%d",num);
	Brake();
	delay_ms(300);
}

void WTurnRight90(void)
{
	int cont;
	Brake();
	delay_ms(300);
	num_1=TIM3->CNT;
	cont = num_1 + 950;
	if(cont > 1560)
	{
		cont = cont - 1560;
	}
	WTurnRight();
	delay_ms(20);
	while(num_1 < cont - 5 || num_1 >cont + 5)
	{
		num_1=TIM3->CNT;
	}
	Brake();
	delay_ms(300);
}

void Distance(u16 Dis,u16 Speed)//初Speed = 450
{
	int ago_num,ago_num_1;
//	printf("--\r\n");
	Brake();
	delay_ms(300);
	WXZFlag = '1';
	record = 0;
	circle_count = 0;
	circle_count_1 = 0;
	ago_num=TIM4->CNT;
	ago_num_1=TIM3->CNT;
	num_record = Dis * 2;
	Wforward(Speed);
//	printf("%d	%d	%d\r\n",ago_num,ago_num_1,record);
	while(record < num_record)//等待识别虚线	
	{
		num=TIM4->CNT;
		num_1=TIM3->CNT;
		record = (circle_count + circle_count_1) * 1560 + num - ago_num + ago_num_1 - num_1;
//		printf("|%d|%d|%d|%d|%d|\r\n",num,num_1,circle_count,circle_count_1,record);
		Wforward(Speed);
	}
//	printf("%d\r\n",record);
	Brake();
	WXZFlag = '0';
	delay_ms(300);
}

//void ShowCircle(void)
//{
//		num=TIM4->CNT;
//		num_1=TIM3->CNT;
//		OLED_ShowString(0,0,"circle:",16);
//		OLED_ShowNum(56,0,circle_count,3,16);
//		OLED_ShowString(0,16,"num:",16);
//		OLED_ShowNum(32,16,num,4,16);
//		OLED_ShowString(0,32,"circle:",16);
//		OLED_ShowNum(56,32,circle_count_1,3,16);
//		OLED_ShowString(0,48,"num:",16);
//		OLED_ShowNum(32,48,num_1,4,16);
//		OLED_Refresh();
//		delay_ms(20);
//}

