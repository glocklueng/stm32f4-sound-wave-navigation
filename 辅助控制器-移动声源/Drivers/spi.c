#include "spi.h"
#include "gpio.h"

//SPI1_SCK->PA5, SPI1_MOSI->PA7, SPI1_MISO->PB4
void spi_config(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	gpio_af_pp_up_init(GPIOB, GPIO_Pin_4);
	gpio_af_pp_up_init(GPIOA, GPIO_Pin_5|GPIO_Pin_7);
	gpio_out_pp_up_init(GPIOA, GPIO_Pin_3);	//触摸屏片选引脚
	gpio_out_pp_up_init(GPIOA, GPIO_Pin_8);	//NRF24L01片选引脚
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;						//主模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					//8位帧
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;							//clk空闲为低
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;						//clk第一个跳变沿采集数据
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;							//NSS信号由软件控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//波特率预分频值为256,低速
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;					//数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;							//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
	//T_CS = 0;			//触摸屏片选有效
	//NRF24L01_CS = 0;	//NRF24L01片选有效
}

uint8_t spi_read_write_byte(uint8_t txData)
{			
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, txData); 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}

//SPI_BaudRatePrescaler_256:低速， SPI_BaudRatePrescaler_8：高速
void spi_set_speed(uint8_t speed)
{
	SPI1->CR1 &= 0XFFC7; 
	SPI1->CR1 |= speed;
	SPI_Cmd(SPI1,ENABLE); 
}

