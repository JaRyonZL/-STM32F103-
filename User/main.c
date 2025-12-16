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
#include "tim2.h"

int main(void)
{
	TIM2_Init();
	// 交通灯测试
	TrafficLight_Init();
	// 数码管测试
	Segment_Init();

	while (1)
	{

	}
}

void TrafficLightSeg_Test(void)
{
	static uint32_t count = 0;
	count++;

	if (count <= 5000)
	{
		// 南北向绿灯亮
		TrafficLight_SN_Green();
	}
	else if (count <= 7000)
	{
		// 南北向黄灯亮
		TrafficLight_SN_Yallow();
	}
	else if (count <= 12000)
	{
		// 东西向绿灯亮
		TrafficLight_EW_Green();
	}
	else if (count <= 14000)
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
	if(count <= 5000)
	{
		snTime = (7000 - count) / 1000;
		ewTime = 0;
	}
	else if(count <= 7000)
	{
		snTime = (7000 - count) / 1000;
		ewTime = 0;
	}
	else if(count <= 12000)
	{
		snTime = 0;
		ewTime = (14000 - count) / 1000;
	}
	else if(count <= 14000)
	{
		snTime = 0;
		ewTime = (14000 - count) / 1000;
	}
	Segment_Display_Number(ewTime, snTime);

}

// TIM2中断处理程序
void TIM2_IRQHandler(void)
{
	// 清除中断标志位
	TIM2->SR &= ~TIM_SR_UIF;

	TrafficLightSeg_Test();

}
