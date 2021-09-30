#include <LiquidCrystal.h>
/*Sección de variables
  La prmera sección de variables enteras son los pines
  correspondientes al LCD.  Luego avanzamos con las variables
  necesarias para la programación del tempriador. Entre ellas
  tenemos la variable que representa los minutos, las
  dimensionadoras del LCD y los extremos de durecion del parpadeo
  de la pantalla
*/
int rs = 7, e = 2, luz = 10, d4 = 3, d5 = 4, d6 = 5, d7 = 6, minutos = 60;
int col = 16, fila = 2;
int mini = 50,  maxi = 1000;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
  pinMode(luz, OUTPUT);
  lcd.begin(col, fila); //dimensionando la variable tipo
  // LiquidCrystal
  lcd.home(); // al origen de la pantalla. La parte más
  //superior izquierda.
  inicio();
}

void loop() {
  // put your main code here, to run repeatedly
  int timer = tempoReloj(minutos);
  //Parpadeo de pantalla
  luzTempo(minutos, timer, luz, mini, maxi);
  delay(mini); //retardo para visualuzar el mensaje sin problemas

}
// Rutina de incio del LCD
void inicio() {
  digitalWrite(luz, 1);
  lcd.home();
  lcd.write("Temporizador...");
  lcd.setCursor(0, 2);
  lcd.write("activado!!");
  delay(3000);
  lcd.clear();
  lcd.write("Usted tiene...");
  lcd.setCursor(0, 1);
  lcd.write("Un tiempo limite");
  delay(3000);
  lcd.clear();
  lcd.home();
  lcd.write("Buena suerte XD");
  delay(5000);
  lcd.clear();
  digitalWrite(luz, 0);
}
// Alternativas de temporizador
// Opera para décimas de segundo con 3 órdenes posibles
void temporizarDec(int minutos, int orden) {
  int sec = minutos * 60;
  int decSec = sec * 10;
  int timer = millis() / 100;
  int cuenta = decSec - timer + 10; //10 de correcion
  if (orden == 1) {
    lcd.clear();
    lcd.print(cuenta);
  }
  else if (orden == 2) {
    lcd.setCursor(3, 0);
    lcd.print(cuenta);
  }
  else if (orden == 3) {
    lcd.setCursor(6, 0);
    lcd.print(cuenta);
  }
}
/* Temporizar segundos con dos órdenes posibles y 2 tipos
  de temporizado:
  tipo =1; singifica que el temporuzador va a contar desde
  el equivalente en segundos de los minutos asignados por el
  programa hasta 0.
  tipo =2; este es el conteo tipo segundero. Empieza en 60
  y termina en 0 parra reiniciar este conteo hasta que se
  acaben los minutos asignados por el programa.
*/
void temporizarSec(int minutos, int orden, int tipo) {
  minutos = minutos - 1;
  int sec = minutos * 60;
  int timer = 0;
  int c = 0;
  int i = minutos;
  int cuenta = -1;
  if (tipo == 1) {
    timer = millis() / 1000;
    cuenta = sec - timer;
  }
  else if (tipo == 2) {
    timer = 0;
    for (int j = 0; j <= 60; j++) {
      timer = millis() / 1000 - 60 * c;
      if (timer > 59) {
        timer = 0;
        cuenta = 0;
        c = c + 1;
        i = i - 1;
      }
      else {
        cuenta = 60 - timer;
      }

    }
  }
  if (orden == 1) {
    lcd.clear();
  }
  else if (orden == 2) {

    if (i < 10) {
      lcd.setCursor(2, 0);
    }
    else {
      lcd.setCursor(3, 0);
    }
  }

  lcd.print(cuenta);

}
// Temporitzador de minutos sin orden ni tipo
int temporizarMin(int minutos) {
  int t = minutos - 1;
  int timer = (millis() / 1000) / 60;
  int cuenta = t - timer;
  lcd.clear();
  lcd.print(cuenta);
  return timer;
}

//Rutina principal del temporizador tipo reloj
int tempoReloj(int minutos) {
  digitalWrite(luz, 1); // en caso de que deshabilitar luzTempo
  int timer = temporizarMin(minutos);
  lcd.print(":");
  temporizarSec(minutos, 2, 2);
  //lcd.print(":");
  //temporizarDec(minutos,2);
  return timer;
}
int luzTempo(int minutos, int timer, int luz, int mini, int maxi) {
  minutos = minutos - 1;
  double m = (mini - maxi) / minutos;
  int   T = m * timer + maxi;
  digitalWrite(luz, 1);
  delay(abs(T));
  digitalWrite(luz, 0);
  delay(abs(T));
}


