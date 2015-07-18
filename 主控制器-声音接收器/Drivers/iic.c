#include "iic.h"
#include "gpio.h"

void iic_config(void)
{
	I2C_InitTypeDef  I2C_InitStructure;
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
	gpio_af_od_no_init(GPIOB,
				GPIO_Pin_8 | GPIO_Pin_9);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	I2C_DeInit(I2C1);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0xA0;  
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
}

void iic_write_byte(u8 id,u8 write_address,u8 byte)
{
	I2C_GenerateSTART(I2C1,ENABLE);													//产生起始条件
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));						//等待ACK
	I2C_Send7bitAddress(I2C1,id,I2C_Direction_Transmitter);							//向设备发送设备地址
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));		//等待ACK
	I2C_SendData(I2C1, write_address);												//寄存器地址
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));				//等待ACK
	I2C_SendData(I2C1, byte);														//发送数据
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));				//发送完成
	I2C_GenerateSTOP(I2C1, ENABLE);													//产生结束信号
}

u8 iic_read_byte(u8 id, u8 read_address)
{  
	u8 temp; 	
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)){}									//等待I2C
  	I2C_GenerateSTART(I2C1, ENABLE);												//产生起始信号
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));						//EV5
  	I2C_Send7bitAddress(I2C1, id, I2C_Direction_Transmitter);						//发送地址
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));		//EV6
  	I2C_Cmd(I2C1, ENABLE);															//重新设置可以清楚EV6
  	I2C_SendData(I2C1, read_address);												//发送读地址
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));				//EV8 
  	I2C_GenerateSTART(I2C1, ENABLE);												//重新发送
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));						//EV5
  	I2C_Send7bitAddress(I2C1, id, I2C_Direction_Receiver);							//发送读地址
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));			//EV6  
	I2C_Cmd(I2C1, ENABLE);															//重新设置可以清楚EV6
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);													//关闭应答和停止条件产生
    while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))){}
    temp = I2C_ReceiveData(I2C1);   
  	I2C_AcknowledgeConfig(I2C1, ENABLE);		
    return temp;
}

void iic_read_bytes(u8 id, u8 reg, u8 length, u8* buf)
{  
	u8 i;
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)){}									//等待I2C
  	I2C_GenerateSTART(I2C1, ENABLE);												//产生起始信号
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));						//EV5
  	I2C_Send7bitAddress(I2C1, id, I2C_Direction_Transmitter);						//发送地址
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));		//EV6
  	I2C_Cmd(I2C1, ENABLE);															//重新设置可以清楚EV6
  	I2C_SendData(I2C1, reg);														//发送读地址
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));				//EV8 
  	I2C_GenerateSTART(I2C1, ENABLE);												//重新发送
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));						//EV5
  	I2C_Send7bitAddress(I2C1, id, I2C_Direction_Receiver);							//发送读地址
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));			//EV6 
	I2C_Cmd(I2C1, ENABLE);														
	for(i=0; i<length; i++)
	{
 		while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))){}
		if(i == length - 2){
			I2C_AcknowledgeConfig(I2C1, DISABLE);
		}
		if(i == length - 1){
			I2C_GenerateSTOP(I2C1, ENABLE);
		}
 		buf[i]=I2C_ReceiveData(I2C1);
	}
  	I2C_AcknowledgeConfig(I2C1, ENABLE);
}
