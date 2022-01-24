#include "Infrared.h"

int Lef,Rig,Tot;

void Infrared_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
}

void ReadInf(void)//高电平表示检测到红线
{
	Lef = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8);
	Rig = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);
	Tot = Lef+Rig;
}

