#ifndef __BSP_TIM_H
#define	__BSP_TIM_H

#include "stm32f10x.h"

void Timing_Decrement(void);
void SysTickDelay(uint32_t nTime);
void TimingDelay_Decrement(void);
void SysTick_Configuration(void);
void SYSCLKConfig_STOP(void);

#endif /* __BSP_TIM_H */
