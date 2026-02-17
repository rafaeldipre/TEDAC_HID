# TEDAC HID — AH-64D Apache TEDAC Electronics

Custom USB HID joystick firmware for the **AH-64D Apache TEDAC** (Target Acquisition Designation Sight / Pilot Night Vision Sensor), designed to work with **DCS World**.

This project provides the **electronics and firmware** for the incredible physical TEDAC build by **[MilKris666](https://github.com/MilKris666/-DCS-AH-64D-TEDAC-v2.0-)**. Huge thanks to MilKris666 for designing and sharing such a wonderful project with the community — your work made this possible!

## Hardware

- **MCU:** STM32H723ZGT6 (LQFP144)
- **Board:** EC Buying FK723M1-ZGT6 V1.0
- **USB:** OTG HS in Full-Speed mode (PA11/PA12)
- **IDE:** STM32CubeIDE

## Features

- **69 digital buttons** organized in 3 groups:
  - **TDU** (Tactical Display Unit) — 21 buttons
  - **LHG** (Left Hand Grip) — 26 buttons
  - **RHG** (Right Hand Grip) — 22 buttons
- **6 analog axes** (16-bit signed, -32768 to +32767):
  - X, Y, Z, Rx, Ry, Rz
- **USB Custom HID** with no Report ID for maximum DCS World compatibility
- **1ms USB poll interval** for fast input response
- **TIM15 interrupt-driven** report sending
- **ADC1 with circular DMA** for analog inputs (16-bit resolution)

## Pin Mapping

Detailed pin mapping documents are included in both English and Spanish:

- `PINOUT_FK723M1-ZGT6_EN.pdf` — English version
- `PINOUT_FK723M1-ZGT6.pdf` — Spanish version

### Analog Axes (ADC)

| Axis | STM32 Pin | Board Label | HID Axis |
|------|-----------|-------------|----------|
| 1    | PA6       | A6          | X        |
| 2    | PA7       | A7          | Y        |
| 3    | PA2       | A2          | Z        |
| 4    | PA3       | A3          | Rx       |
| 5    | PC0       | C0          | Ry       |
| 6    | PC1       | C1          | Rz       |

### Wiring

- **Buttons:** One terminal to the GPIO pin, the other to GND. Internal pull-up enabled — no external resistor needed.
- **Potentiometers:** 3V3 to one end, GND to the other end, wiper to the ADC pin.

## Building

1. Open the project in **STM32CubeIDE**
2. `Build Project` (Ctrl+B)
3. Connect ST-Link and flash via `Run As → STM32 C/C++ Application`

## Credits

- **TEDAC mechanical design:** [MilKris666 — DCS AH-64D TEDAC v2.0](https://github.com/MilKris666/-DCS-AH-64D-TEDAC-v2.0-) — Thank you for this amazing project and for sharing it with the community!
- **Electronics & firmware:** [rafaeldipre](https://github.com/rafaeldipre)

## License

This firmware project is provided as-is for personal/hobby use. The STM32 HAL drivers are licensed by STMicroelectronics under their respective terms.
