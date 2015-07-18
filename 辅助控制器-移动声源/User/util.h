#ifndef __UTIL_H__
#define __UTIL_H__

#include "stm32f4xx.h"

#define RES_OK		0
#define RES_ERROR	1
#define RES_ERROR1	2
#define RES_ERROR2	3

#define max(a, b)			(a>b? a:b)
#define min(a, b)			(a<b? a:b)
#define range(x, a, b)		(min(max(x, a), b))
#define exchange(a, b, tmp) (tmp=a, a=b, b=tmp)

void rcc_clock_enable(void);
void print_clock_freq(void);
void nvic_config(uint8_t irq_channel, uint8_t priority);

#endif
