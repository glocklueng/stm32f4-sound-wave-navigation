#include "control.h"
#include "nrf24l01.h"
#include "location.h"

Control ctrl = {0, 0, 0, 0};

void clear_control(Control *pctrl)
{
	pctrl->ta = 0;
	pctrl->tb = 0;
	pctrl->tc = 0;
	pctrl->a = 0;
	pctrl->b = 0;
	pctrl->c = 0;
	pctrl->all = 0;
}

#define CTRL_START 2
uint8_t is_start(void)
{
	if(nrf_state == RX_OK && nrf_rx_buffer[0] == CTRL_START){
		return 1;
	}
	else{
		return 0;
	}
}

uint8_t is_capture(Control *pctrl)
{
	if(pctrl->all != 0){
		return 1;
	}
	else{
		return 0;
	}
}

void control_process(void)
{
	while(1){
		NRF24L01_Init(NRF_RX_MODE);
		while(is_start() == 0);
		NRF24L01_Init(NRF_TX_MODE);
		nrf24l01_send_ack();
		clear_control(&ctrl);
		while(is_capture(&ctrl) == 0);		//µ»¥˝≤∂ªÒ…˘“Ù–≈∫≈
		pos = calc_position(ctrl.ta-ctrl.tc, ctrl.tb-ctrl.ta);
		nrf24l01_send_position(pos);
	}
}
