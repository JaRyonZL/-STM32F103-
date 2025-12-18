/*
 * @Descripttion: 按键驱动文件.c
 * @Author: JaRyon
 * @version:
 * @Date: 2025-11-20 20:12:47
 */
#include "key.h"
#include "config.h"

#define MODE_KEY1_READ  ((MODE_KEY_PORT->IDR & MODE_KEY1_PIN_R) ? 1 : 0)
#define MODE_KEY2_READ  ((MODE_KEY_PORT->IDR & MODE_KEY2_PIN_R) ? 1 : 0)
#define MODE_KEY3_READ  ((MODE_KEY_PORT->IDR & MODE_KEY3_PIN_R) ? 1 : 0)
#define MODE_KEY4_READ  ((MODE_KEY_PORT->IDR & MODE_KEY4_PIN_R) ? 1 : 0)

// 按键键码
static KEY_NUM KeyNum = NO_PRESSED;

/**
 * @brief      模式按键初始化
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void Key_Init(void)
{
    // 模式按键端口配置 key1-key4
    GPIO_ModeKey_Init();
    // 均默认上拉
    GPIO_SetPin(MODE_KEY_PORT, MODE_KEY1_PIN);
    GPIO_SetPin(MODE_KEY_PORT, MODE_KEY2_PIN);
    GPIO_SetPin(MODE_KEY_PORT, MODE_KEY3_PIN);
    GPIO_SetPin(MODE_KEY_PORT, MODE_KEY4_PIN);
}

// 获取按键状态
// 内部调用
static KEY_NUM Key_GetState(void)
{
    if (MODE_KEY1_READ == 0)
    {
        return KEY1;
    }
    else if (MODE_KEY2_READ == 0)
    {
        return KEY2;
    }
    else if (MODE_KEY3_READ == 0)
    {
        return KEY3;
    }
    else if (MODE_KEY4_READ == 0)
    {
        return KEY4;
    }

    return NO_PRESSED;
}

// 获取按键键码
KEY_NUM Key_GetNum(void)
{
    KEY_NUM temp;

    // 按键非零时,传递后清除
    if (KeyNum != 0)
    {
        temp = KeyNum;
        KeyNum = NO_PRESSED;
        return temp;
    }
    return NO_PRESSED;
}

// 每秒扫描按键
void Key_Tick(void)
{
    static uint32_t keyScan_Tick = 0;
    static KEY_NUM prevKeyState = NO_PRESSED;
    static KEY_NUM currKeyState = NO_PRESSED;

    keyScan_Tick++;

    if (keyScan_Tick >= KEYSCAN_TIME) // 每20ms扫描一次按键状态
    {
        keyScan_Tick = 0;

        prevKeyState = currKeyState;
        currKeyState = Key_GetState();

        // 比较本次与上次按键的状态（20ms检测一次，不可放在外层if外，否则每次会连续返回20次同样的按键键码）
        if (currKeyState != 0 && prevKeyState == 0)
        {
            KeyNum = currKeyState;
        }
    }
}
