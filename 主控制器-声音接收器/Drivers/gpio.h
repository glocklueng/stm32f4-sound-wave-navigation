#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f4xx_gpio.h"

void gpio_config(GPIO_TypeDef *gpio, 
				 uint32_t gpio_pin, 
				 GPIOMode_TypeDef mode, 
				 GPIOOType_TypeDef output_type, 
				 GPIOPuPd_TypeDef pull_type,
				 GPIOSpeed_TypeDef speed_type);

void gpio_out_pp_up_init(GPIO_TypeDef *gpio, uint32_t gpio_pin);
void gpio_in_up_init(GPIO_TypeDef *gpio, uint32_t gpio_pin);
void gpio_in_down_init(GPIO_TypeDef *gpio, uint32_t gpio_pin);
void gpio_af_pp_up_init(GPIO_TypeDef *gpio, uint32_t gpio_pin);
void gpio_af_od_no_init(GPIO_TypeDef *gpio, uint32_t gpio_pin);
void gpio_af_od_up_init(GPIO_TypeDef *gpio, uint32_t gpio_pin);

#endif
