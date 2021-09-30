int conteo = 0, x=0, y=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  Serial.begin(9600);
}

void loop() {
  x = digitalRead(7);
  y = digitalRead(8);

  if (x == 1) {
    conteo = conteo + 1;
  }
  if (y == 1) {
    conteo = conteo - 1;
  }
  Serial.println(conteo);
  delay(1000);
}
