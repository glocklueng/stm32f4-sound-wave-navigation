#include "capture.h"
#include "util.h"
#include "gpio.h"
#include "stm32f4_discovery.h"
#include "control.h"
#include "micros_time.h"

//输入捕获配置
void capture_config(void)
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	gpio_af_pp_up_init(GPIOB, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9);//CH1|CH2|CH4
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	TIM_Cmd(TIM4, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);
	
	nvic_config(TIM4_IRQn, 2);
}

void TIM4_IRQHandler(void)
{ 
	if(TIM_GetITStatus(TIM4, TIM_IT_CC1) == SET) 	//接收器A
	{
		TIM_ClearFlag(TIM4, TIM_IT_CC1);
		if(ctrl.all == 0){
			STM_EVAL_LEDToggle(LED3);
			ctrl.ta = get_micros_time();
			ctrl.a = 1;
			ctrl.all = ctrl.b*ctrl.c;
		}
	}
	if(TIM_GetITStatus(TIM4, TIM_IT_CC2) == SET) 	//接收器B
	{
		TIM_ClearFlag(TIM4, TIM_IT_CC2);
		if(ctrl.all == 0){
			STM_EVAL_LEDToggle(LED4);
			ctrl.tb = get_micros_time();
			ctrl.b = 1;
			ctrl.all = ctrl.a*ctrl.b;
		}
	}
	if(TIM_GetITStatus(TIM4, TIM_IT_CC4) == SET) 	//接收器C
	{
		TIM_ClearFlag(TIM4, TIM_IT_CC4);
		if(ctrl.all == 0){
			STM_EVAL_LEDToggle(LED5);
			ctrl.tc = get_micros_time();
			ctrl.c = 1;
			ctrl.all = ctrl.a*ctrl.c;
		}
	}
}

