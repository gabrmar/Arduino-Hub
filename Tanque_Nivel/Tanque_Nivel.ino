int vertical = 2, horizontal = 3;
int bomba = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(vertical, INPUT_PULLUP);
  pinMode(horizontal, INPUT_PULLUP);
  pinMode(bomba,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int alto = digitalRead(vertical);
  int bajo = digitalRead(horizontal);
  delay(100);
  if(bajo==1){
    while(alto==0){
      digitalWrite(bomba,1);
      alto = digitalRead(vertical);
      }
    }
    
    digitalWrite(bomba,0);
    delayMicroseconds(1000);


 
      
}
