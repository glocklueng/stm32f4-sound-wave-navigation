#ifndef __MYIIC_H__
#define __MYIIC_H__

#include "stm32f4xx.h"
#include "bitband.h"
   	   		   
//IO方向设置
#define SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9输入模式
#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9输出模式
//IO操作函数	 
#define IIC_SCL    PbOutBit(8) //SCL
#define IIC_SDA    PbOutBit(9) //SDA	 
#define READ_SDA   PbInBit(9)  //输入SDA 

//IIC所有操作函数
void myiic_init(void);                //初始化IIC的IO口				 
void myiic_start(void);				//发送IIC开始信号
void myiic_stop(void);	  			//发送IIC停止信号
void myiic_send_Byte(u8 txd);			//IIC发送一个字节
u8 myiic_read_byte(unsigned char ack);//IIC读取一个字节
u8 myiic_wait_ack(void); 				//IIC等待ACK信号
void myiic_ack(void);					//IIC发送ACK信号
void myiic_nack(void);				//IIC不发送ACK信号

u8 myiic_write_one_byte(u8 dev,u8 reg,u8 data);
u8 myiic_read_one_byte(u8 dev,u8 reg);	 

#endif
