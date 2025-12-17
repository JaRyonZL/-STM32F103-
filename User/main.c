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




