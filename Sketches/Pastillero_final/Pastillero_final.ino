#include <RTCZero.h>
#include<Wire.h> // librería para protocolo decomunucación I2C
RTCZero rtc; // reloj de tiempo real
int horas, minutos, fila = 6, columna = 13; int hm = -2, mm = -2, x = -2, y = -2, d = -2, e = -2;
byte direccion = 0x20, numero; // dirección del expansor de pines para esta ocación

// configurar hora del reloj del Arduino interno
const byte seconds = 0;
const byte minutes = 18;
const byte hours =  20;

// Vector de botones
int boton[6] = {0, 1, 2, 3, 4, 5}; // vector que indica los pines de cada uno de los botones de las taapas del pastillero
int entrada[6] = {1, 1, 1, 1, 1, 1}; // Vector que indica los estados lógicos de los botones

// vector de dosis de pastillas. para base de datos
int reporte[6] = {2, 2, 2, 2, 2, 2}; // Vector que se usará para reportar informaciónint

int horario [6][13] = {
  {1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 2, 3},
  {1, 0, 0, 3, 1, 0, 0, 4, 1, 0, 0, 5, 1},
  {1, 0, 0, 6, 1, 0, 0, 7, 1, 0, 0, 8, 2},
  {2, 0, 2, 0, 2, 0, 1, 0, 1, 0, 1, 1, 1},
  {1, 0, 1, 2, 1, 0, 1, 3, 1, 0, 1, 4, 3},
  {1, 0, 1, 5, 1, 0, 1, 6, 1, 0, 1, 7, 1}
};


void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < fila; i++) {
    
    pinMode(boton[i], INPUT); // decalración de los pines de los botones como entradas
  }
  Serial.begin(9600);
  rtc.begin(); // initialize RTC
  // Set the time
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
  pinMode(6, OUTPUT); // pin que tiene LED instlado en Arduino
  Wire.begin(); // iniciando el bus I2C del Arduuino
  Wire.beginTransmission(direccion); // dirección que configura
  Wire.write(0x00); // accediendo al registro IODIRA
  Wire.write(0x00); // configurando el puerto A como salida
  Wire.endTransmission();
  Wire.beginTransmission(direccion);
  Wire.write(0x01); // accediendo al redistor de control de puerto B
  Wire.write(0x00); // congurando el puerto B como salida
  Wire.endTransmission();
  limpiar(); // inciar  rutina de limpieza
}


void loop() {
  // put your main code here, to run repeatedly:
  reloj(); // acceder al RTC del Arduino
  for (int i = 0; i < fila; i++) {
    x = horario[i][0];
    y = horario[i][1];
    hm = 10 * x + y; // hora de la matriz
    x = horario[i][2];
    y = horario[i][3];
    mm = 10 * x + y; // minutos de la matriz
    /*Serial.print("Hora:");
      Serial.println(hm);
      Serial.print("Minutos:");
      Serial.println(mm);
      delay(1000);*/
    if (hm == horas && mm == minutos) {
      Serial.println("Las horas encajan");
      Serial.print("Pastilla numero:");
      e = i + 1; // guardando espacio
      Serial.println(e);
      d = horario[i][columna - 1]; // guardando dosis
      Serial.print("Dosis:");
      Serial.println(d);
      reporte[i] = 0;
      operar(d, e, 1); //operar utiliza: la dosis de la fila, el espacio, y el último numero es la duración de la alarma en minutos
      limpiar();
      alarma(0, 0); // aapaga el zumbador y el motor vibrador conectados en los pines 6 y 7 del pueto B del expansor de pines
      for (int i = 0; i < fila; i++) {
        entrada[i] = 1; // reinicia la entradas a su estado original
      }
    }
    else {
      //Serial.println("Esperando programa...");
      x = horario[i][4];
      y = horario[i][5];
      hm = 10 * x + y;
      x = horario[i][6];
      y = horario[i][7];
      mm = 10 * x + y;
      /*Serial.print("Hora 2:");
        Serial.println(hm);
        Serial.print("Minutos 2:");
        Serial.println(mm);
        delay(1000);*/
      if (hm == horas && mm == minutos) {
        Serial.println("Las horas 2 encajan");
        Serial.print("Pastilla numero:");
        e = i + 1; // guardando espacio
        Serial.println(e);
        d = horario[i][columna - 1];
        Serial.print("Dosis:");
        Serial.println(d);
        reporte[i] = 0;
        operar(d, e, 1);
        limpiar();
        alarma(0, 0); // aapaga el zumbador y el motor vibrador conectados en los pines 6 y 7 del pueto B del expansor de pines
        for (int i = 0; i < fila; i++) {
          entrada[i] = 1; // reinicia la entradas a su estado original
        }
      }
      else {
        x = horario[i][8];
        y = horario[i][9];
        hm = 10 * x + y;
        x = horario[i][10];
        y = horario[i][11];
        mm = 10 * x + y;
        /*Serial.print("Hora 3:");
          Serial.println(hm);
          Serial.print("Minutos 3:");
          Serial.println(mm);
          delay(1000);*/
        if (hm == horas && mm == minutos) {
          Serial.println("Las horas 3 encajan");
          Serial.print("Pastilla numero:");
          e = i + 1; // guardando espacio
          Serial.println(e);
          d = horario[i][columna - 1];
          Serial.print("Dosis:");
          Serial.println(d);
          reporte[i] = 0;
          operar(d, e, 1);
          limpiar();
          alarma(0, 0); // aapaga el zumbador y el motor vibrador conectados en los pines 6 y 7 del pueto B del expansor de pines
          for (int i = 0; i < fila; i++) {
            entrada[i] = 1; // reinicia la entradas a su estado original
          }
        }
        else {
          Serial.println("No hay alarma para esta pastilla");
          delay(1000);
        }
      }

    }
  }
}


