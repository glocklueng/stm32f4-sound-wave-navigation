#ifndef __BITBAND_H__
#define __BITBAND_H__

#include "stm32f4xx.h"

/* �������궨�� bitband macro ------------------------------------------------*/
/* ʹ��bitband����������bit�����ĳ����Ч�ʣ�����GPIO�ܽŵĿ���Ч����Ϊ���� */
/* ��������� ��32MB����������ķ���ӳ��Ϊ��1MB ����bit-band���ķ���(ʵ�ʴ�С����оƬ�й�) */
#define Periph_BASE         0x40000000  // �������ַ Peripheral 
#define Periph_BB_BASE      0x42000000  // �������������ַ Peripheral bitband

/* ע�⣺���볣������ʱ���ڱ���ʱ��������������������ַ�������ܴﵽ����Ч�ʵ�Ŀ��(�Ƽ�)
         ����������������ֻ��������ʱ��STM32�Լ������������ַ��Ч�ʻ����ۿ�(���Ƽ�) */
#define Periph_BB(PeriphAddr, BitNumber)    \
          *(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2))
	 
#define Periph_ResetBit_BB(PeriphAddr, BitNumber)    \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)) = 0)
   
#define Periph_SetBit_BB(PeriphAddr, BitNumber)       \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define Periph_GetBit_BB(PeriphAddr, BitNumber)       \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)))

/* ����GPIO����������������壬nΪbitλ�÷�ΧΪ0��15    */
/* ���Ƕ�GPIOA.15����������Ҫ��ʼ��GPIO��Ȼ��ʹ�÷����� */
/* ��GPIOA.15����͵�ƽ��   PAOutBit(15) = 0;           */
/* ��GPIOA.15����͵�ƽ��   PAOutBit(15) = 1;           */
/* ��ȡGPIOA.15����ĵ�ƽ�� data = PAInBit(15);         */
#define PaOutBit(n)     Periph_BB((uint32_t)&GPIOA->ODR,n)  //��� 
#define PaSetBit(n)     (PaOutBit(n) = 1)                   //��� ��
#define PaResetBit(n)   (PaOutBit(n) = 0)                   //��� ��
#define PaInBit(n)      Periph_BB((uint32_t)&GPIOA->IDR,n)  //���� 

#define PbOutBit(n)     Periph_BB((uint32_t)&GPIOB->ODR,n)  //��� 
#define PbSetBit(n)     (PbOutBit(n) = 1)                   //��� ��
#define PbResetBit(n)   (PbOutBit(n) = 0)                   //��� ��
#define PbInBit(n)      Periph_BB((uint32_t)&GPIOB->IDR,n)  //���� 

#define PcOutBit(n)     Periph_BB((uint32_t)&GPIOC->ODR,n)  //��� 
#define PcSetBit(n)     (PcOutBit(n) = 1)                   //��� ��
#define PcResetBit(n)   (PcOutBit(n) = 0)                   //��� ��
#define PcInBit(n)      Periph_BB((uint32_t)&GPIOC->IDR,n)  //���� 

#define PdOutBit(n)     Periph_BB((uint32_t)&GPIOD->ODR,n)  //��� 
#define PdSetBit(n)     (PdOutBit(n) = 1)                   //��� ��
#define PdResetBit(n)   (PdOutBit(n) = 0)                   //��� ��
#define PdInBit(n)      Periph_BB((uint32_t)&GPIOD->IDR,n)  //���� 

#define PeOutBit(n)     Periph_BB((uint32_t)&GPIOE->ODR,n)  //��� 
#define PeSetBit(n)     (PeOutBit(n) = 1)                   //��� ��
#define PeResetBit(n)   (PeOutBit(n) = 0)                   //��� ��
#define PeInBit(n)      Periph_BB((uint32_t)&GPIOE->IDR,n)  //����

#define PfOutBit(n)     Periph_BB((uint32_t)&GPIOF->ODR,n)  //��� 
#define PfSetBit(n)     (PfOutBit(n) = 1)                   //��� ��
#define PfResetBit(n)   (PfOutBit(n) = 0)                   //��� ��
#define PfInBit(n)      Periph_BB((uint32_t)&GPIOF->IDR,n)  //����

#define PgOutBit(n)     Periph_BB((uint32_t)&GPIOG->ODR,n)  //��� 
#define PgSetBit(n)     (PgOutBit(n) = 1)                   //��� ��
#define PgResetBit(n)   (PgOutBit(n) = 0)                   //��� ��
#define PgInBit(n)      Periph_BB((uint32_t)&GPIOG->IDR,n)  //����
#endif
