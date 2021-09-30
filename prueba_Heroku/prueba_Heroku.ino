#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX CONECTADOS CRUZADOS CON EL MÓDULO WIFI
char serialbuffer[100];
void setup()
{ Serial.begin(115200);
  BT1.begin(115200);
  BT1.println("AT+CWMODE=1"); // Establecer modo estación
  delay(500);
 // BT1.println("AT+CWQAP"); // QUITAR PUNTO DE ACCESO
  delay(500);
  BT1.println("AT+CWJAP=\"Ponton\",\"12345678\""); // establecer conxión 
  // con usuario y contraseña
 
  //esta es la parte que No estoy seguro si es necesaria//
  BT1.println("AT+CIPMUX=1"); //
  delay(500);
  BT1.println("AT+CIPSERVER=1,80");
  delay(500);
  BT1.println("AT+CIFSR");
  delay(500);
  
  
}

void loop()
{ 

  //output everything from ESP8266 to the Arduino Micro Serial output
  Serial.println("Conectando");
  BT1.println("AT+CIPSTART=\"TCP\",\"pruebav1.herokuapp.com\",80");
  delay(5000);
  while (BT1.available() > 0) {
    Serial.write(BT1.read());
  }
  String sendcommand = "GET /index.php?temp=100&hum=50 HTTP/1.1\r\nHost: pruebav1.herokuapp.com\r\n\r\n";
  
  while (BT1.available() > 0) {
    Serial.write(BT1.read());
  }
  BT1.print("AT+CIPSEND=");
  BT1.println(sendcommand.length());
  Serial.print(sendcommand.length());
  delay(5000);
  while (BT1.available() > 0) {
    Serial.write(BT1.read());
  }
  BT1.println(sendcommand);
  delay(5000);  
  while (BT1.available() > 0) {
      Serial.write(BT1.read());
  }

}   
