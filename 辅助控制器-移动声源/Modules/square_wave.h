#ifndef __SQUARE_WAVE_H__
#define __SQUARE_WAVE_H__

#include "stm32f4xx_tim.h"

void square_wave_init(void);
void set_period(uint32_t period);
void set_prescaler(uint32_t prescaler);
void set_freq(uint32_t freq);

#endif

