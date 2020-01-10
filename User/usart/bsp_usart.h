#ifndef __USART_H
#define	__USART_H


#include "stm32f10x.h"
#include <stdio.h>
#define RxBufferSize 21

#define USARTy                   USART1
#define USARTy_GPIO              GPIOA
#define USARTy_CLK               RCC_APB2Periph_USART1
#define USARTy_GPIO_CLK          RCC_APB2Periph_GPIOA
#define USARTy_RxPin             GPIO_Pin_10
#define USARTy_TxPin             GPIO_Pin_9
#define USARTy_IRQn              USART1_IRQn
#define USARTy_IRQHandler        USART1_IRQHandler
  
#define USARTz                   USART2
#define USARTz_GPIO              GPIOA
#define USARTz_CLK               RCC_APB1Periph_USART2
#define USARTz_GPIO_CLK          RCC_APB2Periph_GPIOA
#define USARTz_RxPin             GPIO_Pin_3
#define USARTz_TxPin             GPIO_Pin_2
#define USARTz_IRQn              USART2_IRQn
#define USARTz_IRQHandler        USART2_IRQHandler

void NVIC_USART_Configuration(void);
void USART_Config(void);
uint8_t USART_Scanf(uint32_t value);
void Usart_SendByte(USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString(USART_TypeDef * pUSARTx, char *str);
uint8_t Usart_RecByte(USART_TypeDef *pUSARTx);
void Usart_RecArray(USART_TypeDef *pUSARTx, uint8_t *arr);


#endif /* __USART_H */
