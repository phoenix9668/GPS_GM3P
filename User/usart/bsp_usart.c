/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   调试用的printf串口，重定向printf到串口
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "bsp_usart.h"

uint8_t RxBuffer[RxBufferSize];
__IO uint8_t RxCounter = 0x00;
uint8_t NbrOfDataToRead = RxBufferSize;

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_USART_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTy_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO Configure
  * @param  None
  * @retval None
  */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(USARTy_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USARTy Clock */
  RCC_APB2PeriphClockCmd(USARTy_CLK, ENABLE);

  /* Configure USARTy Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USARTy_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(USARTy_GPIO, &GPIO_InitStructure);

  /* Configure USARTy Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USARTy_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USARTy_GPIO, &GPIO_InitStructure);
	
/* USARTy and USARTz configuration ------------------------------------------------------*/
  /* USARTy and USARTz configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USARTy */
  USART_Init(USARTy, &USART_InitStructure);
  
  /* Enable USARTy Receive and Transmit interrupts */
//  USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USARTy, USART_IT_TXE, ENABLE);

  /* Enable the USARTy */
  USART_Cmd(USARTy, ENABLE);
}


// 重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USARTy, (uint8_t) ch);

		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USARTy, USART_FLAG_TXE) == RESET);

		return (ch);
}

// 重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USARTy, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USARTy);
}

/**
  * @brief  Gets numeric values from the hyperterminal.
  * @param  None
  * @retval None
  */
uint8_t USART_Scanf(uint32_t value)
{
  uint32_t index = 0;
  uint32_t tmp[2] = {0, 0};

  while (index < 2)
  {
    /* Loop until RXNE = 1 */
    while (USART_GetFlagStatus(USARTy, USART_FLAG_RXNE) == RESET)
    {}
    tmp[index++] = (USART_ReceiveData(USARTy));
    if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
    {
      printf("\n\rPlease enter valid number between 0 and 9");
      index--;
    }
  }
  /* Calculate the Corresponding value */
  index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);
  /* Checks */
  if (index > value)
  {
    printf("\n\rPlease enter valid number between 0 and %d", value);
    return 0xFF;
  }
  return index;
}

/*****************  发送一个字符 **********************/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx, ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  发送字符串 **********************/
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte(pUSARTx, *(str + k));
      k++;
  } while(*(str+k) != '\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
  {}
}

//接收一个字节
uint8_t Usart_RecByte(USART_TypeDef *pUSARTx)
{
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_RXNE) == RESET);
	return (uint8_t)USART_ReceiveData(pUSARTx);
}

//接收数组
void Usart_RecArray(USART_TypeDef *pUSARTx, uint8_t *arr)
{
	unsigned int k;
  for(k=0;k<RxBufferSize;k++)
  {
			*(arr+k) = Usart_RecByte(pUSARTx);
			if(k>1)
			{
				if(*(arr+k-1) == 0x0d && *(arr+k) == 0x0a)
				{break;}
			}
  }
}

/*********************************************END OF FILE**********************/
