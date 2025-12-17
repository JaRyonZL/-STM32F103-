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

// TIM2中断处理程序
void TIM2_IRQHandler(void)
{
	// 清除中断标志位
	TIM2->SR &= ~TIM_SR_UIF;

	TrafficLightSeg_Test();

}
