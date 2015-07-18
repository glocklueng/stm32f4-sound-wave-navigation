#include "micros_time_16.h"

void micros_time_16_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 0XFFFF;    
    TIM_TimeBaseStructure.TIM_Prescaler = (84-1);                
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);  
    TIM_Cmd(TIM14, ENABLE);
}

void time_begin(void)
{
	TIM14->CNT = 0;
}

uint32_t get_time(void)
{
	return TIM14->CNT;
}

