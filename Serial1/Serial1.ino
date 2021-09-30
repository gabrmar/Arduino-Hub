int ValorByte[2];   // for incoming serial data
void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
  for(int i=0;i<2;i++){
    ValorByte[i]=0;
    }
  for (int i = 0; i < 2; i++) {
    if (Serial.available() > 0) {
      // read the incoming byte
      ValorByte[i] = Serial.read();
      // say what you got:
      Serial.print("Dato: ");
      Serial.println(ValorByte[i], DEC);
      if (ValorByte > 50) {
        Serial.println("Cumple condicion");
      }
    }
  }
  Serial.print("Primer valor es: ");
  Serial.println(ValorByte[0]);
  Serial.print("Segundo valor es: ");
  Serial.println(ValorByte[1]);
  int suma = ValorByte[0] + ValorByte[1];
  Serial.print("Suma es: ");
  Serial.println(suma);
  delay(1000);
  // send data only when you receive data:

}
