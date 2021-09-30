int espacio =1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
 byte luz = ubicarPin(espacio);
 Serial.println(luz+0x040,BIN);
 delay(1000);
 espacio = espacio+1;
}

 byte ubicarPin(int terminal){
  byte pin = pow(2,terminal-1);
  return pin;
 }
