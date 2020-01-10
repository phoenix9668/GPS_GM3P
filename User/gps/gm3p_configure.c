/**
  ******************************************************************************
  * @file    gm3p_configure.c
  * @version V1.0
  * @date    2019-11-28
  * @brief   ����gm3p��GPS����
  ******************************************************************************
  * @attention  phoenix
  ******************************************************************************
  */

#include "gm3p_configure.h"
#include "bsp_usart.h"
#include "bsp_tim.h"

__IO uint8_t gps_on;					//GPS����ָʾ
__IO uint8_t gps_net;				//GPS����ΪNET����ָʾ
__IO uint8_t gps_heart_on;		//GPS����������ָʾ
__IO uint8_t gps_heart_time; //GPS������ʱ������ָʾ
__IO uint8_t gps_heart_out;	//GPS�������������ָʾ
__IO uint8_t gps_restart_flag; //GPSģ��������־
extern void Delay(__IO uint32_t nCount);
extern uint8_t RxBuffer[];
extern __IO uint8_t RecState;
uint8_t RxBuffer1[RxBufferSize];
uint8_t RxBuffer2[RxBufferSize];

/*===========================================================================
* GM3P_INIT() => GM3Pģ���ʼ��																							* 
============================================================================*/
void GM3P_INIT(void)
{
		Delay(0xFFFFF);
//		SysTickDelay(20);
		if(gps_on == 0x0)
		{
			if(Configure_GPS_ON() == 0x1)
			{
				gps_on = 0x1;
				printf("GPS ON\r\n");
			}
		}
		Delay(0xFFFFF);
		if(gps_net == 0x0)
		{
			if(Configure_GPS_Send_to_NET() == 0x1)
			{
				gps_net = 0x1;
				printf("GPS send to NET\r\n");
			}
		}
		Delay(0xFFFFF);
		if(gps_heart_time == 0x0)
		{
			if(Set_GPS_Heart_Time() == 0x1)
			{
				gps_heart_time = 0x1;
				printf("GPS heart package TIME SET\r\n");
			}
		}
		Delay(0xFFFFF);
		if(gps_heart_out == 0x0)
		{
			if(Configure_GPS_Heart_Out() == 0x1)
			{
				gps_heart_out = 0x1;
				printf("GPS heart package OUT SET\r\n");
			}
		}
		Delay(0xFFFFF);
		if(gps_heart_on == 0x0)
		{
			if(Configure_GPS_Heart_ON() == 0x1)
			{
				gps_heart_on = 0x1;
				printf("GPS heart package ON\r\n");
			}
		}
		Delay(0xFFFFF);
}

/*===========================================================================
* Get_LBS_INFO() => ��ȡGM3Pģ���LSB����																		* 
============================================================================*/
void Get_LBS_INFO(void)
{
	uint8_t i=0;
	
	for (i=0; i<RxBufferSize; i++) //clear array
	{
		RxBuffer[i] = 0;
	}
	Usart_SendString(USARTy,"usr.cn#AT+LBS\r");//��ȡ��վ��λ��Ϣ
	USART_ITConfig(USARTy, USART_IT_IDLE, ENABLE);
	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
	while(RecState == 0)
	{}
	RecState = 0;
	for(i=0; i<RxBufferSize; i++)//for test
	{
		printf("%x ",RxBuffer[i]);
	}
	printf("\n");
}

/*===========================================================================
* Get_GPS_INFO() => ��ȡGM3Pģ���GPS��λ��Ϣ																* 
============================================================================*/
void Get_GPS_INFO(void)
{
	uint8_t i=0;
	
	for (i=0; i<RxBufferSize; i++) //clear array
	{
		RxBuffer[i] = 0;
	}
	Usart_SendString(USARTy,"usr.cn#AT+GPSDT\r");//��ȡGPS��λ��Ϣ
	USART_ITConfig(USARTy, USART_IT_IDLE, ENABLE);
	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
	while(RecState == 0)
	{}
	RecState = 0;
	for(i=0; i<RxBufferSize; i++)//for test
	{
		printf("%x ",RxBuffer[i]);
	}
	printf("\n");
}

