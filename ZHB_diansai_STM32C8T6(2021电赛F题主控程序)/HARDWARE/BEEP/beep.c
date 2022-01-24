#include "beep.h"
//////////////////////////////////////////////////////////////////////////////////	 
//蜂鸣器驱动代码							  
////////////////////////////////////////////////////////////////////////////////// 	   

//蜂鸣器初始化
void BEEP_Init(void)
{
	 
 GPIO_InitTypeDef  GPIO_InitStructure; 

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能GPIOA端口时钟
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB8端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	 //根据参数初始化GPIOA8
	
 //GPIO_SetBits(GPIOA,GPIO_Pin_8);//输出1，关闭蜂鸣器输出
}

void BEEP_OFF(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}

void BEEP_ON(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}
