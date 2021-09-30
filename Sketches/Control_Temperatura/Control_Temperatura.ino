float T, sp =35 ;
int salida = 13;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(salida, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float valor = analogRead(0); // lectura en puerto A0
  float voltaje = valor * (5000 / 1023);
  T = voltaje / 10;
  Serial.print(T);
  Serial.println(" grados centrigrados");
  if (T >= sp) {
    digitalWrite(salida, 0);
  }
  else {
    digitalWrite(salida, 1);
  }
  delay(100);

}
