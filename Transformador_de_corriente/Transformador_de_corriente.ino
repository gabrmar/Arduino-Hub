#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance
double im = 42.426, is = 0.021, rburden = 100;
void setup()
{
  Serial.begin(9600);
  double calibration = (im / is) / rburden;
  emon1.current(0, calibration);             // Current: input pin, calibration.
  //calibration is explained bellow
}

void loop()
{
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only 
  Serial.print(Irms);          // Irms
  Serial.println("A");
}
