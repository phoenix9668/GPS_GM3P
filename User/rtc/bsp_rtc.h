#ifndef __BSP_RTC_H
#define	__BSP_RTC_H

#include "stm32f10x.h"

/* Private function prototypes -----------------------------------------------*/
void EXTI_Line17_Configuration(void);
void RTC_Configuration(void);
void NVIC_RTC_Configuration(void);
void RTC_Alarm_Config(void);
void Time_Adjust(void);
void Interval_Init(void);
void Interval_Adjust(void);
void Time_Display(uint32_t TimeVar);
void Time_Show(void);
	

#endif /* __BSP_RTC_H */
