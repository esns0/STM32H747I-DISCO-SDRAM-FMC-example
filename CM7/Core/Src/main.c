/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t test_count = 0;
#define SDRAM_BASE_ADDRESS 0xD0000000

uint32_t sdram_base_address = SDRAM_BASE_ADDRESS;

uint8_t w_buf[4096] = {0x00, };
uint16_t w_len = 0;
uint8_t r_buf[4096] = {0x00, };
uint16_t r_len = 0;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */
    /* USER CODE BEGIN Boot_Mode_Sequence_0 */
//    int32_t timeout;
    /* USER CODE END Boot_Mode_Sequence_0 */

    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();

    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();

    /* USER CODE BEGIN Boot_Mode_Sequence_1 */
    /* Wait until CPU2 boots and enters in stop mode or timeout*/
//    timeout = 0xFFFF;
//    while ((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
//    if (timeout < 0)
//    {
//        Error_Handler();
//    }
    /* USER CODE END Boot_Mode_Sequence_1 */
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();
    /* USER CODE BEGIN Boot_Mode_Sequence_2 */
    /* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of HSEM notification */
    /*HW semaphore Clock enable*/
//    __HAL_RCC_HSEM_CLK_ENABLE();
//    /*Take HSEM */
//    HAL_HSEM_FastTake(HSEM_ID_0);
//    /*Release HSEM in order to notify the CPU2(CM4)*/
//    HAL_HSEM_Release(HSEM_ID_0, 0);
//    /* wait until CPU2 wakes up from stop mode */
//    timeout = 0xFFFF;
//    while ((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
//    if (timeout < 0)
//    {
//        Error_Handler();
//    }
    /* USER CODE END Boot_Mode_Sequence_2 */

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_FMC_Init();
    /* USER CODE BEGIN 2 */
    for (int i = 0; i < 4096; i++)
    {
        w_buf[i] = 0x77;
    }

//    memcpy((uint32_t*)SDRAM_BASE_ADDRESS, w_buf, 4096);
//    memcpy(r_buf, (uint32_t*)SDRAM_BASE_ADDRESS, 4096);
    uint32_t* p = (uint32_t*)SDRAM_BASE_ADDRESS;
    for (uint32_t i = 0; i < (0x02000000 / 4); i++)
    {
        *(p + i) = 0x12345678;
    }
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
        HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
        HAL_Delay(500);
        test_count++;
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Supply configuration update enable
     */
    HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

    /** Configure the main internal regulator output voltage
     */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
    {
    }

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 50;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 5;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
            | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/**
 ******************************************************************************
 * @file    is42s32800g.c
 * @author  MCD Application Team
 * @brief   IS42S32800G sdram 8MBx32 driver file
 ******************************************************************************
 * @attention
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

/* Includes ------------------------------------------------------------------*/

/** @addtogroup BSP
 * @{
 */

/** @addtogroup Components
 * @{
 */

/** @defgroup IS42S32800G IS42S32800G
 * @brief     This file provides a set of functions needed to drive the
 *            IS42S32800G SDRAM memory.
 * @{
 */

/** @defgroup IS42S32800G_Private_Variables IS42S32800G Private Variables
 * @{
 */
static FMC_SDRAM_CommandTypeDef Command;
/**
 * @}
 */

/** @defgroup IS42S32800G_Function_Prototypes IS42S32800G Function Prototypes
 * @{
 */
static int32_t IS42S32800G_Delay(uint32_t Delay);

/**
 * @}
 */

/** @defgroup IS42S32800G_Exported_Functions IS42S32800G Exported Functions
 * @{
 */
/**
 * @brief  Initializes the IS42S32800G SDRAm memory
 * @param  Ctx Component object pointer
 * @param  pRegMode : Pointer to Register Mode structure
 * @retval error status
 */
