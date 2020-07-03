/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_gpio.h"
#include "gm3p_configure.h"
#include "bsp_tim.h"
#include "bsp_rtc.h"


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t i;
extern uint8_t RxBuffer[];
__IO uint32_t interval;
__IO uint32_t SysTickRestart = 0;
__IO uint32_t EnterSTOPMode = 0;
__IO uint8_t MainState = 0;
__IO uint8_t RecState = 0;
extern __IO uint8_t gps_on;
extern __IO uint8_t gps_net;
extern __IO uint8_t gps_heart_on;
extern __IO uint8_t gps_heart_time;
extern __IO uint8_t gps_heart_out;
extern __IO uint8_t gps_restart_flag;
extern __IO uint32_t Delay_second_time;
uint32_t Delay_time;
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */

  /* Initialize CHARGE, POWER_KEY, Reload, Reload, RESET and COM port(USART) available */
	GPIO_Config();
	NVIC_USART_Configuration();
	USART_Config();
	RTC_Alarm_Config();
	interval = 300;
	Interval_Init();
	SysTick_Configuration();
	gps_on = 0x0;
	gps_net = 0x0;
	gps_heart_on = 0x0;
	gps_heart_time = 0x0;
	gps_heart_out = 0x0;
	gps_restart_flag = 0x0;

  printf("\r\nGPS+GPRS module begin running\r\n");

  /* Infinite loop */
  while (1)
  {
		if(gps_restart_flag == 0x1)
		{
			MainState = 0;
			if(gps_on == 0x1 && gps_net == 0x1 && gps_heart_on == 0x1 && gps_heart_out == 0x1)
			{
				printf("GPS+GPRS module ready\r\n");
				for (i=0; i<RxBufferSize; i++) //clear array
					{RxBuffer[i] = 0;}
				USART_ITConfig(USARTy, USART_IT_IDLE, ENABLE);
				USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
				Delay_time = 0xFFFFF;
				while(RecState == 0 && Delay_time != 0)
				{
					Delay_time--;
				}
				if(RxBuffer[0] == 0xAB && RxBuffer[1] == 0xCD && RxBuffer[2] == 0x4F && RxBuffer[3] == 0x4B)
				{
					printf("GPS+GPRS module will turn off in three seconds\r\n");
					printf("...3...\r\n");
					SysTickDelay(10);
					printf("...2...\r\n");
					SysTickDelay(10);
					printf("...1...\r\n");
					SysTickDelay(10);
					
					POWER_KEY_OFF();
					SysTickDelay(10);
					SysTickDelay(10);
					RESET_KEY_OFF();
					gps_on = 0x0;
					gps_net = 0x0;
					gps_heart_on = 0x0;
					gps_heart_time = 0x0;
					gps_heart_out = 0x0;
					gps_restart_flag = 0x0;
				}
				RecState = 0;
			}
			else
			{
				GM3P_INIT();
			}
		}
		MainState = 1;
		Time_Show();
		Interval_Adjust();
		if(EnterSTOPMode == 1)
		{
			GPIO_STOP_Config();
			/* Disable the USARTy */
			USART_Cmd(USARTy, DISABLE);
			/* Request to enter STOP mode with regulator in low power mode*/
			PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
			/* Configures system clock after wake-up from STOP: enable HSE, PLL and select 
				 PLL as system clock source (HSE and PLL are disabled in STOP mode) */
			SYSCLKConfig_STOP();
			EnterSTOPMode = 0;
			GPIO_Config();
			/* Enable the USARTy */
			USART_Cmd(USARTy, ENABLE);
		}
		if(SysTickRestart == 1)
		{
			SysTick_Configuration();
			SysTickRestart = 0;
			printf("...Z...\r\n");
		}
  }
}

/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
