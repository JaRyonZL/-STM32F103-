/*
 * @Descripttion: GPIO配置文件
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-16 14:24:17
 */
#include "gpio.h"
#include "config.h"

/**
 * @brief      东西南北向红绿灯控制端口初始化
 * @param       
 * @return     
 * @example    
 * @attention  对向交通灯变化同步   通用推挽 50MHz
 */
void GPIO_TrafficLight_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // 使能GPIOA时钟
    // 南北
    SN_PORT->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
    SN_PORT->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
    SN_PORT->CRH &= ~(GPIO_CRH_MODE12 | GPIO_CRH_CNF12);
    SN_PORT->CRH |= GPIO_CRH_MODE10; 
    SN_PORT->CRH |= GPIO_CRH_MODE11; 
    SN_PORT->CRH |= GPIO_CRH_MODE12;
    // 东西
    EW_PORT->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
    EW_PORT->CRH &= ~(GPIO_CRH_MODE14 | GPIO_CRH_CNF14);
    EW_PORT->CRH &= ~(GPIO_CRH_MODE15 | GPIO_CRH_CNF15);
    EW_PORT->CRH |= GPIO_CRH_MODE13; 
    EW_PORT->CRH |= GPIO_CRH_MODE14; 
    EW_PORT->CRH |= GPIO_CRH_MODE15;
}

/**
 * @brief      设置GPIO引脚
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void GPIO_SetPin(GPIO_TypeDef* GPIOx, uint32_t Pin)
{
    GPIOx->ODR |= Pin;
}

/**
 * @brief      清除GPIO引脚
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void GPIO_ResetPin(GPIO_TypeDef* GPIOx, uint32_t Pin)
{
    GPIOx->ODR &= ~Pin;
}
