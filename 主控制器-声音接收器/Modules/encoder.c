#include "encoder.h"
#include "gpio.h"
#include "util.h"
#include "timer.h"

/*
*TIM2,TIM5��32λ��ʱ��
*�ο�һ����������ôд��
*/
void encoder_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//TIM2_CH1->PA15, TIM2_CH2->PB3
	gpio_af_od_up_init(GPIOA, GPIO_Pin_15);	//������AB�������,���ÿ�©����
	gpio_af_od_up_init(GPIOB, GPIO_Pin_3);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
	
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_Period = ENCODER_RELOAD;	//TIM2Ϊ32λ��ʱ��,���������ֵ��Ϊ��󣬿��Բ����Ǽ������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM2->CNT = COUNTER1_RESET;
	TIM_Cmd(TIM2, ENABLE);
	
	//��ʱ��ȡ������, ���10ms
	TIM6_init(100, 8400);
}

void TIM6_DAC_IRQHandler(void)
{
	static uint32_t last1 = COUNTER1_RESET;
	uint32_t cnt1, cnt2;
	
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
		cnt1 = TIM2->CNT;
		cnt2 = TIM5->CNT;
		
		//����
	}
}
