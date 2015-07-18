#include "motor.h"
#include "pwm.h"
#include "gpio.h"

float pwm;

void motor_init(void)
{
	gpio_out_pp_up_init(GPIOE, GPIO_Pin_1|GPIO_Pin_2);
	MOTOR_IN1 = 0;
	MOTOR_IN2 = 0;
	pwm_config(1000);
}

void motor_set_pwm(float pwm)
{
	if(pwm>0){
		MOTOR_IN1 = 1;
		MOTOR_IN2 = 0;
		set_pwm1(pwm);
	}
	else if(pwm<0){
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 1;
		set_pwm1(-pwm);
	}
	else{
		MOTOR_IN1 = 0;
		MOTOR_IN2 = 0;
		set_pwm1(0);
	}
	
}

