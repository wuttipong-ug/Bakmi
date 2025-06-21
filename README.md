# Bakmi
for Bakmi Boards
# Bakmi Library for STM32F103

## 📌 Overview

`Bakmi` is an Arduino library designed for STM32F103 boards.  
It provides simple control over:
- Dual DC motors (via PWM)
- A servo motor
- DIP Switches (for mode selection)
- Start buttons (2 types)
- Configurable analog inputs with threshold comparison

---

## 📐 Pin Mapping (Predefined)

| Function             | STM32F103 Pin     |
|----------------------|-------------------|
| Motor 1              | PA0 (A), PA1 (B)   |
| Motor 2              | PA3 (A), PA8 (B)   |
| Servo                | PA11              |
| DIP Switches         | PB7, PB8, PB9     |
| Start Manual (pullup)| PB10              |
| Start Module (input) | PB11              |
| Analog Inputs        | PA2, PA4, PA5, PA6, PA7, PB0, PB1 *(selectable)*



