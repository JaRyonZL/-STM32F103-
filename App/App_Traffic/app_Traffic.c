/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2025-12-17 15:55:59
 */
#include "app_Traffic.h"
#include "tim2.h"

// 倒计时时间定义
#define EW_GREEN_TIME   30  // 东西绿灯或南北红灯保持时间
#define SN_GREEN_TIME   30  // 南北绿灯或东西红灯保持时间
#define EW_YALLOW_TIME  3   // 东西黄灯过渡时间
#define SN_YALLOW_TIME  3   // 南北黄灯过渡时间
#define EW_GREEN_END_TIME   3   // 东西绿灯结束前提示南北红灯时间
#define SN_GREEN_END_TIME   3   // 南北绿灯结束前提示东西红灯时间
#define EW_RED_END_TIME EW_YALLOW_TIME+EW_GREEN_END_TIME+1   // 东西红灯结束前倒计时
#define SN_RED_END_TIME EW_YALLOW_TIME+EW_GREEN_END_TIME+1   // 南北红灯结束前倒计时

uint8_t snTimer = 30;
uint8_t ewTimer = 30;
uint8_t secFlag = 0;
uint8_t halfFlag = 0;
static uint8_t dirRed = 0;

uint8_t yellowOn = 1; // 1=亮，0=灭
uint16_t yellowTick = 0; // 毫秒计数

TrafficLightState TL_CurrState = TL_ALL_RED;
TrafficMode T_CurrMode = TRAFFIC_MODE_NORMAL;

/**
 * @brief      设置四向交通灯状态
 * @param      TrafficLightState_t state 待设置的状态
 * @return     
 * @example    
 * @attention  
 */
static void TrafficLight_SetState(TrafficLightState state)
{
    switch (state)
    {
        case TL_SN_GREEN:
            TrafficLight_SN_Green();
            Segment_Display_Number(0, SN_GREEN_TIME); // 南北倒计时 30s，东西清零
            break;
        case TL_SN_YELLOW:
            TrafficLight_SN_Yallow();
            Segment_Display_Number(0, 3);  // 南北黄灯3s
            break;
        case TL_EW_GREEN:
            TrafficLight_EW_Green();
            Segment_Display_Number(EW_GREEN_TIME, 0); // 东西绿灯倒计时 30s
            break;
        case TL_EW_YELLOW:
            TrafficLight_EW_Yallow();
            Segment_Display_Number(EW_YALLOW_TIME, 0);  // 东西黄灯3s
            break;
        case TL_ALL_RED:
            TrafficLight_All_Red();
            // Segment_Display_Number(0, 0);  // 全红清零
            Segment_Enable_EW(1);
            Segment_Enable_SN(1);
            Segment_Display_Digit(0); // 显示00
            break;
        default:
            break;
    }
}

