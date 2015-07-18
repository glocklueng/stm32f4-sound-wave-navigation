#include "micros_time.h"

//使用32位定时器TIM5
void micros_time_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 0XFFFFFFFF;    
    TIM_TimeBaseStructure.TIM_Prescaler = (84-1);                
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);  
    TIM_Cmd(TIM5, ENABLE);
}

uint32_t get_micros_time(void)
{
	return TIM5->CNT;
}

uint32_t get_interval_time(void)
{
	static uint32_t last_time = 0;
	uint32_t res;
	uint32_t curr_time = get_micros_time();
	res = curr_time - last_time;
	last_time = curr_time;
	return res;
}
