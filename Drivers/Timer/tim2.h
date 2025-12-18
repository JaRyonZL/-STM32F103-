/*
 * @Descripttion: TIM2定时器配置文件(.h)
 * @Author: JaRyon
 * @version: v1.0
 * @Date: 2025-12-16 21:00:42
 */
#ifndef __TIM2_H
#define __TIM2_H

#include "stm32f10x.h"

void TIM2_Init(void);
uint32_t TIM2_GetTick(void);

#endif // !__TIM2_H
