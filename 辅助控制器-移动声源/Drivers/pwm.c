#include "pwm.h"
#include "util.h"
#include "gpio.h"

void pwm_config(uint32_t freq)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	gpio_af_pp_up_init(GPIOE, GPIO_Pin_5|GPIO_Pin_6);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_TIM9); 
	
	TIM_TimeBaseStructure.TIM_Period = 1000-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 84000000/1000/freq-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM9, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(TIM9, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM9, ENABLE);
	TIM_Cmd(TIM9, ENABLE);
}

//设置通道1占空比
void set_pwm1(float compare)
{
	compare *= 10;
	compare = range(compare, 0, 999);
	TIM9->CCR1 = (uint32_t)(compare+0.5f);
}

//设置通道2占空比
void set_pwm2(float compare)
{
	compare *= 10;
	compare = range(compare, 0, 999);
	TIM9->CCR2 = (uint32_t)(compare+0.5f);
}

void set_pwm(float pwm1, float pwm2)
{
	set_pwm1(pwm1);
	set_pwm2(pwm2);
}


