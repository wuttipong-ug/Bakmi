# Bakmi
for Bakmi Boards
## 📌 Overview

`Bakmi` is an Arduino library designed for STM32F103 boards.  
It provides control over:
- Dual DC motors (PWM)
- A servo motor
- DIP Switches (PB7–PB9)
- Start Module and Manual Buttons (PB11, PB10)
- Configurable analog inputs with thresholds

## Pin Mapping
| Function             | STM32F103 Pin     |
|----------------------|-------------------|
| Motor 1              | PA0, PA1          |
| Motor 2              | PA3, PA8          |
| Servo                | PA11              |
| DIP Switches         | PB7, PB8, PB9     |
| Start Manual         | PB10 (Pull-up)    |
| Start Module         | PB11              |
| Analog Inputs        | PA2, PA4, PA5, PA6, PA7, PB0, PB1

## Setup Example
```cpp
Bakmi bakmi;
bakmi.begin();
uint8_t pins[] = {PA2, PA4};
int th[] = {500, 600};
bakmi.setAnalogPins(pins, th, 2);
```

## License
MIT