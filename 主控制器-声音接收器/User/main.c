#include "stm32f4xx.h"
#include "util.h"
#include "usart.h"
#include "delay.h"
#include "gpio.h"
#include "nrf24l01.h"
#include "stm32f4_discovery.h"
#include "micros_time.h"

int main()
{
	rcc_clock_enable();
	delay_config();
	uart4_init(9600);
//	print_clock_freq();
	
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
//	NRF24L01_Init(NRF_TX_MODE);
	micros_time_init();
	
	while(1){
//		NRF24L01_TxPacket(nrf_tx_buffer);
//		STM_EVAL_LEDToggle(LED3);
//		delay_ms(250);
		printf("hello world");
		delay_ms(1000);
	}
}

