void setup() {
  Serial.begin(9600); //monito serial
  pinMode(3,INPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int boton = digitalRead(3);
  Serial.println(boton);
  delay(500);
}
