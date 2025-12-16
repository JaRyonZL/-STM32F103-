#ifndef __SEG_H
#define __SEG_H

#include "gpio.h"

void Segment_Init(void);
void Segment_Enable_SN(uint8_t state);  
void Segment_Enable_EW(uint8_t state);
void Segment_Clear(void);
void Segment_Display_Number(uint8_t sel, uint8_t num);

#endif // !__SEG_H
