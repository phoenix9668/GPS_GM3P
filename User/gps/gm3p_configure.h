#ifndef __GM3P_CONFIGURE_H
#define	__GM3P_CONFIGURE_H

#include "stm32f10x.h"

/* Private function prototypes -----------------------------------------------*/
void GM3P_INIT(void);
void Get_LBS_INFO(void);
void Get_GPS_INFO(void);
uint8_t Configure_GPS_ON(void);
uint8_t Configure_GPS_Send_to_COM(void);
uint8_t Configure_GPS_Send_to_NET(void);
uint8_t Configure_GPS_Heart_ON(void);
uint8_t Set_GPS_Heart_Time(void);
uint8_t Configure_GPS_Heart_Out(void);

#endif /* __GM3P_CONFIGURE_H */
