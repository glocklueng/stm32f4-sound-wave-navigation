#ifndef __I2C_H__
#define __I2C_H__

#include "stm32f4xx_i2c.h"

void iic_config(void);
void iic_write_byte(u8 id,u8 write_address,u8 byte);
u8 iic_read_byte(u8 id, u8 read_address);
void iic_read_bytes(u8 id, u8 reg, u8 length, u8* buf);

#endif
