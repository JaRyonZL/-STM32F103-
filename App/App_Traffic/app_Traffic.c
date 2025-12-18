/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-17 15:55:59
 */
#include "app_Traffic.h"
#include "tim2.h"

uint8_t snTimer = 30;
uint8_t ewTimer = 30;
uint8_t timerFlag = 0;

uint8_t yellowOn = 1; // 1=亮，0=灭
uint16_t yellowTick = 0; // 毫秒计数

TrafficLightState TL_CurrState = TL_ALL_RED;

/**
 * @brief      设置四向交通灯状态
 * @param      TrafficLightState_t state 待设置的状态
 * @return     
 * @example    
 * @attention  
 */
static void TrafficLight_SetState(TrafficLightState state)
{
    switch (state)
    {
        case TL_SN_GREEN:
            TrafficLight_SN_Green();
            Segment_Display_Number(0, 30); // 南北倒计时 30s，东西清零
            break;
        case TL_SN_YELLOW:
            TrafficLight_SN_Yallow();
            Segment_Display_Number(0, 3);  // 南北黄灯3s
            break;
        case TL_EW_GREEN:
            TrafficLight_EW_Green();
            Segment_Display_Number(30, 0); // 东西绿灯倒计时 30s
            break;
        case TL_EW_YELLOW:
            TrafficLight_EW_Yallow();
            Segment_Display_Number(3, 0);  // 东西黄灯3s
            break;
        case TL_ALL_RED:
            TrafficLight_All_Red();
            // Segment_Display_Number(0, 0);  // 全红清零
            Segment_Enable_EW(1);
            Segment_Enable_SN(1);
            Segment_Display_Digit(0); // 显示00
            break;
        default:
            break;
    }
}

/**
 * @brief      交通灯初始化
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void App_Traffic_Init(void)
{
    // 初始状态 - 四向红灯
    TrafficLight_All_Red();
    snTimer = 0;
    ewTimer = 0;
    
	TrafficLight_SetState(TL_CurrState);

    // 延时1秒显示全红，然后切换到南北绿
    uint32_t delayCount = TIM2_GetTick();
	while(TIM2_GetTick() - delayCount < 100 * 2) // 2秒延时
	{}
    TL_CurrState = TL_SN_GREEN;
    snTimer = 30;
    ewTimer = 0;
    TrafficLight_SetState(TL_CurrState);   
}

// 正常模式
void App_Traffic_Normal(void)
{
    // 动态刷新数码管
    Segment_Display_Number(ewTimer, snTimer);

    // 1秒定时器触发倒计时
    if(timerFlag)
    {
        timerFlag = 0;

        switch(TL_CurrState)
        {
            case TL_SN_GREEN:
                if(snTimer > 0) snTimer--;
                // 红灯方向在绿灯最后2s时开始倒计时
                if(snTimer == 3)	ewTimer = 7;
                if(ewTimer > 0) 	ewTimer--;

                if(snTimer == 0)
                {
                    TL_CurrState = TL_SN_YELLOW;
                    snTimer = 3;              // 南北黄灯 3 秒
                    TrafficLight_SetState(TL_CurrState);
                }
                break;

            case TL_SN_YELLOW:
                if(snTimer > 0) 	snTimer--;
                if(ewTimer > 0) 	ewTimer--;
                if(snTimer == 0)
                {
                    TL_CurrState = TL_EW_GREEN;
                    ewTimer = 30;             // 东西绿灯 30 秒
                    snTimer = 0;
                    TrafficLight_SetState(TL_CurrState);
                }
                break;

            case TL_EW_GREEN:
                if(ewTimer > 0) ewTimer--;
                // 红灯方向在绿灯最后2s时开始倒计时
                if(ewTimer == 3)	snTimer = 7;
                if(snTimer > 0) 	snTimer--;

                if(ewTimer == 0)
                {
                    TL_CurrState = TL_EW_YELLOW;
                    ewTimer = 3;              // 东西黄灯 3 秒
                    TrafficLight_SetState(TL_CurrState);
                }
                break;

            case TL_EW_YELLOW:
                if(ewTimer > 0) ewTimer--;
                if(snTimer > 0) 	snTimer--;
                if(ewTimer == 0)
                {
                    TL_CurrState = TL_SN_GREEN;
                    snTimer = 30;
                    ewTimer = 0;
                    TrafficLight_SetState(TL_CurrState);
                }
                break;

            default:
                break;
        }

    }
}

// 由于proteus8.17中仿真时使用8MHz不会卡顿，所以实际1ms需要改成1/9ms
// 因此count计数也相应变为原来的1/9 即5s即5000变成5000/9约555 1s
/**
 * 5000 -> 556
 * 7000 -> 778
 * 12000 -> 1334
 * 14000 -> 1556
 * 1000 -> 111
 * 
 */
void TrafficLightSeg_Test(void)
{
	static uint32_t count = 0;
	count++;

	if (count <= 556)
	{
		// 南北向绿灯亮
		TrafficLight_SN_Green();
	}
	else if (count <= 778)
	{
		// 南北向黄灯亮
		TrafficLight_SN_Yallow();
	}
	else if (count <= 1334)
	{
		// 东西向绿灯亮
		TrafficLight_EW_Green();
	}
	else if (count <= 1556)
	{
		// 东西向黄灯亮
		TrafficLight_EW_Yallow();
	}
	else
	{
		count = 0;
	}

	// 数码管显示倒计时
	uint8_t snTime = 0;
	uint8_t ewTime = 0;
	if(count <= 556)
	{
		snTime = (778 - count) / 111;
		ewTime = 0;
	}
	else if(count <= 778)
	{
		snTime = (778 - count) / 111;
		ewTime = 0;
	}
	else if(count <= 1334)
	{
		snTime = 0;
		ewTime = (1556 - count) / 111;
	}
	else if(count <= 1556)
	{
		snTime = 0;
		ewTime = (1556 - count) / 111;
	}
	Segment_Display_Number(ewTime, snTime);

}
