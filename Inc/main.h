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
#define CS_ENC_R_Pin GPIO_PIN_13
#define CS_ENC_R_GPIO_Port GPIOC
#define LED_R_R_Pin GPIO_PIN_14
#define LED_R_R_GPIO_Port GPIOC
#define LED_R_G_Pin GPIO_PIN_15
#define LED_R_G_GPIO_Port GPIOC
#define LED_R_B_Pin GPIO_PIN_0
#define LED_R_B_GPIO_Port GPIOH
#define IRLED_RSLF_Pin GPIO_PIN_2
#define IRLED_RSLF_GPIO_Port GPIOA
#define V_BATT_Pin GPIO_PIN_3
#define V_BATT_GPIO_Port GPIOA
#define SEN_RF_Pin GPIO_PIN_6
#define SEN_RF_GPIO_Port GPIOA
#define SEN_RS_Pin GPIO_PIN_7
#define SEN_RS_GPIO_Port GPIOA
#define SEN_LS_Pin GPIO_PIN_0
#define SEN_LS_GPIO_Port GPIOB
#define SEN_LF_Pin GPIO_PIN_1
#define SEN_LF_GPIO_Port GPIOB
#define IRLED_RFLS_Pin GPIO_PIN_12
#define IRLED_RFLS_GPIO_Port GPIOB
#define LED_L_R_Pin GPIO_PIN_13
#define LED_L_R_GPIO_Port GPIOB
#define LED_L_G_Pin GPIO_PIN_14
#define LED_L_G_GPIO_Port GPIOB
#define LED_L_B_Pin GPIO_PIN_15
#define LED_L_B_GPIO_Port GPIOB
#define CS_ENC_L_Pin GPIO_PIN_13
#define CS_ENC_L_GPIO_Port GPIOA
#define MOT_L_PH_Pin GPIO_PIN_14
#define MOT_L_PH_GPIO_Port GPIOA
#define MOT_R_PH_Pin GPIO_PIN_15
#define MOT_R_PH_GPIO_Port GPIOA
#define MOT_L_PWM_Pin GPIO_PIN_6
#define MOT_L_PWM_GPIO_Port GPIOB
#define MOT_R_PWM_Pin GPIO_PIN_7
#define MOT_R_PWM_GPIO_Port GPIOB
#define CS_GYRO_Pin GPIO_PIN_8
#define CS_GYRO_GPIO_Port GPIOB
#define SPK_Pin GPIO_PIN_9
#define SPK_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
