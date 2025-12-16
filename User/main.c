/*
 * @Descripttion:
 * @Author: JaRyon
 * @version:
 * @Date: 2025-12-16 12:55:42
 */
#include "stm32f10x.h"
#include "Delay.h"
#include "trafficLed.h"
#include "seg.h"

int main(void)
{
	// // 交通灯测试
	// TrafficLight_Init();

	// 数码管测试
	Segment_Init();
	uint8_t i = 0;
	while (1)
	{
		// // 南北向绿灯亮5秒
		// TrafficLight_SN_Green();
		// Delay_s(500);
		// // 南北向黄灯亮2秒
		// TrafficLight_SN_Yallow();
		// Delay_s(200);
		// // 东西向绿灯亮5秒
		// TrafficLight_EW_Green();
		// Delay_s(500);
		// // 东西向黄灯亮2秒
		// TrafficLight_EW_Yallow();
		// Delay_s(200);

		// 数码管显示测试
		i = i % 100;
		Segment_Display_Number(i, 99 - i);

		Delay_s(100); // 显示1s
		i++;
	}
}
