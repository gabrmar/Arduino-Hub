/* mostra en el display de 7 segmentos el número del bit del puerto B
  que fue activado en alto usando el expansor de pines MCP23017*/
#include<Wire.h>
byte numero=0x00; // número que será mostrado en el display
byte direccion = 0x20; //dirección por defecto para configurar el
// expansor de pines como esclavo.

//OJO que este valore de dirección puede ser modificado con ayuda de los
// pines del integrado, es decir que la dirección se puede modificar por
// hardware ne este caso en parrticular.

void setup() {
  Serial.begin(9600); //
  //los puestos por edefecto están configurados como entrada. se procede
  // a configurar al puerto A como salida.
  Wire.begin(); // inicio de la habilitación del I2C
  Wire.beginTransmission(direccion); // enviando dirección de configuración.
  // de estamnera el expansor queda confugrado como esclavo con una dirección
  // fija.
  Wire.write(0x00); //accediendo al puerto A
  Wire.write(0x00); // configurando el puerto A como salida
  Wire.endTransmission(); // cerrando protocolo I2C y manda los dos bytes de la transmission
}

void loop() {
  // put your main code here, to run repeatedly:
  // obtener el valor del puerto B. Tener en cuenta los puertos están configurados
  // como entradas por defecto. Se procede inmediatamente con la captura de datos
  // del puerto.
  Wire.beginTransmission(direccion);
  Wire.write(0x13); // acceder al regirstro del puerto B
  Wire.endTransmission(); // fin de I2C y  manda el valor de 0x13 al escalvo
  Wire.requestFrom(direccion, 1); // inicia comunicación con el esclavo de la dirección
  // indicada y le solicita 1 byte de información.
  // el esclavo quedó  accediendo al puerto B, por lo que el byte que ese entregará
  // vendrá de este registro del esclavo.
  numero = Wire.read(); // captura el valor  solciitado al esclavo
  Serial.print("PB:");
  Serial.println(numero,BIN);
  // conversión de binario a 7-segmentos

  switch (numero) {
    case 1:
      numero = 0x7e; //cero 7-S
      Serial.println("Numero 0");
      break;
    case 2:
      numero = 0x30; //uno 7-S
      Serial.println("Numero 1");
      break;
    case 4:
      numero = 0x6d; //dos 7-S
      Serial.println("Numero 2");
      break;
    case 8:
      numero = 0x79; //tres 7-S
      Serial.println("Numero 3");
      break;
    case 16:
      numero = 0x33; //cuatro 7-S
      Serial.println("Numero 4");
      break;
    case 32:
      numero = 0x5b; //cinco 7-S
      Serial.println("Numero 5");
      break;
    case 64:
      numero = 0x5f; //seis 7-S
      Serial.println("Numero 6");
      break;
     default:
     // mantener limpio el display en cualquier otro caso
     numero = 0x00;
     break;
  }

  // mostrar valor de numero en el puerto A
  Serial.println(numero,BIN);
  Wire.beginTransmission(direccion); // iniciando I2C con el dispositivo direccion
  Wire.write(0x12); // direccionando a puerto A
  Wire.write(numero); // enviando información a puerto A
  Wire.endTransmission(); // finalizando I2C
  delay(200);
  //numero = numero + 1;
}
