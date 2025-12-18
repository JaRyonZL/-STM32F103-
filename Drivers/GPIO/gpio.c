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
 * @param      void 无 
 * @return     void
 * @example    GPIO_TrafficLight_Init();
 * @attention  对向交通灯变化同步   PA4-PA9通用推挽 50MHz
 */
void GPIO_TrafficLight_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // 使能GPIOA时钟
    // 南北
    SN_PORT->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);
    SN_PORT->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
    SN_PORT->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);
    SN_PORT->CRL |= GPIO_CRL_MODE4;
    SN_PORT->CRL |= GPIO_CRL_MODE5;
    SN_PORT->CRL |= GPIO_CRL_MODE6;
    // 东西
    EW_PORT->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
    EW_PORT->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);
    EW_PORT->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
    EW_PORT->CRL |= GPIO_CRL_MODE7; 
    EW_PORT->CRH |= GPIO_CRH_MODE8; 
    EW_PORT->CRH |= GPIO_CRH_MODE9;
}

/**
 * @brief      四位数码管端口配置(对应南北和东西向倒计时)
 * @param      void 无 
 * @return     void  
 * @example    GPIO_Segment_Init();
 * @attention  PB0-PB7对应a-g和dp，PB8-PB11对应位选
 */
void GPIO_Segment_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // 使能SEGMENT_PORT时钟
    // 数码管段选
    SEGMENT_PORT->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
    GPIOB->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);
    SEGMENT_PORT->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
    SEGMENT_PORT->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
    SEGMENT_PORT->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);
    SEGMENT_PORT->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
    SEGMENT_PORT->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);
    SEGMENT_PORT->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
    SEGMENT_PORT->CRL |= GPIO_CRL_MODE0; 
    SEGMENT_PORT->CRL |= GPIO_CRL_MODE1; 
    SEGMENT_PORT->CRL |= GPIO_CRL_MODE2; 
    SEGMENT_PORT->CRL |= GPIO_CRL_MODE3; 
    SEGMENT_PORT->CRL |= GPIO_CRL_MODE4; 
    SEGMENT_PORT->CRL |= GPIO_CRL_MODE5; 
    SEGMENT_PORT->CRL |= GPIO_CRL_MODE6; 
    SEGMENT_PORT->CRL |= GPIO_CRL_MODE7; 
    // 数码管位选
    SEGMENT_PORT->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);
    SEGMENT_PORT->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
    SEGMENT_PORT->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
    SEGMENT_PORT->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
    SEGMENT_PORT->CRH |= GPIO_CRH_MODE8; 
    SEGMENT_PORT->CRH |= GPIO_CRH_MODE9; 
    SEGMENT_PORT->CRH |= GPIO_CRH_MODE10; 
    SEGMENT_PORT->CRH |= GPIO_CRH_MODE11; 
}

/**
 * @brief      模式按键端口配置
 * @param      void 无 
 * @return     void      
 * @example    GPIO_ModeKey_Init();
 * @attention  PC0-PC3
 */
void GPIO_ModeKey_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // GPIO工作模式配置 上下拉输入 cnf-10 mode-00
    // KEY1
    MODE_KEY_PORT->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
    MODE_KEY_PORT->CRL |= GPIO_CRL_CNF0_1;
    // KEY2
    MODE_KEY_PORT->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
    MODE_KEY_PORT->CRL |= GPIO_CRL_CNF1_1;
    // KEY3
    MODE_KEY_PORT->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
    MODE_KEY_PORT->CRL |= GPIO_CRL_CNF2_1;
    // KEY4
    MODE_KEY_PORT->CRL &= ~(GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
    MODE_KEY_PORT->CRL |= GPIO_CRL_CNF3_1;
}

/**
 * @brief      设置GPIO引脚
 * @param      GPIO_TypeDef* GPIOx 待设置的端口名 
 * @param      uint32_t Pin 待设置的引脚名 
 * @return     void
 * @example    GPIO_SetPin(GPIOA, GPIO_ODR_ODR1);
 * @attention  Pin是GPIO_ODR_ODRx，用于拉高拉低引脚电平的
 */
void GPIO_SetPin(GPIO_TypeDef* GPIOx, uint32_t Pin)
{
    GPIOx->ODR |= Pin;
}

/**
 * @brief      清除GPIO引脚
 * @param      GPIO_TypeDef* GPIOx 待设置的端口名 
 * @param      uint32_t Pin 待设置的引脚名 
 * @return     void   
 * @example    GPIO_ResetPin(GPIOA, GPIO_ODR_ODR1);
 * @attention  Pin是GPIO_ODR_ODRx，用于拉高拉低引脚电平的
 */
void GPIO_ResetPin(GPIO_TypeDef* GPIOx, uint32_t Pin)
{
    GPIOx->ODR &= ~Pin;
}


