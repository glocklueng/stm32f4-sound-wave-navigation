#include "nrf24l01.h"
#include "delay.h"
#include "spi.h"
#include "gpio.h"
#include "usart.h"
#include "exti.h"

uint8_t nrf_state;
uint8_t nrf_tx_buffer[TX_PLOAD_WIDTH] = "hello world, pretty good hust..";
uint8_t nrf_rx_buffer[RX_PLOAD_WIDTH];

const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址

//初始化24L01的IO口
void NRF24L01_Init(uint8_t mode)
{  
	gpio_out_pp_up_init(GPIOB, GPIO_Pin_7); //NRF24L01_CE初始化
 	spi_config();    		//初始化SPI1  
	exti_config(GPIOB, 5);
	NRF24L01_CE=0; 			//使能24L01
	NRF24L01_CS=1;			//SPI片选取消	 
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

//检测24L01是否存在
//返回值:0，成功;1，失败	
uint8_t NRF24L01_Check(void)
{
	uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint8_t i;
	spi_set_speed(SPI_BaudRatePrescaler_8);	 			//spi速度为10.5Mhz（24L01的最大SPI时钟为10Mhz）   	 
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);	//写入5个字节的地址.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); 					//读出写入的地址  
	for(i=0;i<5;i++){
		if(buf[i]!=0XA5){
			return 1;//检测24L01错误	
		}
	}		
	return 0;		 //检测到24L01
}

//SPI写寄存器
//reg:指定寄存器地址
//value:写入的值
uint8_t NRF24L01_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;	
	NRF24L01_CS=0;                 //使能SPI传输
	status =spi_read_write_byte(reg);//发送寄存器号 
	spi_read_write_byte(value);      //写入寄存器的值
	NRF24L01_CS=1;                 //禁止SPI传输	   
	return(status);       			//返回状态值
}
//读取SPI寄存器值
//reg:要读的寄存器
uint8_t NRF24L01_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;	    
	NRF24L01_CS = 0;          //使能SPI传输		
	spi_read_write_byte(reg);   //发送寄存器号
	reg_val=spi_read_write_byte(0XFF);//读取寄存器内容
	NRF24L01_CS = 1;          //禁止SPI传输		    
	return(reg_val);           //返回状态值
}	
//在指定位置读出指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值 
uint8_t NRF24L01_Read_Buf(uint8_t reg,uint8_t *pBuf,uint8_t len)
{
  uint8_t status,i;	       
  NRF24L01_CS = 0;           //使能SPI传输
  status=spi_read_write_byte(reg);//发送寄存器值(位置),并读取状态值   	   
  for(i=0;i<len;i++){
	  pBuf[i]=spi_read_write_byte(0XFF);//读出数据
  }
  NRF24L01_CS=1;       //关闭SPI传输
  return status;        //返回读到的状态值
}
//在指定位置写指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值
uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status,i;	    
	NRF24L01_CS = 0;          //使能SPI传输
	status = spi_read_write_byte(reg);//发送寄存器值(位置),并读取状态值
	for(i=0; i<len; i++){
		spi_read_write_byte(*pBuf++); //写入数据	 
	}
	NRF24L01_CS = 1;       //关闭SPI传输
	return status;          //返回读到的状态值
}				   
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:发送完成状况
void NRF24L01_TxPacket(uint8_t *txbuf)
{
	spi_set_speed(SPI_BaudRatePrescaler_8);//spi速度为10.5Mhz（24L01的最大SPI时钟为10Mhz）
	while(1){
		if(nrf_state == TX_OK){
			break;
		}
		else if(nrf_state == MAX_TX){
			printf("NRF24L01: 带到最大发送次数\r\n");
			break;
		}
	}
	nrf_state = SENDING_DATA;
	NRF24L01_CE=0;
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
	NRF24L01_CE=1;//启动发送	
}

//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了		   
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;	  
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    //使能通道0的自动应答    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);//使能通道0的接收地址  	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	     //设置RF通信频率		  
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	NRF24L01_CE = 1; //CE为高,进入接收模式 
	delay_us(100);
}

//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了		   
//CE为高大于10us,则启动发送.	 
void NRF24L01_TX_Mode(void)
{								 
	NRF24L01_CE=0;	    
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  

	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //设置RF通道为40
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,发送模式,开启所有中断
	NRF24L01_CE=1;//CE为高,10us后启动发送
	delay_us(100);
}

uint8_t NRF24L01_Get_State(uint8_t *pState)
{
	uint8_t ucState, res=0;
	NRF24L01_CE = 0;
	ucState=NRF24L01_Read_Reg(STATUS);/*读取status寄存器的值  */       
	*pState = ucState;
	if(ucState & RX_OK)    /* 接收到数据 */
	{
		res = RX_OK; 
	}
	else if(ucState & MAX_TX) /* 达到最大重发次数 */
	{	
		res = MAX_TX;
	}
	else if(ucState & TX_OK)/* 发送完成 */
	{
		res = TX_OK;	
	}
	NRF24L01_CE = 1;
	return res;
}






