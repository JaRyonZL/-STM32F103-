/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-16 12:55:42
 */
#include "stm32f10x.h"
#include "Delay.h"
#include "trafficLed.h"

int main(void)
{
	// 交通灯测试
	TrafficLight_Init();

	while(1)
	{
		// 南北向绿灯亮5秒
		TrafficLight_SN_Green();
		Delay_s(5);
		// 南北向黄灯亮2秒
		TrafficLight_SN_Yallow();
		Delay_s(2);
		// 东西向绿灯亮5秒
		TrafficLight_EW_Green();
		Delay_s(5);
		// 东西向黄灯亮2秒
		TrafficLight_EW_Yallow();
		Delay_s(2);
	}
}

