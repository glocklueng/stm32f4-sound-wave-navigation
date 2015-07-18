#ifndef __SPI_H__
#define __SPI_H__

#include "stm32f4xx_spi.h"
#include "bitband.h"

#define T_CS		PaOutBit(3)
#define NRF24L01_CS	PaOutBit(8)

void spi_config(void);
u8 spi_read_write_byte(u8 txData);
void spi_set_speed(u8 speed);

#endif
