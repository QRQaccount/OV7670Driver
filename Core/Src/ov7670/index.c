#include "ov7670/index.h"
#include "sccb.h"
#include "delay_ex/delay.h"
void OV7670_CLK_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    OV7670_CLK_RCC;
    GPIO_InitStruct.Pin = OV7670_CLK_Pin;
    GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pin = OV7670_CLK_Pin;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(OV7670_CLK_GPIO_Port, &GPIO_InitStruct);
}

void OV7670_CLK_Off()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    OV7670_CLK_RCC;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Pin = OV7670_CLK_Pin;
    HAL_GPIO_Init(OV7670_CLK_GPIO_Port, &GPIO_InitStruct);
}

void OV7670_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    OV7670_GPIO_RCC;
    GPIO_InitStruct.Pin = OV7670_Input_0_Pin | OV7670_Input_1_Pin | OV7670_Input_2_Pin | OV7670_Input_3_Pin | OV7670_Input_4_Pin | OV7670_Input_5_Pin | OV7670_Input_6_Pin | OV7670_Input_7_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

uint8_t OV7670_Write_Reg(uint8_t regId, uint8_t regData)
{
    SCCB_Start();
    if (SCCB_Write_Byte(0x42) == 0)
    {
        SCCB_Stop();
        return 0;
    }
    delay_us(100);
    if (SCCB_Write_Byte(regId) == 0)
    {
        SCCB_Stop();
        return 0;
    }
    delay_us(100);
    if (SCCB_Write_Byte(regData) == 0)
    {
        SCCB_Stop();
        return 0;
    }
    SCCB_Stop();
    return 1;
}

uint8_t OV7670_Read_Reg(uint8_t regId, uint8_t *regData)
{
    SCCB_Start();
    if (SCCB_Write_Byte(0x42) == 0)
    {
        SCCB_Stop();
        return 0;
    }
    delay_us(100);
    if (SCCB_Write_Byte(regId) == 0)
    {
        SCCB_Stop();
        return 0;
    }
    delay_us(100);
    SCCB_Stop();
    delay_us(100);

    SCCB_Start();
    if (SCCB_Write_Byte(0x43) == 0)
    {
        SCCB_Stop();
        return 0;
    }
    delay_us(100);
    *regData = SCCB_Read_Byte();
    SCCB_NoAck();
    SCCB_Stop();
    return 1;
}

void OV7670_Window_Config(uint16_t startX, uint16_t startY, uint16_t width, uint16_t height)
{
    uint16_t endX, endY;
    uint8_t reg1, reg2;
    uint8_t temp;
    endX = startX + width;
    endY = startY + height * 2; //限于单片机采集速度，隔行采集
    OV7670_Read_Reg(0x03, &reg1);
    reg1 &= 0xf0;
    OV7670_Read_Reg(0x32, &reg2);
    reg2 &= 0xc0;

    //水平方向设置
    temp = reg2 | (endX & 0x7 << 3) | (startX & 0x7);
    OV7670_Write_Reg(0x32, temp);
    temp = (startX & 0x7F8) >> 3;
    OV7670_Write_Reg(0x17, temp);
    temp = (endX & 0x7F8) >> 3;
    OV7670_Write_Reg(0x18, temp);

    //竖直
    temp = reg1 | ((endY & 0x3) << 2) | (startY & 0x3);
    OV7670_Write_Reg(0x03, temp);
    temp = startY >> 2;
    OV7670_Write_Reg(0x19, temp);
    temp = endY >> 2;
    OV7670_Write_Reg(0x1A, temp);
}

// 初始化OV7670的寄存器

