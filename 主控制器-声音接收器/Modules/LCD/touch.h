#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "stm32f4xx.h"

#define CMD_RDX 0XD0
#define CMD_RDY 0X90

u16 readAdc(u8 cmd);
u16 readFilterAdc(u8 cmd);
u8 readTouchPos(u16 *x,u16 *y);
u8 readXY(u16 *x, u16 *y);
void touchAdjust(void);
u8 readTiwceTouchPos(u16 *x,u16 *y);
//void saveAdjustResult(void);
//void getAdjustValue(void);
void waitButton(u16 *x, u16 *y);
void invoking(void);

#endif
