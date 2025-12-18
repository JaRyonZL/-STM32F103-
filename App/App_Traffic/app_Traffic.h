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
#include "key.h"

typedef enum   // 交通灯状态定义 
{
    TL_SN_GREEN,   // 南北绿灯
    TL_SN_YELLOW,  // 南北黄灯
    TL_EW_GREEN,   // 东西绿灯
    TL_EW_YELLOW,  // 东西黄灯
    TL_ALL_RED     // 全红
} TrafficLightState;

typedef enum   // 交通灯模式定义
{
    TRAFFIC_MODE_NORMAL = 0,   // 正常自动
    TRAFFIC_MODE_ALL_RED,      // 全红
    TRAFFIC_MODE_YELLOW_BLINK, // 黄闪
    TRAFFIC_MODE_SINGLE_RED    // 南北/东西禁止
} TrafficMode;

extern uint8_t snTimer;
extern uint8_t ewTimer;
extern uint8_t secFlag;
extern uint8_t halfFlag;

extern TrafficLightState TL_CurrState;
extern TrafficMode T_CurrMode;


void App_Traffic_Init(void);
void App_Traffic_Tick(void);
void App_TrafficMode_Switch(KEY_NUM key);
void App_Traffic_ModeRun(void);

#endif // !__APP_TRAFFIC_H
