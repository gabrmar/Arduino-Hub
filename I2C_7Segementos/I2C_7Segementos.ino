#include<Wire.h>
int n = 0x00, d=100  ;
void setup() {
  Wire.begin(); // Inicio de la comunicación I2C
  // set I/O pins to outputs
  Wire.beginTransmission(0x20); //iniciar transmisión de datos
  // configurando el integrado esclavo según la hoja de datos
  Wire.write(0x00); // Accediendo al registro IODIRA que contorla al puerto A
  Wire.write(0x00); // Configurando todo el puerto A como salida
  Wire.endTransmission(); // finalizando el protocolo I2C
}

void loop() {
  // put your main code here, to run repeatedly:
  cero();
  delay(d);
  //limpiar();
  uno();
  delay(d);
 // limpiar();
  dos();
  delay(d);
  //limpiar();
  tres();
  delay(d);
  //limpiar();
  cuatro();
  delay(d);
  //limpiar();
  cinco();
  delay(d);
  //limpiar();
  seis();
  delay(d);
  //limpiar();
  siete();
  delay(d);
  //limpiar();
  ocho();
  delay(d);
  //limpiar();
  nueve();
  delay(d);
}

void limpiar() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x00); // value to send
  Wire.endTransmission();

}
void cero() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x7e); // value to send
  Wire.endTransmission();
}

void uno() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x30); // value to send
  Wire.endTransmission();
}

void dos() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x6d); // value to send
  Wire.endTransmission();
}

void tres() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x79); // value to send
  Wire.endTransmission();
}

void cuatro() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x33); // value to send
  Wire.endTransmission();
}

void cinco() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x5b); // value to send
  Wire.endTransmission();
}
void seis() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x5f); // value to send
  Wire.endTransmission();
}
void siete() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x70); // value to send
  Wire.endTransmission();
}
void ocho() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x7f); // value to send
  Wire.endTransmission();
}
void nueve() {
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address port A
  Wire.write(0x7b); // value to send
  Wire.endTransmission();
}


