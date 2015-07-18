#ifndef __NANO_BOARD_H__
#define __NANO_BOARD_H__

#include "stm32f4xx.h"
#include "bitband.h"

#define NANO_BOARD_LED2		PbOutBit(0)
#define NANO_BOARD_LED3		PcOutBit(0)
#define NANO_BOARD_KEY		PaInBit(0)

void nano_board_led_init(void);
void nano_board_led2_on(void);
void nano_board_led3_on(void);
void nano_board_led2_off(void);
void nano_board_led3_off(void);
void nano_board_led2_toggle(void);
void nano_board_led3_toggle(void);
void nano_board_key_init(void);
u8 is_nano_board_key_down(void);

#endif
