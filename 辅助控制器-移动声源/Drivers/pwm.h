#ifndef __PWM_H__
#define __PWM_H__

#include "stm32f4xx_tim.h"

void pwm_config(uint32_t freq);
void set_pwm1(float compare);
void set_pwm2(float compare);
void set_pwm(float pwm1, float pwm2);

#endif


