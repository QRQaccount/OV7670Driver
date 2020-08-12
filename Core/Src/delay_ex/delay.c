#include "delay_ex/delay.h"

void delay_us(uint16_t time)
{
    for (int i = time / 32; i > 0; i--)
        ;
}