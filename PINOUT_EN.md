# TEDAC HID — Pin Assignment

**MCU:** STM32H723ZGT6 (LQFP144)
**Board:** EC Buying FK723M1-ZGT6 V1.0
**Firmware:** 72 digital buttons + 6 analog axes

---

## Analog Axes (ADC1 — circular DMA)

| # | STM32 Pin | ADC1 Channel | HID Axis | Function        |
|---|-----------|--------------|----------|-----------------|
| 1 | PA6       | CH3          | X        | Joystick X      |
| 2 | PA7       | CH7          | Y        | Joystick Y      |
| 3 | PA2       | CH14         | Z        | Joystick Z      |
| 4 | PA3       | CH15         | Rx       | Rotation X      |
| 5 | PC0       | CH10         | Ry       | Rotation Y      |
| 6 | PC1       | CH11         | Rz       | Rotation Z      |

> HID range: –32768 to +32767 (signed 16-bit). Potentiometers: 3V3 — wiper — GND.

---

## Digital Buttons

Internal pull-up enabled. Active-low logic (GND = pressed).

### TDU (Tactical Display Unit) — BTN 01–21

| HID # | Name                | STM32 Pin | Port   | Pin # |
|-------|---------------------|-----------|--------|-------|
| 01    | TDU TAD             | PE0       | GPIOE  | 0     |
| 02    | TDU FCR             | PE1       | GPIOE  | 1     |
| 03    | TDU PNV             | PE2       | GPIOE  | 2     |
| 04    | TDU GS              | PE3       | GPIOE  | 3     |
| 05    | TDU AZ              | PE4       | GPIOE  | 4     |
| 06    | TDU SW6             | PE5       | GPIOE  | 5     |
| 07    | TDU SW7             | PE6       | GPIOE  | 6     |
| 08    | TDU LMC             | PE7       | GPIOE  | 7     |
| 09    | TDU CAGE            | PE8       | GPIOE  | 8     |
| 10    | TDU RF UP           | PE9       | GPIOE  | 9     |
| 11    | TDU RF DOWN         | PE10      | GPIOE  | 10    |
| 12    | TDU EL UP           | PE11      | GPIOE  | 11    |
| 13    | TDU EL DOWN         | PE12      | GPIOE  | 12    |
| 14    | TDU SYM UP          | PE13      | GPIOE  | 13    |
| 15    | TDU SYM DOWN        | PE14      | GPIOE  | 14    |
| 16    | TDU BRT UP          | PE15      | GPIOE  | 15    |
| 17    | TDU BRT DOWN        | PD8       | GPIOD  | 8     |
| 18    | TDU COM UP          | PD9       | GPIOD  | 9     |
| 19    | TDU COM DOWN        | PD10      | GPIOD  | 10    |
| 20    | TDU DAY             | PD11      | GPIOD  | 11    |
| 21    | TDU NT              | PD12      | GPIOD  | 12    |

### LHG (Left Hand Grip) — BTN 22–47

| HID # | Name                | STM32 Pin | Port   | Pin # |
|-------|---------------------|-----------|--------|-------|
| 22    | LHG SW1             | PD0       | GPIOD  | 0     |
| 23    | LHG SW2             | PD1       | GPIOD  | 1     |
| 24    | LHG SW3             | PD2       | GPIOD  | 2     |
| 25    | LHG SW4             | PD3       | GPIOD  | 3     |
| 26    | LHG SW5             | PD4       | GPIOD  | 4     |
| 27    | LHG HAT1 UP         | PD5       | GPIOD  | 5     |
| 28    | LHG HAT1 DOWN       | PD6       | GPIOD  | 6     |
| 29    | LHG HAT1 LEFT       | PD7       | GPIOD  | 7     |
| 30    | LHG HAT1 RIGHT      | PB0       | GPIOB  | 0     |
| 31    | LHG HAT2 UP         | PB1       | GPIOB  | 1     |
| 32    | LHG HAT2 DOWN       | PB2       | GPIOB  | 2     |
| 33    | LHG HAT2 LEFT       | PB3       | GPIOB  | 3     |
| 34    | LHG HAT2 RIGHT      | PB4       | GPIOB  | 4     |
| 35    | LHG HAT3 UP         | PB5       | GPIOB  | 5     |
| 36    | LHG HAT3 DOWN       | PB6       | GPIOB  | 6     |
| 37    | LHG HAT3 LEFT       | PB7       | GPIOB  | 7     |
| 38    | LHG HAT3 RIGHT      | PB8       | GPIOB  | 8     |
| 39    | LHG TEMP1 A         | PB9       | GPIOB  | 9     |
| 40    | LHG TEMP1 B         | PB10      | GPIOB  | 10    |
| 41    | LHG TEMP2 A         | PB11      | GPIOB  | 11    |
| 42    | LHG TEMP2 B         | PB12      | GPIOB  | 12    |
| 43    | LHG TEMP3 A         | PB13      | GPIOB  | 13    |
| 44    | LHG TEMP3 B         | PC4       | GPIOC  | 4     |
| 45    | LHG 3POS A          | PC5       | GPIOC  | 5     |
| 46    | LHG 3POS B          | PC6       | GPIOC  | 6     |
| 47    | LHG PUSH            | PC7       | GPIOC  | 7     |