void OV7670_Set_Regs()
{

    OV7670_Write_Reg(0x8c, 0x00);
    OV7670_Write_Reg(0x3a, 0x04);
    OV7670_Write_Reg(0x40, 0xd0);
    OV7670_Write_Reg(0x8c, 0x00);
    OV7670_Write_Reg(0x12, 0x14);
    OV7670_Write_Reg(0x32, 0x80);
    OV7670_Write_Reg(0x17, 0x16);
    OV7670_Write_Reg(0x18, 0x04);
    OV7670_Write_Reg(0x19, 0x02);
    OV7670_Write_Reg(0x1a, 0x7b);
    OV7670_Write_Reg(0x03, 0x06);
    OV7670_Write_Reg(0x0c, 0x04);
    OV7670_Write_Reg(0x3e, 0x00);
    OV7670_Write_Reg(0x70, 0x3a);
    OV7670_Write_Reg(0x71, 0x35);
    OV7670_Write_Reg(0x72, 0x11);
    OV7670_Write_Reg(0x73, 0x00);
    OV7670_Write_Reg(0xa2, 0x00);
    OV7670_Write_Reg(0x11, 0xff);
    //OV7670_Write_Reg(0x15 , 0x31);
    OV7670_Write_Reg(0x7a, 0x20);
    OV7670_Write_Reg(0x7b, 0x1c);
    OV7670_Write_Reg(0x7c, 0x28);
    OV7670_Write_Reg(0x7d, 0x3c);
    OV7670_Write_Reg(0x7e, 0x55);
    OV7670_Write_Reg(0x7f, 0x68);
    OV7670_Write_Reg(0x80, 0x76);
    OV7670_Write_Reg(0x81, 0x80);
    OV7670_Write_Reg(0x82, 0x88);
    OV7670_Write_Reg(0x83, 0x8f);
    OV7670_Write_Reg(0x84, 0x96);
    OV7670_Write_Reg(0x85, 0xa3);
    OV7670_Write_Reg(0x86, 0xaf);
    OV7670_Write_Reg(0x87, 0xc4);
    OV7670_Write_Reg(0x88, 0xd7);
    OV7670_Write_Reg(0x89, 0xe8);

    OV7670_Write_Reg(0x32, 0xb6);

    OV7670_Write_Reg(0x13, 0xff);
    OV7670_Write_Reg(0x00, 0x00);
    OV7670_Write_Reg(0x10, 0x00);
    OV7670_Write_Reg(0x0d, 0x00);
    OV7670_Write_Reg(0x14, 0x4e);
    OV7670_Write_Reg(0xa5, 0x05);
    OV7670_Write_Reg(0xab, 0x07);
    OV7670_Write_Reg(0x24, 0x75);
    OV7670_Write_Reg(0x25, 0x63);
    OV7670_Write_Reg(0x26, 0xA5);
    OV7670_Write_Reg(0x9f, 0x78);
    OV7670_Write_Reg(0xa0, 0x68);
    //	OV7670_Write_Reg(0xa1, 0x03);//0x0b,
    OV7670_Write_Reg(0xa6, 0xdf);
    OV7670_Write_Reg(0xa7, 0xdf);
    OV7670_Write_Reg(0xa8, 0xf0);
    OV7670_Write_Reg(0xa9, 0x90);
    OV7670_Write_Reg(0xaa, 0x94);
    //OV7670_Write_Reg(0x13, 0xe5);
    OV7670_Write_Reg(0x0e, 0x61);
    OV7670_Write_Reg(0x0f, 0x43);
    OV7670_Write_Reg(0x16, 0x02);
    OV7670_Write_Reg(0x1e, 0x37);
    OV7670_Write_Reg(0x21, 0x02);
    OV7670_Write_Reg(0x22, 0x91);
    OV7670_Write_Reg(0x29, 0x07);
    OV7670_Write_Reg(0x33, 0x0b);
    OV7670_Write_Reg(0x35, 0x0b);
    OV7670_Write_Reg(0x37, 0x3f);
    OV7670_Write_Reg(0x38, 0x01);
    OV7670_Write_Reg(0x39, 0x00);
    OV7670_Write_Reg(0x3c, 0x78);
    OV7670_Write_Reg(0x4d, 0x40);
    OV7670_Write_Reg(0x4e, 0x20);
    OV7670_Write_Reg(0x69, 0x00);
    OV7670_Write_Reg(0x6b, 0x4a);
    OV7670_Write_Reg(0x74, 0x19);
    OV7670_Write_Reg(0x8d, 0x4f);
    OV7670_Write_Reg(0x8e, 0x00);
    OV7670_Write_Reg(0x8f, 0x00);
    OV7670_Write_Reg(0x90, 0x00);
    OV7670_Write_Reg(0x91, 0x00);
    OV7670_Write_Reg(0x92, 0x00);
    OV7670_Write_Reg(0x96, 0x00);
    OV7670_Write_Reg(0x9a, 0x80);
    OV7670_Write_Reg(0xb0, 0x84);
    OV7670_Write_Reg(0xb1, 0x0c);
    OV7670_Write_Reg(0xb2, 0x0e);
    OV7670_Write_Reg(0xb3, 0x82);
    OV7670_Write_Reg(0xb8, 0x0a);
    OV7670_Write_Reg(0x43, 0x14);
    OV7670_Write_Reg(0x44, 0xf0);
    OV7670_Write_Reg(0x45, 0x34);
    OV7670_Write_Reg(0x46, 0x58);
    OV7670_Write_Reg(0x47, 0x28);
    OV7670_Write_Reg(0x48, 0x3a);

    OV7670_Write_Reg(0x59, 0x88);
    OV7670_Write_Reg(0x5a, 0x88);
    OV7670_Write_Reg(0x5b, 0x44);
    OV7670_Write_Reg(0x5c, 0x67);
    OV7670_Write_Reg(0x5d, 0x49);
    OV7670_Write_Reg(0x5e, 0x0e);

    OV7670_Write_Reg(0x64, 0x04);
    OV7670_Write_Reg(0x65, 0x20);
    OV7670_Write_Reg(0x66, 0x05);

    OV7670_Write_Reg(0x94, 0x04);
    OV7670_Write_Reg(0x95, 0x08);

    OV7670_Write_Reg(0x6c, 0x0a);
    OV7670_Write_Reg(0x6d, 0x55);
    OV7670_Write_Reg(0x6e, 0x11);
    OV7670_Write_Reg(0x6f, 0x9f);

    OV7670_Write_Reg(0x6a, 0x40);
    OV7670_Write_Reg(0x01, 0x40);
    OV7670_Write_Reg(0x02, 0x40);

    //OV7670_Write_Reg(0x13, 0xe7);
    OV7670_Write_Reg(0x15, 0x00);
    OV7670_Write_Reg(0x4f, 0x80);
    OV7670_Write_Reg(0x50, 0x80);
    OV7670_Write_Reg(0x51, 0x00);
    OV7670_Write_Reg(0x52, 0x22);
    OV7670_Write_Reg(0x53, 0x5e);
    OV7670_Write_Reg(0x54, 0x80);
    OV7670_Write_Reg(0x58, 0x9e);

    OV7670_Write_Reg(0x41, 0x08);
    OV7670_Write_Reg(0x3f, 0x00);
    OV7670_Write_Reg(0x75, 0x05);
    OV7670_Write_Reg(0x76, 0xe1);

    OV7670_Write_Reg(0x4c, 0x00);
    OV7670_Write_Reg(0x77, 0x01);

    OV7670_Write_Reg(0x3d, 0xc1);
    OV7670_Write_Reg(0x4b, 0x09);
    OV7670_Write_Reg(0xc9, 0x60);
    //OV7670_Write_Reg(0x41, 0x38);
    OV7670_Write_Reg(0x56, 0x40);
    OV7670_Write_Reg(0x34, 0x11);
    OV7670_Write_Reg(0x3b, 0x02);
    OV7670_Write_Reg(0xa4, 0x89);

    OV7670_Write_Reg(0x96, 0x00);
    OV7670_Write_Reg(0x97, 0x30);
    OV7670_Write_Reg(0x98, 0x20);
    OV7670_Write_Reg(0x99, 0x30);
    OV7670_Write_Reg(0x9a, 0x84);
    OV7670_Write_Reg(0x9b, 0x29);
    OV7670_Write_Reg(0x9c, 0x03);
    OV7670_Write_Reg(0x9d, 0x4c);
    OV7670_Write_Reg(0x9e, 0x3f);

    OV7670_Write_Reg(0x09, 0x00);
    OV7670_Write_Reg(0x3b, 0xc2);
}

uint8_t OV7670_Init()
{
    OV7670_GPIO_Init();
    SCCB_GPIO_Init();
    OV7670_CLK_Init();
    if (OV7670_Write_Reg(0x12, 0x80) == 0)
    {
        return 0;
    }
    HAL_Delay(100);
    OV7670_Set_Regs();
    OV7670_Window_Config(217, 12, OV7670_Width, OV7670_Height);
    return 1;
}