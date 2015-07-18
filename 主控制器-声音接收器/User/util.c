#include "util.h"
#include "usart.h"

void rcc_clock_enable(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
}

void print_clock_freq(void)
{
	RCC_ClocksTypeDef rcc_clocks;
	SystemCoreClockUpdate();
	RCC_GetClocksFreq(&rcc_clocks);
	printf("RCC_Clocks.SYSCLK_Frequency = %d\r\n", rcc_clocks.SYSCLK_Frequency);
	printf("RCC_Clocks.HCLK_Frequency = %d\r\n", rcc_clocks.HCLK_Frequency);
	printf("RCC_Clocks.PCLK1_Frequency = %d\r\n", rcc_clocks.PCLK1_Frequency);
	printf("RCC_Clocks.PCLK2_Frequency = %d\r\n", rcc_clocks.PCLK2_Frequency);
}

//priority: 0~15, 越小优先级越高
void nvic_config(uint8_t irq_channel, uint8_t priority)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	uint8_t pre, sub;
	pre = priority/4;
	sub = priority%4;
	NVIC_InitStructure.NVIC_IRQChannel = irq_channel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pre;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}



