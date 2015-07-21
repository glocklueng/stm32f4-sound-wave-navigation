#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "bitband.h"

extern float pwm;

#define MOTOR_IN1	 PeOutBit(1)
#define MOTOR_IN2	 PeOutBit(2)

void motor_init(void);
void motor_set_pwm(float pwm);

#endif

