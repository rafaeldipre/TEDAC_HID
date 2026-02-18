# TEDAC AH-64D — Notas de Implementación STM32H723ZGT6

Referencia técnica para no repetir los mismos bugs en futuras implementaciones
de USB HID + ADC DMA + GPIO en la familia STM32H7.

---

## 1. ADC con DMA Circular — STM32H723

### Bugs que genera CubeMX (NO confiar en el código generado para ADC multicanal)

CubeMX genera la configuración ADC incorrecta cuando se configuran múltiples
canales. Siempre verificar y corregir manualmente:

| Campo HAL | Valor CubeMX (MAL) | Valor correcto |
|---|---|---|
| `ScanConvMode` | `ADC_SCAN_DISABLE` | `ADC_SCAN_ENABLE` |
| `NbrOfConversion` | `1` | número real de canales (ej. 6) |
| `EOCSelection` | `ADC_EOC_SINGLE_CONV` | `ADC_EOC_SEQ_CONV` |
| `Overrun` | `ADC_OVR_DATA_PRESERVED` | `ADC_OVR_DATA_OVERWRITTEN` |
| Canales en secuencia | Repetidos/incorrectos | Verificar Rank1..N sin duplicados |

### Registro PCSEL_RES0 (crítico para STM32H723)

El STM32H723 requiere preseleccionar cada canal ADC en el registro PCSEL
**antes** de habilitar el ADC (ADEN=0). Sin esto el ADC muestrea entradas
flotantes silenciosamente.

- En el struct `ADC_TypeDef` del H723, este registro se llama `PCSEL_RES0`
  (nombre compartido con la reserva del ADC3).
- **DEBE escribirse en `USER CODE BEGIN ADC1_Init 1`**, antes de `HAL_ADC_Init()`.
- Si se escribe después (con ADEN=1), el hardware ignora el write sin error.

```c
/* USER CODE BEGIN ADC1_Init 1 */
__HAL_RCC_ADC12_CLK_ENABLE();  // necesario para acceder al registro
ADC1->PCSEL_RES0 = (1UL << 3)   /* CH3  = PA6 */
                 | (1UL << 7)   /* CH7  = PA7 */
                 | (1UL << 10)  /* CH10 = PC0 */
                 | (1UL << 11)  /* CH11 = PC1 */
                 | (1UL << 14)  /* CH14 = PA2 */
                 | (1UL << 15); /* CH15 = PA3 */
/* USER CODE END ADC1_Init 1 */
```

### Pinout ADC1 — 6 ejes joystick

| Pin | Canal ADC | Rank | adc_buf[] | Eje HID |
|-----|-----------|------|-----------|---------|
| PA6 | ADC1_IN3  | 1    | [0]       | X Axis  |
| PA7 | ADC1_IN7  | 2    | [1]       | Y Axis  |
| PA2 | ADC1_IN14 | 3    | [2]       | Z Axis  |
| PA3 | ADC1_IN15 | 4    | [3]       | X Rotation |
| PC0 | ADC1_IN10 | 5    | [4]       | Y Rotation |
| PC1 | ADC1_IN11 | 6    | [5]       | Z Rotation |

Wiring potenciómetros: 3V3 → extremo A, GND → extremo B, WIPER → pin ADC.
GPIO mode: Analog, NoPull.

### Configuración HAL correcta completa

```c
hadc1.Init.ClockPrescaler        = ADC_CLOCK_ASYNC_DIV2;
hadc1.Init.Resolution            = ADC_RESOLUTION_16B;
hadc1.Init.ScanConvMode          = ADC_SCAN_ENABLE;
hadc1.Init.EOCSelection          = ADC_EOC_SEQ_CONV;
hadc1.Init.LowPowerAutoWait      = DISABLE;
hadc1.Init.ContinuousConvMode    = ENABLE;
hadc1.Init.NbrOfConversion       = 6;
hadc1.Init.DiscontinuousConvMode = DISABLE;
hadc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
hadc1.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
hadc1.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;
hadc1.Init.LeftBitShift          = ADC_LEFTBITSHIFT_NONE;
hadc1.Init.OversamplingMode      = DISABLE;
```

### Verificación por debugger (comandos GDB)

Después de flash, suspender y ejecutar:

