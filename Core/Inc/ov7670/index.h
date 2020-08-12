#ifndef _INDEX_H
#define _INDEX_h
#include "stm32f4xx_hal.h"

#define OV7670_CLK_RCC __HAL_RCC_GPIOA_CLK_ENABLE()
#define OV7670_GPIO_RCC __HAL_RCC_GPIOC_CLK_ENABLE()

// 设置接受端口的别名

#define OV7670_Input_0_Pin GPIO_PIN_0
#define OV7670_Input_0_GPIO_Port GPIOC
#define OV7670_Input_1_Pin GPIO_PIN_1
#define OV7670_Input_1_GPIO_Port GPIOC
#define OV7670_Input_2_Pin GPIO_PIN_2
#define OV7670_Input_2_GPIO_Port GPIOC
#define OV7670_Input_3_Pin GPIO_PIN_3
#define OV7670_Input_3_GPIO_Port GPIOC
#define OV7670_Input_4_Pin GPIO_PIN_4
#define OV7670_Input_4_GPIO_Port GPIOC
#define OV7670_Input_5_Pin GPIO_PIN_5
#define OV7670_Input_5_GPIO_Port GPIOC
#define OV7670_Input_6_Pin GPIO_PIN_6
#define OV7670_Input_6_GPIO_Port GPIOC
#define OV7670_Input_7_Pin GPIO_PIN_7
#define OV7670_Input_7_GPIO_Port GPIOC

// 设置OV7670时钟的别名

#define OV7670_CLK_Pin GPIO_PIN_8
#define OV7670_CLK_GPIO_Port GPIOA

// 窗口大小配置

#define OV7670_Window_StartX 217
#define OV7670_Window_StartY 12
#define OV7670_Height 240
#define OV7670_Width 320

static uint8_t OV7670_Image[320][240];

/**
 * @brief 初始化OV7670的时钟信号
*/
#define OV7670_CLK_Init()                     \
    GPIO_InitTypeDef GPIO_InitStruct = {0};   \
    OV7670_CLK_RCC;                           \
    GPIO_InitStruct.Pin = OV7670_CLK_Pin;     \
    GPIO_InitStruct.Alternate = GPIO_AF0_MCO; \
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;   \
    GPIO_InitStruct.Pin = OV7670_CLK_Pin;     \
    GPIO_InitStruct.Pull = GPIO_NOPULL;       \
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;  \
    HAL_GPIO_Init(OV7670_CLK_GPIO_Port, &GPIO_InitStruct);

/**
 * @brief 关闭OV7670的时钟信号
*/
#define OV7670_CLK_Off()                        \
    GPIO_InitTypeDef GPIO_InitStruct = {0};     \
    OV7670_CLK_RCC;                             \
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; \
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;    \
    GPIO_InitStruct.Pull = GPIO_NOPULL;         \
    GPIO_InitStruct.Pin = OV7670_CLK_Pin;       \
    HAL_GPIO_Init(OV7670_CLK_GPIO_Port, &GPIO_InitStruct);

/**
 * @brief 初始化用于接受OV7670读取的像素的值的8个端口 
*/
#define OV7670_GPIO_Init()                                                                                                                                                                       \
    GPIO_InitTypeDef GPIO_InitStruct = {0};                                                                                                                                                      \
    OV7670_GPIO_RCC;                                                                                                                                                                             \
    GPIO_InitStruct.Pin = OV7670_Input_0_Pin | OV7670_Input_1_Pin | OV7670_Input_2_Pin | OV7670_Input_3_Pin | OV7670_Input_4_Pin | OV7670_Input_5_Pin | OV7670_Input_6_Pin | OV7670_Input_7_Pin; \
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;                                                                                                                                                      \
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;                                                                                                                                                        \
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/**
 * @brief Ov7670写寄存器函数
 * @param regId 寄存器编号
 * @param regData 要写入寄存器的值
 * @return 写入成功则返回1,否则返回0
*/
uint8_t OV7670_Write_Reg(uint8_t regId, uint8_t regData);

/**
 * @brief Ov7670读取寄存器函数
 * @param regId 寄存器编号
 * @param regData 用于存放读取的值的地址
 * @return 读取成功则返回1,否则返回0
*/
uint8_t OV7670_Read_Reg(uint8_t regId, uint8_t *regData);

/**
 * @brfixief Ov7670采集窗口大小配置函数
 * @param startX 水平坐标起始位置
 * @param startY 竖直坐标起始位置
 * @param width 窗口宽度
 * @param height 窗口高度
 * 
*/
void OV7670_Window_Config(uint16_t startX, uint16_t startY, uint16_t width, uint16_t height);

/**
 * @brief 初始化OV7670
*/
uint8_t OV7670_Init();

#endif
