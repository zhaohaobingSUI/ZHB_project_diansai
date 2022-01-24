#include "s307.h"

int D7_1,D7_2,D7_3,D7_4,D7_5,D7_6,D7_7,Total7;

void S307_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//禁止JTAG功能，把PB3，PB4作为普通IO口使用
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void ReadS307(void)//高电平表示检测到红线
{
	D7_1 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
	D7_2 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
	D7_3 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
	D7_4 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
	D7_5 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
	D7_6 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
	D7_7 = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
	Total7 = D7_1+D7_2+D7_3+D7_4+D7_5+D7_6+D7_7;
}


