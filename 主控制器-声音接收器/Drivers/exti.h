#ifndef __EXTI_H__
#define __EXTI_H__

#include "stm32f4xx.h"

void exti_config(GPIO_TypeDef *gpiox, u8 pin_num);

#endif
