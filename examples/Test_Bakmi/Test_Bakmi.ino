#include "Bakmi.h"

Bakmi bakmi;

// Define analog pins and thresholds
const uint8_t analogPins[] = {PA2, PA4, PA5}; // example analog pins
const int analogThresholds[] = {500, 600, 700};  // example thresholds for each analog pin

void setup() {
  Serial.begin(9600);
  bakmi.begin();  

  // set analog pins and thresholds
  bakmi.setAnalogPins(analogPins, analogThresholds, 3);

  // Set servo to initial position
  bakmi.writeServo(90);
  // botton start Munual
  while (bakmi.startManualState())
  {
    Serial.println("Waiting for start botton...");
  }
  
}

void loop() {
  bakmi.update();  // start module

  // DIP switch (1-8)
  uint8_t mode = bakmi.getMode();
  Serial.print("Mode: ");
  Serial.println(mode);

  //  threshold
  for (uint8_t i = 0; i < 3; i++) {
    int val = bakmi.readAnalog(i);
    bool ok = bakmi.checkThreshold(i);
    Serial.print("Analog["); Serial.print(i); Serial.print("] = ");
    Serial.print(val);
    Serial.print(" >= ");
    Serial.print(analogThresholds[i]);
    Serial.print(" ? ");
    Serial.println(ok ? "YES" : "NO");
  }

  // start module 
  if (bakmi.startModuleState()) {
    Serial.println("START MODULE ACTIVE");
    bakmi.forward(200);
    bakmi.writeServo(120);
  } else {
    bakmi.brake(255);
    bakmi.writeServo(90);
  }

  delay(500);
}
