#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <stdint.h>

typedef struct{
	uint32_t ta;
	uint32_t tb;
	uint32_t tc;
	uint8_t a;//A接收到声音信号
	uint8_t b;//B接收到声音信号
	uint8_t c;//C接收到声音信号
	uint8_t all;//都接收到声音信号
}Control;

extern Control ctrl;

void clear_control(Control *pctrl);
void control_process(void);


#endif

