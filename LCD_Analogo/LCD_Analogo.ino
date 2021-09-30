#include<LiquidCrystal.h>
float T = 0, valor = 0; // lm35=100, cad=5/1023;
int rs = 8, e = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3, c = 16, r = 2; // RW conectado a Vss
LiquidCrystal lcd(rs, e, d4, d5, d6, d7); //Declaración de una variable tipo LCD 
void setup() {
  // put your setup code here, to run once:
  lcd.begin(c, r); // dimensionando colmunas y filas del LCD
  lcd.print("LCD analogo");
  lcd.setCursor(0, 1);
  lcd.print("con Arduino");
  delay(4000);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  valor = analogRead(0); // lectura en puerto A0
  lcd.clear();
  lcd.print("Valor=");
  lcd.print(valor);
  delay(200);

}