```
p/x ADC1->CR          // bit0=ADEN=1, bit2=ADSTART=1 → ADC corriendo
p/x ADC1->CFGR        // bits1:0=0b11=DMA circular, bit13=CONT=1
p/x ADC1->SQR1        // bits3:0=L=5(6conv), verificar SQ1..SQ4
p/x ADC1->SQR2        // verificar SQ5=10(CH10), SQ6=11(CH11)
p/x ADC1->PCSEL_RES0  // debe tener bits 3,7,10,11,14,15 en 1
p/x ADC1->ISR         // bit0=ADRDY, bit3=EOS esperados
p adc_buf[0]          // valor entre 0 y 65535
```

---

## 2. DMA + D-Cache — STM32H7

### Problema

El Cortex-M7 tiene D-Cache de 16KB. Si el buffer DMA está en RAM_D1
(caché habilitada), la CPU lee valores viejos del caché aunque el DMA
haya escrito nuevos valores.

### Solución — doble defensa

**A) Buffer en RAM_D2 (preferido):**

RAM_D2 (0x30000000) es accesible por DMA1/DMA2 y puede marcarse
non-cacheable por MPU. Los buffers DMA SIEMPRE deben estar aquí.

```c
// Declaración
volatile uint16_t adc_buf[6] __attribute__((section(".RAM_D2")));

// Linker script (STM32H723ZGTX_FLASH.ld)
.RAM_D2 (NOLOAD) :
{
    . = ALIGN(4);
    *(.RAM_D2)
    *(.RAM_D2.*)
    . = ALIGN(4);
} >RAM_D2
```

**B) MPU non-cacheable para RAM_D2:**

```c
// En MPU_Config(), añadir Region 1 después de la region background:
MPU_InitStruct.Number          = MPU_REGION_NUMBER1;
MPU_InitStruct.BaseAddress     = 0x30000000;
MPU_InitStruct.Size            = MPU_REGION_SIZE_32KB;
MPU_InitStruct.SubRegionDisable = 0x00;
MPU_InitStruct.TypeExtField    = MPU_TEX_LEVEL1;   // TEX=1, C=0, B=0
MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
MPU_InitStruct.DisableExec     = MPU_INSTRUCTION_ACCESS_DISABLE;
MPU_InitStruct.IsShareable     = MPU_ACCESS_NOT_SHAREABLE;
MPU_InitStruct.IsCacheable     = MPU_ACCESS_NOT_CACHEABLE;
MPU_InitStruct.IsBufferable    = MPU_ACCESS_NOT_BUFFERABLE;
HAL_MPU_ConfigRegion(&MPU_InitStruct);
```

**C) Invalidar caché en callbacks (defensa adicional):**

```c
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
        SCB_InvalidateDCache_by_Addr((uint32_t *)adc_buf, sizeof(adc_buf));
}
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
        SCB_InvalidateDCache_by_Addr((uint32_t *)adc_buf, sizeof(adc_buf));
}
```

---

## 3. USB Custom HID — Report Buffer y Endpoint

### Bug: buffer en stack

`USBD_CUSTOM_HID_SendReport` inicia una transmisión DMA. Si el buffer
está en el stack de una función, cuando la función retorna el stack se
reutiliza y el DMA lee datos corruptos.

```c
// MAL — buffer local en stack:
void JOYSTICK_SendReport(void) {
    uint8_t report[21];  // ← peligroso con USB DMA
    ...
    USBD_CUSTOM_HID_SendReport(..., report, 21);
}

// BIEN — buffer estático en memoria fija:
static uint8_t report[21];
void JOYSTICK_SendReport(void) { ... }
```

### Bug: saturación del endpoint

Si se llama `USBD_CUSTOM_HID_SendReport` mientras el endpoint IN está
ocupado, retorna `USBD_BUSY` y en algunas versiones del middleware deja
el estado interno corrupto, bloqueando futuros envíos.

Siempre verificar el estado antes de enviar:

```c
void JOYSTICK_SendReport(void)
{
    USBD_CUSTOM_HID_HandleTypeDef *hhid =
        (USBD_CUSTOM_HID_HandleTypeDef *)hUsbDeviceHS.pClassData;

    if (hhid == NULL || hhid->state == CUSTOM_HID_BUSY)
        return;  // el próximo tick del timer enviará con valores frescos

    // ... empaquetar report ...
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceHS, report, sizeof(report));
}
```

