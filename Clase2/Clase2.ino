
double pote;
double volt;
void setup() {
  Serial.begin(9600);
}

void loop() {
  pote=analogRead(A1);
  volt=(5*pote)/1023;
  Serial.println(volt);
  delay(500);

}
