// Bakmi.h
#ifndef BAKMI_H
#define BAKMI_H

#include <Arduino.h>
#include <Servo.h>

class Bakmi {
public:
    Bakmi();
    void begin();

    // Motor Control
    void forward(int pwm);
    void backward(int pwm);
    void turnLeft(int pwml, int pwmr);
    void turnRight(int pwml, int pwmr);
    void brake(int pwm);

    // Servo Control
    void writeServo(uint8_t angle);

    // DIP Switch Mode (1-8)
    uint8_t getMode();

    // Start Module
    void update();
    bool startModuleState();
    bool startManualState();

    // Analog Input
    void setAnalogPins(const uint8_t* pins, const int* thresholds, uint8_t count);
    bool checkThreshold(uint8_t index);
    int readAnalog(uint8_t index);
private:
    void setMotor(uint8_t a, uint8_t b, int pwm);

    Servo _servo;

    // Analog config
    static const uint8_t MAX_ANALOG = 7;
    uint8_t _analogPins[MAX_ANALOG];
    int _thresholds[MAX_ANALOG];
    uint8_t _analogCount;

    // Start module state
    bool _startModuleState;
    

};

#endif
