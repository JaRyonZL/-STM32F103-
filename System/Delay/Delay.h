/*
 * @Descripttion: 基于系统定时器的延时函数工具
 * @Author: JaRyon
 * @version: v1.0
 * @Date: 2025-12-16 13:30:46
 */
#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);
void Delay_s(uint16_t s);

#endif
