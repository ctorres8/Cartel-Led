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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BH1750.h"
#include "DOT_MATRIX.h"
#include "RTC.h"
#include "Bluetooth.h"
//#include "arrebote.h"
#include "dht11.h"
#include "fatfs_app.h"
//#include <stdlib.h>
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
//void tarea_led( void *pvParameters );
void tarea_bh1750( void *pvParameters );
void tarea_cartel( void *pvParameters );
void tarea_uart (void *);
void tarea_actualizarRTC (void *);
void tarea_pulsador1 (void *);
void tarea_pulsador2 (void *);
void tarea_pulsador3 (void *);
void tarea_acciones_pulsador (void *);
void tarea_DHT11(void *);
void tarea_sd( void *);


void inicializar_tareas (void);
void inicializar_perifericos(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PUSH1_Pin GPIO_PIN_1
#define PUSH1_GPIO_Port GPIOC
#define PUSH1_EXTI_IRQn EXTI1_IRQn
#define PUSH2_Pin GPIO_PIN_2
#define PUSH2_GPIO_Port GPIOC
#define PUSH2_EXTI_IRQn EXTI2_IRQn
#define PUSH3_Pin GPIO_PIN_3
#define PUSH3_GPIO_Port GPIOC
#define PUSH3_EXTI_IRQn EXTI3_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define SD_CD_Pin GPIO_PIN_8
#define SD_CD_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define RTC_BKUP_DEFINE_CODE 0xBEBE
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
