#ifndef _DELAY_H
#define _DELAY_H
// 芯片工作频率84M赫兹
#define Operating_Frequency 84
#include "stm32f4xx_hal.h"
void delay_us(uint16_t time);
#endif
