#ifndef __BITBAND_H__
#define __BITBAND_H__

#include "stm32f4xx.h"

/* 别名区宏定义 bitband macro ------------------------------------------------*/
/* 使用bitband可以提高设计bit操作的程序的效率，外设GPIO管脚的控制效果尤为明显 */
/* 外设别名区 对32MB外设别名区的访问映射为对1MB 外设bit-band区的访问(实际大小根据芯片有关) */
#define Periph_BASE         0x40000000  // 外设基地址 Peripheral 
#define Periph_BB_BASE      0x42000000  // 外设别名区基地址 Peripheral bitband

/* 注意：传入常量参数时，在编译时编译器会计算出别名区地址，这样能达到提升效率的目的(推荐)
         如果传入变量参数，只能在运行时由STM32自己计算别名区地址，效率会大打折扣(不推荐) */
#define Periph_BB(PeriphAddr, BitNumber)    \
          *(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2))
	 
#define Periph_ResetBit_BB(PeriphAddr, BitNumber)    \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)) = 0)
   
#define Periph_SetBit_BB(PeriphAddr, BitNumber)       \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define Periph_GetBit_BB(PeriphAddr, BitNumber)       \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)))

/* 外设GPIO输入输出别名区定义，n为bit位置范围为0到15    */
/* 我们对GPIOA.15操作，首先要初始化GPIO，然后使用方法： */
/* 对GPIOA.15输出低电平：   PAOutBit(15) = 0;           */
/* 对GPIOA.15输出低电平：   PAOutBit(15) = 1;           */
/* 读取GPIOA.15输入的电平： data = PAInBit(15);         */
#define PaOutBit(n)     Periph_BB((uint32_t)&GPIOA->ODR,n)  //输出 
#define PaSetBit(n)     (PaOutBit(n) = 1)                   //输出 高
#define PaResetBit(n)   (PaOutBit(n) = 0)                   //输出 低
#define PaInBit(n)      Periph_BB((uint32_t)&GPIOA->IDR,n)  //输入 

#define PbOutBit(n)     Periph_BB((uint32_t)&GPIOB->ODR,n)  //输出 
#define PbSetBit(n)     (PbOutBit(n) = 1)                   //输出 高
#define PbResetBit(n)   (PbOutBit(n) = 0)                   //输出 低
#define PbInBit(n)      Periph_BB((uint32_t)&GPIOB->IDR,n)  //输入 

#define PcOutBit(n)     Periph_BB((uint32_t)&GPIOC->ODR,n)  //输出 
#define PcSetBit(n)     (PcOutBit(n) = 1)                   //输出 高
#define PcResetBit(n)   (PcOutBit(n) = 0)                   //输出 低
#define PcInBit(n)      Periph_BB((uint32_t)&GPIOC->IDR,n)  //输入 

#define PdOutBit(n)     Periph_BB((uint32_t)&GPIOD->ODR,n)  //输出 
#define PdSetBit(n)     (PdOutBit(n) = 1)                   //输出 高
#define PdResetBit(n)   (PdOutBit(n) = 0)                   //输出 低
#define PdInBit(n)      Periph_BB((uint32_t)&GPIOD->IDR,n)  //输入 

#define PeOutBit(n)     Periph_BB((uint32_t)&GPIOE->ODR,n)  //输出 
#define PeSetBit(n)     (PeOutBit(n) = 1)                   //输出 高
#define PeResetBit(n)   (PeOutBit(n) = 0)                   //输出 低
#define PeInBit(n)      Periph_BB((uint32_t)&GPIOE->IDR,n)  //输入

#define PfOutBit(n)     Periph_BB((uint32_t)&GPIOF->ODR,n)  //输出 
#define PfSetBit(n)     (PfOutBit(n) = 1)                   //输出 高
#define PfResetBit(n)   (PfOutBit(n) = 0)                   //输出 低
#define PfInBit(n)      Periph_BB((uint32_t)&GPIOF->IDR,n)  //输入

#define PgOutBit(n)     Periph_BB((uint32_t)&GPIOG->ODR,n)  //输出 
#define PgSetBit(n)     (PgOutBit(n) = 1)                   //输出 高
#define PgResetBit(n)   (PgOutBit(n) = 0)                   //输出 低
#define PgInBit(n)      Periph_BB((uint32_t)&GPIOG->IDR,n)  //输入
#endif
