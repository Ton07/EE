#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;  // พินสำหรับ HX711 DOUT
const int LOADCELL_SCK_PIN = 3;   // พินสำหรับ HX711 SCK
const int relayPin = 4;           // พินควบคุมรีเลย์

HX711 scale;

// Calibration factor for the scale
float calibrationFactor = 2280.0; // ปรับให้เหมาะสมตามน้ำหนักที่ทราบ

// E18-D80NK sensor pin
const int sensorPin = 2;          // เปลี่ยนพินสำหรับเซ็นเซอร์ E18-D80NK
int statusVal = 0;
int count = 0;                    // ตัวแปรนับจำนวนวัตถุที่พบ
const float thresholdWeight = 1000.0; // น้ำหนักที่กำหนด (กรัม)

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  pinMode(sensorPin, INPUT);      // ตั้งค่าเซ็นเซอร์เป็น Input
  pinMode(relayPin, OUTPUT);      // ตั้งค่ารีเลย์เป็น Output
  digitalWrite(relayPin, LOW);    // ปิดมอเตอร์เริ่มต้น
}

void loop() {
  // การอ่านน้ำหนัก
  if (scale.is_ready()) {
    scale.set_scale(calibrationFactor); // ตั้งค่าปรับเทียบ
    long reading = scale.get_units(10); // อ่านค่าเฉลี่ย 10 ครั้ง
    Serial.print("Weight: ");
    Serial.print(reading);
    Serial.print(" g, ");
    
    // แปลงน้ำหนักเป็นกิโลกรัม
    float weightInKg = reading / 1000.0;
    Serial.print(weightInKg);
    Serial.println(" kg");

    // การตรวจสอบน้ำหนักและการควบคุมมอเตอร์
    if (weightInKg < (thresholdWeight / 1000.0)) {
      // อ่านค่าจากเซ็นเซอร์
      statusVal = digitalRead(sensorPin); // อ่านค่าจากเซ็นเซอร์

      if (statusVal == LOW) { // ถ้ามีวัตถุ (OFF)
        count++; // เพิ่มจำนวน
        Serial.print("Object detected! Count: ");
        Serial.print(count);
        Serial.println(" objects detected.");
        digitalWrite(relayPin, HIGH); // เปิดมอเตอร์
      } else { // ถ้าไม่มีวัตถุ (ON)
        Serial.println("No Object Detected.");
        digitalWrite(relayPin, LOW); // ปิดมอเตอร์
      }
    } else {
      // ถ้าน้ำหนักมากกว่าที่กำหนด ให้ปิดมอเตอร์
      Serial.println("Weight limit exceeded! Motor stopped.");
      digitalWrite(relayPin, LOW); // ปิดมอเตอร์
    }
  } 
  else {
    Serial.println("HX711 not found.");
  }

  delay(500); // Delay for stability
}
