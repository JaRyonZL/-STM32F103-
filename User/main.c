/*
 * @Descripttion:
 * @Author: JaRyon
 * @version:
 * @Date: 2025-12-16 12:55:42
 */
#include "stm32f10x.h"
#include "Delay.h"
#include "app_Traffic.h"
#include "config.h"
#include "tim2.h"

int main(void)
{
	TIM2_Init();
	TrafficLight_Init();
	Segment_Init();

	// 设置交通灯初始状态 - 南北绿灯
	TrafficLightState TL_CurrState = TL_SN_GREEN;

	while (1)
	{
		// 更新交通灯状态
		TrafficLight_SetState(TL_CurrState);
		// 显示倒计时
		Segment_Display_Number(ewTimer, snTimer);
		
		// 倒计时 1 秒触发
        if (timerFlag)
        {
            timerFlag = 0;

            if (TL_CurrState == TL_SN_GREEN || TL_CurrState == TL_SN_YELLOW)
            {
                if (snTimer > 0) snTimer--;
            }
            else if (TL_CurrState == TL_EW_GREEN || TL_CurrState == TL_EW_YELLOW)
            {
                if (ewTimer > 0) ewTimer--;
            }
			// 状态切换
            switch(TL_CurrState)
            {
                case TL_SN_GREEN:  if (snTimer == 0) { TL_CurrState = TL_SN_YELLOW; snTimer = 5; TrafficLight_SetState(TL_CurrState); } break;
                case TL_SN_YELLOW: if (snTimer == 0) { TL_CurrState = TL_EW_GREEN;  snTimer = 30; TrafficLight_SetState(TL_CurrState); } break;
                case TL_EW_GREEN:  if (ewTimer == 0) { TL_CurrState = TL_EW_YELLOW; ewTimer = 5; TrafficLight_SetState(TL_CurrState); } break;
                case TL_EW_YELLOW: if (ewTimer == 0) { TL_CurrState = TL_SN_GREEN; ewTimer = 30; TrafficLight_SetState(TL_CurrState); } break;
                default: break;
            }
        }

	}
}