int32_t IS42S32800G_Init(SDRAM_HandleTypeDef *Ctx, IS42S32800G_Context_t *pRegMode)
{
    int32_t ret = IS42S32800G_ERROR;

    /* Step 1: Configure a clock configuration enable command */
    if (IS42S32800G_ClockEnable(Ctx, pRegMode->TargetBank) == IS42S32800G_OK)
    {
        /* Step 2: Insert 100 us minimum delay */
        /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
        (void)IS42S32800G_Delay(1);

        /* Step 3: Configure a PALL (precharge all) command */
        if (IS42S32800G_Precharge(Ctx, pRegMode->TargetBank) == IS42S32800G_OK)
        {
            /* Step 4: Configure a Refresh command */
            if (IS42S32800G_RefreshMode(Ctx, pRegMode->TargetBank, pRegMode->RefreshMode) == IS42S32800G_OK)
            {
                /* Step 5: Program the external memory mode register */
                if (IS42S32800G_ModeRegConfig(Ctx, pRegMode) == IS42S32800G_OK)
                {
                    /* Step 6: Set the refresh rate counter */
                    if (IS42S32800G_RefreshRate(Ctx, pRegMode->RefreshRate) == IS42S32800G_OK)
                    {
                        ret = IS42S32800G_OK;
                    }
                }
            }
        }
    }
    return ret;
}

/**
 * @brief  Enable SDRAM clock
 * @param  Ctx Component object pointer
 * @param  Interface Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
 * @retval error status
 */
int32_t IS42S32800G_ClockEnable(SDRAM_HandleTypeDef *Ctx, uint32_t Interface)
{
    Command.CommandMode = IS42S32800G_CLK_ENABLE_CMD;
    Command.CommandTarget = Interface;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    if (HAL_SDRAM_SendCommand(Ctx, &Command, IS42S32800G_TIMEOUT) != HAL_OK)
    {
        return IS42S32800G_ERROR;
    }
    else
    {
        return IS42S32800G_OK;
    }
}

/**
 * @brief  Precharge all sdram banks
 * @param  Ctx Component object pointer
 * @param  Interface Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
 * @retval error status
 */
int32_t IS42S32800G_Precharge(SDRAM_HandleTypeDef *Ctx, uint32_t Interface)
{
    Command.CommandMode = IS42S32800G_PALL_CMD;
    Command.CommandTarget = Interface;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    if (HAL_SDRAM_SendCommand(Ctx, &Command, IS42S32800G_TIMEOUT) != HAL_OK)
    {
        return IS42S32800G_ERROR;
    }
    else
    {
        return IS42S32800G_OK;
    }
}

/**
 * @brief  Program the external memory mode register
 * @param  Ctx Component object pointer
 * @param  pRegMode : Pointer to Register Mode structure
 * @retval error status
 */
int32_t IS42S32800G_ModeRegConfig(SDRAM_HandleTypeDef *Ctx, IS42S32800G_Context_t *pRegMode)
{
    uint32_t tmpmrd;

    /* Program the external memory mode register */
    tmpmrd = (uint32_t)pRegMode->BurstLength |\
 pRegMode->BurstType |\
 pRegMode->CASLatency |\
 pRegMode->OperationMode
            |\
 pRegMode->WriteBurstMode;

    Command.CommandMode = IS42S32800G_LOAD_MODE_CMD;
    Command.CommandTarget = pRegMode->TargetBank;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = tmpmrd;

    /* Send the command */
    if (HAL_SDRAM_SendCommand(Ctx, &Command, IS42S32800G_TIMEOUT) != HAL_OK)
    {
        return IS42S32800G_ERROR;
    }
    else
    {
        return IS42S32800G_OK;
    }
}

/**
 * @brief  Program the SDRAM timing
 * @param  Ctx Component object pointer
 * @param  pTiming Pointer to SDRAM timing configuration structure
 * @retval error status
 */
int32_t IS42S32800G_TimingConfig(SDRAM_HandleTypeDef *Ctx, FMC_SDRAM_TimingTypeDef *pTiming)
{
    /* Program the SDRAM timing */
    if (HAL_SDRAM_Init(Ctx, pTiming) != HAL_OK)
    {
        return IS42S32800G_ERROR;
    }
    else
    {
        return IS42S32800G_OK;
    }
}

