

float R2 =10020, c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  float R = R2*((5/voltage)-1);
  float T = (1.0 / (c1 + c2*log(R) + c3*pow(log(R),3)));
  float C = T-273.15;
  // print out the value you read:
  Serial.println(String(R/1000)+"Kohms"+" "+String(C)+"°C");

}
