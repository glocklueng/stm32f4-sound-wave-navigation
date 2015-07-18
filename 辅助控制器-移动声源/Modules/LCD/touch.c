#include "touch.h"
#include "spi.h"
#include "lcd.h"
#include "delay.h"
#include <math.h>

float xFac = -0.068097;
float yFac = -0.090498;
float xOff = 261.334717;
float yOff = 349.773743;
u16 xPos, yPos;

u16 readAdc(u8 cmd)
{
	u8 high, low;
	u16 res = 0;
	spi_read_write_byte(cmd);
	high = spi_read_write_byte(0x00);
	low = spi_read_write_byte(0x00);
	res = high<<8;
	res = (res | low)>>3;
	if(cmd == CMD_RDY && res == 4095){
		res = 0;
	}
	return res;
}

#define READ_TIMES 5 	//读取次数
#define LOST_VAL 1	  	//丢弃值
u16 readFilterAdc(u8 cmd)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum;
	u16 temp;
	for(i=0; i<READ_TIMES; i++){
		buf[i]=readAdc(cmd);		
	}
	for(i=0; i<READ_TIMES-1; i++){	//升序排列
		for(j=i+1; j<READ_TIMES; j++){
			if(buf[i]>buf[j]){		
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL; i<READ_TIMES-LOST_VAL; i++){
		sum+=buf[i];
	}
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
}

u8 readTouchPos(u16 *x,u16 *y)
{
	u16 xTemp,yTemp;			 	 		  
	xTemp = readFilterAdc(CMD_RDX);
	yTemp = readFilterAdc(CMD_RDY);
	if(xTemp<250 || yTemp<100){
		return 0;		//读数失败
	}
	*x = xTemp;
	*y = yTemp;
	return 1;			//读数成功
}

#define ERR_RANGE 200 //误差范围 
u8 readTiwceTouchPos(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;    
    if(readTouchPos(&x1,&y1) == 0){
		return 0;
	}
    if(readTouchPos(&x2,&y2) == 0){
		return 0;
	}
    if(((x2<=x1&&x1<x2+ERR_RANGE) || (x1<=x2&&x2<x1+ERR_RANGE))
			&& ((y2<=y1&&y1<y2+ERR_RANGE) || (y1<=y2&&y2<y1+ERR_RANGE))){
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }
	else{
		return 0;	  
	}
} 

u8 readXY(u16 *x, u16 *y)
{
	u16 xAd, yAd;
	if(!readTiwceTouchPos(&xAd, &yAd)){
		return 0;
	}
	*x=(u16)(xFac * xAd + xOff + 0.5f);
	*y=(u16)(yFac * yAd + yOff + 0.5f);
	return 1;
}

void drawAdjustPoint(u16 x, u16 y)
{
	lcd_draw_line(x-12, y, x+13, y, RED);//横线
	lcd_draw_line(x, y-12, x, y+13, RED);//竖线
	lcd_draw_point(x+1, y+1, RED);
	lcd_draw_point(x-1, y+1, RED);
	lcd_draw_point(x+1, y-1, RED);
	lcd_draw_point(x-1, y-1, RED);
	lcd_draw_circle(x, y, 6, RED);//画中心圈
}

void touchAdjust(void)
{
	u16 posTmp[4][2];
	float d1, d2, fac;
	u32 tem1, tem2;
	
	while(1){
		lcd_clear(WHITE);
		drawAdjustPoint(20,20);
		while(T_IRQ){}
		if(!readTouchPos(&posTmp[0][0], &posTmp[0][1])){
			continue;
		}
		while(!T_IRQ){}
			
		lcd_clear(WHITE);
		drawAdjustPoint(220,20);
		while(T_IRQ){}
		if(!readTouchPos(&posTmp[1][0], &posTmp[1][1])){
			continue;
		}
		while(!T_IRQ){}
		
		lcd_clear(WHITE);
		drawAdjustPoint(20,300);
		while(T_IRQ){}
		if(!readTouchPos(&posTmp[2][0], &posTmp[2][1])){
			continue;
		}
		while(!T_IRQ){}
			
		lcd_clear(WHITE);
		drawAdjustPoint(220,300);
		while(T_IRQ){}
		if(!readTouchPos(&posTmp[3][0], &posTmp[3][1])){
			continue;
		}
		while(!T_IRQ){}
		
		tem1 = fabs(posTmp[0][0]-posTmp[1][0]);//x1-x2
		tem2 = fabs(posTmp[0][1]-posTmp[1][1]);//y1-y2
		tem1 *= tem1;
		tem2 *= tem2;
		d1 = sqrt(tem1+tem2);//得到1,2的距离
		
		tem1 = fabs(posTmp[2][0]-posTmp[3][0]);//x3-x4
		tem2 = fabs(posTmp[2][1]-posTmp[3][1]);//y3-y4
		tem1 *= tem1;
		tem2 *= tem2;
		d2 = sqrt(tem1+tem2);//得到3,4的距离
		fac = (float)d1/d2;
		if(fac<0.95f || fac>1.05f || d1==0.0f || d2==0.0f){//不合格
			continue;
		}
		tem1=fabs(posTmp[0][0]-posTmp[2][0]);//x1-x3
		tem2=fabs(posTmp[0][1]-posTmp[2][1]);//y1-y3
		tem1*=tem1;
		tem2*=tem2;
		d1=sqrt(tem1+tem2);//得到1,3的距离
		
		tem1=fabs(posTmp[1][0]-posTmp[3][0]);//x2-x4
		tem2=fabs(posTmp[1][1]-posTmp[3][1]);//y2-y4
		tem1*=tem1;
		tem2*=tem2;
		d2=sqrt(tem1+tem2);//得到2,4的距离
		fac=(float)d1/d2;
		if(fac<0.95f || fac>1.05f || d1==0.0f || d2==0.0f)//不合格
		{
			continue;
		}//正确了						   
		//对角线相等
		tem1=fabs(posTmp[1][0]-posTmp[2][0]);//x2-x3
		tem2=fabs(posTmp[1][1]-posTmp[2][1]);//y2-y3
		tem1*=tem1;
		tem2*=tem2;
		d1=sqrt(tem1+tem2);//得到2,3的距离

		tem1=fabs(posTmp[0][0]-posTmp[3][0]);//x1-x4
		tem2=fabs(posTmp[0][1]-posTmp[3][1]);//y1-y4
		tem1*=tem1;
		tem2*=tem2;
		d2=sqrt(tem1+tem2);//得到1,4的距离
		fac=(float)d1/d2;
		if(fac<0.95f || fac>1.05f || d1==0.0f || d2==0.0f){	//不合格
			continue;
		}
		break;
	}
	xFac=(float)200/(posTmp[1][0]-posTmp[0][0]);//得到xfac		 
	xOff=(240-xFac*(posTmp[1][0]+posTmp[0][0]))/2;//得到xoff  
	yFac=(float)280/(posTmp[2][1]-posTmp[0][1]);//得到yfac
	yOff=(320-yFac*(posTmp[2][1]+posTmp[0][1]))/2;//得到yoff
	
	lcd_clear(WHITE);
	lcd_show_str(5, 140, "adjust succeed", BLUE);
	while(T_IRQ){}
	lcd_clear(WHITE);
}

void waitButton(u16 *x, u16 *y)
{
	while(1){
		while(T_IRQ){}
		delay_ms(5);
		if(!readXY(x, y)){
			continue;
		}
		break;
	}
	while(!T_IRQ){}
	delay_ms(20);
}


