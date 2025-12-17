/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-17 15:56:11
 */
#ifndef __APP_TRAFFIC_H
#define __APP_TRAFFIC_H

#include "trafficLed.h"
#include "seg.h"

typedef enum 
{
    TL_SN_GREEN,   // 南北绿灯
    TL_SN_YELLOW,  // 南北黄灯
    TL_EW_GREEN,   // 东西绿灯
    TL_EW_YELLOW,  // 东西黄灯
    TL_ALL_RED     // 全红
} TrafficLightState;

extern uint8_t snTimer;
extern uint8_t ewTimer;
extern uint8_t timerFlag;
extern uint8_t yellowOn;
extern uint16_t yellowTick;

extern TrafficLightState TL_CurrState;

void App_Traffic_Init(void);
void App_Traffic_Normal(void);

void TrafficLightSeg_Test(void);

#endif // !__APP_TRAFFIC_H
