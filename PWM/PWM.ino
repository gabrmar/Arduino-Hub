int pin = 9;  // pin con salida de PWM
int retraso = 100; // Valor del tiempo de espera
void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 255; i++) {
    analogWrite(pin, i);
    delay(retraso);
  }
  delay(2000);
  for (int i = 255; i > 0; i--) {
    analogWrite(pin, i);
    delay(retraso);
  }
  delay(2000);



}
