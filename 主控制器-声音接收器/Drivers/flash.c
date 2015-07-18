#include "flash.h"
#include "usart.h"

__IO u32 *flash_buffer32 = (__IO u32 *)FLASH_USER_START_ADDR;
__IO u16 *flash_buffer16 = (__IO u16 *)FLASH_USER_START_ADDR;
__IO u8 *flash_buffer8 = (__IO u8 *)FLASH_USER_START_ADDR;

void flash_init(void)
{
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                 FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	flash_erase_sector();
}

void flash_erase_sector(void)
{
	FLASH_EraseSector(FLASH_USER_SECTOR1, VoltageRange_3);
//	FLASH_EraseSector(FLASH_USER_SECTOR2, VoltageRange_3);
}

void flash_write_data8(u8 *buffer, u32 length)
{
	u32 i;
	flash_init();
	for(i=0; i<length; i++){
		if (FLASH_ProgramByte(i+FLASH_USER_START_ADDR, buffer[i]) != FLASH_COMPLETE){
			printf("flash write data8 error!");
			while(1);
		}
	}
	FLASH_Lock();
}

void flash_write_data16(u16 *buffer, u32 length)
{
	u32 i;
	flash_init();
	for(i=0; i<length; i++){
		if (FLASH_ProgramHalfWord(2*i+FLASH_USER_START_ADDR, buffer[i]) != FLASH_COMPLETE){
			printf("flash write data16 error!");
			while(1);
		}
	}
	FLASH_Lock();
}

void flash_write_data32(u32 *buffer, u32 length)
{
	u32 i;
	flash_init();
	for(i=0; i<length; i++){
		if (FLASH_ProgramWord(4*i+FLASH_USER_START_ADDR, buffer[i]) != FLASH_COMPLETE){
			printf("flash write data32 error!");
			while(1);
		}
	}
	FLASH_Lock();
}
