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

ErrorStatus HSEStartUpStatus;
__IO uint32_t GPStiming = 0;
static __IO uint32_t TimingDelay;
extern __IO uint8_t gps_restart_flag;
extern __IO uint8_t gps_on;
extern __IO uint8_t gps_net;
extern __IO uint8_t gps_heart_on;
extern __IO uint8_t gps_heart_time;
extern __IO uint8_t gps_heart_out;
extern __IO uint32_t TimeDisplay;
extern __IO uint32_t EnterSTOPMode;
extern __IO uint8_t MainState;
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
	if (GPStiming == 0)//10mins
	{
		GPStiming = 6000;
	}
	else if (GPStiming == 5990)
	{
		RESET_KEY_ON();
		CHARGE_ON();
		GPStiming--;
	}
	else if (GPStiming == 5980)
	{
		POWER_KEY_ON();
		GPStiming--;
	}
	else if (GPStiming == 5880)
	{
		gps_restart_flag = 1;
		printf("GPS Module Restarting\n");
		GPStiming--;
	}
	else if (GPStiming == 5780)
	{
		/* Enable time update */
    TimeDisplay = 1;
		GPStiming--;
	}
	else if (GPStiming == 5080)
	{
		printf("GPS+GPRS module turn off\r\n");
		printf("...3...\r\n");
		GPStiming--;
	}
	else if (GPStiming == 5070)
	{
		printf("...2...\r\n");
		GPStiming--;
	}
	else if (GPStiming == 5060)
	{
		printf("...1...\r\n");
		GPStiming--;
	}
	else if (GPStiming == 5040)
	{
		CHARGE_OFF();
		POWER_KEY_OFF();
		gps_restart_flag = 0x0;
		GPStiming--;
	}
	else if (GPStiming == 5030)
	{
		if(MainState == 1)
		{
			RESET_KEY_OFF();
			gps_on = 0x0;
			gps_net = 0x0;
			gps_heart_on = 0x0;
			gps_heart_time = 0x0;
			gps_heart_out = 0x0;
			EnterSTOPMode = 1;
			printf("EnterSTOPMode = %x ",EnterSTOPMode);
			SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
		}
	}
	else{
		GPStiming--;
	}
}

/*===========================================================================
* Delay_Second() => Decrements the Timing variable,1 second									* 
============================================================================*/
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void SysTickDelay(uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

/**
  * @brief  Configures the SysTick to generate an interrupt each 100 millisecond.
  * @param  None
  * @retval None
  */
void SysTick_Configuration(void)
{
  /* Setup SysTick Timer for 100 msec interrupts  */
  if (SysTick_Config(SystemCoreClock / 10))
  { 
    /* Capture error */ 
//		Usart_SendString(DEBUG_USARTx,"SysTick_Config Error\n");
    while (1);
  }
  /* Set SysTick Priority to 3,3 */
  NVIC_SetPriority(SysTick_IRQn, 0x0F);
}

/**
  * @brief  Configures system clock after wake-up from STOP: enable HSE, PLL
  *         and select PLL as system clock source.
  * @param  None
  * @retval None
  */
void SYSCLKConfig_STOP(void)
{
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {

#ifdef STM32F10X_CL
    /* Enable PLL2 */ 
    RCC_PLL2Cmd(ENABLE);

    /* Wait till PLL2 is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
    {
    }

#endif

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

