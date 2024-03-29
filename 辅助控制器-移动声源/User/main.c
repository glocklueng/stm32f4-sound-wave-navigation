#include "stm32f4xx.h"
#include "util.h"
#include "usart.h"
#include "delay.h"
#include "gpio.h"
#include "nrf24l01.h"
#include "stm32f4_discovery.h"
#include <string.h>
#include "square_wave.h"

uint32_t freq = 1000;

int main()
{
	rcc_clock_enable();
	delay_config();
	uart4_init(115200);
	print_clock_freq();

	square_wave_init();		//	方波输出初始化,默认为1KHz
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
//	NRF24L01_Init(NRF_RX_MODE);
	
	while(1){
//		if(nrf_state == RX_OK){
//			nrf_state = WAITING_DATA;
//			printf("rev: %s\r\n", nrf_rx_buffer);
//			memset(nrf_rx_buffer, 0, sizeof(uint8_t)*RX_ADR_WIDTH);
//			STM_EVAL_LEDToggle(LED3);
//		}
		printf("\r\ninput freq: ");
		scanf("%d", &freq);
		if(freq == 0){
			stop_output();
		}
		else{
			start_output();
			set_freq(freq);
		}
		
//		STM_EVAL_LEDToggle(LED6);
//		delay_ms(250);
	}
}

