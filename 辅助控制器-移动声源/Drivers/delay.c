#include "delay.h"

vu32 systick_counter=0;

void delay_config(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	if (SysTick_Config(SystemCoreClock / 1000000))
	{ 
		while (1);
	}
	delay_cmd(DISABLE);
}

void delay_cmd(FunctionalState state)
{
	if(state == ENABLE){
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	}
	else{
		SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
	}
}

void delay_ms(vu32 nTime)
{
	delay_cmd(ENABLE);
	systick_counter = nTime*1000;
	while(systick_counter != 0);
	delay_cmd(DISABLE);
}

void delay_us(vu32 nTime)
{
	delay_cmd(ENABLE);
	systick_counter = nTime;
	while(systick_counter != 0);
	delay_cmd(DISABLE);
}
