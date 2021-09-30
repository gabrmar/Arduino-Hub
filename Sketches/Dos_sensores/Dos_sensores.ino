// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

float T, t, h, f, err, errp, mean;
#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //T = lm35();
  T = ntc();
  dht11();
  err = abs(T - t);
  errp = (err / t) * 100;
  mean = (T + t) / 2;
  Serial.println("Sensor de prueba:" + String(T) + "°C  " + "Referencia:" + String(t) + "°C  " + "Error:" + String(err) + "°C ," + "" + String(errp) + "%"  + " Promedio:" + String(mean) + "°C");

}


float lm35() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float milivoltage = sensorValue * (1 / 0.2046);
  float T =  milivoltage * 0.1;
  // print out the value you read:
  //Serial.println("Digito:" + String(sensorValue) + " " + "  Voltaje:" + String(milivoltage) + "mV" + "  Temperatura:" + String(T) + "°C");
  return T;
}

float ntc() {
  float R2 = 10020, c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
  int sensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  float R = R2 * ((5 / voltage) - 1);
  float T = (1.0 / (c1 + c2 * log(R) + c3 * pow(log(R), 3)));
  float C = T - 273.15;
  // print out the value you read:
  return C;
}

void dht11() {

  // Wait a few seconds between measurements.
  delay(1500);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}
