#include "usart3.h"
#include "sys.h"
#include <stdarg.h>

u8 res3;

void Usart3_Init(unsigned int baud)
{
 
	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//USART3_TX   GPIOB.10
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10; 				
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;			
  	GPIO_Init(GPIOB, &gpioInitStruct);					
   
	//USART3_RX	  GPIOB.11
  	gpioInitStruct.GPIO_Pin = GPIO_Pin_11;				
  	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;		
  	GPIO_Init(GPIOB, &gpioInitStruct);					
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;			
	usartInitStruct.USART_Parity = USART_Parity_No;					
	usartInitStruct.USART_StopBits = USART_StopBits_1;			
	usartInitStruct.USART_WordLength = USART_WordLength_8b;				
	USART_Init(USART3, &usartInitStruct);
	
	USART_Cmd(USART3, ENABLE);														
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);						
	
	nvicInitStruct.NVIC_IRQChannel = USART3_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicInitStruct);
}

/*
*********串口打印函数******************
*函数名称：UsartPrintf
*参数：	*USARTx:选择打印的端口
*				fmt：需要打印的数据
*
*说明：
****************************
*/
void USART_Printf(USART_TypeDef *USARTx, char *fmt,...)
{
 
	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf; //指针pStr指向数组
	
	va_start(ap, fmt);
	vsprintf((char *)UsartPrintfBuf, fmt, ap);				
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
 
}

void USART3_IRQHandler(void) 
{ 	
    if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)  //判断是否发生中断
    { 
      USART_ClearITPendingBit(USART3,USART_IT_RXNE);  //清除当前中断标志位
			//中断处理函数
			res3= USART_ReceiveData(USART3); 	 
			USART_SendData(USART1,res3);
      
    } 
}

