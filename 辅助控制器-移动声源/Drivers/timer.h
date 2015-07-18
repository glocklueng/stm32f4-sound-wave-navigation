#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f4xx_tim.h"

void TIM6_init(uint32_t period, uint16_t prescaler);
void TIM7_init(uint32_t period, uint16_t prescaler);

#endif
