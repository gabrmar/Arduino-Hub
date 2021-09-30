int dosis[5] = { -1, -1, -1, -1, -1}; // número de pastillas por dosis
int fila[5] = { -1, -1, -1, -1, -1}; // indicador de los espacios de los vector dosis ocupados con alarmas
String color[5] = {"Amarillo", "Azul", "Rojo", "Verde", "Blanco"};
int estado[] = {8, 9, 10, 11, 12}; // indicadores de los detectores de la apertura del compartimiento indicado
boolean pulsador[5] = {1, 1, 1, 1, 1  }; // valores por defecto de los estados de los pulsadores
int LED[] {2, 3, 4, 5, 6}; // vector de alarmas LED
int buzzer = 7;
int lecturas = 1000;
int minutos = 2;
int espacio = 0;
int turno = 0;
int aux = -1;
int valor = 1;
int sumatoria = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  for (int i = 0; i < 5; i++) {
    pinMode(LED[i], OUTPUT);
  }
  for (int i = 0; i < 5; i++) {
    pinMode(estado[i], INPUT_PULLUP);
  }
//  dosis[0] = 2;
  dosis[1] = 3;
  ordenarAlarmas();
  sumatoria = revisarfila();
  Serial.print("fila revisada con valor de:");
  Serial.println(sumatoria);
}

void loop() {
  // put your main code here, to run repeatedly
  turno = revisarAlarmas();
  operacion(lecturas, minutos);
  turno = descontarAlarma();
  aux = -1;
  fin(turno);

}



// ADN2
void ordenarAlarmas() {
  for (int i = 0; i < 5; i++) {
    if (dosis[i] != -1) {
      fila[i] = i;
    }
  }
}

int revisarfila() {
  sumatoria=0;
  for (int i = 0; i < 5; i++) {
    if (fila[i] > -1) {
      sumatoria = sumatoria + fila[i];
    }
  }
  return sumatoria;
}

int revisarAlarmas() {
  int i = 0;
  espacio = 0;
  while (espacio == 0 && i < 5) {
    if (fila[i] != -1) {
      if (aux == -1) {
        aux = fila[i];
      }
      espacio = i + 1;
      turno = turno + fila[i] + 1;
    }
    i = i + 1;
  }
  return turno;
}

void operacion(int lecturas, int minutos) {
  int i = 0, j = 0;
  unsigned int milisec = minutos * 60 * 1000;
  unsigned int espera = milisec / lecturas;
  while (i < minutos && valor == 1) {
    j = 0;
    while ( j < lecturas && valor == 1) {
      activarAlarma(espacio);
      mostrarDosis(espacio);
      valor = revisarDosis();
      Serial.println(j + 1);
      delay(espera);
      j = j + 1;
    }
    i = i + 1;
  }
}


int descontarAlarma() {
  int i = 0;
  while (i < 5) {
    if (fila[i] != -1) {
      turno = turno - fila[i] - 1;
      fila[i] = -1;

    }
    i = i + 1;
  }
  sumatoria = revisarfila();
  Serial.print("turno al final es de:");
  Serial.println(turno);
  return turno;
}


void fin(int turno) {
  digitalWrite(LED[espacio - 1], 0);
  digitalWrite(buzzer, 0);
  if (turno <= 0 && sumatoria == 0) {
    Serial.println("FIN");
    while (buzzer == buzzer) {

    }
  }

}
// ADN3


void  activarAlarma(int espacio) {
  digitalWrite(LED[espacio - 1], 1);
  digitalWrite(buzzer, 1);
}

void mostrarDosis(int espacio) {
  Serial.print("Dosis ");
  Serial.print(color[espacio - 1]);
  Serial.print(":");
  Serial.println(dosis[espacio - 1]);

}
int revisarDosis() {
  int valor = 1;
  for (int i = 0; i < 5; i++) {
    pulsador[i] = digitalRead(estado[i]);
    if (pulsador[i] == 0) {
      Serial.print("Seccion ");
      Serial.print(i + 1);
      Serial.println(" abierta");
      if (i == aux) {
        Serial.println("Apagar");
        valor = 0;
      }

    }
  }
  return valor;
}




