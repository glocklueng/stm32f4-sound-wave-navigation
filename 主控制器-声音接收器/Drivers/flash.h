#ifndef __FLASH_W_R_H__
#define __FLASH_W_R_H__

#include "stm32f4xx.h"

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#define FLASH_USER_START_ADDR	(ADDR_FLASH_SECTOR_10)
#define FLASH_USER_BYTES		(256)
#define FLASH_USER_END_ADDR		(FLASH_USER_START_ADDR + FLASH_USER_BYTES)

#define FLASH_USER_SECTOR1		(FLASH_Sector_8)
//#define FLASH_USER_SECTOR2		(FLASH_Sector_9)

extern __IO u32 *flash_buffer32;
extern __IO u16 *flash_buffer16;
extern __IO u8 *flash_buffer8;

void flash_init(void);
void flash_erase_sector(void);
void flash_write_data32(u32 *buffer, u32 length);
void flash_write_data16(u16 *buffer, u32 length);
void flash_write_data8(u8 *buffer, u32 length);



#endif
