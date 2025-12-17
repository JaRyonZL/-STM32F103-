/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-16 15:23:07
 */
/*
 * @Descripttion:
 * @Author: JaRyon
 * @version:
 * @Date: 2025-12-16 15:23:07
 */
#include "trafficLed.h"
#include "config.h"

#define LED_ON(GPIO_PORT, GPIO_PIN)   GPIO_ResetPin(GPIO_PORT, GPIO_PIN)
#define LED_OFF(GPIO_PORT, GPIO_PIN)  GPIO_SetPin(GPIO_PORT, GPIO_PIN)


/**
 * @brief      关闭所有交通灯
 * @param      
 * @return     
 * @example    
 * @attention  
 */
static void TrafficLight_AllOff(void)
{
    LED_OFF(SN_PORT, SN_RED_PIN);
    LED_OFF(SN_PORT, SN_GREEN_PIN);
    LED_OFF(SN_PORT, SN_YALLOW_PIN);

    LED_OFF(EW_PORT, EW_RED_PIN);
    LED_OFF(EW_PORT, EW_GREEN_PIN);
    LED_OFF(EW_PORT, EW_YALLOW_PIN);
}


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
    TrafficLight_AllOff();
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
    // 关闭交通灯
    TrafficLight_AllOff();
    // 南北向绿灯亮，东西向红灯亮
    LED_ON(SN_PORT, SN_GREEN_PIN);
    LED_ON(EW_PORT, EW_RED_PIN);
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
    // 关闭交通灯
    TrafficLight_AllOff();
    // 南北向黄灯亮，东西向红灯亮
    LED_ON(SN_PORT, SN_YALLOW_PIN);
    LED_ON(EW_PORT, EW_RED_PIN);
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
    // 关闭交通灯
    TrafficLight_AllOff();
    // 东西向绿灯亮，南北向红灯亮
    LED_ON(EW_PORT, EW_GREEN_PIN);
    LED_ON(SN_PORT, SN_RED_PIN);
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
    // 关闭交通灯
    TrafficLight_AllOff();
    // 东西向黄灯亮，南北向红灯亮
    LED_ON(EW_PORT, EW_YALLOW_PIN);
    LED_ON(SN_PORT, SN_RED_PIN);
}

/**
 * @brief      交通灯全部红灯
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void TrafficLight_All_Red(void)
{
    // 关闭交通灯
    TrafficLight_AllOff();
    // 南北向红灯亮，东西向红灯亮
    LED_ON(SN_PORT, SN_RED_PIN);
    LED_ON(EW_PORT, EW_RED_PIN);
}

/**
 * @brief      东西方向黄灯闪烁
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void TrafficLight_EW_YellowBlink(void)
{
    static uint8_t state = 1;
    // 关闭交通灯
    TrafficLight_AllOff();
    if (state == 0)
    {
        LED_ON(EW_PORT, EW_YALLOW_PIN);
        state = 1;
    }
    else
    {
        LED_OFF(EW_PORT, EW_YALLOW_PIN);
        state = 0;
    }
    LED_ON(SN_PORT, SN_RED_PIN);
}

/**
 * @brief      南北方向黄灯闪烁
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void TrafficLight_SN_YellowBlink(void)
{
    static uint8_t state = 1;
    // 关闭交通灯
    TrafficLight_AllOff();
    if (state == 0)
    {
        LED_ON(SN_PORT, SN_YALLOW_PIN);
        state = 1;
    }
    else
    {
        LED_OFF(SN_PORT, SN_YALLOW_PIN);
        state = 0;
    }
    LED_ON(EW_PORT, EW_RED_PIN);
}

