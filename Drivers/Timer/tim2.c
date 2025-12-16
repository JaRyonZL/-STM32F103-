/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-16 21:00:34
 */
#include "tim2.h"

/**
 * @brief      TIM2初始化
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void TIM2_Init(void)
{
    // 开启TIM2时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    // 72分频 1000重装载 -> 1ms
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

// TIM2中断处理程序
void TIM2_IRQHandler(void)
{
	// 清除中断标志位
	TIM2->SR &= ~TIM_SR_UIF;

    
}
