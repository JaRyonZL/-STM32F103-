/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-11-20 20:12:47
 */
#ifndef __KEY_H
#define __KEY_H

#include "gpio.h"

typedef enum
{
    NO_PRESSED = 0,
    KEY1,
    KEY2,
    KEY3,
    KEY4
}KEY_NUM;

void Key_Init(void);
KEY_NUM Key_GetNum(void);
void Key_Tick(void);

#endif
