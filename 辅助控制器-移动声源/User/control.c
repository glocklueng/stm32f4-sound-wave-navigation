#include "control.h"
#include "nrf24l01.h"
#include "motor.h"
#include "usart.h"

Point pos;

#define NRF_ACK 1
uint8_t is_ack(void){
	if(nrf_state == RX_OK && nrf_rx_buffer[0] == NRF_ACK){
		return 1;
	}
	else{
		return 0;
	}
}

uint8_t wait_for_position(Point *p)
{
	uint32_t x, y;
	if(nrf_state != RX_OK){
		return 0;
	}
	x = nrf_rx_buffer[0]<<24|nrf_rx_buffer[1]<<16|nrf_rx_buffer[2]<<8|nrf_rx_buffer[3];
	y = nrf_rx_buffer[4]<<24|nrf_rx_buffer[5]<<16|nrf_rx_buffer[6]<<8|nrf_rx_buffer[7];
	p->x = (float)x/1000.0f;
	p->y = (float)y/1000.0f;
	return 1;
}

void control_process(void)
{
	while(1){
		NRF24L01_Init(NRF_TX_MODE);
		nef24l01_send_start_signal();
		NRF24L01_Init(NRF_RX_MODE);
		while(is_ack() == 0);
		nrf_state = WAITING_DATA;
		while(wait_for_position(&pos) == 0);
		//control motor
	}
}










