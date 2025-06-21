#include "Bakmi.h"

Bakmi bakmi;

// กำหนดพิน Analog ที่ต้องการใช้งาน
const uint8_t analogPins[] = {PA2, PA4, PA5};
const int analogThresholds[] = {500, 600, 700};  // เทียบแต่ละช่อง

void setup() {
  Serial.begin(9600);
  bakmi.begin();  // เริ่มใช้งาน

  // ตั้งค่าพิน analog และ threshold
  bakmi.setAnalogPins(analogPins, analogThresholds, 3);

  // ตั้งเซอร์โวเริ่มต้น
  bakmi.writeServo(90);
  // botton start Munual
  while (bakmi.startManualState())
  {
    Serial.println("Waiting for start botton...");
  }
  
}

void loop() {
  bakmi.update();  // อ่านค่า start module

  // อ่านโหมดจาก DIP switch (1-8)
  uint8_t mode = bakmi.getMode();
  Serial.print("Mode: ");
  Serial.println(mode);

  // ตรวจ threshold
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

  // ถ้า start module ถูกกด (PB11 == HIGH)
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
