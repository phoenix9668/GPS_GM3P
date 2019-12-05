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

uint8_t gps_on;					//GPS����ָʾ
uint8_t gps_net;				//GPS����ΪNET����ָʾ
uint8_t gps_heart_on;		//GPS����������ָʾ
uint8_t gps_heart_time; //GPS������ʱ������ָʾ
uint8_t gps_heart_out;	//GPS�������������ָʾ
extern void Delay(__IO uint32_t nCount);
uint8_t PCCommand1[PCCOMMAND_LENGTH] = {0};
uint8_t PCCommand2[PCCOMMAND_LENGTH] = {0};

/*===========================================================================
* GM3P_INIT() => GM3Pģ���ʼ��																							* 
============================================================================*/
void GM3P_INIT(void)
{
		Delay(0xFFFFF);
		if(Configure_GPS_ON() == 0x1 && gps_on == 0x0)
		{
			gps_on = 0x1;
			printf("GPS ON\r\n");
		}
		Delay(0x7FFFF);
		if(Configure_GPS_Send_to_NET() == 0x1 && gps_net == 0x0)
		{
			gps_net = 0x1;
			printf("GPS send to NET\r\n");
		}
		Delay(0x7FFFF);
		if(Set_GPS_Heart_Time() == 0x1 && gps_heart_time == 0x0)
		{
			gps_heart_time = 0x1;
			printf("GPS heart package TIME SET\r\n");
		}
		Delay(0x7FFFF);
		if(Configure_GPS_Heart_Out() == 0x1 && gps_heart_out == 0x0)
		{
			gps_heart_out = 0x1;
			printf("GPS heart package OUT SET\r\n");
		}
		Delay(0x7FFFF);
		if(Configure_GPS_Heart_ON() == 0x1 && gps_heart_on == 0x0)
		{
			gps_heart_on = 0x1;
			printf("GPS heart package ON\r\n");
		}
		Delay(0x7FFFF);
}

/*===========================================================================
* Get_LBS_INFO() => ��ȡGM3Pģ���LSB����																		* 
============================================================================*/
void Get_LBS_INFO(void)
{
	uint8_t i=0;
	
	for (i=0; i<PCCOMMAND_LENGTH; i++) //clear array
	{
		PCCommand1[i] = 0;
		PCCommand2[i] = 0;
	}
	Usart_SendString(DEBUG_USARTx,"usr.cn#AT+LBS\r");//��ȡ��վ��λ��Ϣ
	Usart_RecArray(DEBUG_USARTx, PCCommand1);
	Usart_RecArray(DEBUG_USARTx, PCCommand2);
	for(i=0; i<PCCOMMAND_LENGTH; i++)//for test
	{
		printf("%x ",PCCommand1[i]);
	}
	printf("\n");
	for(i=0; i<PCCOMMAND_LENGTH; i++)//for test
	{
		printf("%x ",PCCommand2[i]);
	}
	printf("\n");
}

