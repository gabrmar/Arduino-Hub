int dato = -1, pin;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  inicio();


}

void loop() {
  // put your main code here, to run repeatedly:
  while (dato == -1) {
    if (Serial.available() > 0) {
      dato = Serial.read();
    }
  }
  pin = seleccionPin(dato);
  Serial.println("Iniciando prueba");
  delay(1000);
  pruebaServoTotal(pin);
}

void inicio() {
  int pin = 11;
  Serial.println("Rutina de prueba de servomotor");
  delay(2000);
  Serial.println("Puede usar los pines 9, 10 y 11 para la prueba");
  delay(2000);
  Serial.println("Escriba el valor del pin PWM para hacer la prueba");
}


int seleccionPin(int dato) {
  int nueve = 57, diez = 97, once = 98;
  int s = 0;
  if (dato == nueve) {
    pinMode(9, OUTPUT);
    s = 9;
  }
  else if (dato == diez) {
    pinMode(10, OUTPUT);
    s = 10;
  }
  else if (dato == once) {
    pinMode(11, OUTPUT);
    s = 11;
  }
  Serial.print("Pin seleccionado:");
  Serial.println(s);
  return s;
}

void pruebaServo(int pin) {
  int T = 2000; //periodo de la señal PWM del arduino UNO en microsegundos
  int PW = 500; // Ancho de pulso deseado en microsegundos
  int DC = 1500 / 2000; //ciclo de trabajo
  int valor = (PW * 100) / T; // adaptación de PW a valores en bits
  analogWrite(pin, valor);
}

void pruebaServoTotal(int pin) {
  int T = 2000;
  int PW = 800;
  double m=0.1275; //pendiete de relacta que relaciona PW con los bits del módulo PWM
  while (PW <= T) {
    Serial.println(m);
    int valor =m*PW;
    analogWrite(pin,valor);
    Serial.print(PW);
    Serial.print(",");
    Serial.println(valor);
    PW = PW + 50;
    delay(2000);
  }
}

