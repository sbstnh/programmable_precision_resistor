/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define RLY_PWR_Pin GPIO_PIN_2
#define RLY_PWR_GPIO_Port GPIOA
#define ADC1_IN4_TEMP1_Pin GPIO_PIN_3
#define ADC1_IN4_TEMP1_GPIO_Port GPIOA
#define RLY_LE_Pin GPIO_PIN_4
#define RLY_LE_GPIO_Port GPIOA
#define RLY_SPI1_SCK_Pin GPIO_PIN_5
#define RLY_SPI1_SCK_GPIO_Port GPIOA
#define RLY_OE_Pin GPIO_PIN_6
#define RLY_OE_GPIO_Port GPIOA
#define RLY_SPI1_MOSI_Pin GPIO_PIN_7
#define RLY_SPI1_MOSI_GPIO_Port GPIOA
#define ADC1_IN_15_TEMP2_Pin GPIO_PIN_0
#define ADC1_IN_15_TEMP2_GPIO_Port GPIOB
#define GPIO_EXT_IN2_Pin GPIO_PIN_8
#define GPIO_EXT_IN2_GPIO_Port GPIOA
#define GPIO_EXT_IN1_Pin GPIO_PIN_9
#define GPIO_EXT_IN1_GPIO_Port GPIOA
#define NC_Pin GPIO_PIN_3
#define NC_GPIO_Port GPIOB
#define INT_UI_Pin GPIO_PIN_4
#define INT_UI_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
