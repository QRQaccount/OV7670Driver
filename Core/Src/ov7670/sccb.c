#include "ov7670/sccb.h"
#include "delay_ex/delay.h"
void SCCB_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_Initstruct;
    SCCB_SIC_RCC;
    SCCB_SID_RCC;
    GPIO_Initstruct.Pin = SCCB_SIC_BIT_Pin;
    GPIO_Initstruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initstruct.Speed = GPIO_SPEED_MEDIUM;
    HAL_GPIO_Init(SCCB_SIC_BIT_GPIO_Port, &GPIO_Initstruct);
    SCCB_SID_Output_Config();
}

void SCCB_SID_Output_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct ={ 0 };
    SCCB_SID_RCC;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pin = SCCB_SID_BIT_Pin;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    HAL_GPIO_Init(SCCB_SID_BIT_GPIO_Port, &GPIO_InitStruct);
}

void SCCB_SID_Input_Config()
{
    GPIO_InitTypeDef GPIO_Initstruct ={ 0 };
    SCCB_SID_RCC;
    GPIO_Initstruct.Mode = GPIO_MODE_INPUT;
    GPIO_Initstruct.Speed = GPIO_SPEED_MEDIUM;
    GPIO_Initstruct.Pin = SCCB_SID_BIT_Pin;
    HAL_GPIO_Init(SCCB_SID_BIT_GPIO_Port, &GPIO_Initstruct);
}

void SCCB_Start()
{

    SCCB_SID_High;
    delay_us(500);
    SCCB_SIC_High;
    delay_us(500);
    SCCB_SID_Low;
    delay_us(500);
    SCCB_SIC_Low;
    delay_us(500);
}

void SCCB_Stop()
{
    SCCB_SIC_Low;
    delay_us(500);
    SCCB_SIC_High;
    delay_us(500);
    SCCB_SID_High;
    delay_us(500);
}

uint8_t SCCB_Write_Byte(uint8_t data)
{
    uint8_t j, value;
    for (j = 0; j < 8; j++)
    {
        if ((data << j) & 0x80)
        {
            SCCB_SID_High;
        }
        else
        {
            SCCB_SID_Low;
        }
        delay_us(500);
        SCCB_SIC_High;
        delay_us(500);
        SCCB_SIC_Low;
        delay_us(500);
    }
    delay_us(100);

    // 读返回是否写入成功的状态
    SCCB_SID_Input_Config();
    delay_us(500);
    SCCB_SIC_High;
    delay_us(100);
    if (SCCB_SID_DATA)
    {
        value = 0;
    }
    else
    {
        value = 1;
    }
    SCCB_SIC_Low;
    delay_us(500);
    SCCB_SID_Output_Config();
    return value;
}

uint8_t SCCB_Read_Byte()
{
    uint8_t read, j;
    read = 0x00;
    SCCB_SID_Input_Config();
    delay_us(500);
    for (j = 0; j < 8; j++)
    {
        delay_us(500);
        SCCB_SIC_High;
        delay_us(500);
        read <<= 1;
        if (SCCB_SID_DATA)
        {
            read += 1;
        }
        SCCB_SIC_Low;
        delay_us(500);
    }
    return read;
}

void SCCB_NoAck()
{
    SCCB_SID_High;
    delay_us(500);
    SCCB_SIC_High;
    delay_us(500);
    SCCB_SIC_Low;
    delay_us(500);
}