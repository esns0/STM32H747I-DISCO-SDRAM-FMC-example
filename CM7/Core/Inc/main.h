/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define LED_1_Pin GPIO_PIN_12
#define LED_1_GPIO_Port GPIOI
#define LED_2_Pin GPIO_PIN_13
#define LED_2_GPIO_Port GPIOI

/* USER CODE BEGIN Private defines */
#ifndef IS42S32800G_H
#define IS42S32800G_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/** @addtogroup BSP
 * @{
 */

/** @addtogroup Components
 * @{
 */

/** @addtogroup IS42S32800G
 * @{
 */

/** @defgroup IS42S32800G_Exported_Types Exported Types
 * @{
 */

#define REFRESH_COUNT                    ((uint32_t)0x0603)   /* SDRAM refresh counter (100Mhz SD clock) */

#define IS42S32800G_TIMEOUT             ((uint32_t)0xFFFF)

typedef struct
{
    uint32_t TargetBank; /*!< Target Bank                             */
    uint32_t RefreshMode; /*!< Refresh Mode                            */
    uint32_t RefreshRate; /*!< Refresh Rate                            */
    uint32_t BurstLength; /*!< Burst Length                            */
    uint32_t BurstType; /*!< Burst Type                              */
    uint32_t CASLatency; /*!< CAS Latency                             */
    uint32_t OperationMode; /*!< Operation Mode                          */
    uint32_t WriteBurstMode; /*!< Write Burst Mode                        */
} IS42S32800G_Context_t;

/**
 * @}
 */

/** @defgroup IS42S32800G_Exported_Constants
 * @{
 */
#define IS42S32800G_OK                         (0)
#define IS42S32800G_ERROR                      (-1)

/* Register Mode */
#define IS42S32800G_BURST_LENGTH_1              0x00000000U
#define IS42S32800G_BURST_LENGTH_2              0x00000001U
#define IS42S32800G_BURST_LENGTH_4              0x00000002U
#define IS42S32800G_BURST_LENGTH_8              0x00000004U
#define IS42S32800G_BURST_TYPE_SEQUENTIAL       0x00000000U
#define IS42S32800G_BURST_TYPE_INTERLEAVED      0x00000008U
#define IS42S32800G_CAS_LATENCY_2               0x00000020U
#define IS42S32800G_CAS_LATENCY_3               0x00000030U
#define IS42S32800G_OPERATING_MODE_STANDARD     0x00000000U
#define IS42S32800G_WRITEBURST_MODE_PROGRAMMED  0x00000000U
#define IS42S32800G_WRITEBURST_MODE_SINGLE      0x00000200U

/* Command Mode */
#define IS42S32800G_NORMAL_MODE_CMD             0x00000000U
#define IS42S32800G_CLK_ENABLE_CMD              0x00000001U
#define IS42S32800G_PALL_CMD                    0x00000002U
#define IS42S32800G_AUTOREFRESH_MODE_CMD        0x00000003U
#define IS42S32800G_LOAD_MODE_CMD               0x00000004U
#define IS42S32800G_SELFREFRESH_MODE_CMD        0x00000005U
#define IS42S32800G_POWERDOWN_MODE_CMD          0x00000006U

/**
 * @}
 */

/** @addtogroup IS42S32800G_Private_Functions
 * @{
 */
int32_t IS42S32800G_Init(SDRAM_HandleTypeDef *Ctx, IS42S32800G_Context_t *pRegMode);
int32_t IS42S32800G_ClockEnable(SDRAM_HandleTypeDef *Ctx, uint32_t Interface);
int32_t IS42S32800G_Precharge(SDRAM_HandleTypeDef *Ctx, uint32_t Interface);
int32_t IS42S32800G_ModeRegConfig(SDRAM_HandleTypeDef *Ctx, IS42S32800G_Context_t *pRegMode);
int32_t IS42S32800G_TimingConfig(SDRAM_HandleTypeDef *Ctx, FMC_SDRAM_TimingTypeDef *pTiming);
int32_t IS42S32800G_RefreshMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface, uint32_t RefreshMode);
int32_t IS42S32800G_RefreshRate(SDRAM_HandleTypeDef *Ctx, uint32_t RefreshCount);
int32_t IS42S32800G_EnterPowerMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface);
int32_t IS42S32800G_ExitPowerMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface);
int32_t IS42S32800G_Sendcmd(SDRAM_HandleTypeDef *Ctx, FMC_SDRAM_CommandTypeDef *SdramCmd);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* IS42S32800G_H */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
