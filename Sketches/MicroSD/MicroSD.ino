#include <SPI.h>
#include <SD.h>


Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = 4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
}

void loop() {
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  delay(500);
  if (dataFile) {
    dataFile.println("hola");
    dataFile.close();
    // print to the serial port too:
    Serial.println("hola");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  // put your main code here, to run repeatedly:
  //  bool x = card.init(SPI_HALF_SPEED, chipSelect);
  //  Serial.println(x);
  //  Serial.println("card initialized.");
  //  dataFile.println("hola");
  //  dataFile.close();
  //  // print to the serial port too:
  //  Serial.println("hola");
}
