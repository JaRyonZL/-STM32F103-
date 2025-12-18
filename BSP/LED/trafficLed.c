/*
 * @Descripttion: 交通灯LED控制文件(.c)
 * @Author: JaRyon
 * @version: v1.0
 * @Date: 2025-12-16 15:23:07
 */
#include "trafficLed.h"
#include "config.h"

// 交通灯开关宏定义
#define LED_ON(GPIO_PORT, GPIO_PIN)   GPIO_ResetPin(GPIO_PORT, GPIO_PIN)
#define LED_OFF(GPIO_PORT, GPIO_PIN)  GPIO_SetPin(GPIO_PORT, GPIO_PIN)


/**
 * @brief      关闭所有交通灯
 * @param      void 无
 * @return     void
 * @example    TrafficLight_AllOff();
 * @attention  内部调用
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
 * @param      void 无
 * @return     void
 * @example    TrafficLight_Init(); 
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
 * @param      void 无
 * @return     void
 * @example    TrafficLight_SN_Green();
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
 * @param      void 无
 * @return     void
 * @example    TrafficLight_SN_Yallow();
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
 * @param      void 无
 * @return     void
 * @example    TrafficLight_EW_Green();
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
 * @param      void 无
 * @return     void
 * @example    TrafficLight_EW_Yallow();
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
 * @brief      仅南北向红灯
 * @param      void 无
 * @return     void   
 * @example    Traffic_SN_RED();
 * @attention  
 */
void Traffic_SN_RED(void)
{
    // 关闭交通灯
    TrafficLight_AllOff();  
    // 南北向红灯,东西向绿灯
    LED_ON(SN_PORT, SN_RED_PIN);  
    LED_ON(EW_PORT, EW_GREEN_PIN);
}   

/**
 * @brief      仅东西向红灯
 * @param      void 无
 * @return     void  
 * @example    Traffic_EW_RED();
 * @attention  
 */
void Traffic_EW_RED(void)
{
    // 关闭交通灯
    TrafficLight_AllOff();  
    // 东西向红灯，南北向绿灯
    LED_ON(EW_PORT, EW_RED_PIN);  
    LED_ON(SN_PORT, SN_GREEN_PIN);
}   

/**
 * @brief      交通灯全部红灯
 * @param      void 无
 * @return     void   
 * @example    TrafficLight_All_Red();
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
 * @brief      四向向黄灯闪烁
 * @param      void 无
 * @return     void  
 * @example    TrafficLight_YellowBlink();
 * @attention  用于夜间黄闪
 */
void TrafficLight_YellowBlink(void)
{
    static uint8_t state = 1;
    // 关闭交通灯
    TrafficLight_AllOff();
    if (state == 0)
    {
        LED_ON(SN_PORT, SN_YALLOW_PIN);
        LED_ON(SN_PORT, EW_YALLOW_PIN);
        state = 1;
    }
    else
    {
        LED_OFF(SN_PORT, SN_YALLOW_PIN);
        LED_OFF(SN_PORT, EW_YALLOW_PIN);
        state = 0;
    }
}
