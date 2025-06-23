// Bakmi.cpp
#include "Bakmi.h"

#define M1A PA0
#define M1B PA1
#define M2A PA3
#define M2B PA8
#define SERVO_PIN PA11

#define DIP1 PB7
#define DIP2 PB8
#define DIP3 PB9

#define START_MANUAL PB10  // Pullup
#define START_MODULE PB11  // Digital input

Bakmi::Bakmi() : _startModuleState(false), _analogCount(0) {}

void Bakmi::begin() {
    // Motor pins
    pinMode(M1A, OUTPUT);
    pinMode(M1B, OUTPUT);
    pinMode(M2A, OUTPUT);
    pinMode(M2B, OUTPUT);

    // Servo
    _servo.attach(SERVO_PIN);

    // DIP switches
    pinMode(DIP1, INPUT_PULLUP);
    pinMode(DIP2, INPUT_PULLUP);
    pinMode(DIP3, INPUT_PULLUP);

    // Start switches
    pinMode(START_MANUAL, INPUT_PULLUP);
    pinMode(START_MODULE, INPUT);
}

void Bakmi::setMotor(uint8_t a, uint8_t b, int pwm) {
    if (pwm >= 0) {
        analogWrite(a, pwm);
        analogWrite(b, 0);
    } else {
        analogWrite(a, 0);
        analogWrite(b, -pwm);
    }
}

void Bakmi::forward(int pwm) {
    setMotor(M1A, M1B, pwm);
    setMotor(M2A, M2B, pwm);
}

void Bakmi::backward(int pwm) {
    setMotor(M1A, M1B, -pwm);
    setMotor(M2A, M2B, -pwm);
}

void Bakmi::turnLeft(int pwml, int pwmr) {
    setMotor(M1A, M1B, pwml);
    setMotor(M2A, M2B, pwmr);
}

void Bakmi::turnRight(int pwml, int pwmr) {
    setMotor(M1A, M1B, pwml);
    setMotor(M2A, M2B, pwmr);
}

void Bakmi::brake(int pwm) {
    analogWrite(M1A, pwm);
    analogWrite(M1B, pwm);
    analogWrite(M2A, pwm);
    analogWrite(M2B, pwm);
}

void Bakmi::writeServo(uint8_t angle) {
    _servo.write(angle);
}

uint8_t Bakmi::getMode() {
    uint8_t val = (!digitalRead(DIP1) << 0) |
                  (!digitalRead(DIP2) << 1) |
                  (!digitalRead(DIP3) << 2);
    return val + 1;  // Return 1–8
}

void Bakmi::update() {
    _startModuleState = digitalRead(START_MODULE);
}

bool Bakmi::startModuleState() {
    return _startModuleState;
}

void Bakmi::setAnalogPins(const uint8_t* pins, const int* thresholds, uint8_t count) {
    _analogCount = min(count, MAX_ANALOG);
    for (uint8_t i = 0; i < _analogCount; i++) {
        _analogPins[i] = pins[i];
        _thresholds[i] = thresholds[i];
    }
}

bool Bakmi::checkThreshold(uint8_t index) {
    if (index >= _analogCount) return false;
    return analogRead(_analogPins[index]) >= _thresholds[index];
}

int Bakmi::readAnalog(uint8_t index) {
    if (index >= _analogCount) return -1;
    return analogRead(_analogPins[index]);
}

bool Bakmi::startManualState() {
    return !digitalRead(START_MANUAL);
}

