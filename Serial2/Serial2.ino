void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int fila = Serial.available();
  Serial.println(fila);
  delay(500);
  if (fila >= 20) {
    while (fila > 0) {
      int dato = Serial.read();
      Serial.print("Dato: ");
      Serial.println(dato);
      Serial.print("Fila: ");
      Serial.println(fila);
      fila= fila-1;
      delay(500);
    }

  }
}

