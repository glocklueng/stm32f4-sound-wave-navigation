#include "exti.h"
#include "util.h"
#include "gpio.h"
#include "usart.h"
#include "nrf24l01.h"

void exti_config(GPIO_TypeDef *gpiox, u8 pin_num)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	u8 exti_port_source_gpio;
	u32 pin_line = 0x00000001<<pin_num;
	uint8_t irq_channel;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	gpio_in_up_init(gpiox, pin_line);
	
	if(gpiox == GPIOA){
		exti_port_source_gpio = EXTI_PortSourceGPIOA;
	}
	else if(gpiox == GPIOB){
		exti_port_source_gpio = EXTI_PortSourceGPIOB;
	}
	else if(gpiox == GPIOC){
		exti_port_source_gpio = EXTI_PortSourceGPIOC;
	}
	else if(gpiox == GPIOD){
		exti_port_source_gpio = EXTI_PortSourceGPIOD;
	}
	else if(gpiox == GPIOE){
		exti_port_source_gpio = EXTI_PortSourceGPIOE;
	}
	else if(gpiox == GPIOF){
		exti_port_source_gpio = EXTI_PortSourceGPIOF;
	}
	else if(gpiox == GPIOG){
		exti_port_source_gpio = EXTI_PortSourceGPIOG;
	}
	else if(gpiox == GPIOH){
		exti_port_source_gpio = EXTI_PortSourceGPIOH;
	}
	else if(gpiox == GPIOI){
		exti_port_source_gpio = EXTI_PortSourceGPIOI;
	}
	else if(gpiox == GPIOJ){
		exti_port_source_gpio = EXTI_PortSourceGPIOJ;
	}
	else if(gpiox == GPIOK){
		exti_port_source_gpio = EXTI_PortSourceGPIOK;
	}
	else{
		printf("GPIO Port is not supported!\r\n");
		while(1);
	}
	
	SYSCFG_EXTILineConfig(exti_port_source_gpio, pin_num);
	
	EXTI_InitStructure.EXTI_Line = pin_line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	if(pin_num >= 10){
		irq_channel = EXTI15_10_IRQn;
	}
	else if(pin_num >= 5){
		irq_channel = EXTI9_5_IRQn;
	}
	else {
		irq_channel = pin_num + 6;
	}
	
	nvic_config(irq_channel, 10);
}

void EXTI9_5_IRQHandler(void)
{
	uint8_t state = 0;
	if(EXTI_GetITStatus(EXTI_Line5) != RESET){
		EXTI_ClearITPendingBit(EXTI_Line5);
		switch(NRF24L01_Get_State(&state)){
			case TX_OK:
				NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,state); //清除TX_DS或MAX_RT中断标志
				NRF24L01_Write_Reg(FLUSH_TX,0xff);				//清除TX FIFO寄存器 
				nrf_state = TX_OK;
				break;
			case MAX_TX:
				NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,state); //清除TX_DS或MAX_RT中断标志
				NRF24L01_Write_Reg(FLUSH_TX,0xff);				//清除TX FIFO寄存器 
				nrf_state = MAX_TX;
				break;
			case RX_OK:
				NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS, state); 				//清除TX_DS或MAX_RT中断标志
				NRF24L01_Read_Buf(RD_RX_PLOAD, nrf_rx_buffer, RX_PLOAD_WIDTH);	//读取数据
				NRF24L01_Write_Reg(FLUSH_TX, 0xff);								//清除TX FIFO寄存器 
				nrf_state = RX_OK;
				break;
		}
	}
}

