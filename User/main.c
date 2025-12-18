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
	App_Traffic_Init();

	while (1)
	{
		// 获取按键键码
		KEY_NUM keyNum = Key_GetNum();
		// 模式控制-按键被按下时根据键码调整
		if(keyNum != NO_PRESSED)
		{
			App_TrafficMode_Switch(keyNum);
		}
		// 动态刷新数码管倒计时
		Segment_Display_Number(ewTimer, snTimer);
		// 1s定时处理
		if(timerFlag == 1)
		{
			timerFlag = 0;
			// "总指挥"-交通灯执行
			App_Traffic_ModeRun();
		}
		
	}
}
