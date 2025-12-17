/*
 * @Descripttion:
 * @Author: JaRyon
 * @version:
 * @Date: 2025-12-16 12:55:42
 */
#include "stm32f10x.h"
#include "app_Traffic.h"
#include "tim2.h"
#include "Delay.h"


int main(void)
{
    // 初始化
    TIM2_Init();           // 1秒定时器
    TrafficLight_Init();   // LED 初始化
    Segment_Init();        // 数码管初始化

    // 初始状态 - 四向红灯
    TrafficLight_All_Red();
    snTimer = 0;
    ewTimer = 0;
    TrafficLightState TL_CurrState = TL_ALL_RED;
	TrafficLight_SetState(TL_CurrState);

    // 延时1秒显示全红，然后切换到南北绿
    uint32_t delayCount = TIM2_GetTick();
	while(TIM2_GetTick() - delayCount < 111 * 3) // 1秒延时
	{}
    TL_CurrState = TL_SN_GREEN;
    snTimer = 30;
    ewTimer = 0;
    TrafficLight_SetState(TL_CurrState);

    while(1)
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
                    ewTimer = 0;
                    if(snTimer == 0)
                    {
                        TL_CurrState = TL_SN_YELLOW;
                        snTimer = 3;              // 南北黄灯 3 秒
                        TrafficLight_SetState(TL_CurrState);
                    }
                    break;

                case TL_SN_YELLOW:
                    if(snTimer > 0) snTimer--;
                    ewTimer = 0;
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
                    snTimer = 0;
                    if(ewTimer == 0)
                    {
                        TL_CurrState = TL_EW_YELLOW;
                        ewTimer = 3;              // 东西黄灯 3 秒
                        TrafficLight_SetState(TL_CurrState);
                    }
                    break;

                case TL_EW_YELLOW:
                    if(ewTimer > 0) ewTimer--;
                    snTimer = 0;
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
}

