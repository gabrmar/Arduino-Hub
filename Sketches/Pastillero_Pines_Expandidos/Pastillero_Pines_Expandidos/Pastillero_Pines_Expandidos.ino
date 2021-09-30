#include<Wire.h> // librería para protocolo decomunucación I2C
#include <RTCZero.h>
RTCZero rtc;
int  tiempo, adaptado, fila = 6, columna = 24, cont, hora_informe = -1, a = -1;
unsigned long c = 0; // variable larga por el tamaño de los números a almacenar
byte direccion = 0x20, numero; // dirección del expansor de pines para esta ocación
// numero será el dato a desplegar en un display de 7 segmentos

// Vector de botones
int boton[6] = {0, 1, 2, 3, 4, 5}; // vector que indica los pines de cada uno de los botones de las taapas del pastillero
int entrada[6] = {1, 1, 1, 1, 1, 1}; // Vector que indica los estados lógicos de los botones

// vector de dosis de pastillas
int dosis[6] = {0, 0, 0, 0, 0, 0}; // alamacena las cantidades de los medicamentos a mostrar
int reporte[6] = {2, 2, 2, 2, 2, 2}; // Vector que se usará para reportar información

/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 0;
const byte hours = 0 ;



// matriz  de horarios

int horario[6][24] = {
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < fila; i++) {
    pinMode(boton[i], INPUT); // decalración de los pines de los botones como entradas
  }
  rtc.begin(); // initialize RTC
  // Set the time
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
  Serial.begin(9600);
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
  tiempo = contador(); // inicia la medición de tiempo del programa principal
  //Serial.println(tiempo);
  delay(5000);
  if (hora_informe != tiempo) {
    cont = comparacion(tiempo); // muestra  la cantidad de medicamentos a tomar de un índice de la matriz
    //delay(5000);
    if (cont > 0) {
      buscarDosis();
      Serial.print("a=");
      Serial.println(a);
      if (a != -1) {
        operar(dosis[a], a + 1, 1); // operar tiene tres parámetros: el valor a mostrar, el espacio del pastillero
        // y el tiempo en que la alarma debe estar sonando en minutos
      }
      limpiar();
      alarma(0, 0); // aapaga el zumbador y el motor vibrador conectados en los pines 6 y 7 del pueto B del expansor de pines
      for (int i = 0; i < fila; i++) {
        entrada[i] = 1; // reinicia la entradas a su estado original
      }
    }
    // apagar LED interno del Arduino
    // asegurar que no haya ningún mensaje o LED prendido mientras no se cuenten medicamentos
    digitalWrite(6, 0);
    limpiar();
    alarma(0, 0);

  }
  Serial.print("Esperando proxima hora:");
  Serial.print(tiempo);
  Serial.print(":");
  Serial.println(rtc.getMinutes());
  // Si ya se presentó un informe para ese tiempo, entonces no hacer nada más que mostrar la hora, sino se proce a hacer lo qye ya se hace

}

int contador() {
  // contador  obtiene los segundos y minutos transcurridos con base en métodos propios del Arduino
  int hora = rtc.getHours(); // La hora configurada
  Serial.println(hora);
  return hora; // rregsa los minutos transcurridos
}

int comparacion(int adap) {
  /* El índice entregado de Adaptaciion()  se utiliza para buscar en  una
    columna específica de la matriz de horarios. En ella se revisa  los medicamentos
    a tomar según cada uno de los 6 compartimientos disponibles en el pastillero y son
    alamacenadas las dosis de cada uno  en el vector dosis[]*/
  int aux = 0; // auxiliar que conserva la cantidad de medicinas a tomar
  for (int i = 0; i < fila; i++) {
    dosis[i] = 0; // asegurando que el vector no tenga información de otras horas
  }
  if (adap >= 0) { // buscar medicinas sólo si el tiempo dio un índice válido (indice mayor a cero)
    for (int i = 0; i < fila; i++) {
      if (horario[i][adap] != 0) {
        dosis[i] = horario[i][adap]; // almacena la dosis de la medicina y el compartimiento donde está
        reporte[i] = 0; // coloca valores para indicar cuáles espacios fueron programados
        aux = aux + 1; // cuenta la cantidad de medicinas a tomar para la hora (columna) estudiada
      }
    }
  }
  Serial.print("Numero de dosis:");
  Serial.println(aux);
  if (aux > 0) { // se escribe las dosis de cada medicina y su ubicación
    Serial.print("Dosis:");
    for (int i = 0; i < fila; i++) {
      Serial.print(dosis[i]);
      if (i != fila - 1) {
        Serial.print(",");
      }
    }
    Serial.println(";");
  }

  Serial.print("Numero de programaciones:");
  Serial.println(aux);
  if (aux > 0) { // se escribe las dosis de cada medicina y su ubicación
    Serial.print("programas:");
    for (int i = 0; i < fila; i++) {
      Serial.print(reporte[i]);
      if (i != fila - 1) {
        Serial.print(",");
      }
    }
    Serial.println(";");
  }
  return aux;
}

