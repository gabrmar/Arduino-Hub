#include "SoftwareSerial.h" //Libreria para emular puerto serial
SoftwareSerial Serial2(3, 2); // RX, TX
void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
}
void loop() {
  if (Serial2.available()) {
    char a = Serial2.read();
    Serial.print(a);
  }
  if (Serial.available()) {
    char a = Serial.read();
    Serial.print(a);
  }
}