/**
 * @brief      交通灯控制触发计时器
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void App_Taffic_Tick(void)
{
    static uint32_t count1 = 0;
    static uint32_t count2 = 0;
    count1++;
    count2++;

    if (count1 == 50) // 0.5秒到达
    {
        count1 = 0;
        halfFlag = 1; 
    }
    if(count2 == 100) // 1s到达
    {
        count2 = 0;
        secFlag = 1;
    }
}

/**
 * @brief      交通灯初始化
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void App_Traffic_Init(void)
{
    // 初始状态 - 四向红灯
    TrafficLight_All_Red();
    snTimer = 0;
    ewTimer = 0;
    
	TrafficLight_SetState(TL_CurrState);

    // 延时1秒显示全红，然后切换到南北绿
    uint32_t delayCount = TIM2_GetTick();
	while(TIM2_GetTick() - delayCount < 100 * 2) // 2秒延时
	{}
    TL_CurrState = TL_SN_GREEN;
    snTimer = SN_GREEN_TIME;
    ewTimer = 0;
    TrafficLight_SetState(TL_CurrState);   
}

// 正常模式
void App_Traffic_Normal(void)
{
    if(secFlag != 1)  return;
    else if(secFlag == 1) secFlag = 0;

    switch(TL_CurrState)
    {
        case TL_SN_GREEN:
            if(snTimer > 0) snTimer--;
            // 红灯方向在绿灯最后7s时开始倒计时
            if(snTimer == SN_GREEN_END_TIME)	ewTimer = EW_RED_END_TIME;
            if(ewTimer > 0) 	ewTimer--;

            if(snTimer == 0)
            {
                TL_CurrState = TL_SN_YELLOW;
                snTimer = SN_YALLOW_TIME;      // 南北黄灯 3 秒
                TrafficLight_SetState(TL_CurrState);
            }
            break;

        case TL_SN_YELLOW:
            if(snTimer > 0) 	snTimer--;
            if(ewTimer > 0) 	ewTimer--;
            if(snTimer == 0)
            {
                TL_CurrState = TL_EW_GREEN;
                ewTimer = EW_GREEN_TIME;     // 东西绿灯 30 秒
                snTimer = 0;
                TrafficLight_SetState(TL_CurrState);
            }
            break;

        case TL_EW_GREEN:
            if(ewTimer > 0) ewTimer--;
            // 红灯方向在绿灯最后7s时开始倒计时
            if(ewTimer == EW_GREEN_END_TIME)	snTimer = SN_RED_END_TIME;
            if(snTimer > 0) 	snTimer--;

            if(ewTimer == 0)
            {
                TL_CurrState = TL_EW_YELLOW;
                ewTimer = EW_YALLOW_TIME;       // 东西黄灯 3 秒
                TrafficLight_SetState(TL_CurrState);
            }
            break;

        case TL_EW_YELLOW:
            if(ewTimer > 0)     ewTimer--;
            if(snTimer > 0) 	snTimer--;
            if(ewTimer == 0)
            {
                TL_CurrState = TL_SN_GREEN;
                snTimer = SN_GREEN_TIME;
                ewTimer = 0;
                TrafficLight_SetState(TL_CurrState);
            }
            break;

        default:
            break;
    }
}

/**
 * @brief      交通灯全红模式
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void App_Traffic_AllRed(void)
{
    if(secFlag != 1)  return;
    else if(secFlag == 1) secFlag = 0;

    TrafficLight_All_Red();
    snTimer = 0;
    ewTimer = 0;
}

/**
 * @brief      交通灯夜间黄闪模式
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void App_Traffic_YallowBlink(void)
{
    if(halfFlag != 1)  return;
    else if(halfFlag == 1) halfFlag = 0;

    // 四向黄灯闪烁
    TrafficLight_YellowBlink();
    // 倒计时清零
    snTimer = 0;
    ewTimer = 0;
}

/**
 * @brief      南北/东西一方禁止通行
 * @param       
 * @return     
 * @example    
 * @attention  按键控制方向变化
 */
void App_Traffic_SingleRed(void)
{
    if(secFlag != 1)  return;
    else if(secFlag == 1) secFlag = 0;

    if(dirRed == 0) Traffic_SN_RED();
    else            Traffic_EW_RED();
    
    snTimer = 0;
    ewTimer = 0;    
}


/**
 * @brief      交通灯模式切换控制
 * @param      KEY_NUM key 传入的按键键码 
 * @return     
 * @example    
 * @attention  
 */
void App_TrafficMode_Switch(KEY_NUM key)
{
    // 由其他模式切换至常规模式时，需重置交通灯参数(上次按键为0或1无需重置)
    // 避免倒计时清零导致的红绿灯状态突变
    static KEY_NUM prevKey = NO_PRESSED;

    if(key == KEY1 && prevKey != KEY1 && prevKey != NO_PRESSED)
    {
        TL_CurrState = TL_SN_GREEN;
        snTimer = SN_GREEN_TIME;;
        ewTimer = 0;
        TrafficLight_SetState(TL_CurrState);  
    }

    switch (key)
    {
        case KEY1:T_CurrMode = TRAFFIC_MODE_NORMAL;         break;
        case KEY2:T_CurrMode = TRAFFIC_MODE_ALL_RED;        break;
        case KEY3:T_CurrMode = TRAFFIC_MODE_YELLOW_BLINK;   break;
        case KEY4:T_CurrMode = TRAFFIC_MODE_SINGLE_RED; dirRed=~dirRed;break;

        default:break;
    }
    prevKey = key; // 记录上一次按下的按键键码
}

/**
 * @brief      交通灯执行控制中心，调度运行
 * @param       
 * @return     
 * @example    
 * @attention  
 */
void App_Traffic_ModeRun(void)
{
    switch (T_CurrMode)
    {
        case TRAFFIC_MODE_NORMAL:       App_Traffic_Normal();       break;
        case TRAFFIC_MODE_ALL_RED:      App_Traffic_AllRed();       break;
        case TRAFFIC_MODE_YELLOW_BLINK: App_Traffic_YallowBlink();  break;
        case TRAFFIC_MODE_SINGLE_RED:   App_Traffic_SingleRed();    break;

        default:break;
    }
}


// 由于proteus8.17中仿真时使用8MHz不会卡顿，所以实际1ms需要改成1/9ms
// 因此count计数也相应变为原来的1/9 即5s即5000变成5000/9约555 1s
/**
 * 5000 -> 556
 * 7000 -> 778
 * 12000 -> 1334
 * 14000 -> 1556
 * 1000 -> 111
 * 
 */
