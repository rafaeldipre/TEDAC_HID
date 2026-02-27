/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_custom_hid_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

TIM_HandleTypeDef htim15;

/* USER CODE BEGIN PV */
/*
 * CRITICAL: adc_buf MUST be in D2 SRAM (0x30000000) because DMA1 lives in the
 * D2 bus-matrix domain and CANNOT access D1 AXI SRAM (0x24000000 / RAM_D1).
 * Without this attribute the linker places it in .bss → RAM_D1 → DMA writes go nowhere.
 */
volatile uint16_t adc_buf[6] __attribute__((section(".RAM_D2")));
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM15_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM15_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buf, 6) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_Base_Start_IT(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_CRSInitTypeDef RCC_CRSInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 22;
  RCC_OscInitStruct.PLL.PLLP = 1;
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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the SYSCFG APB clock
  */
  __HAL_RCC_CRS_CLK_ENABLE();

  /** Configures CRS
  */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB2;
  RCC_CRSInitStruct.Polarity = RCC_CRS_SYNC_POLARITY_RISING;
  RCC_CRSInitStruct.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000,1000);
  RCC_CRSInitStruct.ErrorLimitValue = 34;
  RCC_CRSInitStruct.HSI48CalibrationValue = 32;

  HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_10B;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;        /* 6 channels */
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;       /* end of sequence */
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 6;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.Oversampling.Ratio = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /* Rank 1: IN3  = PA6  = X axis */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_387CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /* Rank 2: IN7  = PA7  = Y axis */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /* Rank 3: IN14 = PA2  = Z axis */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /* Rank 4: IN15 = PA3  = Rx axis */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /* Rank 5: IN10 = PC0  = Ry axis */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /* Rank 6: IN11 = PC1  = Rz axis */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN ADC1_Init 2 */

  /*
   * STM32H7 CRITICAL: PCSEL register must pre-select all channels before
   * starting conversions. Without this, the ADC samples floating inputs.
   * Bits correspond directly to channel numbers (bit N = channel N).
   */
  /* On STM32H723, ADC_TypeDef names this field PCSEL_RES0 (shared with ADC3
   * reservation), but it is the PCSEL register at offset 0x1C for ADC1/2. */
  ADC1->PCSEL_RES0 |= (1UL << 3)  /* IN3  = PA6 */
                    | (1UL << 7)  /* IN7  = PA7 */
                    | (1UL << 10) /* IN10 = PC0 */
                    | (1UL << 11) /* IN11 = PC1 */
                    | (1UL << 14) /* IN14 = PA2 */
                    | (1UL << 15);/* IN15 = PA3 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM15 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM15_Init(void)
{

  /* USER CODE BEGIN TIM15_Init 0 */

  /* USER CODE END TIM15_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM15_Init 1 */

  /* USER CODE END TIM15_Init 1 */
  htim15.Instance = TIM15;
  htim15.Init.Prescaler = 2750-1;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim15.Init.Period = 100-1;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim15.Init.RepetitionCounter = 0;
  htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM15_Init 2 */

  /* USER CODE END TIM15_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pins : BTN_03_TDU_PNV_Pin BTN_04_TDU_GS_Pin BTN_05_TDU_AZ_Pin BTN_06_TDU_SW6_Pin
                           BTN_07_TDU_SW7_Pin BTN_08_TDU_LMC_Pin BTN_09_TDU_CAGE_Pin BTN_10_TDU_RF_UP_Pin
                           BTN_11_TDU_RF_DOWN_Pin BTN_12_TDU_EL_UP_Pin BTN_13_TDU_EL_DOWN_Pin BTN_14_TDU_SYM_UP_Pin
                           BTN_15_TDU_SYM_DOWN_Pin BTN_16_TDU_BRT_UP_Pin BTN_01_TDU_TAD_Pin BTN_02_TDU_FCR_Pin */
  GPIO_InitStruct.Pin = BTN_03_TDU_PNV_Pin|BTN_04_TDU_GS_Pin|BTN_05_TDU_AZ_Pin|BTN_06_TDU_SW6_Pin
                          |BTN_07_TDU_SW7_Pin|BTN_08_TDU_LMC_Pin|BTN_09_TDU_CAGE_Pin|BTN_10_TDU_RF_UP_Pin
                          |BTN_11_TDU_RF_DOWN_Pin|BTN_12_TDU_EL_UP_Pin|BTN_13_TDU_EL_DOWN_Pin|BTN_14_TDU_SYM_UP_Pin
                          |BTN_15_TDU_SYM_DOWN_Pin|BTN_16_TDU_BRT_UP_Pin|BTN_01_TDU_TAD_Pin|BTN_02_TDU_FCR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_53_RHG_SW6_Pin BTN_44_LHG_TEMP3_B_Pin BTN_45_LHG_3POS_A_Pin BTN_46_LHG_3POS_B_Pin
                           BTN_47_LHG_PUSH_Pin BTN_50_RHG_SW3_Pin BTN_51_RHG_SW4_Pin BTN_52_RHG_SW5_Pin */
  GPIO_InitStruct.Pin = BTN_53_RHG_SW6_Pin|BTN_44_LHG_TEMP3_B_Pin|BTN_45_LHG_3POS_A_Pin|BTN_46_LHG_3POS_B_Pin
                          |BTN_47_LHG_PUSH_Pin|BTN_50_RHG_SW3_Pin
                          |BTN_51_RHG_SW4_Pin|BTN_52_RHG_SW5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_54_RHG_SW7_Pin BTN_55_RHG_HAT1_UP_Pin BTN_56_RHG_HAT1_DOWN_Pin BTN_57_RHG_HAT1_LEFT_Pin
                           BTN_58_RHG_HAT1_RIGHT_Pin BTN_59_RHG_HAT2_UP_Pin BTN_60_RHG_HAT2_DOWN_Pin
                           BTN_71_SPARE1_Pin BTN_72_SPARE2_Pin BTN_48_RHG_SW1_Pin BTN_49_RHG_SW2_Pin */
  GPIO_InitStruct.Pin = BTN_54_RHG_SW7_Pin|BTN_55_RHG_HAT1_UP_Pin|BTN_56_RHG_HAT1_DOWN_Pin|BTN_57_RHG_HAT1_LEFT_Pin
                          |BTN_58_RHG_HAT1_RIGHT_Pin|BTN_59_RHG_HAT2_UP_Pin|BTN_60_RHG_HAT2_DOWN_Pin
                          |BTN_71_SPARE1_Pin|BTN_72_SPARE2_Pin|BTN_48_RHG_SW1_Pin|BTN_49_RHG_SW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_30_LHG_HAT1_RIGHT_Pin BTN_31_LHG_HAT2_UP_Pin BTN_32_LHG_HAT2_DOWN_Pin BTN_40_LHG_TEMP1_B_Pin
                           BTN_41_LHG_TEMP2_A_Pin BTN_42_LHG_TEMP2_B_Pin BTN_43_LHG_TEMP3_A_Pin BTN_33_LHG_HAT2_LEFT_Pin
                           BTN_34_LHG_HAT2_RIGHT_Pin BTN_35_LHG_HAT3_UP_Pin BTN_36_LHG_HAT3_DOWN_Pin BTN_37_LHG_HAT3_LEFT_Pin
                           BTN_38_LHG_HAT3_RIGHT_Pin BTN_39_LHG_TEMP1_A_Pin BTN_77_TEST1_Pin BTN_78_TEST2_Pin */
  GPIO_InitStruct.Pin = BTN_30_LHG_HAT1_RIGHT_Pin|BTN_31_LHG_HAT2_UP_Pin|BTN_32_LHG_HAT2_DOWN_Pin|BTN_40_LHG_TEMP1_B_Pin
                          |BTN_41_LHG_TEMP2_A_Pin|BTN_42_LHG_TEMP2_B_Pin|BTN_43_LHG_TEMP3_A_Pin|BTN_33_LHG_HAT2_LEFT_Pin
                          |BTN_34_LHG_HAT2_RIGHT_Pin|BTN_35_LHG_HAT3_UP_Pin|BTN_36_LHG_HAT3_DOWN_Pin|BTN_37_LHG_HAT3_LEFT_Pin
                          |BTN_38_LHG_HAT3_RIGHT_Pin|BTN_39_LHG_TEMP1_A_Pin|BTN_77_TEST1_Pin|BTN_78_TEST2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_17_TDU_BRT_DOWN_Pin BTN_18_TDU_COM_UP_Pin BTN_19_TDU_COM_DOWN_Pin BTN_20_TDU_DAY_Pin
                           BTN_21_TDU_NT_Pin BTN_22_LHG_SW1_Pin BTN_23_LHG_SW2_Pin BTN_24_LHG_SW3_Pin
                           BTN_25_LHG_SW4_Pin BTN_26_LHG_SW5_Pin BTN_27_LHG_HAT1_UP_Pin BTN_28_LHG_HAT1_DOWN_Pin
                           BTN_29_LHG_HAT1_LEFT_Pin BTN_73_LHG_TRIG_POS1_Pin BTN_74_LHG_TRIG_POS2_Pin */
  GPIO_InitStruct.Pin = BTN_17_TDU_BRT_DOWN_Pin|BTN_18_TDU_COM_UP_Pin|BTN_19_TDU_COM_DOWN_Pin|BTN_20_TDU_DAY_Pin
                          |BTN_21_TDU_NT_Pin|BTN_22_LHG_SW1_Pin|BTN_23_LHG_SW2_Pin|BTN_24_LHG_SW3_Pin
                          |BTN_25_LHG_SW4_Pin|BTN_26_LHG_SW5_Pin|BTN_27_LHG_HAT1_UP_Pin|BTN_28_LHG_HAT1_DOWN_Pin
                          |BTN_29_LHG_HAT1_LEFT_Pin|BTN_73_LHG_TRIG_POS1_Pin|BTN_74_LHG_TRIG_POS2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_61_RHG_HAT2_LEFT_Pin BTN_62_RHG_HAT2_RIGHT_Pin BTN_63_RHG_TEMP_A_Pin BTN_64_RHG_TEMP_B_Pin
                           BTN_65_RHG_3POS1_A_Pin BTN_66_RHG_3POS1_B_Pin BTN_67_RHG_3POS2_A_Pin BTN_68_RHG_3POS2_B_Pin
                           BTN_69_RHG_PUSH_Pin BTN_70_TDU_OFF_Pin BTN_75_RHG_SW8_Pin BTN_76_RHG_SW9_Pin */
  GPIO_InitStruct.Pin = BTN_61_RHG_HAT2_LEFT_Pin|BTN_62_RHG_HAT2_RIGHT_Pin|BTN_63_RHG_TEMP_A_Pin|BTN_64_RHG_TEMP_B_Pin
                          |BTN_65_RHG_3POS1_A_Pin|BTN_66_RHG_3POS1_B_Pin|BTN_67_RHG_3POS2_A_Pin|BTN_68_RHG_3POS2_B_Pin
                          |BTN_69_RHG_PUSH_Pin|BTN_70_TDU_OFF_Pin|BTN_75_RHG_SW8_Pin|BTN_76_RHG_SW9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM15)
  {
    JOYSTICK_SendReport();
  }
}

/*
 * DCache invalidation callbacks — belt-and-suspenders defence.
 * RAM_D2 is already marked non-cacheable by MPU_Config (Region 1),
 * so these are normally no-ops. If the MPU were ever misconfigured,
 * these callbacks ensure the CPU sees fresh DMA data.
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1)
  {
    SCB_InvalidateDCache_by_Addr((uint32_t *)adc_buf, sizeof(adc_buf));
  }
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1)
  {
    SCB_InvalidateDCache_by_Addr((uint32_t *)adc_buf, sizeof(adc_buf));
  }
}
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /* Region 0: default — whole 4GB no-access background region */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /*
   * Region 1: RAM_D2 (0x30000000, 32K) — non-cacheable, non-bufferable.
   * DMA1 writes adc_buf[] here. The D-Cache must NOT cache this region or
   * the CPU will read stale values. TEX=1, C=0, B=0 = Normal, non-cacheable.
   */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.BaseAddress = 0x30000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_32KB;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

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
#ifdef USE_FULL_ASSERT
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
