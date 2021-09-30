// Librerías incluidas
#include<LiquidCrystal.h>
// Variables de entrada y salida
int salida = 13;
int entrada = 0;
int sp = 70;
float temp = 0;
// vairables para la pantalla LCD
int rs = 8, e = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3, c = 16, r = 2; // RW conectado a Vss
LiquidCrystal lcd(rs, e, d4, d5, d6, d7); // Declaración de una variable tipo LCD
// Variables internas
int T = 100; // periodo de la señal de PWM
double CT = 0.2; // ciclo de trabajo de la señal PWM
double kp = -3; //constante proporcional
double emin = -3; // error mínimo aceptable

void setup() {
  // put your setup code here, to run once:
  pinMode(salida, OUTPUT);
  bienvenida();
}

void loop() {
  // put your main code here, to run repeatedly:
  temp = leerTemperatura(entrada);
  /*Serial.print(temp);
    Serial.println("Centigrados");*/
  estado();
  CT = controlador(CT, temp, sp);
  actuador(CT);

}


void bienvenida() {
  lcd.begin(c, r); // dimensionando colmunas y filas del LCD
  lcd.setCursor(0, 0);
  lcd.print("Control P");
  lcd.setCursor(0, 1);
  lcd.print("de Temperatura");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set point");
  lcd.setCursor(0, 1);
  lcd.print(sp);
  lcd.print(" Celsius");
  delay(4000);
}

void actuador(float CT) {
  int ton = T * CT;
  int toff = T - ton;
  digitalWrite(salida, 1);
  delay(ton);
  digitalWrite(salida, 0);
  delay(toff);
}

double leerTemperatura(int puerto) {
  int digito = analogRead(puerto);
  float voltaje = digito * (5000 / 1023);
  float valor = voltaje / 10;
  return valor;

}

void estado() {
  lcd.clear();
  lcd.print(temp);
  lcd.print(" Celsius");
  lcd.setCursor(0, 1);
  lcd.print("Trabajo:");
  lcd.print(int(CT * 100));
  lcd.print("%");
}

double controlador (double CT, double temp, double sp) {
  double e = temp - sp;
  if (e > 0) {
    CT = 0;
  }
  else {
    double u = e * kp; // señal de control
    double kp2 = 1 / (emin * kp); // constante para adaptar la señal de contol a ciclo de trabajo
    if (e < emin) {
      u = emin * kp;
    }
    CT =  u * kp2; // calculado en excel

  }
  return CT;
}
