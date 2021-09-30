int s1 = 9, s2 = 10, s3 = 11; //Salidas analogas
int s4 = 4, s5 = 5, s6 = 6; //Salidas digitales
int digital = 100, pwm = 112, alto = 115, cero = 48, uno = 49, tres = 51, cuatro = 52, cinco = 53, seis = 54, siete = 55, ocho = 56, nueve = 57, diez=97, once=98; // números de teclas
int tecla[2];
int f = 25; //frecuencia d brillo para prueba digital
boolean aux = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  Serial.begin(9600);
  Serial.println("Prueba de salidas de Arduino");
  delay(2000);
  Serial.println("'d' para digitales y 'p' para salidas PWM ");
  delay(1000);
  Serial.println("Eliga una opcion");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (tecla[0] == alto) {
    Serial.println("'d' para digitales y 'p' para salidas PWM ");
    delay(1000);
    Serial.println("Eliga una opcion");
  }
  int fila = 0;
  tecla[0] = -1;
  tecla[1] = 0;
  while (tecla[0] == -1) {
    if (Serial.available() > 0) {
      tecla[0] = Serial.read();
    }
  }
  if (tecla[0] == pwm) {
    aux = true;
    Serial.println("Activando salidas PWM");
    delay(2000);
    Serial.print("Podemos usar las salidas PWM de los pines ");
    Serial.print(s1);
    Serial.print(",");
    Serial.print(s2);
    Serial.print(" y ");
    Serial.print(s3);
    Serial.println(" en este codigo");
    delay(3000);
    Serial.println("Elige el pin a utilizar");
  }

  if (tecla[0] == digital) {
    Serial.println("Acitvando salidas digitales");
    delay(2000);
    Serial.print("Podemos usar las salidas digitales de los pines ");
    Serial.print(s4);
    Serial.print(",");
    Serial.print(s5);
    Serial.print(" y ");
    Serial.print(s6);
    Serial.println(" en este codigo");
    delay(3000);
    Serial.println("Elige el pin a utilizar");
  }
  //Sección en evaluación
  while (tecla[0] != alto) {
    tecla[0] = -1;
    tecla[1] = 0;
    while (tecla[0] == -1) {
      if (Serial.available() > 0) {
        delay(200);
        fila = Serial.available();
        for (int i = 0; i < fila; i++) {
          tecla[i] = Serial.read();
        }
      }
    }
    // formación del mensaje
    int mensaje = tecla[0] + tecla[1];
    if (mensaje == cuatro) {
      Serial.print("pin ");
      Serial.print(s4);
      Serial.print(" activado como salida digital ");
      delay(2000);
      Serial.println("iniciando prueba");
      baileLED(s4, f);
    }
    else if (mensaje == cinco) {
      Serial.print("pin ");
      Serial.print(s5);
      Serial.print(" activado como salida digital ");
      delay(2000);
      Serial.println("iniciando prueba");
      baileLED(s5, f);
    }
    else if (mensaje == seis) {
      Serial.print("pin ");
      Serial.print(s6);
      Serial.print(" activado como salida digital ");
      delay(2000);
      Serial.println("iniciando prueba");
      baileLED(s6, f);

    }

    else if (mensaje == nueve) {
      Serial.print("pin ");
      Serial.print(s1);
      Serial.println(" activado como salida PWM");
      delay(2000);
      pruebaAnaloga(s1);
      Serial.println("Segunda fase activada");
      delay(2000);
      controlAnalogo3Teclas(s1);
    }

    else if (mensaje == diez) {
      Serial.print("pin " );
      Serial.print(s2);
      Serial.println(" activado como salida PWM");
      delay(2000);
      pruebaAnaloga(s2);
      Serial.println("Segunda fase activada");
      delay(2000);
      controlAnalogo3Teclas(s2);
    }
    else if (mensaje == once) {
      Serial.print("pin ");
      Serial.print(s3);
      Serial.println(" activado como salida PWM");
      delay(2000);
      pruebaAnaloga(s3);
      Serial.println("Segunda fase activada");
      delay(2000);
      controlAnalogo3Teclas(s3);
    }

  }
  delay(250);
}


//Subrutinas
void pruebaAnaloga(int pin) {
  pinMode(pin, OUTPUT);
  int paso = 0;
  for (int c = 0; c < 256; c++) {
    analogWrite(pin, paso);
    paso = paso + 1;
    Serial.println(paso);
    delay(100);
  }
  delay(2000);
  for (int c = 255; c > -1; c--) {
    analogWrite(pin, paso);
    paso = paso - 1;
    Serial.println(paso);
    delay(100);
  }
}

void controlAnalogo3Teclas(int pin) {
  pinMode(pin, OUTPUT);
  int aux = 0;
  int nivel = -1;
  Serial.println("eliga uno de los tres niveles:");
  delay(500);
  Serial.println("Bajo:0");
  Serial.println("Medio:3");
  Serial.println("Alto:5");
  while (aux < 5) {
    nivel = -1;
    while (nivel == -1) {
      if (Serial.available() > 0) {
        nivel = Serial.read();
      }
    }
    if (nivel == cero) {
      analogWrite(pin, 0);
    }
    else if (nivel == tres) {
      analogWrite(pin, 128);
    }
    else if (nivel == cinco) {
      analogWrite(pin, 255);
    }
    aux = aux + 1;
    Serial.println(aux);
  }
  Serial.print("PRUEBA PWM DEL PIN ");
  Serial.print(pin);
  Serial.println(" TERMINADA");
  delay(3000);
  Serial.println("Eliga un pin PWM para seguir probando");
}

void baileLED(int pin, int d) {
  Serial.println("Inicia prueba digital");
  pinMode(pin, OUTPUT);
  for (int t = 0; t < 50; t++) {
    digitalWrite(pin, 1);
    Serial.println("1");
    delay(d);
    digitalWrite(pin, 0);
    Serial.println("0");
    delay(d);
  }


}
