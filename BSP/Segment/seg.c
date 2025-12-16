/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-16 17:02:55
 */
#include "seg.h"
#include "config.h"
#include "Delay.h"

// 共阳极数码管0-9段码表
const static uint8_t segment_digit_map[10] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};

/**
 * @brief      四向数码管初始化
 * @param       
 * @return     
 * @example    
 * @attention  东西向与南北向同步，因此本质只有四位数码管
 */
void Segment_Init(void)
{
    // 初始化数码管端口
    GPIO_Segment_Init();
    // 默认关闭所有段选
    GPIO_SetPin(SEGMENT_PORT, SEG_A_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_B_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_C_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_D_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_E_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_F_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_G_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_DP_PIN);
    // 默认关闭所有位选
    GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT1_PIN);
    GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT2_PIN);
    GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT3_PIN);
    GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT4_PIN);
}

/**
 * @brief      开启南北向两位数码管 1-开启 0-关闭
 * @param       
 * @return     
 * @example    
 * @attention  对应三四位数码管
 */
void Segment_Enable_SN(uint8_t state)
{
    if (state)
    {
        GPIO_SetPin(SEGMENT_PORT, SEG_DIGIT3_PIN);
        GPIO_SetPin(SEGMENT_PORT, SEG_DIGIT4_PIN);
    }
    else
    {
        GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT3_PIN);
        GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT4_PIN);
    }
}

/**
 * @brief      开启东西向两位数码管 1-开启 0-关闭
 * @param       
 * @return     
 * @example    
 * @attention  对应一二位数码管
 */
void Segment_Enable_EW(uint8_t state)
{
    if (state)
    {
        GPIO_SetPin(SEGMENT_PORT, SEG_DIGIT1_PIN);
        GPIO_SetPin(SEGMENT_PORT, SEG_DIGIT2_PIN);
    }
    else
    {
        GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT1_PIN);
        GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT2_PIN);
    }
}

/**
 * @brief      关闭全部数码管，即清除位选
 * @param       
 * @return     
 * @example    
 * @attention  将四位数码管的位选均拉低即关闭
 */
void Segment_Disable(void)
{
    GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT1_PIN);
    GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT2_PIN);
    GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT3_PIN);
    GPIO_ResetPin(SEGMENT_PORT, SEG_DIGIT4_PIN);
}

/**
 * @brief      关闭数码管全部段选脚
 * @param       
 * @return     
 * @example    
 * @attention  数码管（共阳极），关闭段选即a-g、dp全部拉高
 */
void Segment_Clear(void)
{
    GPIO_SetPin(SEGMENT_PORT, SEG_A_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_B_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_C_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_D_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_E_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_F_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_G_PIN);
    GPIO_SetPin(SEGMENT_PORT, SEG_DP_PIN);
}

/**
 * @brief      一位数码管显示数字0-9
 * @param      uint8_t num 待显示的数字
 * @return     
 * @example    
 * @attention  
 */
void Segment_Display_Digit(uint8_t num)
{
    if (num > 9) return; // 数字超出范围
    uint8_t seg_code = segment_digit_map[num];
    // 循环设置各位段选
    if (!(seg_code & 0x01)) GPIO_ResetPin(SEGMENT_PORT, SEG_A_PIN); else GPIO_SetPin(SEGMENT_PORT, SEG_A_PIN);
    if (!(seg_code & 0x02)) GPIO_ResetPin(SEGMENT_PORT, SEG_B_PIN); else GPIO_SetPin(SEGMENT_PORT, SEG_B_PIN);
    if (!(seg_code & 0x04)) GPIO_ResetPin(SEGMENT_PORT, SEG_C_PIN); else GPIO_SetPin(SEGMENT_PORT, SEG_C_PIN);
    if (!(seg_code & 0x08)) GPIO_ResetPin(SEGMENT_PORT, SEG_D_PIN); else GPIO_SetPin(SEGMENT_PORT, SEG_D_PIN);
    if (!(seg_code & 0x10)) GPIO_ResetPin(SEGMENT_PORT, SEG_E_PIN); else GPIO_SetPin(SEGMENT_PORT, SEG_E_PIN);
    if (!(seg_code & 0x20)) GPIO_ResetPin(SEGMENT_PORT, SEG_F_PIN); else GPIO_SetPin(SEGMENT_PORT, SEG_F_PIN);
    if (!(seg_code & 0x40)) GPIO_ResetPin(SEGMENT_PORT, SEG_G_PIN); else GPIO_SetPin(SEGMENT_PORT, SEG_G_PIN);
}

/**
 * @brief      显示数字0-99在对应数码管上
 * @param      uint8_t sn_num 南北向数字
 * @param      uint8_t ew_num 东西向数字
 * @return     
 * @example    
 * @attention  动态扫描显示
 */
void Segment_Display_Number(uint8_t ewNum, uint8_t snNum)
{
    // 显示数据合法性检查
    if (ewNum > 99) return;
    if (snNum > 99) return;
    // 位码分离
    uint8_t ewTens = ewNum / 10;      // 十位
    uint8_t ewUnits = ewNum % 10;     // 个位
    uint8_t snTens = snNum / 10;      // 十位
    uint8_t snUnits = snNum % 10;     // 个位

    // 显示东西向数码管
    // 显示十位 
    Segment_Disable();
    Segment_Display_Digit(ewTens);  // 显示数字
    GPIO_SetPin(SEGMENT_PORT, SEG_DIGIT1_PIN);  // 开启第一位
    // 延时一段时间以保持显示
    Delay_ms(10);

    // 显示个位
    Segment_Disable();
    Segment_Display_Digit(ewUnits);
    GPIO_SetPin(SEGMENT_PORT, SEG_DIGIT2_PIN);
    // 延时一段时间以保持显示
    Delay_ms(10);

    // 显示南北向数码管
    // 显示十位 
    Segment_Disable();
    Segment_Display_Digit(snTens);
    GPIO_SetPin(SEGMENT_PORT, SEG_DIGIT3_PIN);
    // 延时一段时间以保持显示
    Delay_ms(10);

    // 显示个位
    Segment_Disable();
    Segment_Display_Digit(snUnits);
    GPIO_SetPin(SEGMENT_PORT, SEG_DIGIT4_PIN);
    // 延时一段时间以保持显示
    Delay_ms(10);
}
