/*
 * @Descripttion: TIM2定时器配置文件(.c)
 * @Author: JaRyon
 * @version: v1.0
 * @Date: 2025-12-16 21:00:34
 */
#include "tim2.h"
#include "app_Traffic.h"
#include "key.h"

// TIM2进行1ms中断，记录计数次数 内部使用
static uint32_t Tick = 0;

/**
 * @brief      TIM2初始化
 * @param      void 无 
 * @return     void
 * @example    TIM2_Init();
 * @attention  
 */
void TIM2_Init(void)
{
    // 开启TIM2时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    // 72分频 1000重装载
    TIM2->PSC = 72 - 1;
    TIM2->ARR = 1000 - 1;
    // 向上计数
    TIM2->CR1 &= ~TIM_CR1_DIR;
    // 允许更新中断
    TIM2->DIER |= TIM_DIER_UIE;

    // NVIC中断优先级配置
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM2_IRQn, 2);
    NVIC_EnableIRQ(TIM2_IRQn);

    // 开启TIM2
    TIM2->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief      获取Tick数
 * @param      void 无 
 * @return     uint32_t 获取的滴答次数
 * @example    uint32_t TIM2_GetTick();
 * @attention  
 */
uint32_t TIM2_GetTick(void)
{   
    return Tick;
}


// TIM2中断处理程序
void TIM2_IRQHandler(void)
{
	// 清除中断标志位
	TIM2->SR &= ~TIM_SR_UIF;
    Tick++;

    App_Traffic_Tick(); // 交通灯时控
    Key_Tick(); // 按键处理

}