### Conversión ADC → HID axis

El ADC produce valores unsigned 16-bit (0–65535).
El descriptor HID declara ejes signed 16-bit (-32768–32767).

```c
int16_t val = (int16_t)((int32_t)adc_buf[i] - 32768);
report[i * 2]     = (uint8_t)(val & 0xFF);       // byte bajo
report[i * 2 + 1] = (uint8_t)((val >> 8) & 0xFF); // byte alto
```

### Descriptor HID — estructura del report (21 bytes)

```
Bytes  0-11 : 6 ejes × 2 bytes (signed 16-bit, little-endian)
Bytes 12-20 : 69 botones en 9 bytes (72 bits = 69 bits datos + 3 bits padding)
```

```c
// Descriptor:
0x75, 0x10,  // Report Size (16)
0x95, 0x06,  // Report Count (6)   → 6 ejes
0x81, 0x02,  // Input (Data, Var, Abs)

0x75, 0x01,  // Report Size (1)
0x95, 0x45,  // Report Count (69)  → 69 botones
0x81, 0x02,  // Input (Data, Var, Abs)

0x75, 0x01,  // Report Size (1)
0x95, 0x03,  // Report Count (3)   → 3 bits padding
0x81, 0x01,  // Input (Const)
```

---

## 4. GPIO — Botones digitales

### Configuración

- Mode: `GPIO_MODE_INPUT`
- Pull: `GPIO_PULLUP` (lógica invertida: RESET = pulsado)

### Lectura

```c
// Botón pulsado cuando el pin lee LOW (PULLUP + switch a GND)
if (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET)
    report[12 + (i / 8)] |= (1U << (i % 8));
```

### Distribución de pines — 69 botones

| Botones | Puerto | Pines |
|---------|--------|-------|
| 01-16   | GPIOE  | PE0-PE15 |
| 17-29   | GPIOD  | PD8-PD12, PD0-PD7 |
| 30-43   | GPIOB  | PB0-PB13 |
| 44-53   | GPIOC  | PC4-PC13 |
| 54-60   | GPIOF  | PF0-PF6 |
| 61-69   | GPIOG  | PG6-PG14 |

---

## 5. Arquitectura de memoria STM32H723

| Región | Dirección | Tamaño | Uso |
|--------|-----------|--------|-----|
| FLASH  | 0x08000000 | 1MB | Código |
| RAM_D1 (AXI) | 0x24000000 | 320KB | Stack, heap, variables generales |
| RAM_D2 | 0x30000000 | 32KB | **Buffers DMA** (DMA1/DMA2) |
| RAM_D3 | 0x38000000 | 16KB | Buffers DMA4/BDMA |
| DTCMRAM | 0x20000000 | 128KB | Variables críticas de tiempo real |

**Regla:** Todo buffer que use DMA1 o DMA2 **DEBE** estar en RAM_D2.
DMA1/DMA2 no pueden acceder a RAM_D1 (bus AXI, dominio D1).

---

## 6. Checklist para nuevas implementaciones ADC+DMA+HID

- [ ] Buffer DMA en RAM_D2 con `__attribute__((section(".RAM_D2")))`
- [ ] Sección `.RAM_D2 (NOLOAD)` en linker script apuntando a `>RAM_D2`
- [ ] MPU Region non-cacheable para 0x30000000 (32KB)
- [ ] `PCSEL_RES0` escrito **antes** de `HAL_ADC_Init()` (con ADEN=0)
- [ ] `ScanConvMode = ADC_SCAN_ENABLE`
- [ ] `NbrOfConversion` igual al número real de canales
- [ ] `EOCSelection = ADC_EOC_SEQ_CONV`
- [ ] `Overrun = ADC_OVR_DATA_OVERWRITTEN`
- [ ] Canales en Rank1..N sin duplicados, en orden correcto
- [ ] `HAL_ADCEx_Calibration_Start` antes de `HAL_ADC_Start_DMA`
- [ ] Report buffer USB declarado `static`, no en stack
- [ ] Verificar `hhid->state != CUSTOM_HID_BUSY` antes de `SendReport`
- [ ] GPIOs analógicos: mode=Analog, pull=NoPull
- [ ] GPIOs digitales: mode=Input, pull=PullUp (si switch a GND)
