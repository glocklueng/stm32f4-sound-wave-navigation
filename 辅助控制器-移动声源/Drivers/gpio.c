#include "gpio.h"

void gpio_config(GPIO_TypeDef *gpio, 
				 uint32_t gpio_pin, 
				 GPIOMode_TypeDef mode, 
				 GPIOOType_TypeDef output_type, 
				 GPIOPuPd_TypeDef pull_type,
				 GPIOSpeed_TypeDef speed_type)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = gpio_pin;
	GPIO_InitStructure.GPIO_Mode = mode;
	GPIO_InitStructure.GPIO_OType = output_type;
	GPIO_InitStructure.GPIO_PuPd = pull_type;
	GPIO_InitStructure.GPIO_Speed = speed_type;
	GPIO_Init(gpio, &GPIO_InitStructure);
}

//�����������
void gpio_out_pp_up_init(GPIO_TypeDef *gpio, uint32_t gpio_pin)
{
	gpio_config(gpio, gpio_pin, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
}

//��������
void gpio_in_up_init(GPIO_TypeDef *gpio, uint32_t gpio_pin)
{
	gpio_config(gpio, gpio_pin, GPIO_Mode_IN, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_100MHz);
}

//��������
void gpio_in_down_init(GPIO_TypeDef *gpio, uint32_t gpio_pin)
{
	gpio_config(gpio, gpio_pin, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_100MHz);
}

//������������
void gpio_af_pp_up_init(GPIO_TypeDef *gpio, uint32_t gpio_pin)
{
	gpio_config(gpio, gpio_pin, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
}

//���ÿ�©����
void gpio_af_od_no_init(GPIO_TypeDef *gpio, uint32_t gpio_pin)
{
	gpio_config(gpio, gpio_pin, GPIO_Mode_AF, GPIO_OType_OD, GPIO_PuPd_NOPULL, GPIO_Speed_100MHz);
}

//���ÿ�©����
void gpio_af_od_up_init(GPIO_TypeDef *gpio, uint32_t gpio_pin)
{
	gpio_config(gpio, gpio_pin, GPIO_Mode_AF, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_100MHz);
}

