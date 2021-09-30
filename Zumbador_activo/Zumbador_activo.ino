int pwm = 11,B,d=100;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  B = 0;
  for (int i = 0; i < 256; i++) {
    analogWrite(pwm, i);
    B = i;
    Serial.println(B);
    delay(d);
  }
  delay(2000);
    for (int i = 255; i > 0; i--) {
    analogWrite(pwm, i);
    B = i;
    Serial.println(B);
    delay(d);
  }
  digitalWrite(pwm,1);
  delay(5000);
  digitalWrite(pwm,0);
  delay(5000);
}
