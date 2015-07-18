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
	I2C_GenerateSTART(I2C1,ENABLE);													//������ʼ����
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));						//�ȴ�ACK
	I2C_Send7bitAddress(I2C1,id,I2C_Direction_Transmitter);							//���豸�����豸��ַ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));		//�ȴ�ACK
	I2C_SendData(I2C1, write_address);												//�Ĵ�����ַ
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));				//�ȴ�ACK
	I2C_SendData(I2C1, byte);														//��������
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));				//�������
	I2C_GenerateSTOP(I2C1, ENABLE);													//���������ź�
}

u8 iic_read_byte(u8 id, u8 read_address)
{  
	u8 temp; 	
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)){}									//�ȴ�I2C
  	I2C_GenerateSTART(I2C1, ENABLE);												//������ʼ�ź�
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));						//EV5
  	I2C_Send7bitAddress(I2C1, id, I2C_Direction_Transmitter);						//���͵�ַ
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));		//EV6
  	I2C_Cmd(I2C1, ENABLE);															//�������ÿ������EV6
  	I2C_SendData(I2C1, read_address);												//���Ͷ���ַ
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));				//EV8 
  	I2C_GenerateSTART(I2C1, ENABLE);												//���·���
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));						//EV5
  	I2C_Send7bitAddress(I2C1, id, I2C_Direction_Receiver);							//���Ͷ���ַ
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));			//EV6  
	I2C_Cmd(I2C1, ENABLE);															//�������ÿ������EV6
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);													//�ر�Ӧ���ֹͣ��������
    while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))){}
    temp = I2C_ReceiveData(I2C1);   
  	I2C_AcknowledgeConfig(I2C1, ENABLE);		
    return temp;
}

void iic_read_bytes(u8 id, u8 reg, u8 length, u8* buf)
{  
	u8 i;
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)){}									//�ȴ�I2C
  	I2C_GenerateSTART(I2C1, ENABLE);												//������ʼ�ź�
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));						//EV5
  	I2C_Send7bitAddress(I2C1, id, I2C_Direction_Transmitter);						//���͵�ַ
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));		//EV6
  	I2C_Cmd(I2C1, ENABLE);															//�������ÿ������EV6
  	I2C_SendData(I2C1, reg);														//���Ͷ���ַ
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));				//EV8 
  	I2C_GenerateSTART(I2C1, ENABLE);												//���·���
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));						//EV5
  	I2C_Send7bitAddress(I2C1, id, I2C_Direction_Receiver);							//���Ͷ���ַ
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
