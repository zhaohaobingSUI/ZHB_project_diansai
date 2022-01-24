#include "golo.h"

extern u8 res3;
extern u8 CheckYP;
extern u8 WXZFlag,BXZFlag;//修正标志位
extern u8 WJCFlag,BJCFlag;//是否开启检测的标志位
extern int F1,F2,F3,F4,F5,TotalF;
extern int YaoP;

int Destination;

int VisGO(void)
{
	OLED_Clear();
	OLED_ShowString(0,2,"Ready>>");
	BEEP_ON();
	YaoP = 0;
	CheckYP = '1';//开启检测药品
	while(YaoP == 0);//等待放药品 空
	R();
	CheckYP = '0';//关闭检测药品
	BEEP_OFF();
	delay_ms(1000);
	WXZFlag = '1';//开启修正
	WJCFlag = '1';//开启检测
	delay_ms(500);
	TotalF = 0;
	while(TotalF < 3)//等待识别路口
	{Wforward(SetSpeed);}		
	WXZFlag = '0';//关闭修正
	Distance(ds,SetSpeed);//等待车身中心到达路口
	/*前进一段距离再开启接收识别的数字*/
	
	Distance(TestDistance,SetSpeed);//等待进入识别范围

	/*此处用于测试TestDistance参数*/
	res3 = 'N';//清空错误	
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);
	
	WXZFlag = '1';//开启修正	
	
	TotalF = 0;
	/*到达第二个十字路口*/
	while(TotalF < 3)//等待识别路口
	{Wforward(SetSpeed);}	
	Distance(kCARDDistance,SetSpeed);//等待车身中心到达路口
	
	/*第二个十字路口的判断*/
	if(res3 == 'L')
	{
		Destination = 3;
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
		BackFrom3();
		return Destination;
	}
	if(res3 == 'R')
	{
		Destination = 4;
		WTurnRight90();//左转
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
		BackFrom4();
		return Destination;
	}	
	
	/*进入远端病房*/
	Distance(TestDistance,SetSpeed);//等待进入识别范围

	/*此处用于测试TestDistance参数*/
	res3 = 'N';//清空错误	
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);
	
	WXZFlag = '1';//开启修正	
	
	TotalF = 0;
	/*到达第三个十字路口*/
	while(TotalF < 3)//等待识别路口
	{Wforward(SetSpeed);}	
	Distance(kCARDDistance,SetSpeed);//等待车身中心到达路口
	
	
	/*第三个十字路口的判断*/
	if(res3 == 'L')
	{
		WTurnLeft90();//左转
		WXZFlag = '1';//开启修正
		delay_ms(200);
			/*前进一段距离再开启接收识别的数字*/
	
		Distance(TestDistance,SetSpeed);//等待进入识别范围

		/*此处用于测试TestDistance参数*/
		res3 = 'N';//清空错误	
		delay_ms(1500);
		delay_ms(1500);
		delay_ms(1500);

		WXZFlag = '1';//开启修正	
		
		TotalF = 0;
		/*到达左边第四个十字路口*/
		while(TotalF < 3)//等待识别路口
		{Wforward(SetSpeed);}	
		Distance(kCARDDistance,SetSpeed);//等待车身中心到达路口
		if(res3 == 'L')
		{
			Destination = 7;
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
			BackFrom7();
			return Destination;
		}
		if(res3 == 'R')
		{
			Destination = 5;
			WTurnRight90();//左转
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
			BackFrom5();
			return Destination;
		}	
	}
	/*第三个十字路口的判断*/
	if(res3 == 'R')
	{
		WTurnRight90();//左转
		WXZFlag = '1';//开启修正
		delay_ms(200);
			/*前进一段距离再开启接收识别的数字*/
	
		Distance(TestDistance,SetSpeed);//等待进入识别范围

		/*此处用于测试TestDistance参数*/
		res3 = 'N';//清空错误	
		delay_ms(1500);
		delay_ms(1500);
		delay_ms(1500);

		WXZFlag = '1';//开启修正	
		
		TotalF = 0;
		/*到达左边第四个十字路口*/
		while(TotalF < 3)//等待识别路口
		{Wforward(SetSpeed);}	
		Distance(kCARDDistance,SetSpeed);//等待车身中心到达路口
		if(res3 == 'L')
		{
			Destination = 8;
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
			BackFrom8();
			return Destination;
		}
		if(res3 == 'R')
		{
			Destination = 6;
			WTurnRight90();//左转
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
			BackFrom6();
			return Destination;
		}	
	}
	return 0;
}


