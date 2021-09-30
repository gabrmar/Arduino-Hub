int y = 0, x = 0;
float integral = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  y = x;
  integral = integrar(integral, y);
  Serial.print("Valor:");
  Serial.println(y);
  Serial.print("integracion:");
  Serial.println(integral);
  x = x + 1;
  delay(1000);

}

float integrar(float y0, float yi) {
  float suma = y0 + yi;
  return suma;
}


