#include <dht.h>

dht DHT;
#include <Wire.h>

#include <Servo.h>
Servo myservo;
#include <LiquidCrystal.h>

//#include <DHT.h>

//LiquidCrystal lcd(0x27F,16,2); //0x3F - 0x20F
#include <LiquidCrystal.h>


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define DHTPIN 8
#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);
int vcc= 10; //crear pínes de 5v

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  myservo.attach(6);//
  pinMode(9,OUTPUT);//ventilador
  pinMode(vcc,OUTPUT);
  //pinMode(servoMotor,OUTPUT);
  //pinMode(ventilador,OUTPUT);
 // dht.begin();
  Serial.begin(9600);
  // put your setup code here, to run once:

}


void loop() {
 
  digitalWrite(vcc,HIGH);
  //int h = dht.readHumidity();
  //int t = dht.readTemperature();
  Serial.println(DHT.temperature);
  Serial.println("____");
  Serial.println(DHT.humidity);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humedad: ");
  lcd.setCursor(8,0);
  lcd.print(DHT.humidity);
  lcd.print("%");
  
  lcd.setCursor(0,1);
  lcd.print("Temperatura: ");
  lcd.setCursor(12,1);
  lcd.print(DHT.temperature);
  lcd.print("C");
  delay(2500);
  
  if(DHT.temperature<25){
    myservo.write(50);
    digitalWrite(9,250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LAMPARA OFF");
    delay(5000);
    // put your main code here, to run repeatedly:
  }else {
  myservo.write(180);
  digitalWrite(9,250);
  //digitalWrite(ventilador,255);
  
}
}
