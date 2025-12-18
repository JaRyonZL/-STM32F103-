/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-16 14:24:07
 */
#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

void GPIO_TrafficLight_Init(void);

void GPIO_Segment_Init(void);
void GPIO_ModeKey_Init(void);

void GPIO_SetPin(GPIO_TypeDef* GPIOx, uint32_t Pin);
void GPIO_ResetPin(GPIO_TypeDef* GPIOx, uint32_t Pin);

#endif // !__GPIO_H
