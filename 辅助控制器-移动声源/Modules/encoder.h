#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "stm32f4xx_tim.h"

#define ENCODER1_PPR 		(500*16)		//电机编码器线数
#define ENCODER2_PPR 		(1000)			//摆杆编码器线数
#define ENCODER_RELOAD 		0XFFFFFFFF
#define COUNTER1_RESET 		(0X7FFFFFFF)
#define COUNTER2_RESET 		(0X7FFFFFFF)

void encoder1_init(void);
void encoder1_init(void);

#endif

