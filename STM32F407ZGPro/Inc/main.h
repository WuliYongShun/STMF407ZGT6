/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#define K1_Pin GPIO_PIN_2
#define K1_GPIO_Port GPIOE
#define K2_Pin GPIO_PIN_3
#define K2_GPIO_Port GPIOE
#define K3_Pin GPIO_PIN_4
#define K3_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_9
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_10
#define LED2_GPIO_Port GPIOF
#define K_WakeUp_Pin GPIO_PIN_0
#define K_WakeUp_GPIO_Port GPIOA
#define LATCH_Pin GPIO_PIN_4
#define LATCH_GPIO_Port GPIOD
#define SCLK_Pin GPIO_PIN_5
#define SCLK_GPIO_Port GPIOD
#define SDI_Pin GPIO_PIN_6
#define SDI_GPIO_Port GPIOD
#define SDO_Pin GPIO_PIN_7
#define SDO_GPIO_Port GPIOD
#define ADS7321_SCK_Pin GPIO_PIN_3
#define ADS7321_SCK_GPIO_Port GPIOB
#define ADS7321_SDO_Pin GPIO_PIN_4
#define ADS7321_SDO_GPIO_Port GPIOB
#define ADS7321_SDI_Pin GPIO_PIN_5
#define ADS7321_SDI_GPIO_Port GPIOB
#define ADS7321_CS_Pin GPIO_PIN_8
#define ADS7321_CS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
