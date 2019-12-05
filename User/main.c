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


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t i;
uint8_t PCCommand[PCCOMMAND_LENGTH] = {0};	// 接收上位机命令数组
extern uint8_t gps_on;
extern uint8_t gps_net;
extern uint8_t gps_heart_on;
extern uint8_t gps_heart_time;
extern uint8_t gps_heart_out;
extern uint8_t gps_restart_flag;
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
	USART_Config();
	systick_init();
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
			if(gps_on == 0x1 && gps_net == 0x1 && gps_heart_on == 0x1 && gps_heart_out == 0x1)
			{
				printf("GPS+GPRS module ready\r\n");
				for (i=0; i<PCCOMMAND_LENGTH; i++) //clear array
					{PCCommand[i] = 0;}
				Usart_RecArray(DEBUG_USARTx, PCCommand);
				if(PCCommand[0] == 0xAB && PCCommand[1] == 0xCD && PCCommand[2] == 0x4F && PCCommand[3] == 0x4B)
				{
					printf("GPS+GPRS module will turn off in three seconds\r\n");
					printf("...3...\r\n");
					Delay_Second();
					printf("...2...\r\n");
					Delay_Second();
					printf("...1...\r\n");
					Delay_Second();
					
					POWER_KEY_OFF();
					Delay_Second();
					Delay_Second();
					RESET_KEY_OFF();
					gps_on = 0x0;
					gps_net = 0x0;
					gps_heart_on = 0x0;
					gps_heart_time = 0x0;
					gps_heart_out = 0x0;
					gps_restart_flag = 0x0;
				}
			}
			else{
				GM3P_INIT();
			}
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
