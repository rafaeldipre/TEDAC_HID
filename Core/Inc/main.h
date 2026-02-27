/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#define BTN_03_TDU_PNV_Pin GPIO_PIN_2
#define BTN_03_TDU_PNV_GPIO_Port GPIOE
#define BTN_04_TDU_GS_Pin GPIO_PIN_3
#define BTN_04_TDU_GS_GPIO_Port GPIOE
#define BTN_05_TDU_AZ_Pin GPIO_PIN_4
#define BTN_05_TDU_AZ_GPIO_Port GPIOE
#define BTN_06_TDU_SW6_Pin GPIO_PIN_5
#define BTN_06_TDU_SW6_GPIO_Port GPIOE
#define BTN_07_TDU_SW7_Pin GPIO_PIN_6
#define BTN_07_TDU_SW7_GPIO_Port GPIOE
#define BTN_53_RHG_SW6_Pin GPIO_PIN_13
#define BTN_53_RHG_SW6_GPIO_Port GPIOC
#define BTN_54_RHG_SW7_Pin GPIO_PIN_0
#define BTN_54_RHG_SW7_GPIO_Port GPIOF
#define BTN_55_RHG_HAT1_UP_Pin GPIO_PIN_1
#define BTN_55_RHG_HAT1_UP_GPIO_Port GPIOF
#define BTN_56_RHG_HAT1_DOWN_Pin GPIO_PIN_2
#define BTN_56_RHG_HAT1_DOWN_GPIO_Port GPIOF
#define BTN_57_RHG_HAT1_LEFT_Pin GPIO_PIN_3
#define BTN_57_RHG_HAT1_LEFT_GPIO_Port GPIOF
#define BTN_58_RHG_HAT1_RIGHT_Pin GPIO_PIN_4
#define BTN_58_RHG_HAT1_RIGHT_GPIO_Port GPIOF
#define BTN_59_RHG_HAT2_UP_Pin GPIO_PIN_5
#define BTN_59_RHG_HAT2_UP_GPIO_Port GPIOF
#define BTN_60_RHG_HAT2_DOWN_Pin GPIO_PIN_6
#define BTN_60_RHG_HAT2_DOWN_GPIO_Port GPIOF
#define BTN_44_LHG_TEMP3_B_Pin GPIO_PIN_4
#define BTN_44_LHG_TEMP3_B_GPIO_Port GPIOC
#define BTN_45_LHG_3POS_A_Pin GPIO_PIN_5
#define BTN_45_LHG_3POS_A_GPIO_Port GPIOC
#define BTN_30_LHG_HAT1_RIGHT_Pin GPIO_PIN_0
#define BTN_30_LHG_HAT1_RIGHT_GPIO_Port GPIOB
#define BTN_31_LHG_HAT2_UP_Pin GPIO_PIN_1
#define BTN_31_LHG_HAT2_UP_GPIO_Port GPIOB
#define BTN_32_LHG_HAT2_DOWN_Pin GPIO_PIN_2
#define BTN_32_LHG_HAT2_DOWN_GPIO_Port GPIOB
#define BTN_08_TDU_LMC_Pin GPIO_PIN_7
#define BTN_08_TDU_LMC_GPIO_Port GPIOE
#define BTN_09_TDU_CAGE_Pin GPIO_PIN_8
#define BTN_09_TDU_CAGE_GPIO_Port GPIOE
#define BTN_10_TDU_RF_UP_Pin GPIO_PIN_9
#define BTN_10_TDU_RF_UP_GPIO_Port GPIOE
#define BTN_11_TDU_RF_DOWN_Pin GPIO_PIN_10
#define BTN_11_TDU_RF_DOWN_GPIO_Port GPIOE
#define BTN_12_TDU_EL_UP_Pin GPIO_PIN_11
#define BTN_12_TDU_EL_UP_GPIO_Port GPIOE
#define BTN_13_TDU_EL_DOWN_Pin GPIO_PIN_12
#define BTN_13_TDU_EL_DOWN_GPIO_Port GPIOE
#define BTN_14_TDU_SYM_UP_Pin GPIO_PIN_13
#define BTN_14_TDU_SYM_UP_GPIO_Port GPIOE
#define BTN_15_TDU_SYM_DOWN_Pin GPIO_PIN_14
#define BTN_15_TDU_SYM_DOWN_GPIO_Port GPIOE
#define BTN_16_TDU_BRT_UP_Pin GPIO_PIN_15
#define BTN_16_TDU_BRT_UP_GPIO_Port GPIOE
#define BTN_40_LHG_TEMP1_B_Pin GPIO_PIN_10
#define BTN_40_LHG_TEMP1_B_GPIO_Port GPIOB
#define BTN_41_LHG_TEMP2_A_Pin GPIO_PIN_11
#define BTN_41_LHG_TEMP2_A_GPIO_Port GPIOB
#define BTN_42_LHG_TEMP2_B_Pin GPIO_PIN_12
#define BTN_42_LHG_TEMP2_B_GPIO_Port GPIOB
#define BTN_43_LHG_TEMP3_A_Pin GPIO_PIN_13
#define BTN_43_LHG_TEMP3_A_GPIO_Port GPIOB
#define BTN_17_TDU_BRT_DOWN_Pin GPIO_PIN_8
#define BTN_17_TDU_BRT_DOWN_GPIO_Port GPIOD
#define BTN_18_TDU_COM_UP_Pin GPIO_PIN_9
#define BTN_18_TDU_COM_UP_GPIO_Port GPIOD
#define BTN_19_TDU_COM_DOWN_Pin GPIO_PIN_10
#define BTN_19_TDU_COM_DOWN_GPIO_Port GPIOD
#define BTN_20_TDU_DAY_Pin GPIO_PIN_11
#define BTN_20_TDU_DAY_GPIO_Port GPIOD
#define BTN_21_TDU_NT_Pin GPIO_PIN_12
#define BTN_21_TDU_NT_GPIO_Port GPIOD
#define BTN_61_RHG_HAT2_LEFT_Pin GPIO_PIN_6
#define BTN_61_RHG_HAT2_LEFT_GPIO_Port GPIOG
#define BTN_62_RHG_HAT2_RIGHT_Pin GPIO_PIN_7
#define BTN_62_RHG_HAT2_RIGHT_GPIO_Port GPIOG
#define BTN_63_RHG_TEMP_A_Pin GPIO_PIN_8
#define BTN_63_RHG_TEMP_A_GPIO_Port GPIOG
#define BTN_46_LHG_3POS_B_Pin GPIO_PIN_6
#define BTN_46_LHG_3POS_B_GPIO_Port GPIOC
#define BTN_47_LHG_PUSH_Pin GPIO_PIN_7
#define BTN_47_LHG_PUSH_GPIO_Port GPIOC
#define BTN_48_RHG_SW1_Pin GPIO_PIN_11
#define BTN_48_RHG_SW1_GPIO_Port GPIOF
#define BTN_49_RHG_SW2_Pin GPIO_PIN_12
#define BTN_49_RHG_SW2_GPIO_Port GPIOF
#define BTN_50_RHG_SW3_Pin GPIO_PIN_10
#define BTN_50_RHG_SW3_GPIO_Port GPIOC
#define BTN_51_RHG_SW4_Pin GPIO_PIN_11
#define BTN_51_RHG_SW4_GPIO_Port GPIOC
#define BTN_52_RHG_SW5_Pin GPIO_PIN_12
#define BTN_52_RHG_SW5_GPIO_Port GPIOC
#define BTN_22_LHG_SW1_Pin GPIO_PIN_0
#define BTN_22_LHG_SW1_GPIO_Port GPIOD
#define BTN_23_LHG_SW2_Pin GPIO_PIN_1
#define BTN_23_LHG_SW2_GPIO_Port GPIOD
#define BTN_24_LHG_SW3_Pin GPIO_PIN_2
#define BTN_24_LHG_SW3_GPIO_Port GPIOD
#define BTN_25_LHG_SW4_Pin GPIO_PIN_3
#define BTN_25_LHG_SW4_GPIO_Port GPIOD
#define BTN_26_LHG_SW5_Pin GPIO_PIN_4
#define BTN_26_LHG_SW5_GPIO_Port GPIOD
#define BTN_27_LHG_HAT1_UP_Pin GPIO_PIN_5
#define BTN_27_LHG_HAT1_UP_GPIO_Port GPIOD
#define BTN_28_LHG_HAT1_DOWN_Pin GPIO_PIN_6
#define BTN_28_LHG_HAT1_DOWN_GPIO_Port GPIOD
#define BTN_29_LHG_HAT1_LEFT_Pin GPIO_PIN_7
#define BTN_29_LHG_HAT1_LEFT_GPIO_Port GPIOD
#define BTN_64_RHG_TEMP_B_Pin GPIO_PIN_9
#define BTN_64_RHG_TEMP_B_GPIO_Port GPIOG
#define BTN_65_RHG_3POS1_A_Pin GPIO_PIN_10
#define BTN_65_RHG_3POS1_A_GPIO_Port GPIOG
#define BTN_66_RHG_3POS1_B_Pin GPIO_PIN_11
#define BTN_66_RHG_3POS1_B_GPIO_Port GPIOG
#define BTN_67_RHG_3POS2_A_Pin GPIO_PIN_12
#define BTN_67_RHG_3POS2_A_GPIO_Port GPIOG
#define BTN_68_RHG_3POS2_B_Pin GPIO_PIN_13
#define BTN_68_RHG_3POS2_B_GPIO_Port GPIOG
#define BTN_69_RHG_PUSH_Pin GPIO_PIN_14
#define BTN_69_RHG_PUSH_GPIO_Port GPIOG
#define BTN_70_TDU_OFF_Pin GPIO_PIN_15
#define BTN_70_TDU_OFF_GPIO_Port GPIOG
#define BTN_71_SPARE1_Pin GPIO_PIN_7
#define BTN_71_SPARE1_GPIO_Port GPIOF
#define BTN_72_SPARE2_Pin GPIO_PIN_8
#define BTN_72_SPARE2_GPIO_Port GPIOF
#define BTN_33_LHG_HAT2_LEFT_Pin GPIO_PIN_3
#define BTN_33_LHG_HAT2_LEFT_GPIO_Port GPIOB
#define BTN_34_LHG_HAT2_RIGHT_Pin GPIO_PIN_4
#define BTN_34_LHG_HAT2_RIGHT_GPIO_Port GPIOB
#define BTN_35_LHG_HAT3_UP_Pin GPIO_PIN_5
#define BTN_35_LHG_HAT3_UP_GPIO_Port GPIOB
#define BTN_36_LHG_HAT3_DOWN_Pin GPIO_PIN_6
#define BTN_36_LHG_HAT3_DOWN_GPIO_Port GPIOB
#define BTN_37_LHG_HAT3_LEFT_Pin GPIO_PIN_7
#define BTN_37_LHG_HAT3_LEFT_GPIO_Port GPIOB
#define BTN_38_LHG_HAT3_RIGHT_Pin GPIO_PIN_8
#define BTN_38_LHG_HAT3_RIGHT_GPIO_Port GPIOB
#define BTN_39_LHG_TEMP1_A_Pin GPIO_PIN_9
#define BTN_39_LHG_TEMP1_A_GPIO_Port GPIOB
#define BTN_01_TDU_TAD_Pin GPIO_PIN_0
#define BTN_01_TDU_TAD_GPIO_Port GPIOE
#define BTN_02_TDU_FCR_Pin GPIO_PIN_1
#define BTN_02_TDU_FCR_GPIO_Port GPIOE
#define BTN_73_LHG_TRIG_POS1_Pin GPIO_PIN_13
#define BTN_73_LHG_TRIG_POS1_GPIO_Port GPIOD
#define BTN_74_LHG_TRIG_POS2_Pin GPIO_PIN_14
#define BTN_74_LHG_TRIG_POS2_GPIO_Port GPIOD
#define BTN_75_RHG_SW8_Pin GPIO_PIN_0
#define BTN_75_RHG_SW8_GPIO_Port GPIOG
#define BTN_76_RHG_SW9_Pin GPIO_PIN_1
#define BTN_76_RHG_SW9_GPIO_Port GPIOG
#define BTN_77_TEST1_Pin GPIO_PIN_14
#define BTN_77_TEST1_GPIO_Port GPIOB
#define BTN_78_TEST2_Pin GPIO_PIN_15
#define BTN_78_TEST2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
