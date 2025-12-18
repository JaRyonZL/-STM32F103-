#ifndef __TRAFFICLED_H
#define __TRAFFICLED_H

#include "gpio.h"

void TrafficLight_Init(void);
void TrafficLight_SN_Green(void);
void TrafficLight_SN_Yallow(void);  
void TrafficLight_EW_Green(void);
void TrafficLight_EW_Yallow(void);
void Traffic_EW_RED(void);
void Traffic_SN_RED(void);
void TrafficLight_All_Red(void);

#endif // !__TRAFFICLED_H
