#include "l298n.h"

/***********************************
				TIM2 CH1	CH2						TIM2	CH3		CH4
***********************************/

void TIM2_PWM_Init(u16 arr,u16 psc)
{
	//**结构体声明**//
	GPIO_InitTypeDef GPIO_InitStructure;            //声明GPIO
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; //声明定时器
	TIM_OCInitTypeDef  TIM_OCInitStructure;         //声明PWM通道
	
	//**时钟使能**//
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能定时器TIM2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	
	//****//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //TIM2_CH1 --> PA0 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.0
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//****//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //TIM2_CH2 --> PA1 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.1
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
		//****//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //TIM2_CH3 --> PA2 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.2
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	//****//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //TIM2_CH4 --> PA3 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.3
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	
  //初始化TIM2
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM2 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC1
	
	//初始化TIM2 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC2
	
		//初始化TIM2 Channel3 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC3
	
	//初始化TIM2 Channel4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC4

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2_CH1预装载寄存器
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2_CH2预装载寄存器
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2_CH3预装载寄存器
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2_CH4预装载寄存器
	
	TIM_Cmd(TIM2, ENABLE);  //使能TIM2	
}


void Wforward(u16 speed)
{
	TIM_SetCompare1(TIM2,XiuZhengValue * speed );
	TIM_SetCompare2(TIM2,0);
	TIM_SetCompare4(TIM2,speed );
	TIM_SetCompare3(TIM2,0);
}

void Wback(u16 speed)
{
	TIM_SetCompare1(TIM2,0);
	TIM_SetCompare2(TIM2,speed);
	TIM_SetCompare4(TIM2,0);
	TIM_SetCompare3(TIM2,speed);	
}

void LWcorect()//前行向zuo修正
{
	TIM_SetCompare1(TIM2,0);
	TIM_SetCompare2(TIM2,SetSpeed);
	TIM_SetCompare4(TIM2,SetSpeed + 160);
	TIM_SetCompare3(TIM2,0);
	delay_ms(3);
}

void RWcorect ()//前行向you修正
{
	TIM_SetCompare1(TIM2,SetSpeed + 160);
	TIM_SetCompare2(TIM2,0);
	TIM_SetCompare4(TIM2,0 );
	TIM_SetCompare3(TIM2,SetSpeed);
	delay_ms(3);
}

void BLWcorect()//前行向zuo修正
{
	TIM_SetCompare1(TIM2,0);
	TIM_SetCompare2(TIM2,SetSpeed);
	TIM_SetCompare4(TIM2,SetSpeed + 250);
	TIM_SetCompare3(TIM2,0);
	delay_ms(5);
}

void BRWcorect ()//前行向you修正
{
	TIM_SetCompare1(TIM2,SetSpeed + 250);
	TIM_SetCompare2(TIM2,0);
	TIM_SetCompare4(TIM2,0 );
	TIM_SetCompare3(TIM2,SetSpeed);
	delay_ms(5);
}


void Brake()
{
	TIM_SetCompare1(TIM2,999);
	TIM_SetCompare2(TIM2,999);
	TIM_SetCompare3(TIM2,999);
	TIM_SetCompare4(TIM2,999);
}

void WTurnLeft()//前进时左转
{
	TIM_SetCompare1(TIM2,0);
	TIM_SetCompare2(TIM2,XiuZhengValue * 450);
	TIM_SetCompare4(TIM2,450);
	TIM_SetCompare3(TIM2,0);
}

void WTurnRight()//前进时右转
{
	TIM_SetCompare1(TIM2,XiuZhengValue * 450);
	TIM_SetCompare2(TIM2,0);
	TIM_SetCompare4(TIM2,0);
	TIM_SetCompare3(TIM2,450);
}

