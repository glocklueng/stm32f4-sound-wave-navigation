#include "square_wave.h"
#include "gpio.h"

void square_wave_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
	gpio_af_pp_up_init(GPIOB, GPIO_Pin_8);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM10); 
	
	TIM_TimeBaseStructure.TIM_Period = 9;
	TIM_TimeBaseStructure.TIM_Prescaler = 16800;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OCInitStructure.TIM_Pulse = 5;
	TIM_OC1Init(TIM10, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM10, ENABLE);
	TIM_Cmd(TIM10, ENABLE);
}

void set_period(uint32_t period)
{
	TIM10->ARR = period; 
	TIM10->CCR1 = period/2;
}

void set_prescaler(uint32_t prescaler)
{
	TIM10->PSC = prescaler;
}

void set_freq(uint32_t freq)
{
	set_prescaler(16800000/freq);
}

