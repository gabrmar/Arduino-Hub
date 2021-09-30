// Medición de distancias por miedo del sensor ultrasónico
//HC-SR04
int trigger = 5, echo = 6, e6;
unsigned long t_h, t_l, t_echo_max = 23531, t_echo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigger, OUTPUT); //salida
  pinMode(echo, INPUT); //entrada
}

void loop() {
  float x = 0;
  t_l = 0;
  e6 = 1;
  digitalWrite(trigger, 0);
  delayMicroseconds(2);
  Serial.println("Activar");
  digitalWrite(trigger, 1);
  delayMicroseconds(10);
  digitalWrite(trigger, 0);
  t_echo = pulseIn(echo, HIGH);
  Serial.println(t_echo);
  if (t_echo > t_echo_max) {
    t_echo = t_echo_max;
  }
  Serial.print("Duracion pulso: ");
  Serial.println(t_echo);
  Serial.println("microsegundos");
  x = 0.017 * t_echo;
  if (x < 2) {
    Serial.println("-----");
  }
  else {
    Serial.print("Distancia: ");
    Serial.print(x);
    Serial.println("cm");
  }

  delay(500);


}
