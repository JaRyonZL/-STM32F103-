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
	// 交通灯初始化
	App_Traffic_Init();

    while(1)
    {
		App_Traffic_Normal();
	}
}

