#include "spi.h"
#include "gpio.h"

//SPI1_SCK->PA5, SPI1_MOSI->PA7, SPI1_MISO->PB4
void spi_config(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	gpio_af_pp_up_init(GPIOB, GPIO_Pin_4);
	gpio_af_pp_up_init(GPIOA, GPIO_Pin_5|GPIO_Pin_7);
	gpio_out_pp_up_init(GPIOA, GPIO_Pin_3);	//������Ƭѡ����
	gpio_out_pp_up_init(GPIOA, GPIO_Pin_8);	//NRF24L01Ƭѡ����
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;						//��ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					//8λ֡
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;							//clk����Ϊ��
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;						//clk��һ�������زɼ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;							//NSS�ź����������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//������Ԥ��ƵֵΪ256,����
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;					//���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;							//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
	//T_CS = 0;			//������Ƭѡ��Ч
	//NRF24L01_CS = 0;	//NRF24L01Ƭѡ��Ч
}

uint8_t spi_read_write_byte(uint8_t txData)
{			
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, txData); 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}

//SPI_BaudRatePrescaler_256:���٣� SPI_BaudRatePrescaler_8������
void spi_set_speed(uint8_t speed)
{
	SPI1->CR1 &= 0XFFC7; 
	SPI1->CR1 |= speed;
	SPI_Cmd(SPI1,ENABLE); 
}

