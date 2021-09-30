int buzzer = 13, T = 5000, d = 500, aux = T, s = 1000, k = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  k = 0;
  Serial.println(T);
  for (int i = 0; i <= T; i++) {
    digitalWrite(buzzer, 1);
    delayMicroseconds(i / 2);
    digitalWrite(buzzer, 0);
    delayMicroseconds(i / 2);
  }

  T = T - s;
  delay(d);
  if (T == 0) {
    T = aux;
    delay(d);
  }
}
