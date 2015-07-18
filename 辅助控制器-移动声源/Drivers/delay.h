#ifndef __SYSTICK_H_
#define __SYSTICK_H_

#include "stm32f4xx.h"

void delay_config(void);
void delay_cmd(FunctionalState state);
void delay_ms(vu32);
void delay_us(vu32);

#endif
