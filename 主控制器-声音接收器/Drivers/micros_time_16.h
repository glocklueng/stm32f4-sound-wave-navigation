#ifndef __MICROS_TIME_16_H__
#define __MICROS_TIME_16_H__

#include "stm32f4xx_tim.h"

void micros_time_16_init(void);
void time_begin(void);
uint32_t get_time(void);

#endif

