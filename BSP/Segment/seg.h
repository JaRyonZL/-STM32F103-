#ifndef __SEG_H
#define __SEG_H

#include "gpio.h"

void Segment_Init(void);
void Segment_Enable_SN(uint8_t state);  
void Segment_Enable_EW(uint8_t state);
void Segment_Disable(void);
void Segment_Clear(void);
void Segment_Display_Digit(uint8_t num);
void Segment_Display_Number(uint8_t ewNum, uint8_t snNum);

#endif // !__SEG_H
