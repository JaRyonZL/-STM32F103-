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
#include "config.h"

int main(void)
{
	// // 交通灯测试
	// TrafficLight_Init();

	// 数码管测试
	Segment_Init();

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

		Segment_Display_Number(12, 34);
	}
}
