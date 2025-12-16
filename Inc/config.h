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

#endif // !__CONFIG_H
