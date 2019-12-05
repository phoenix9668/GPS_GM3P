#ifndef __BSP_TIM_H
#define	__BSP_TIM_H

#include "stm32f10x.h"

void Timing_Decrement(void);
void Delay_Second(void);
void systick_init(void);

#endif /* __BSP_TIM_H */
