#ifndef __USART3_H
#define __USART3_H 			   
#include "sys.h"  
void Usart3_Init(unsigned int baud);
void USART_Printf(USART_TypeDef *USARTx, char *fmt,...);


#endif
