/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-16 15:23:07
 */
#include "trafficLed.h"
#include "config.h"

/**
 * @brief      南北东西向交通灯初始化
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void TrafficLight_Init(void)
{
    // 初始化
    GPIO_TrafficLight_Init();
    // 默认南北东西向红灯灭
    GPIO_SetPin(SN_PORT, SN_RED_PIN);
    GPIO_SetPin(SN_PORT, SN_RED_PIN);
    GPIO_SetPin(SN_PORT, SN_RED_PIN);
    GPIO_SetPin(EW_PORT, EW_RED_PIN);
    GPIO_SetPin(EW_PORT, EW_RED_PIN);
    GPIO_SetPin(EW_PORT, EW_RED_PIN);
    
}

/**
 * @brief      南北向绿灯
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void TrafficLight_SN_Green(void)
{
    // 南北向绿灯亮，东西向红灯亮
    GPIO_ResetPin(SN_PORT, SN_GREEN_PIN);
    GPIO_ResetPin(EW_PORT, EW_RED_PIN);
}

/**
 * @brief      南北向黄灯
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void TrafficLight_SN_Yallow(void)
{
    // 南北向黄灯亮，东西向红灯亮
    GPIO_ResetPin(SN_PORT, SN_YALLOW_PIN);
    GPIO_ResetPin(EW_PORT, EW_RED_PIN);
}

/**
 * @brief      东西向绿灯
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void TrafficLight_EW_Green(void)
{
    // 东西向绿灯亮，南北向红灯亮
    GPIO_ResetPin(EW_PORT, EW_GREEN_PIN);
    GPIO_ResetPin(SN_PORT, SN_RED_PIN);
}

/**
 * @brief      东西向黄灯
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void TrafficLight_EW_Yallow(void)
{
    // 东西向黄灯亮，南北向红灯亮
    GPIO_ResetPin(EW_PORT, EW_YALLOW_PIN);
    GPIO_ResetPin(SN_PORT, SN_RED_PIN);
}


