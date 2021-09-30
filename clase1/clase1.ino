int e = 0, entrada = 0,aux=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  entrada = digitalRead(2);
  if (entrada == 0)
  {
    e = e + 1;
    delay(500);
    Serial.println(e);
    aux=0;
  }
  if (entrada==1 && aux==0) 
  {
    Serial.println("no hay señal");
    aux=1;

    delay(500);
  }
}
