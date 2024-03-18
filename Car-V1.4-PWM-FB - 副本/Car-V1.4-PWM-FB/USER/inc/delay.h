#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

void Systick_Init(void);
void delay_us(u32 nus);
void delay_ms(uint16_t nms);
void delay_s(u32 ns);

#endif

