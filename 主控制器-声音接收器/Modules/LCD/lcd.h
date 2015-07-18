#ifndef __LCD_H__
#define __LCD_H__

#include "stm32f4xx_fsmc.h"
#include "bitband.h"

//定义LCD的尺寸	
#define LCD_W 240
#define LCD_H 320

#define T_IRQ	PcInBit(5)

#define LCD_LED_A	PbOutBit(1)
#define LCD_RESET	PfOutBit(11)

typedef struct
{
	uint16_t LCD_REG;
	uint16_t LCD_RAM;
} LCD_TypeDef;			    
#define LCD_BASE	((u32)(0x6C000000 | 0x0000007E))
#define LCD			((LCD_TypeDef *) LCD_BASE)

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 

#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

void lcd_init(void);

void lcd_write_reg(uint16_t reg);
void lcd_write_data(uint16_t dat);
void lcd_write_reg_data(uint16_t reg, uint16_t dat);
uint16_t lcd_read_data(void);
uint16_t lcd_read_reg(uint16_t reg);
void lcd_prepare_write_ram(void);
void lcd_write_ram(uint16_t color);
void lcd_set_cursor(uint16_t x, uint16_t y);
uint16_t lcd_read_point_color(uint16_t x, uint16_t y);
void lcd_display_on(void);
void lcd_display_off(void);
void lcd_set_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void lcd_clear(uint16_t color);
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
void lcd_fill(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t color);
void lcd_draw_big_point(uint16_t x, uint16_t y, uint16_t color);
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void lcd_show_char(uint16_t x, uint16_t y, uint8_t num, uint16_t color);
void lcd_show_str(uint16_t x, uint16_t y, const char *p, uint16_t color);
void lcd_show_num(uint16_t x, uint16_t y, u32 num, uint16_t color);

#endif
