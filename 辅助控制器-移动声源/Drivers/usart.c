#include "usart.h"
#include "util.h"
#include "gpio.h"

void usart1_init(uint32_t baudRate)
{
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	gpio_af_pp_up_init(GPIOB, GPIO_Pin_6|GPIO_Pin_7);
	
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1, ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	nvic_config(USART1_IRQn, 4);
}

void uart4_init(uint32_t baudRate)
{
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);
	gpio_af_pp_up_init(GPIOC, GPIO_Pin_10|GPIO_Pin_11);
	
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure); 
	//USART_ITConfig(UART4, USART_IT_RXNE,ENABLE);
	USART_Cmd(UART4, ENABLE);
	USART_ClearFlag(UART4, USART_FLAG_TC);
	
	//nvic_config(UART4_IRQn, 4);
}

//重定向printf函数
int fputc(int ch, FILE *f)
{	
	USART_SendData(UART4, (uint8_t) ch);
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	return ch;
}

//重定向scanf函数
int fgetc(FILE *f)
{
	uint8_t val;
	while (USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET);
	val = USART_ReceiveData(UART4);
	USART_SendData(UART4, val);
	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	return (int)val;
}

void usart_sendByte(USART_TypeDef *usart, u8 val)
{
	USART_SendData(usart, val);
	while (USART_GetFlagStatus(usart, USART_FLAG_TC) == RESET);
}

void usart_sendBytes(USART_TypeDef *usart, u8 *buffer, u16 len)
{
	u16 i;
	for(i=0; i<len; i++){
		usart_sendByte(usart, buffer[i]);
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
	{
		USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		
	}
}

void UART4_IRQHandler(void)
{
	if(USART_GetFlagStatus(UART4,USART_FLAG_RXNE)==SET)
	{
		USART_ReceiveData(UART4);
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);

	}
}
