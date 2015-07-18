#ifndef __MYIIC_H__
#define __MYIIC_H__

#include "stm32f4xx.h"
#include "bitband.h"
   	   		   
//IO��������
#define SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9����ģʽ
#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9���ģʽ
//IO��������	 
#define IIC_SCL    PbOutBit(8) //SCL
#define IIC_SDA    PbOutBit(9) //SDA	 
#define READ_SDA   PbInBit(9)  //����SDA 

//IIC���в�������
void myiic_init(void);                //��ʼ��IIC��IO��				 
void myiic_start(void);				//����IIC��ʼ�ź�
void myiic_stop(void);	  			//����IICֹͣ�ź�
void myiic_send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 myiic_read_byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 myiic_wait_ack(void); 				//IIC�ȴ�ACK�ź�
void myiic_ack(void);					//IIC����ACK�ź�
void myiic_nack(void);				//IIC������ACK�ź�

u8 myiic_write_one_byte(u8 dev,u8 reg,u8 data);
u8 myiic_read_one_byte(u8 dev,u8 reg);	 

#endif
