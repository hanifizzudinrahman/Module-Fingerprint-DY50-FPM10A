#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

// TX = White, RX = Green
// ==> Serial3 	Tx = 14, Rx = 15 		==> Serial2  Tx = 17 , Rx = 16		==> Serial1	Tx = 18 , Rx = 19 

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial3);	// every syntax "Serial3" can be change with "Serial1" or "Serial2"

void setup()  
{ 
  while(!Serial);
  Serial.begin(57600);
  Serial3.println("Fingerprint template extractor");

  // set the data rate for the sensor serial port
  finger.begin(9600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
}

void loop ()
{}