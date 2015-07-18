#include "nano_board.h"
#include "gpio.h"
#include "delay.h"

/*
*led2: PB0
*led3: PC0
*key:  PA0
*/
void nano_board_led_init(void)
{
	gpio_out_pp_up_init(GPIOB, GPIO_Pin_0);
	gpio_out_pp_up_init(GPIOC, GPIO_Pin_0);
	LED2_OFF;
	LED3_OFF;
}

void nano_board_led2_toggle(void)
{
//	static u8 flag = 0;
//	if(flag){
//		flag = 0;
//		NANO_BOARD_LED2 = 0;
//	}
//	else{
//		flag = 1;
//		NANO_BOARD_LED2 = 1;
//	}
	
	NANO_BOARD_LED2 = (((GPIOB->ODR) & GPIO_Pin_0) != (uint32_t)Bit_RESET)? 0:1;
}

void nano_board_led3_toggle(void)
{
//	static u8 flag = 0;
//	if(flag){
//		flag = 0;
//		NANO_BOARD_LED3 = 0;
//	}
//	else{
//		flag = 1;
//		NANO_BOARD_LED3 = 1;
//	}
//	
	NANO_BOARD_LED3 = (((GPIOC->ODR) & GPIO_Pin_0) != (uint32_t)Bit_RESET)? 0:1;
}

void nano_board_led2_twinkle(void)
{
	LED2_ON;
	delay_ms(250);
	LED2_OFF;
	delay_ms(250);
}

void nano_board_led3_twinkle(void)
{
	LED3_ON;
	delay_ms(250);
	LED3_OFF;
	delay_ms(250);
}

void nano_board_key_init(void)
{
	gpio_in_up_init(GPIOC, GPIO_Pin_0);
}

u8 is_nano_board_key_down(void)
{
	if(!NANO_BOARD_KEY){
		delay_ms(10);
		if(!NANO_BOARD_KEY){
			while(!NANO_BOARD_KEY);
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}
