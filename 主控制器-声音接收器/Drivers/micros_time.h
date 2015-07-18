#ifndef __MICROS_TIME_H__
#define __MICROS_TIME_H__

#include "stm32f4xx_tim.h"

void micros_time_init(void);
uint32_t get_interval_time(void);

#endif