/**
 * @brief  Configure Refresh mode
 * @param  Ctx Component object pointer
 * @param  Interface Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
 * @param  RefreshMode Could be IS42S32800G_CMD_AUTOREFRESH_MODE or
 *                      IS42S32800G_CMD_SELFREFRESH_MODE
 * @retval error status
 */
int32_t IS42S32800G_RefreshMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface, uint32_t RefreshMode)
{
    Command.CommandMode = RefreshMode;
    Command.CommandTarget = Interface;
    Command.AutoRefreshNumber = 8;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    if (HAL_SDRAM_SendCommand(Ctx, &Command, IS42S32800G_TIMEOUT) != HAL_OK)
    {
        return IS42S32800G_ERROR;
    }
    else
    {
        return IS42S32800G_OK;
    }
}

/**
 * @brief  Set the device refresh rate
 * @param  Ctx Component object pointer
 * @param  RefreshCount The refresh rate to be programmed
 * @retval error status
 */
int32_t IS42S32800G_RefreshRate(SDRAM_HandleTypeDef *Ctx, uint32_t RefreshCount)
{
    /* Set the device refresh rate */
    if (HAL_SDRAM_ProgramRefreshRate(Ctx, RefreshCount) != HAL_OK)
    {
        return IS42S32800G_ERROR;
    }
    else
    {
        return IS42S32800G_OK;
    }
}

/**
 * @brief  Enter Power mode
 * @param  Ctx Component object pointer
 * @param  Interface Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
 * @retval error status
 */
int32_t IS42S32800G_EnterPowerMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface)
{
    Command.CommandMode = IS42S32800G_POWERDOWN_MODE_CMD;
    Command.CommandTarget = Interface;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    if (HAL_SDRAM_SendCommand(Ctx, &Command, IS42S32800G_TIMEOUT) != HAL_OK)
    {
        return IS42S32800G_ERROR;
    }
    else
    {
        return IS42S32800G_OK;
    }
}

/**
 * @brief  Exit Power mode
 * @param  Ctx Component object pointer
 * @param  Interface Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
 * @retval error status
 */
int32_t IS42S32800G_ExitPowerMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface)
{
    Command.CommandMode = IS42S32800G_NORMAL_MODE_CMD;
    Command.CommandTarget = Interface;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;

    /* Send the command */
    if (HAL_SDRAM_SendCommand(Ctx, &Command, IS42S32800G_TIMEOUT) != HAL_OK)
    {
        return IS42S32800G_ERROR;
    }
    else
    {
        return IS42S32800G_OK;
    }
}

/**
 * @brief  Sends command to the SDRAM bank.
 * @param  Ctx Component object pointer
 * @param  SdramCmd : Pointer to SDRAM command structure
 * @retval SDRAM status
 */
int32_t IS42S32800G_Sendcmd(SDRAM_HandleTypeDef *Ctx, FMC_SDRAM_CommandTypeDef *SdramCmd)
{
    if (HAL_SDRAM_SendCommand(Ctx, SdramCmd, IS42S32800G_TIMEOUT) != HAL_OK)
    {
        return IS42S32800G_ERROR;
    }
    else
    {
        return IS42S32800G_OK;
    }
}

/**
 * @}
 */

/** @defgroup IS42S32800G_Private_Functions IS42S32800G Private Functions
 * @{
 */

/**
 * @brief This function provides accurate delay (in milliseconds)
 * @param Delay : specifies the delay time length, in milliseconds
 * @retval IS42S32800G_OK
 */
static int32_t IS42S32800G_Delay(uint32_t Delay)
{
    uint32_t tickstart;
    tickstart = HAL_GetTick();
    while ((HAL_GetTick() - tickstart) < Delay)
    {
    }
    return IS42S32800G_OK;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