/*===========================================================================
* Configure_GPS_ON() => ����GM3Pģ���GPS����																*
* �ظ���һ��usr.cn#,ASCIIΪ75 73 72 2e 63 6e 23 d a													*
* �ظ��ڶ���+GPS: 1,ASCIIΪ2b 47 50 53 3a 20 31 d a													*
============================================================================*/
uint8_t Configure_GPS_ON(void)
{
	uint8_t i=0;
	
	for (i=0; i<RxBufferSize; i++) //clear array
	{
		RxBuffer[i] = 0;
	}
	Usart_SendString(USARTy,"usr.cn#AT+GPS=1\r");//����GPS
//	USART_ITConfig(USARTy, USART_IT_IDLE, ENABLE);
//	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
//	while(RecState == 0)
//	{}
//	RecState = 0;
	Usart_RecArray(USARTy, RxBuffer1);
	Usart_RecArray(USARTy, RxBuffer2);
	if(RxBuffer2[0]==0x2b && RxBuffer2[1]==0x47 && RxBuffer2[2]==0x50 
		&& RxBuffer2[3]==0x53 && RxBuffer2[4]==0x3a && RxBuffer2[5]==0x20 && RxBuffer2[6]==0x31
		&& RxBuffer2[7]==0xd && RxBuffer2[8]==0xa)
//	if(RxBuffer[0]==0x75 && RxBuffer[1]==0x73 && RxBuffer[2]==0x72 
//		&& RxBuffer[3]==0x2e && RxBuffer[4]==0x63 && RxBuffer[5]==0x6e && RxBuffer[6]==0x23
//		&& RxBuffer[7]==0xd && RxBuffer[8]==0xa && RxBuffer[9]==0x2b && RxBuffer[10]==0x47 && RxBuffer[11]==0x50 
//		&& RxBuffer[12]==0x53 && RxBuffer[13]==0x3a && RxBuffer[14]==0x20 && RxBuffer[15]==0x31
//		&& RxBuffer[16]==0xd && RxBuffer[17]==0xa)
	{
		return 0x1;
	}
	else
	{
		return 0x0;
	}
}

/*===========================================================================
* Configure_GPS_Send_to_COM() => ����GM3Pģ���GPS��λ��Ϣ���ͷ�ʽΪCOM			*
* �ظ���һ��usr.cn#,ASCIIΪ75 73 72 2e 63 6e 23 d a													*
* �ظ��ڶ���OK,ASCIIΪ4f 4b d a																				*
============================================================================*/
uint8_t Configure_GPS_Send_to_COM(void)
{
	uint8_t i=0;
	
	for (i=0; i<RxBufferSize; i++) //clear array
	{
		RxBuffer[i] = 0;
	}
	Usart_SendString(USARTy,"usr.cn#AT+GPSTP=COM\r");//����GPS��λ��Ϣ���ͷ�ʽΪCOM
//	USART_ITConfig(USARTy, USART_IT_IDLE, ENABLE);
//	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
//	while(RecState == 0)
//	{}
//	RecState = 0;
	Usart_RecArray(USARTy, RxBuffer1);
	Usart_RecArray(USARTy, RxBuffer2);
	if(RxBuffer2[0]==0x4f && RxBuffer2[1]==0x4b && RxBuffer2[2]==0xd && RxBuffer2[3]==0xa)
//	if(RxBuffer[0]==0x75 && RxBuffer[1]==0x73 && RxBuffer[2]==0x72 
//		&& RxBuffer[3]==0x2e && RxBuffer[4]==0x63 && RxBuffer[5]==0x6e && RxBuffer[6]==0x23
//		&& RxBuffer[7]==0xd && RxBuffer[8]==0xa && RxBuffer[9]==0x4f && RxBuffer[10]==0x4b && RxBuffer[11]==0xd && RxBuffer[12]==0xa)
	{
		return 0x1;
	}
	else
	{
		return 0x0;
	}
}

/*===========================================================================
* Configure_GPS_Send_to_NET() => ����GM3Pģ���GPS��λ��Ϣ���ͷ�ʽΪNET			*
* �ظ���һ��usr.cn#,ASCIIΪ75 73 72 2e 63 6e 23 d a													*
* �ظ��ڶ���OK,ASCIIΪ4f 4b d a																				*
============================================================================*/
uint8_t Configure_GPS_Send_to_NET(void)
{
	uint8_t i=0;
	
	for (i=0; i<RxBufferSize; i++) //clear array
	{
		RxBuffer[i] = 0;
	}
	Usart_SendString(USARTy,"usr.cn#AT+GPSTP=NET\r");//����GPS��λ��Ϣ���ͷ�ʽΪNET
//	USART_ITConfig(USARTy, USART_IT_IDLE, ENABLE);
//	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
//	while(RecState == 0)
//	{}
//	RecState = 0;
	Usart_RecArray(USARTy, RxBuffer1);
	Usart_RecArray(USARTy, RxBuffer2);
	if(RxBuffer2[0]==0x4f && RxBuffer2[1]==0x4b && RxBuffer2[2]==0xd && RxBuffer2[3]==0xa)
//	if(RxBuffer[0]==0x75 && RxBuffer[1]==0x73 && RxBuffer[2]==0x72 
//		&& RxBuffer[3]==0x2e && RxBuffer[4]==0x63 && RxBuffer[5]==0x6e && RxBuffer[6]==0x23
//		&& RxBuffer[7]==0xd && RxBuffer[8]==0xa && RxBuffer[9]==0x4f && RxBuffer[10]==0x4b && RxBuffer[11]==0xd && RxBuffer[12]==0xa)
	{
		return 0x1;
	}
	else
	{
		return 0x0;
	}
}