### RHG (Right Hand Grip) — BTN 48–72

| HID # | Name                | STM32 Pin | Port   | Pin # |
|-------|---------------------|-----------|--------|-------|
| 48    | RHG SW1             | PC8       | GPIOC  | 8     |
| 49    | RHG SW2             | PC9       | GPIOC  | 9     |
| 50    | RHG SW3             | PC10      | GPIOC  | 10    |
| 51    | RHG SW4             | PC11      | GPIOC  | 11    |
| 52    | RHG SW5             | PC12      | GPIOC  | 12    |
| 53    | RHG SW6             | PC13      | GPIOC  | 13    |
| 54    | RHG SW7             | PF0       | GPIOF  | 0     |
| 55    | RHG HAT1 UP         | PF1       | GPIOF  | 1     |
| 56    | RHG HAT1 DOWN       | PF2       | GPIOF  | 2     |
| 57    | RHG HAT1 LEFT       | PF3       | GPIOF  | 3     |
| 58    | RHG HAT1 RIGHT      | PF4       | GPIOF  | 4     |
| 59    | RHG HAT2 UP         | PF5       | GPIOF  | 5     |
| 60    | RHG HAT2 DOWN       | PF6       | GPIOF  | 6     |
| 61    | RHG HAT2 LEFT       | PG6       | GPIOG  | 6     |
| 62    | RHG HAT2 RIGHT      | PG7       | GPIOG  | 7     |
| 63    | RHG TEMP A          | PG8       | GPIOG  | 8     |
| 64    | RHG TEMP B          | PG9       | GPIOG  | 9     |
| 65    | RHG 3POS1 A         | PG10      | GPIOG  | 10    |
| 66    | RHG 3POS1 B         | PG11      | GPIOG  | 11    |
| 67    | RHG 3POS2 A         | PG12      | GPIOG  | 12    |
| 68    | RHG 3POS2 B         | PG13      | GPIOG  | 13    |
| 69    | RHG PUSH            | PG14      | GPIOG  | 14    |
| 70    | TDU OFF *(new)*     | PG15      | GPIOG  | 15    |
| 71    | SPARE 1             | PF7       | GPIOF  | 7     |
| 72    | SPARE 2             | PF8       | GPIOF  | 8     |

> BTN 70 maps to the **Off** position of the TDU Day/NT/Off 3-position switch (DCS World has a separate binding for this position).
> BTN 71–72 are spare/reserve inputs.

---

## GPIO Port Summary

| Port   | Pins used              | Function                              |
|--------|------------------------|---------------------------------------|
| GPIOA  | PA2, PA3, PA6, PA7, PA11, PA12 | ADC Z/Rx, ADC X/Y, USB DP/DM  |
| GPIOB  | PB0–PB13               | LHG BTN 30–43                         |
| GPIOC  | PC0, PC1, PC4–PC13     | ADC Ry/Rz, LHG BTN 44–47, RHG BTN 48–53 |
| GPIOD  | PD0–PD12               | TDU BTN 17–21, LHG BTN 22–29          |
| GPIOE  | PE0–PE15               | TDU BTN 01–16                         |
| GPIOF  | PF0–PF8                | RHG BTN 54–60, Spare BTN 71–72        |
| GPIOG  | PG6–PG15               | RHG BTN 61–70                         |

---

## HID Report Format

| Bytes     | Content                                              |
|-----------|------------------------------------------------------|
| 0–11      | 6 analog axes (2 bytes each, signed 16-bit, little-endian) |
| 12–20     | 72 digital buttons (9 bytes, 1 bit per button)       |
| **Total** | **21 bytes**                                         |

Descriptor size: 49 bytes. No Report ID.
