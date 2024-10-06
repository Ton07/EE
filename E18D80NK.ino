const int sensorPin = 2; // ใช้พินดิจิตอล 2 สำหรับเซ็นเซอร์ E18-D80NK
int statusVal = 0;
int count = 0; // ตัวแปรนับจำนวนวัตถุที่พบ
const float thresholdDistance = 15.0; // ระยะที่ต้องการ (เช่น 15 เซนติเมตร)

void setup() {
  pinMode(sensorPin, INPUT); // ตั้งค่าเซ็นเซอร์เป็น Input
  Serial.begin(9600);
}

void loop() {
  statusVal = digitalRead(sensorPin); // อ่านค่าจากเซ็นเซอร์

  if (statusVal == LOW) { // ถ้ามีวัตถุ (OFF)
    count++; // เพิ่มจำนวน
    Serial.print("Object detected! Count: ");
    Serial.print(count);
    Serial.print(" objects detected within ");
    Serial.print(thresholdDistance);
    Serial.println(" cm."); // แสดงจำนวนวัตถุและระยะที่ตั้งไว้
    delay(1000); // หน่วงเวลา 1 วินาทีเพื่อไม่ให้เพิ่มจำนวนซ้ำ
  } else { // ถ้าไม่มีวัตถุ (ON)
    Serial.println("No Object Detected.");
  }

  delay(500); // Delay for stability
}