/// codigos internos : 


void reloj() {
  horas = rtc.getHours(); // Medir horas del RTC
  Serial.print("hora RTC:");
  Serial.println(horas);
  minutos = rtc.getMinutes(); // Medir minutos del RTC
  Serial.print("minutos RTC:");
  Serial.println(minutos);
}

void operar(int numero, int espacio, int tiempo) {
  int segundos;
  rtc.setSeconds(0); // asegurando que quede en cero segundos

  do {
operar:
    if (entrada[espacio - 1] == 1) {
      entrada[espacio - 1] = digitalRead(boton[espacio - 1]); //leer el botón del espacio donde
      // se debe sacar la medicina siempre que su valor sea alto
    }
    segundos = rtc.getSeconds();
    Serial.println(segundos);
    delay(1000);
    if (entrada[espacio - 1] == 1) {
      // deplegar la información acerca de la dosis
      Serial.println("Cumple: brillar");
      digitalWrite(6, 1); // prender LED interno
      sieteSeg(numero); // mostrar la cantidad de la dosis en un dislay 7seg
      alarma(1, espacio); //  activar zumbador, vibrador y prender el LED del compartimiento de la dosis
      delay(1000); //
      alarma(0, espacio); // Apagar para mantener un sonido intermitente
    }
    else if (entrada[espacio - 1 == 0]) {
      // caso en que la tapa fue abierta
      Serial.println("Tapa abierta");
      limpiar();
      alarma(0, 0);
      //dosis[espacio - 1] = 0; // dar por tomada esta dosis para poder seguir con la siguiente
      reporte[espacio - 1] = 1; // guardar en el reporte que esa pastilla fue tomada
      delay(500);
    }
    else {
      Serial.println("Esperando...");
      limpiar();
      alarma(0, 0);
    }
  }  while (segundos < tiempo * 59); // realizar toda esta operación sólo durante el tiempo especificado

  informe();
}


void informe() {
  int hora_informe, minuto_informe;
  for (int i = 0; i < fila; i++) {
    if (reporte[i] == 0 || reporte[i] == 1) { // se buscan las posiciones programadas 0 significa que nunca se tomó y 1 que sí
      Serial.print("Medicina en espacio ");
      Serial.print(i + 1);
      Serial.print(":");
      if (reporte[i] == 0) {
        Serial.println("No tomada");
        reporte[i] = 2; // se reinicia su posición para prepararse para la próxima hora
      }
      else {
        Serial.println("Tomada");
        reporte[i] = 2;
      }
    }
  }
  Serial.print("Hora del reporte:");
  hora_informe = rtc.getHours();
  Serial.print(hora_informe);
  Serial.print(":");
  Serial.println(rtc.getMinutes());

}


void sieteSeg(int numero) {
  //  aquí se hace una adaptación del número entero a su equivalente en código de 7 segmentos
  switch (numero) {
    case 1:
      uno();
      break;
    case 2:
      dos();
      break;
    case 3:
      tres();
      break;
    default:
      limpiar();
      break;
  }
}

void alarma (boolean estado, int led) {
  // activación de las alarmas del pastillero y  del LED de la medicina a tomar
  byte luz = 0; // este byte representa la ubicación donde está el LED a prender
  if (led > 0) {
    // ubicar el  comopartimiento del LED a prender
    luz = ubicarPin(led);
  }
  if (estado == 1) {
    Wire.beginTransmission(direccion); // configuración del integrado como esclavo
    Wire.write(0x13); // accediendo al puerto B
    Wire.write(0xC0 + luz); // activar alarma y vibraador en el pin 6 y 7 del puerto B junto con el led correspondiente
    Wire.endTransmission();
  }
  else {
    Wire.beginTransmission(direccion);
    Wire.write(0x13); //puerto B
    Wire.write(0x00); // desactivar alarma, vibrador y LED
    Wire.endTransmission();

  }
}

byte ubicarPin(int terminal) {
  // la fórmula para covertir de entero a byte (binario) se halló por inspección
  byte pin = pow(2, terminal - 1);
  return pin;
}

void limpiar() {
  // limpieza de los dos puertos
  //Serial.println("Limpiando...");
  Wire.beginTransmission(direccion);
  Wire.write(0x12); // acccediendo al puerto A
  Wire.write(0x00); // limpiando puerto
  Wire.endTransmission();
  Wire.beginTransmission(direccion);
  Wire.write(0x13); // accediendo al puerto B
  Wire.write(0x00); // limpiando puerto
  Wire.endTransmission();

}

void cero() {
  Wire.beginTransmission(direccion);
  Wire.write(0x12); //
  Wire.write(0x7e); //
  Wire.endTransmission();
}

void uno() {
  Wire.beginTransmission(direccion);
  Wire.write(0x12); // accediendo a puerto A
  Wire.write(0x30); // Número en 7 segmentos
  Wire.endTransmission();
}

void dos() {
  Wire.beginTransmission(direccion);
  Wire.write(0x12); // accediendo a puerto A
  Wire.write(0x6d); // Número en 7 segmentos
  Wire.endTransmission();
}

void tres() {
  Wire.beginTransmission(direccion);
  Wire.write(0x12); // accediendo a puerto A
  Wire.write(0x79); // Número en 7 segmentos
  Wire.endTransmission();
}


