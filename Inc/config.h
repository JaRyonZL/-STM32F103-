/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-16 15:29:26
 */
#ifndef __CONFIG_H
#define __CONFIG_H

#include "stm32f10x.h"

// 红绿灯控制引脚定义
#define SN_PORT             GPIOA           // 南北向交通灯端口
#define EW_PORT             GPIOA           // 东西向交通灯端口

#define SN_RED_PIN          GPIO_ODR_ODR10  // 南北向红灯 - PA10
#define SN_GREEN_PIN        GPIO_ODR_ODR11  // 南北向绿灯 - PA11
#define SN_YALLOW_PIN       GPIO_ODR_ODR12  // 南北向黄灯 - PA12
#define EW_RED_PIN          GPIO_ODR_ODR13  // 东西向红灯 - PA13
#define EW_GREEN_PIN        GPIO_ODR_ODR14  // 东西向绿灯 - PA14
#define EW_YALLOW_PIN       GPIO_ODR_ODR15  // 东西向黄灯 - PA15

// 数码管控制引脚定义
#define SEGMENT_PORT        GPIOB           // 数码管端口

#define SEG_A_PIN           GPIO_ODR_ODR0   // 段选 a - PB0
#define SEG_B_PIN           GPIO_ODR_ODR1   // 段选 b - PB1
#define SEG_C_PIN           GPIO_ODR_ODR2   // 段选 c - PB2
#define SEG_D_PIN           GPIO_ODR_ODR3   // 段选 d - PB3
#define SEG_E_PIN           GPIO_ODR_ODR4   // 段选 e - PB4
#define SEG_F_PIN           GPIO_ODR_ODR5   // 段选 f - PB5
#define SEG_G_PIN           GPIO_ODR_ODR6   // 段选 g - PB6
#define SEG_DP_PIN          GPIO_ODR_ODR7   // 段选 dp - PB7

#define SEG_DIGIT1_PIN      GPIO_ODR_ODR8   // 位选 第1位 - PB8
#define SEG_DIGIT2_PIN      GPIO_ODR_ODR9   // 位选 第2位 - PB9
#define SEG_DIGIT3_PIN      GPIO_ODR_ODR10  // 位选 第3位 - PB10
#define SEG_DIGIT4_PIN      GPIO_ODR_ODR11  // 位选 第4位 - PB11

#endif // !__CONFIG_H