/*===========================================================================
* Get_GPS_INFO() => ��ȡGM3Pģ���GPS��λ��Ϣ																* 
============================================================================*/
void Get_GPS_INFO(void)
{
	uint8_t i=0;
	
	for (i=0; i<PCCOMMAND_LENGTH; i++) //clear array
	{
		PCCommand1[i] = 0;
		PCCommand2[i] = 0;
	}

	Usart_SendString(DEBUG_USARTx,"usr.cn#AT+GPSDT\r");//��ȡGPS��λ��Ϣ
	Usart_RecArray(DEBUG_USARTx, PCCommand1);
	Usart_RecArray(DEBUG_USARTx, PCCommand2);
	for(i=0; i<PCCOMMAND_LENGTH; i++)//for test
	{
		printf("%x ",PCCommand1[i]);
	}
	printf("\n");
	for(i=0; i<PCCOMMAND_LENGTH; i++)//for test
	{
		printf("%x ",PCCommand2[i]);
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
	
	for (i=0; i<PCCOMMAND_LENGTH; i++) //clear array
	{
		PCCommand1[i] = 0;
		PCCommand2[i] = 0;
	}
	Usart_SendString(DEBUG_USARTx,"usr.cn#AT+GPS=1\r");//����GPS
	Usart_RecArray(DEBUG_USARTx, PCCommand1);
	Usart_RecArray(DEBUG_USARTx, PCCommand2);
	if(PCCommand2[0]==0x2b && PCCommand2[1]==0x47 && PCCommand2[2]==0x50 
		&& PCCommand2[3]==0x53 && PCCommand2[4]==0x3a && PCCommand2[5]==0x20 && PCCommand2[6]==0x31
		&& PCCommand2[7]==0xd && PCCommand2[8]==0xa)
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
* �ظ��ڶ���+GPS: 1,ASCIIΪ4f 4b d a																				*
============================================================================*/
uint8_t Configure_GPS_Send_to_COM(void)
{
	uint8_t i=0;
	
	for (i=0; i<PCCOMMAND_LENGTH; i++) //clear array
	{
		PCCommand1[i] = 0;
		PCCommand2[i] = 0;
	}
	Usart_SendString(DEBUG_USARTx,"usr.cn#AT+GPSTP=COM\r");//����GPS��λ��Ϣ���ͷ�ʽΪCOM
	Usart_RecArray(DEBUG_USARTx, PCCommand1);
	Usart_RecArray(DEBUG_USARTx, PCCommand2);
	if(PCCommand2[0]==0x4f && PCCommand2[1]==0x4b && PCCommand2[2]==0xd && PCCommand2[3]==0xa)
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
* �ظ��ڶ���+GPS: 1,ASCIIΪ4f 4b d a																				*
============================================================================*/
uint8_t Configure_GPS_Send_to_NET(void)
{
	uint8_t i=0;
	
	for (i=0; i<PCCOMMAND_LENGTH; i++) //clear array
	{
		PCCommand1[i] = 0;
		PCCommand2[i] = 0;
	}
	Usart_SendString(DEBUG_USARTx,"usr.cn#AT+GPSTP=NET\r");//����GPS��λ��Ϣ���ͷ�ʽΪNET
	Usart_RecArray(DEBUG_USARTx, PCCommand1);
	Usart_RecArray(DEBUG_USARTx, PCCommand2);
	if(PCCommand2[0]==0x4f && PCCommand2[1]==0x4b && PCCommand2[2]==0xd && PCCommand2[3]==0xa)
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
* �ظ��ڶ���+GPS: 1,ASCIIΪ4f 4b d a																				*
============================================================================*/
uint8_t Configure_GPS_Heart_ON(void)
{
	uint8_t i=0;
	
	for (i=0; i<PCCOMMAND_LENGTH; i++) //clear array
	{
		PCCommand1[i] = 0;
		PCCommand2[i] = 0;
	}
	Usart_SendString(DEBUG_USARTx,"usr.cn#AT+GPSEN=ON\r");//����GPS������
	Usart_RecArray(DEBUG_USARTx, PCCommand1);
	Usart_RecArray(DEBUG_USARTx, PCCommand2);
	if(PCCommand2[0]==0x4f && PCCommand2[1]==0x4b && PCCommand2[2]==0xd && PCCommand2[3]==0xa)
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
* �ظ��ڶ���+GPS: 1,ASCIIΪ4f 4b d a																				*
============================================================================*/
uint8_t Set_GPS_Heart_Time(void)
{
	uint8_t i=0;
	
	for (i=0; i<PCCOMMAND_LENGTH; i++) //clear array
	{
		PCCommand1[i] = 0;
		PCCommand2[i] = 0;
	}
	Usart_SendString(DEBUG_USARTx,"usr.cn#AT+GPSTM=10\r");//����GPS������ʱ����Ϊ10��
	Usart_RecArray(DEBUG_USARTx, PCCommand1);
	Usart_RecArray(DEBUG_USARTx, PCCommand2);
	if(PCCommand1[0]==0x75 && PCCommand1[1]==0x73 && PCCommand1[2]==0x72 && PCCommand1[3]==0x2e 
		&& PCCommand1[4]==0x63 && PCCommand1[5]==0x6e && PCCommand1[6]==0x23 && PCCommand1[7]==0xd 
		&& PCCommand1[8]==0xa && PCCommand2[0]==0x4f && PCCommand2[1]==0x4b && PCCommand2[2]==0xd && PCCommand2[3]==0xa)
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
* �ظ��ڶ���+GPS: 1,ASCIIΪ4f 4b d a																				*
============================================================================*/
uint8_t Configure_GPS_Heart_Out(void)
{
	uint8_t i=0;
	
	for (i=0; i<PCCOMMAND_LENGTH; i++) //clear array
	{
		PCCommand1[i] = 0;
		PCCommand2[i] = 0;
	}
	Usart_SendString(DEBUG_USARTx,"usr.cn#AT+GPSOUT=1,1,1,1,1\r");//����GPS����������
	Usart_RecArray(DEBUG_USARTx, PCCommand1);
	Usart_RecArray(DEBUG_USARTx, PCCommand2);
	if(PCCommand2[0]==0x4f && PCCommand2[1]==0x4b && PCCommand2[2]==0xd && PCCommand2[3]==0xa)
	{
		return 0x1;
	}
	else
	{
		return 0x0;
	}
}
