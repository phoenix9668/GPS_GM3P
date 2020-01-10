#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f10x.h"

// define gpio
#define CHARGE_GPIO_PIN						GPIO_Pin_15
#define	CHARGE_GPIO_PORT					GPIOB
#define	CHARGE_GPIO_CLK        		RCC_APB2Periph_GPIOB

#define POWER_KEY_GPIO_PIN				GPIO_Pin_8
#define	POWER_KEY_GPIO_PORT				GPIOB
#define	POWER_KEY_GPIO_CLK        RCC_APB2Periph_GPIOB

#define ADC_GPIO_PIN							GPIO_Pin_1
#define	ADC_GPIO_PORT							GPIOB
#define	ADC_GPIO_CLK        			RCC_APB2Periph_GPIOB

#define Reload_GPIO_PIN						GPIO_Pin_3
#define	Reload_GPIO_PORT					GPIOB
#define	Reload_GPIO_CLK        		RCC_APB2Periph_GPIOB

#define wake_up_GPIO_PIN					GPIO_Pin_4
#define	wake_up_GPIO_PORT					GPIOB
#define	wake_up_GPIO_CLK       		RCC_APB2Periph_GPIOB

#define RESET_GPIO_PIN						GPIO_Pin_5
#define	RESET_GPIO_PORT						GPIOB
#define	RESET_GPIO_CLK       			RCC_APB2Periph_GPIOB

// operate gpio
#define CHARGE_ON()								GPIO_ResetBits(CHARGE_GPIO_PORT,CHARGE_GPIO_PIN)
#define CHARGE_OFF()    					GPIO_SetBits(CHARGE_GPIO_PORT,CHARGE_GPIO_PIN)
#define CHARGE_TOG()   						GPIO_ToggleBits(CHARGE_GPIO_PORT,CHARGE_GPIO_PIN)

#define POWER_KEY_ON()						GPIO_ResetBits(POWER_KEY_GPIO_PORT,POWER_KEY_GPIO_PIN)
#define POWER_KEY_OFF()    				GPIO_SetBits(POWER_KEY_GPIO_PORT,POWER_KEY_GPIO_PIN)
#define POWER_KEY_TOG()   				GPIO_ToggleBits(POWER_KEY_GPIO_PORT,POWER_KEY_GPIO_PIN)

#define ADC_V_OFF()								GPIO_ResetBits(ADC_GPIO_PORT,ADC_GPIO_PIN)
#define ADC_V_ON()    						GPIO_SetBits(ADC_GPIO_PORT,ADC_GPIO_PIN)
#define ADC_V_TOG()   						GPIO_ToggleBits(ADC_GPIO_PORT,ADC_GPIO_PIN)

#define Reload_KEY_OFF()					GPIO_ResetBits(Reload_GPIO_PORT,Reload_GPIO_PIN)
#define Reload_KEY_ON()    				GPIO_SetBits(Reload_GPIO_PORT,Reload_GPIO_PIN)
#define Reload_KEY_TOG()   				GPIO_ToggleBits(Reload_GPIO_PORT,Reload_GPIO_PIN)

#define wake_up_KEY_OFF()					GPIO_ResetBits(wake_up_GPIO_PORT,wake_up_GPIO_PIN)
#define wake_up_KEY_ON()    			GPIO_SetBits(wake_up_GPIO_PORT,wake_up_GPIO_PIN)
#define wake_up_KEY_TOG()   			GPIO_ToggleBits(wake_up_GPIO_PORT,wake_up_GPIO_PIN)

#define RESET_KEY_OFF()						GPIO_ResetBits(RESET_GPIO_PORT,RESET_GPIO_PIN)
#define RESET_KEY_ON()    				GPIO_SetBits(RESET_GPIO_PORT,RESET_GPIO_PIN)
#define RESET_KEY_TOG()   				GPIO_ToggleBits(RESET_GPIO_PORT,RESET_GPIO_PIN)

void GPIO_Config(void);

#endif /* __GPIO_H */