void buscarDosis() {
  int i = 0;
  a = -1;
  while (i < fila && a < 0) {
    if (dosis[i] != 0) {
      a = i;
      Serial.print("espacio en:");
      Serial.println(a + 1);
    }
    i = i + 1;
  }
}

void operar(int numero, int espacio, int tiempo) {
  /*dado lo grande  de los números es necesario usar variables tipo long,
    y para evitar desbordes se utilizan de forma unsigned para tener más espacio positivo*/
  unsigned long m0 = millis(); // Se mide el nstante de tiempo donde empiza la operación
  unsigned long m1 = 0;
  int minu0, minu1;
  int s0 = m0 / 1000;
  minu0 = s0 / 60;
  do {
operar:
    if (entrada[espacio - 1] == 1) {
      entrada[espacio - 1] = digitalRead(boton[espacio - 1]); //leer el botón del espacio donde
      // se debe sacar la medicina siempre que su valor sea alto
    }
    m1 = millis(); // Se mide cuánto tiempo ha pasado desde que se empezó a leer el botón
    int s1 = m1 / 1000;
    minu1 = s1 / 60;
    Serial.print("minu0:");
    Serial.println(minu0); // mostrar el valor del tiempo de refernecia en minutos
    Serial.print("minu1:");
    Serial.println(minu1); // mostrar el valor del tiempo medido en minutos
    delay(250);
    if (entrada[espacio - 1] == 1) {
      // deplegar la información acerca de la dosis
      Serial.println("Cumple: brillar");
      digitalWrite(6, 1); // prender LED interno
      sieteSeg(numero); // mostrar la cantidad de la dosis en un dislay 7seg
      alarma(1, espacio); //  activar zumbador, vibrador y prender el LED del compartimiento de la dosis
      delay(500); //
      alarma(0, espacio); // Apagar para mantener un sonido intermitente
    }
    else if (entrada[espacio - 1 == 0] && cont > 0) {
      // caso en que la tapa fue abierta
      Serial.println("Tapa abierta");
      limpiar();
      alarma(0, 0);
      dosis[espacio - 1] = 0; // dar por tomada esta dosis para poder seguir con la siguiente
      reporte[espacio - 1] = 1; // guardar en el reporte que esa pastilla fue tomada
      cont = cont - 1; // resta un valor a la cantidad de medicinas por tomar a esa hora
      Serial.print("Faltan:");
      Serial.print(cont);
      Serial.println(" medicinas");
      delay(500);
      if (cont > 0) {
        entrada[espacio - 1] = 1; // se reinicia la entrada usada a su estado original
        Serial.println("Buscando proxima medicina");
        delay(1000);
        for (int i = 0; i < fila; i++) {
          // se inicia la búsqueda de la próxima medicina en el vector dosis
          if (dosis[i] != 0) {
            Serial.println("Econtrado");
            numero = dosis[i]; // se modifica el valor de número  para volver a iniciar la rutina operar
            espacio = i + 1; // se modifica el valor del espacio para volver a iniciar la rutina operar
            goto operar; // al hacerlo de esta manera estamos garantizando que  un sólo vector dosis[] puede mostrar
            // todas las dosis que tiene almacenadas dentro del intervalo aignado de tiempo, 1 minuto en estos casos
          }
        }
      }
    }
    else {
      Serial.println("Esperando...");
      limpiar();
      alarma(0, 0);
    }
  }  while (minu1 - minu0 < tiempo); // realizar toda esta operación sólo durante el tiempo especificado

  informe();
}


void informe() {
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
  Serial.println(hora_informe);

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