/*===========================================================================
* Configure_GPS_Heart_ON() => ����GM3Pģ���GPS������												*
* �ظ���һ��usr.cn#,ASCIIΪ75 73 72 2e 63 6e 23 d a													*
* �ظ��ڶ���OK,ASCIIΪ4f 4b d a																				*
============================================================================*/
uint8_t Configure_GPS_Heart_ON(void)
{
	uint8_t i=0;
	
	for (i=0; i<RxBufferSize; i++) //clear array
	{
		RxBuffer[i] = 0;
	}
	Usart_SendString(USARTy,"usr.cn#AT+GPSEN=ON\r");//����GPS������
//	USART_ITConfig(USARTy, USART_IT_IDLE, ENABLE);
//	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
//	while(RecState == 0)
//	{}
//	RecState = 0;
	Usart_RecArray(USARTy, RxBuffer1);
	Usart_RecArray(USARTy, RxBuffer2);
	if(RxBuffer2[0]==0x4f && RxBuffer2[1]==0x4b && RxBuffer2[2]==0xd && RxBuffer2[3]==0xa)
//	if(RxBuffer[0]==0x75 && RxBuffer[1]==0x73 && RxBuffer[2]==0x72 
//		&& RxBuffer[3]==0x2e && RxBuffer[4]==0x63 && RxBuffer[5]==0x6e && RxBuffer[6]==0x23
//		&& RxBuffer[7]==0xd && RxBuffer[8]==0xa && RxBuffer[9]==0x4f && RxBuffer[10]==0x4b && RxBuffer[11]==0xd && RxBuffer[12]==0xa)
	{
		return 0x1;
	}
	else
	{
		return 0x0;
	}
}

/*===========================================================================
* Set_GPS_Heart_Time() => ����GPS������ʱ����Ϊ10��												*
* �ظ���һ��usr.cn#,ASCIIΪ75 73 72 2e 63 6e 23 d a													*
* �ظ��ڶ���OK,ASCIIΪ4f 4b d a																				*
============================================================================*/
uint8_t Set_GPS_Heart_Time(void)
{
	uint8_t i=0;
	
	for (i=0; i<RxBufferSize; i++) //clear array
	{
		RxBuffer[i] = 0;
	}
	Usart_SendString(USARTy,"usr.cn#AT+GPSTM=30\r");//����GPS������ʱ����Ϊ30��
//	USART_ITConfig(USARTy, USART_IT_IDLE, ENABLE);
//	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
//	while(RecState == 0)
//	{}
//	RecState = 0;
	Usart_RecArray(USARTy, RxBuffer1);
	Usart_RecArray(USARTy, RxBuffer2);
	if(RxBuffer2[0]==0x4f && RxBuffer2[1]==0x4b && RxBuffer2[2]==0xd && RxBuffer2[3]==0xa)
//	if(RxBuffer[0]==0x75 && RxBuffer[1]==0x73 && RxBuffer[2]==0x72 
//		&& RxBuffer[3]==0x2e && RxBuffer[4]==0x63 && RxBuffer[5]==0x6e && RxBuffer[6]==0x23
//		&& RxBuffer[7]==0xd && RxBuffer[8]==0xa && RxBuffer[9]==0x4f && RxBuffer[10]==0x4b && RxBuffer[11]==0xd && RxBuffer[12]==0xa)
	{
		return 0x1;
	}
	else
	{
		return 0x0;
	}
}

/*===========================================================================
* Configure_GPS_Heart_Out() => ����GM3Pģ���GPS����������									*
* �ظ���һ��usr.cn#,ASCIIΪ75 73 72 2e 63 6e 23 d a													*
* �ظ��ڶ���OK,ASCIIΪ4f 4b d a																				*
============================================================================*/
uint8_t Configure_GPS_Heart_Out(void)
{
	uint8_t i=0;
	
	for (i=0; i<RxBufferSize; i++) //clear array
	{
		RxBuffer[i] = 0;
	}
	Usart_SendString(USARTy,"usr.cn#AT+GPSOUT=1,1,1,1,1\r");//����GPS����������
//	USART_ITConfig(USARTy, USART_IT_IDLE, ENABLE);
//	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);
//	while(RecState == 0)
//	{}
//	RecState = 0;
	Usart_RecArray(USARTy, RxBuffer1);
	Usart_RecArray(USARTy, RxBuffer2);
	if(RxBuffer2[0]==0x4f && RxBuffer2[1]==0x4b && RxBuffer2[2]==0xd && RxBuffer2[3]==0xa)
//	if(RxBuffer[0]==0x75 && RxBuffer[1]==0x73 && RxBuffer[2]==0x72 
//		&& RxBuffer[3]==0x2e && RxBuffer[4]==0x63 && RxBuffer[5]==0x6e && RxBuffer[6]==0x23
//		&& RxBuffer[7]==0xd && RxBuffer[8]==0xa && RxBuffer[9]==0x4f && RxBuffer[10]==0x4b && RxBuffer[11]==0xd && RxBuffer[12]==0xa)
	{
		return 0x1;
	}
	else
	{
		return 0x0;
	}
}
