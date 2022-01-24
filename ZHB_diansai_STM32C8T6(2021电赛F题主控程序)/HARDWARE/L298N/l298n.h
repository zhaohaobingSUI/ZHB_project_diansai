#ifndef __L298N_H
#define __L298N_H 			   
#include "sys.h"  

#define XiuZhengValue 0.975

void TIM2_PWM_Init(u16 arr,u16 psc);
void Wforward(u16 speed);
void Wback(u16 speed);
void RWcorect(void);//前行向右修
void LWcorect(void);//前行向左修正
void BRWcorect(void);//前行向右修
void BLWcorect(void);//前行向左修正
void Brake(void);//停车
void WTurnLeft(void);//前进时向左转
void WTurnRight(void);//前进时向右转

#endif
