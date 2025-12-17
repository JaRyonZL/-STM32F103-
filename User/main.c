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
#include "key.h"

int main(void)
{
	// 初始化
	TIM2_Init();		 // 1ms定时器
	TrafficLight_Init(); // LED 初始化
	Segment_Init();		 // 数码管初始化
	Key_Init();			 // 按键初始化
	// 交通灯初始化
	// App_Traffic_Init();
	
	while (1)
	{
		uint8_t keyNum = Key_GetNum();

		if (keyNum == KEY1)
		{
			TrafficLight_SN_Green();
		}
		if (keyNum == KEY2)
		{
			TrafficLight_SN_Yallow();
		}
		if (keyNum == KEY3)
		{
			TrafficLight_EW_Green();
		}
		if (keyNum == KEY4)
		{
			TrafficLight_EW_Yallow();
		}

		// App_Traffic_Normal();
	}
}
