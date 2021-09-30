#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX CONECTADOS CRUZADOS CON EL MÓDULO WIFI

void setup()
{ Serial.begin(115200);
  BT1.begin(115200);
  BT1.println("AT+CWMODE=1"); // Establecer modo estación
  delay(500);
  BT1.println("AT+CWQAP"); // QUITAR PUNTO DE ACCESO
  delay(500);
  BT1.println("AT+CWJAP=\"gabriel\",\"Aa123456789\""); // establecer conxión 
  // con usuario y contraseña
  BT1.println("AT+CIPMUX=1");
  delay(500);
  BT1.println("AT+CIPSERVER=1,80");
  delay(500);
  BT1.println("AT+CIFSR");
  
}

void loop()
{ String B = "." ;
  if (BT1.available())
  { char c = BT1.read() ;
    Serial.print(c);
  }
  if (Serial.available())
  { char c = Serial.read();
    BT1.print(c);
  }
}
