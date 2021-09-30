int a,b,button, pin1=7,pin2=6,pin3=5;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  pinMode(pin3,INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
 a = digitalRead(pin1); 
 b = digitalRead(pin2);
 button = digitalRead(pin3);
 Serial.println(String(a)+","+String(b)+","+String(button));
}
