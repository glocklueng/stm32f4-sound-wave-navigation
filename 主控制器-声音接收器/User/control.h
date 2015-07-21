#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <stdint.h>

typedef struct{
	uint32_t ta;
	uint32_t tb;
	uint32_t tc;
	uint8_t a;//A���յ������ź�
	uint8_t b;//B���յ������ź�
	uint8_t c;//C���յ������ź�
	uint8_t all;//�����յ������ź�
}Control;

extern Control ctrl;

void clear_control(Control *pctrl);
void control_process(void);


#endif

