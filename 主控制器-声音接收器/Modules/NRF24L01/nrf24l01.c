#include "nrf24l01.h"
#include "delay.h"
#include "spi.h"
#include "gpio.h"
#include "usart.h"
#include "exti.h"

uint8_t nrf_state;
uint8_t nrf_tx_buffer[TX_PLOAD_WIDTH] = "hello world, pretty good hust..";
uint8_t nrf_rx_buffer[RX_PLOAD_WIDTH];

const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ

//��ʼ��24L01��IO��
void NRF24L01_Init(uint8_t mode)
{  
	gpio_out_pp_up_init(GPIOB, GPIO_Pin_7); //NRF24L01_CE��ʼ��
 	spi_config();    		//��ʼ��SPI1  
	exti_config(GPIOB, 5);
	NRF24L01_CE=0; 			//ʹ��24L01
	NRF24L01_CS=1;			//SPIƬѡȡ��	 
	while(NRF24L01_Check()){
		printf("not found NRF24L01\r\n");
		delay_ms(500);
	}
	printf("NRF24L01 init ok\r\n");
	
	if(mode == NRF_RX_MODE){
		nrf_state = RX_OK;
		NRF24L01_RX_Mode();
	}
	else{
		nrf_state = TX_OK;
		NRF24L01_TX_Mode();
	}
}

//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��	
uint8_t NRF24L01_Check(void)
{
	uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint8_t i;
	spi_set_speed(SPI_BaudRatePrescaler_8);	 			//spi�ٶ�Ϊ10.5Mhz��24L01�����SPIʱ��Ϊ10Mhz��   	 
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);	//д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); 					//����д��ĵ�ַ  
	for(i=0;i<5;i++){
		if(buf[i]!=0XA5){
			return 1;//���24L01����	
		}
	}		
	return 0;		 //��⵽24L01
}

//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
uint8_t NRF24L01_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;	
	NRF24L01_CS=0;                 //ʹ��SPI����
	status =spi_read_write_byte(reg);//���ͼĴ����� 
	spi_read_write_byte(value);      //д��Ĵ�����ֵ
	NRF24L01_CS=1;                 //��ֹSPI����	   
	return(status);       			//����״ֵ̬
}
//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
uint8_t NRF24L01_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;	    
	NRF24L01_CS = 0;          //ʹ��SPI����		
	spi_read_write_byte(reg);   //���ͼĴ�����
	reg_val=spi_read_write_byte(0XFF);//��ȡ�Ĵ�������
	NRF24L01_CS = 1;          //��ֹSPI����		    
	return(reg_val);           //����״ֵ̬
}	
//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
uint8_t NRF24L01_Read_Buf(uint8_t reg,uint8_t *pBuf,uint8_t len)
{
  uint8_t status,i;	       
  NRF24L01_CS = 0;           //ʹ��SPI����
  status=spi_read_write_byte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
  for(i=0;i<len;i++){
	  pBuf[i]=spi_read_write_byte(0XFF);//��������
  }
  NRF24L01_CS=1;       //�ر�SPI����
  return status;        //���ض�����״ֵ̬
}
//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status,i;	    
	NRF24L01_CS = 0;          //ʹ��SPI����
	status = spi_read_write_byte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
	for(i=0; i<len; i++){
		spi_read_write_byte(*pBuf++); //д������	 
	}
	NRF24L01_CS = 1;       //�ر�SPI����
	return status;          //���ض�����״ֵ̬
}				   
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
void NRF24L01_TxPacket(uint8_t *txbuf)
{
	spi_set_speed(SPI_BaudRatePrescaler_8);//spi�ٶ�Ϊ10.5Mhz��24L01�����SPIʱ��Ϊ10Mhz��
	while(1){
		if(nrf_state == TX_OK){
			break;
		}
		else if(nrf_state == MAX_TX){
			printf("NRF24L01: ��������ʹ���\r\n");
			break;
		}
	}
	nrf_state = SENDING_DATA;
	NRF24L01_CE=0;
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
	NRF24L01_CE=1;//��������	
}

//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;	  
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	     //����RFͨ��Ƶ��		  
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);//����TX�������,0db����,2Mbps,���������濪��   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
	NRF24L01_CE = 1; //CEΪ��,�������ģʽ 
	delay_us(100);
}

//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
//CEΪ�ߴ���10us,����������.	 
void NRF24L01_TX_Mode(void)
{								 
	NRF24L01_CE=0;	    
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  

	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //����RFͨ��Ϊ40
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE=1;//CEΪ��,10us����������
	delay_us(100);
}

uint8_t NRF24L01_Get_State(uint8_t *pState)
{
	uint8_t ucState, res=0;
	NRF24L01_CE = 0;
	ucState=NRF24L01_Read_Reg(STATUS);/*��ȡstatus�Ĵ�����ֵ  */       
	*pState = ucState;
	if(ucState & RX_OK)    /* ���յ����� */
	{
		res = RX_OK; 
	}
	else if(ucState & MAX_TX) /* �ﵽ����ط����� */
	{	
		res = MAX_TX;
	}
	else if(ucState & TX_OK)/* ������� */
	{
		res = TX_OK;	
	}
	NRF24L01_CE = 1;
	return res;
}






