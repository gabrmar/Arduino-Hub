int pwm1 = 11, pwm2 = 10, pwm3 = 9,R=0,G=0,B=0, d=25;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  R=0;
  G=0;
  B=0;
  for (int i = 0; i < 256; i++) {
    analogWrite(pwm1, i);
    B=i;
    Serial.println(String(B)+","+String(R)+","+String(G));
    delay(d);
  }
  for (int i = 0; i < 256; i++) {
    analogWrite(pwm2, i);
    R=i;
    Serial.println(String(B)+","+String(R)+","+String(G));
    delay(d);
  }
    for (int i = 0; i < 256; i++) {
    analogWrite(pwm3, i);
    G=i;
    Serial.println(String(B)+","+String(R)+","+String(G));
    delay(d);
  }
  delay(4000);
    for (int i = 255; i > 0; i--) {
    analogWrite(pwm1, i);
    B=i;
    Serial.println(String(B)+","+String(R)+","+String(G));
    delay(d);
  }
    for (int i = 255; i > 0; i--) {
    analogWrite(pwm2, i);
    R=i;
    Serial.println(String(B)+","+String(R)+","+String(G));
    delay(d);
  }
      for (int i = 255; i > 0; i--) {
    analogWrite(pwm3  , i);
    G=i;
    Serial.println(String(B)+","+String(R)+","+String(G));
    delay(d);
  }
}
