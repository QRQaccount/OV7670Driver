#ifndef _INDEX_H
#define _INDEX_h
#include "user_laber.h"
#include "stm32f4xx_hal.h"

#define OV7670_CLK_RCC __HAL_RCC_GPIOA_CLK_ENABLE()
#define OV7670_GPIO_RCC __HAL_RCC_GPIOC_CLK_ENABLE()

// 窗口大小配置

#define OV7670_Window_StartX 217
#define OV7670_Window_StartY 12
#define OV7670_Height 240
#define OV7670_Width 320

static uint8_t OV7670_Image[320][240];

/**
 * @brief 初始化OV7670的时钟信号
*/
void OV7670_CLK_Init();

/**
 * @brief 关闭OV7670的时钟信号
*/
void OV7670_CLK_Off();

/**
 * @brief 初始化用于接受OV7670读取的像素的值的8个端口 
*/
void OV7670_GPIO_Init();

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
