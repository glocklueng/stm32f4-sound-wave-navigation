#include "timer.h"
#include "util.h"
#include "usart.h"

//TIM6挂在APB1，输入时钟为42*2=84MHz
void TIM6_init(uint32_t period, uint16_t prescaler)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = period-1;    
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler-1;                
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);  
    TIM_Cmd (TIM6, ENABLE);
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	nvic_config(TIM6_DAC_IRQn, 1);	//优先级暂定为1
}

//TIM7挂在APB1，输入时钟为42*2=84MHz
void TIM7_init(uint32_t period, uint16_t prescaler)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = period-1;    
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler-1;                
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);  
    TIM_Cmd (TIM7, ENABLE);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	nvic_config(TIM7_IRQn, 3);		//优先级暂定为3
}

void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

	}
}
