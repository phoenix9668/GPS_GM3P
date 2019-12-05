/**
  ******************************************************************************
  * @file    gm3p_configure.c
  * @version V1.0
  * @date    2019-11-28
  * @brief   time function
  ******************************************************************************
  * @attention  phoenix
  ******************************************************************************
  */

#include "bsp_tim.h"
#include "bsp_usart.h"
#include "bsp_gpio.h"   


uint32_t GPStiming;
uint32_t Delay_second_time;
uint8_t gps_restart_flag;
extern uint8_t gps_on;
extern uint8_t gps_net;
extern uint8_t gps_heart_on;
extern uint8_t gps_heart_time;
extern uint8_t gps_heart_out;

/*===========================================================================
* Timing_Decrement() => Decrements the Timing variable,Reset GPS module.				* 
============================================================================*/
/**
  * @brief  Decrements the Timing variable,Reset GPS module.
  * @param  None
  * @retval None
  */
void Timing_Decrement(void)
{
	if (GPStiming == 0)
	{
//		GPStiming = 7200000;//2hours
		GPStiming = 600000;//10mins
	}
//	else if (GPStiming == 7170000)
	else if (GPStiming == 570000)
	{
		RESET_KEY_ON();
		GPStiming--;
	}
//	else if (GPStiming == 7168000)
	else if (GPStiming == 568000)
	{
		POWER_KEY_ON();
		gps_restart_flag = 1;
		printf("GPS Module Restarting\n");
		GPStiming--;
	}
//	else if (GPStiming == 7108000)
	else if (GPStiming == 508000)
	{
		printf("GPS+GPRS module turn off\r\n");
		printf("...3...\r\n");
		GPStiming--;
	}
//	else if (GPStiming == 7107000)
	else if (GPStiming == 507000)
	{
		printf("...2...\r\n");
		GPStiming--;
	}
//	else if (GPStiming == 7106000)
	else if (GPStiming == 506000)
	{
		printf("...1...\r\n");
		GPStiming--;
	}
	//	else if (GPStiming == 7105000)
	else if (GPStiming == 504000)
	{
		POWER_KEY_OFF();
		GPStiming--;
	}
	//	else if (GPStiming == 7104000)
	else if (GPStiming == 503000)
	{
		RESET_KEY_OFF();
		gps_on = 0x0;
		gps_net = 0x0;
		gps_heart_on = 0x0;
		gps_heart_time = 0x0;
		gps_heart_out = 0x0;
		gps_restart_flag = 0x0;
		GPStiming--;
	}	
	else
	{
		GPStiming--;
	}
}

/*===========================================================================
* Delay_Second() => Decrements the Timing variable,1 second									* 
============================================================================*/
/**
  * @brief  Decrements the Timing variable,Reset GPS module.
  * @param  None
  * @retval None
  */
void Delay_Second(void)
{
	Delay_second_time = 1000;
  while(Delay_second_time != 0)
  {
  }
}

void systick_init(void)
{
	if(SysTick_Config(SystemCoreClock / 1000))
  {
    /* Capture error */ 
		Usart_SendString(DEBUG_USARTx,"SysTick_Config Error\n");
    while (1);
  }
}

