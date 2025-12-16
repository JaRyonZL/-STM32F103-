/*
 * @Descripttion: 基于系统定时器的延时函数工具源文件
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-16 13:30:35
 */
#include "Delay.h"

/**
 * @brief      微秒级延时
 * @param      uint16_t us 微秒时间
 * @return     void
 * @example    
 * @attention  
 */
void Delay_us(uint16_t us)
{
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;            
    SysTick->LOAD = us * 72 - 1;                         // 72MHz时钟频率
    SysTick->VAL = 0;                                   // 清空当前计数值
    SysTick->CTRL |= SysTick_CTRL_ENABLE;               // 使能SysTick定时器
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG));  // 等待计数到达0
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE;              // 关闭SysTick定时器
}

/**
 * @brief      微秒级延时函数
 * @param      uint16_t ms 需要延时的毫秒数
 * @return     void
 * @example    
 * @attention  
 */
void Delay_ms(uint16_t ms)
{
    while (ms--)
    {
        Delay_us(1000); // 调用微秒延时函数实现毫秒延时
    }
}

/**
 * @brief      秒级延时函数
 * @param      uint16_t s 需要延时的秒数
 * @return     void
 * @example    
 * @attention  
 */
void Delay_s(uint16_t s)
{
    while (s--)
    {
        Delay_ms(1000); // 调用毫秒延时函数实现秒延时
    }
}
