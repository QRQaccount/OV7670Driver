#ifndef _SCCB_H
#define _SCCB_H
#include "stm32f4xx_hal.h"

#include "user_laber.h"
#define SCCB_SID_RCC __HAL_RCC_GPIOA_CLK_ENABLE()
#define SCCB_SIC_RCC __HAL_RCC_GPIOA_CLK_ENABLE()
#define SCCB_SID_High HAL_GPIO_WritePin(SCCB_SID_BIT_GPIO_Port, SCCB_SID_BIT_Pin, GPIO_PIN_SET)
#define SCCB_SID_Low HAL_GPIO_WritePin(SCCB_SID_BIT_GPIO_Port, SCCB_SID_BIT_Pin, GPIO_PIN_RESET)
#define SCCB_SIC_High HAL_GPIO_WritePin(SCCB_SIC_BIT_GPIO_Port, SCCB_SIC_BIT_Pin, GPIO_PIN_SET)
#define SCCB_SIC_Low HAL_GPIO_WritePin(SCCB_SIC_BIT_GPIO_Port, SCCB_SIC_BIT_Pin, GPIO_PIN_RESET)
#define SCCB_SID_DATA (uint8_t) HAL_GPIO_ReadPin(SCCB_SIC_BIT_GPIO_Port, SCCB_SIC_BIT_Pin)

void SCCB_GPIO_Init();

// SCCB中SID设置为输出模式
void SCCB_SID_Output_Config();

// SCCB中SID设置位输入模式
void SCCB_SID_Input_Config();

// 启动SCCB
void SCCB_Start();

// 停止SCCB
void SCCB_Stop();

void SCCB_NoAck();

uint8_t SCCB_Write_Byte(uint8_t data);

uint8_t SCCB_Read_Byte();
#endif