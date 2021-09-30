int e2 = 2, e3 = 3, e4 = 4; // pines de entrada
int tecla, intro = 0; // intro es la variable que condiciona los menús de presentación en el monitor serial
int cero = 48, uno = 49, cuatro = 52, dos = 50, tres = 51, digital = 100, analogo = 97, alto = 115   ; //valores correspondientes  en bytes de dichos números en el teclado
boolean salir = false, aux = false; //  aux es la variable que aayuda a alternar entre las condiciones de las entradas digitales y las de las analogas
void setup() {
  // put your setup code here, to run once:
  pinMode(e2, INPUT);
  pinMode(e3, INPUT);
  pinMode(e4, INPUT);
  Serial.begin(9600);
  Serial.println("Prueba de entradas de Arduino");
  delay(2000);
  Serial.println("'d' para digitales y 'a' para Analogas");
  delay(1000);
  Serial.println("Eliga una opcion");

}

void loop() {
  // put your main code here, to run repeatedly:

  int valor = 0, entrada = 0;

  // Sección de interrupción de inspección de entradas
  if (tecla == alto) {
    Serial.println("'d' digitales y 'a' para Analogas");
    delay(1000);
    Serial.println("Eliga una opcion");
    intro = 0;
  }

  tecla = -1;
  while (tecla == -1) {
    if (Serial.available() > 0) {
      tecla = Serial.read();
    }
  }

  // Sección de entradas analogas
  if (tecla == analogo) {
    aux = true;
    if (intro == 0) {
      Serial.println("Puertos analogos activados");
      delay(1500);
      Serial.println("Este codigo utiliza las entradas analogas A0 y A1");
      delay(2500);
      Serial.println("Digite el numero del puerto que desea usar");
      intro = 1;
    }
  }

  if (tecla == cero && aux == true ) {
    Serial.println("Puerto A0 activado");
    for (int i = 0; i < 20; i++) {
      Serial.println(valor);
      valor = analogRead(0);
      delay(1000);
    }

  }

  if (tecla == uno && aux == true ) {
    Serial.println("Puerto A1 activado");
    for (int i = 0; i < 20; i++) {
      Serial.println(valor);
      valor = analogRead(1);
      delay(1000);
    }

  }


  // sección de entradas digitales
  if (tecla == digital) {
    aux = false;
    if (intro == 0) {
      Serial.println("Puertos digitales activados");
      delay(1500);
      Serial.println("Este codigo activa los pines 2, 3 y 4 como entradas digitales ");
      delay(2500);
      Serial.println("Digite el numero del puerto que desea usar");
      intro = 1;
    }

    while (tecla != alto) {
      tecla = -1;
      while (tecla == -1) {
        if (Serial.available() > 0) {
          tecla = Serial.read();
        }
      }
      if (tecla == dos && aux == false) {
        Serial.println("Dos");
        valor = digitalRead(e2);
        entrada = e2;
      }
      else if (tecla == tres && aux == false) {
        Serial.println("Tres");
        valor = digitalRead(e3);
        entrada = e3;
      }
      else if (tecla == cuatro && aux == false) {
        Serial.println("Cuatro");
        valor = digitalRead(e4);
        entrada = e4;
      }
      if (tecla != alto && aux == false) {
        Serial.print("Pin #");
        Serial.print(entrada);
        Serial.print(":");
        Serial.println(valor);
      }
    }
  }
  delay(250);
}




