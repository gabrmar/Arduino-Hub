


#define TRIGGER 12
#define ECHO    11
const int pin_RELE1 = 2;
const int pin_RELE2 = 3;
int estado_RELE1 = LOW;  
int estado_RELE2 = LOW;

unsigned long previousMillis=0;
const long interval = 1000 ;
int cont =0;


void setup() {
  Serial.begin (9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(pin_RELE1, OUTPUT);  
  pinMode(pin_RELE2, OUTPUT); 
}

void loop(){

  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  
  Serial.print(distance);
  Serial.println(" Centimetros:");
  delay(500);

  //int tiempo ()
  unsigned long currentMillis= millis();

  if (currentMillis - previousMillis >=interval){
  previousMillis = currentMillis;
  cont++;
  }
  if (cont == 30){
  cont=0;
  return 1;
  
  if(distance <= 20) {  
      digitalWrite(pin_RELE1) = HIGH;
    }
    else {
       digitalWrite(pin_RELE1) = LOW;
    }
    
}



}










