#ifndef __NANO_BOARD_H__
#define __NANO_BOARD_H__

#include "stm32f4xx.h"
#include "bitband.h"

#define NANO_BOARD_LED2		PbOutBit(0)
#define NANO_BOARD_LED3		PcOutBit(0)
#define NANO_BOARD_KEY		PaInBit(0)

#define LED2_ON		NANO_BOARD_LED2=0
#define LED3_ON		NANO_BOARD_LED3=0
#define LED2_OFF	NANO_BOARD_LED2=1
#define LED3_OFF	NANO_BOARD_LED3=1

void nano_board_led_init(void);
void nano_board_led2_toggle(void);
void nano_board_led3_toggle(void);
void nano_board_led2_twinkle(void);
void nano_board_led3_twinkle(void);
void nano_board_key_init(void);
u8 is_nano_board_key_down(void);

#endif
