#include "bsp_gpio.h"   

 /**
  * @brief  control hardware
  * @param  none
  * @retval none
  */
void GPIO_Config(void)
{		
		GPIO_InitTypeDef GPIO_InitStructure;
	
    /* Enable GPIOB clock */
    RCC_APB2PeriphClockCmd(CHARGE_GPIO_CLK, ENABLE);
	
    // configure CHARGE gpio
    GPIO_InitStructure.GPIO_Pin = CHARGE_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CHARGE_GPIO_PORT, &GPIO_InitStructure);
	
	  // configure POWER_KEY gpio
    GPIO_InitStructure.GPIO_Pin = POWER_KEY_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(POWER_KEY_GPIO_PORT, &GPIO_InitStructure);

		// configure ADC_V gpio
    GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);
		
	  // configure Reload gpio
    GPIO_InitStructure.GPIO_Pin = Reload_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Reload_GPIO_PORT, &GPIO_InitStructure);
		
		// configure wake_up gpio
    GPIO_InitStructure.GPIO_Pin = wake_up_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(wake_up_GPIO_PORT, &GPIO_InitStructure);
		
		// configure RESET gpio
    GPIO_InitStructure.GPIO_Pin = RESET_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RESET_GPIO_PORT, &GPIO_InitStructure);
		
		// 打开所有硬件
		CHARGE_ON();
		POWER_KEY_OFF();
		Reload_KEY_ON();
		wake_up_KEY_ON();
		RESET_KEY_OFF();
}

/*********************************************END OF FILE**********************/
