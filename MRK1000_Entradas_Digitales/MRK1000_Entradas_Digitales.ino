int entrada=5;
void setup() {
  // put your setup code here, to run once:
pinMode(entrada, INPUT);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  boolean x = digitalRead(entrada);
  Serial.print("Entrada:");
  Serial.println(x);
  delay(500);
  
  
}
