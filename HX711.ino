#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

// Calibration factor for the scale
float calibrationFactor = 2280.0; // ปรับให้เหมาะสมตามน้ำหนักที่ทราบ

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {
  if (scale.is_ready()) {
    scale.set_scale(calibrationFactor); // ตั้งค่าปรับเทียบ
    Serial.println("Tare... remove any weights from the scale.");
    delay(5000);
    scale.tare();
    Serial.println("Tare done...");
    Serial.print("Place a known weight on the scale...");
    delay(5000);
    
    long reading = scale.get_units(10); // อ่านค่าเฉลี่ย 10 ครั้ง
    Serial.print("Result: ");
    Serial.print(reading); // แสดงน้ำหนักเป็นกรัม
    Serial.print(" g, ");
    
    // แปลงน้ำหนักเป็นกิโลกรัม
    float weightInKg = reading / 1000.0;
    Serial.print(weightInKg);
    Serial.println(" kg");
  } 
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}
