#include "stm32f4xx.h"
#include "util.h"
#include "usart.h"
#include "delay.h"
#include "gpio.h"
#include "nrf24l01.h"
#include "stm32f4_discovery.h"

uint8_t nrf_buffer[32] = "hello world, pretty good hust..";

int main()
{
	rcc_clock_enable();
	delay_config();
	uart4_init(115200);
	print_clock_freq();
	
	STM_EVAL_LEDInit(LED3);
	NRF24L01_Init();
	
	while(1){
		NRF24L01_TxPacket(nrf_buffer);
		STM_EVAL_LEDToggle(LED3);
		delay_ms(250);
	}
}

