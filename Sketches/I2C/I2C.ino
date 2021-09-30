#include<Wire.h>
int n=0x00;
void setup() {
  Wire.begin(); // wake up I2C bus
  // set I/O pins to outputs
  Wire.beginTransmission(0x20);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission(0x20);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();

}

void loop() {
  // put your main code here, to run repeatedly:  
Wire.beginTransmission(0x20);
Wire.write(0x12); // address port A
Wire.write(n); // value to send
Wire.endTransmission();
n=n+1;
delay(120);
}
