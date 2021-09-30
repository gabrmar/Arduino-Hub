#include <OneWire.h>
#include <DallasTemperature.h>
#define pin 2 
OneWire oneWire(pin);
DallasTemperature sensors(&oneWire);
void setup() {
delay(500);
Serial.begin(9600);
sensors.begin();
}

void loop() {
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" grados centigrados");
  Serial.print(sensors.getTempFByIndex(0));
  Serial.println(" grados fahrenheit");
  delay(500);  

}
