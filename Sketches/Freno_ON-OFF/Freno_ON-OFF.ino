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
double freno = 0.7; // limitador del estado ON  del controlador

void setup() {
  // put your setup code here, to run once:
  pinMode(salida, OUTPUT);
  bienvenida();
}

void loop() {
  // put your main code here, to run repeatedly:
  actuador(CT);
  temp = leerTemperatura(entrada);
  /*Serial.print(temp);
    Serial.println("Centigrados");*/
  estado();
  CT = controlador(CT);



}
void bienvenida() {
  lcd.begin(c, r); // dimensionando colmunas y filas del LCD
  lcd.setCursor(0, 0);
  lcd.print("Control ON-OFF ");
  lcd.setCursor(0, 1);
  lcd.print("de Temperatura");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Freno de ");
  lcd.print(freno);
  delay(2000);
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

float leerTemperatura(int puerto) {
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

double controlador (double CT) {
  if (temp > sp) {
    CT = 0;
  }
  else {
    CT = freno;
  }
  return CT;
}
