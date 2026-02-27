/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v1.0_Cube
  * @brief          : USB Device Custom HID interface file.
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
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */
#include "main.h"
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb custom HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_HS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 1 */
  0x05, 0x01,        // Usage Page (Generic Desktop)
  0x09, 0x04,        // Usage (Joystick)
  0xA1, 0x01,        // Collection (Application)

  // 6 axes: X, Y, Z, Rx, Ry, Rz — signed 16-bit
  0x05, 0x01,        //   Usage Page (Generic Desktop)
  0x09, 0x30,        //   Usage (X)
  0x09, 0x31,        //   Usage (Y)
  0x09, 0x32,        //   Usage (Z)
  0x09, 0x33,        //   Usage (Rx)
  0x09, 0x34,        //   Usage (Ry)
  0x09, 0x35,        //   Usage (Rz)
  0x16, 0x00, 0x80,  //   Logical Minimum (-32768)
  0x26, 0xFF, 0x7F,  //   Logical Maximum (32767)
  0x75, 0x10,        //   Report Size (16)
  0x95, 0x06,        //   Report Count (6)
  0x81, 0x02,        //   Input (Data, Var, Abs)

  // 78 buttons: 76 physical + 2 virtual (78 bits + 2-bit padding = 10 bytes)
  0x05, 0x09,        //   Usage Page (Button)
  0x19, 0x01,        //   Usage Minimum (1)
  0x29, 0x4E,        //   Usage Maximum (78)
  0x15, 0x00,        //   Logical Minimum (0)
  0x25, 0x01,        //   Logical Maximum (1)
  0x75, 0x01,        //   Report Size (1)
  0x95, 0x4E,        //   Report Count (78)
  0x81, 0x02,        //   Input (Data, Var, Abs)
  // 2-bit padding to reach byte boundary (80 bits = 10 bytes total)
  0x75, 0x02,        //   Report Size (2)
  0x95, 0x01,        //   Report Count (1)
  0x81, 0x03,        //   Input (Const, Var, Abs)

  /* USER CODE END 1 */
  0xC0               /*     END_COLLECTION             */
};
/* USER CODE BEGIN PRIVATE_VARIABLES */
extern volatile uint16_t adc_buf[6];
/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceHS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_HS(void);
static int8_t CUSTOM_HID_DeInit_HS(void);
static int8_t CUSTOM_HID_OutEvent_HS(uint8_t event_idx, uint8_t state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_HS =
{
  CUSTOM_HID_ReportDesc_HS,
  CUSTOM_HID_Init_HS,
  CUSTOM_HID_DeInit_HS,
  CUSTOM_HID_OutEvent_HS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_HS(void)
{
  /* USER CODE BEGIN 8 */
  return (USBD_OK);
  /* USER CODE END 8 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_HS(void)
{
  /* USER CODE BEGIN 9 */
  return (USBD_OK);
  /* USER CODE END 9 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_HS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 10 */
  UNUSED(event_idx);
  UNUSED(state);

    /* Start next USB packet transfer once data processing is completed */
  if (USBD_CUSTOM_HID_ReceivePacket(&hUsbDeviceHS) != (uint8_t)USBD_OK)
  {
    return -1;
  }

  return (USBD_OK);
  /* USER CODE END 10 */
}

/* USER CODE BEGIN 11 */

/* USER CODE END 11 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

static const GPIO_TypeDef* btn_port[76] = {
  GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE,  // BTN 01-08
  GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE,  // BTN 09-16
  GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,  // BTN 17-24
  GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOB, GPIOB, GPIOB,  // BTN 25-32
  GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB,  // BTN 33-40
  GPIOB, GPIOB, GPIOB, GPIOC, GPIOC, GPIOC, GPIOC, GPIOB,  // BTN 41-48
  GPIOB, GPIOC, GPIOC, GPIOC, GPIOC, GPIOF, GPIOF, GPIOF,  // BTN 49-56
  GPIOF, GPIOF, GPIOF, GPIOF, GPIOG, GPIOG, GPIOG, GPIOG,  // BTN 57-64
  GPIOG, GPIOG, GPIOG, GPIOG, GPIOG, GPIOG, GPIOF, GPIOF,  // BTN 65-72
  GPIOD, GPIOD,                                              // BTN 73-74
  GPIOG, GPIOG                                               // BTN 75-76
};

static const uint16_t btn_pin[76] = {
  GPIO_PIN_0,  GPIO_PIN_1,  GPIO_PIN_2,  GPIO_PIN_3,   // BTN 01-04 (PE0-PE3)
  GPIO_PIN_4,  GPIO_PIN_5,  GPIO_PIN_6,  GPIO_PIN_7,   // BTN 05-08 (PE4-PE7)
  GPIO_PIN_8,  GPIO_PIN_9,  GPIO_PIN_10, GPIO_PIN_11,  // BTN 09-12 (PE8-PE11)
  GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15,  // BTN 13-16 (PE12-PE15)
  GPIO_PIN_8,  GPIO_PIN_9,  GPIO_PIN_10, GPIO_PIN_11,  // BTN 17-20 (PD8-PD11)
  GPIO_PIN_12, GPIO_PIN_0,  GPIO_PIN_1,  GPIO_PIN_2,   // BTN 21-24 (PD12,PD0-PD2)
  GPIO_PIN_3,  GPIO_PIN_4,  GPIO_PIN_5,  GPIO_PIN_6,   // BTN 25-28 (PD3-PD6)
  GPIO_PIN_7,  GPIO_PIN_0,  GPIO_PIN_1,  GPIO_PIN_2,   // BTN 29-32 (PD7,PB0-PB2)
  GPIO_PIN_3,  GPIO_PIN_4,  GPIO_PIN_5,  GPIO_PIN_6,   // BTN 33-36 (PB3-PB6)
  GPIO_PIN_7,  GPIO_PIN_8,  GPIO_PIN_9,  GPIO_PIN_10,  // BTN 37-40 (PB7-PB10)
  GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_4,   // BTN 41-44 (PB11-PB13,PC4)
  GPIO_PIN_5,  GPIO_PIN_6,  GPIO_PIN_7,  GPIO_PIN_14,  // BTN 45-48 (PC5,PC6,PC7,PB14)
  GPIO_PIN_15, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12,  // BTN 49-52 (PB15,PC10,PC11,PC12)
  GPIO_PIN_13, GPIO_PIN_0,  GPIO_PIN_1,  GPIO_PIN_2,   // BTN 53-56 (PC13,PF0-PF2)
  GPIO_PIN_3,  GPIO_PIN_4,  GPIO_PIN_5,  GPIO_PIN_6,   // BTN 57-60 (PF3-PF6)
  GPIO_PIN_6,  GPIO_PIN_7,  GPIO_PIN_8,  GPIO_PIN_9,   // BTN 61-64 (PG6-PG9)
  GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13,  // BTN 65-68 (PG10-PG13)
  GPIO_PIN_14, GPIO_PIN_15, GPIO_PIN_7,  GPIO_PIN_8,   // BTN 69-72 (PG14,PG15,PF7,PF8)
  GPIO_PIN_13, GPIO_PIN_14,                             // BTN 73-74 (PD13,PD14)
  GPIO_PIN_0,  GPIO_PIN_1                               // BTN 75-76 (PG0,PG1)
};

void JOYSTICK_SendReport(void)
{
  static uint8_t report[22];
  const int32_t adc_max = 1023; /* ADC_RESOLUTION_10B */

  /* Skip if USB endpoint is busy — next timer tick will send fresh values */
  USBD_CUSTOM_HID_HandleTypeDef *hhid =
      (USBD_CUSTOM_HID_HandleTypeDef *)hUsbDeviceHS.pClassData;
  if (hhid == NULL || hhid->state == CUSTOM_HID_BUSY)
    return;

  /* Pack 6 axes: scale ADC raw value to signed HID range (-32768..32767) */
  for (uint8_t i = 0; i < 6; i++)
  {
    int32_t raw = adc_buf[i];
    if (raw < 0)
    {
      raw = 0;
    }
    else if (raw > adc_max)
    {
      raw = adc_max;
    }

    int32_t scaled = ((raw * 65535) / adc_max) - 32768;
    int16_t val = (int16_t)scaled;
    report[i * 2]     = (uint8_t)(val & 0xFF);
    report[i * 2 + 1] = (uint8_t)((val >> 8) & 0xFF);
  }

  /* Pack 78 buttons into 10 bytes (76 physical + 2 virtual, 78 bits + 2-bit padding)
   * Physical (BTN 01-76): GPIO_PIN_RESET (LOW) = pressed = bit 1
   * Virtual  (BTN 77-78): computed from GPIO states, ON = bit 1               */
  for (uint8_t i = 0; i < 10; i++)
  {
    report[12 + i] = 0;
  }

  for (uint8_t i = 0; i < 76; i++)
  {
    if (HAL_GPIO_ReadPin((GPIO_TypeDef*)btn_port[i], btn_pin[i]) == GPIO_PIN_RESET)
    {
      report[12 + (i / 8)] |= (1U << (i % 8));
    }
  }

  /* BTN77 Virtual A: ON when PF3 (RHG HAT1 LEFT) AND PF4 (RHG HAT1 RIGHT) are both NOT pressed
   * virtual_A = !(PF3 pressed || PF4 pressed)  →  bit index 76 = byte 21 bit 4 */
  if (HAL_GPIO_ReadPin(BTN_57_RHG_HAT1_LEFT_GPIO_Port,  BTN_57_RHG_HAT1_LEFT_Pin)  == GPIO_PIN_SET &&
      HAL_GPIO_ReadPin(BTN_58_RHG_HAT1_RIGHT_GPIO_Port, BTN_58_RHG_HAT1_RIGHT_Pin) == GPIO_PIN_SET)
  {
    report[12 + (76 / 8)] |= (1U << (76 % 8));
  }

  /* BTN78 Virtual B: ON when PD2 (LHG SW3) AND PD4 (LHG SW5) are both NOT pressed
   * virtual_B = !(PD2 pressed || PD4 pressed)  →  bit index 77 = byte 21 bit 5 */
  if (HAL_GPIO_ReadPin(BTN_24_LHG_SW3_GPIO_Port, BTN_24_LHG_SW3_Pin) == GPIO_PIN_SET &&
      HAL_GPIO_ReadPin(BTN_26_LHG_SW5_GPIO_Port, BTN_26_LHG_SW5_Pin) == GPIO_PIN_SET)
  {
    report[12 + (77 / 8)] |= (1U << (77 % 8));
  }

  USBD_CUSTOM_HID_SendReport(&hUsbDeviceHS, report, 22);
}

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
