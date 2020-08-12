/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay_ex/delay.h"
#include "ov7670/index.h"
#include "user_laber.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OV7670_Input_0_Pin GPIO_PIN_0
#define OV7670_Input_0_GPIO_Port GPIOC
#define OV7670_Input_1_Pin GPIO_PIN_1
#define OV7670_Input_1_GPIO_Port GPIOC
#define OV7670_Input_2_Pin GPIO_PIN_2
#define OV7670_Input_2_GPIO_Port GPIOC
#define OV7670_Input_3_Pin GPIO_PIN_3
#define OV7670_Input_3_GPIO_Port GPIOC
#define SCCB_SIC_BIT_Pin GPIO_PIN_4
#define SCCB_SIC_BIT_GPIO_Port GPIOA
#define SCCB_SID_BIT_Pin GPIO_PIN_5
#define SCCB_SID_BIT_GPIO_Port GPIOA
#define OV7670_Input_4_Pin GPIO_PIN_4
#define OV7670_Input_4_GPIO_Port GPIOC
#define OV7670_Input_5_Pin GPIO_PIN_5
#define OV7670_Input_5_GPIO_Port GPIOC
#define OV7670_Input_6_Pin GPIO_PIN_6
#define OV7670_Input_6_GPIO_Port GPIOC
#define OV7670_Input_7_Pin GPIO_PIN_7
#define OV7670_Input_7_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
