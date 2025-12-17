/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-17 13:32:05
 */
#include "sys.h"

/**
 * @brief      系统时钟配置为8MHz
 * @param       
 * @return     
 * @example    
 * @attention  
 */
/**
  * @brief  使用内部HSI配置系统时钟为8MHz
  * @note   STM32F1系列HSI频率为8MHz（±1%精度）
  *         无需外部晶振，配置简单可靠
  */
void SystemClock_Config_HSI_8MHz(void)
{
    /* 1. 确保HSI开启（复位后默认开启） */
    RCC->CR |= RCC_CR_HSION;
    
    /* 2. 等待HSI就绪 */
    while((RCC->CR & RCC_CR_HSIRDY) == 0);
    
    /* 3. 配置Flash预取和等待周期（8MHz不需要等待） */
    FLASH->ACR = FLASH_ACR_PRFTBE;  // 使能预取缓冲区
    // LATENCY保持为0（0等待周期），8MHz下不需要等待
    
    /* 4. 关闭PLL（如果之前开启） */
    RCC->CR &= ~RCC_CR_PLLON;
    
    /* 5. 配置时钟分频器（全部不分频） */
    RCC->CFGR = 0x00000000;  // 清除所有配置
    
    /* 6. 选择HSI作为系统时钟源 */
    RCC->CFGR &= ~RCC_CFGR_SW;  // 清除SW位
    RCC->CFGR |= RCC_CFGR_SW_HSI;  // 选择HSI
    
    /* 7. 等待切换完成 */
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
    
    /* 8. 配置总线时钟 */
    // AHB不分频（HCLK = SYSCLK = 8MHz）
    RCC->CFGR &= ~RCC_CFGR_HPRE;
    
    // APB1不分频（PCLK1 = HCLK = 8MHz）
    RCC->CFGR &= ~RCC_CFGR_PPRE1;
    
    // APB2不分频（PCLK2 = HCLK = 8MHz）
    RCC->CFGR &= ~RCC_CFGR_PPRE2;
    
    /* 9. 关闭不需要的时钟源（可选） */
    RCC->CR &= ~RCC_CR_HSEON;  // 关闭外部晶振（如果不需要）
    
    /* 10. 更新系统时钟变量 */
    SystemCoreClock = 8000000;
}
