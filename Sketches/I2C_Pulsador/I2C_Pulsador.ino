// mostrar en el monitor serial el contenido del puerto B
// en una variable tipo byte;
#include "Wire.h"
byte PB=0;  // variable byte que tendrá los valores del puerto B
void setup()
{
 Serial.begin(9600); 
 Wire.begin(); // habilitando el protoclo I2C
 
}
void loop()
{
 Wire.beginTransmission(0x20);  // enviar byte de configuración
 // establece la dirección del integrado y su condición
 // de esclavo
 Wire.write(0x13); // acceder al regristro de puerto B
 Wire.endTransmission();
 Wire.requestFrom(0x20, 1); // Solicitar información de un esclavo
 // en al dirección especificada indicando el número de bytes.
 // en este caso se solicita al esclavo de la dirección 0x20
 // entregar un byte de información. Va entregar el  bte proveniente
 // del registros accedido anteriormente, es decir 0x13(Puerto B)
 PB=Wire.read(); // Captura el valor solicitado y lo alamacena en PB.
 if (PB>0) // analizar si uno de los bits está en alto
 {
 Serial.println(PB, BIN); // mostrar contenido en binario
 delay(200); // para evitar rebotes
 }
}
