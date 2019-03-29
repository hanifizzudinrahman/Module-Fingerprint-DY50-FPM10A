#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

// TX = White, RX = Green
// ==> Serial3 	Tx = 14, Rx = 15 		==> Serial2  Tx = 17 , Rx = 16		==> Serial1	Tx = 18 , Rx = 19 

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial3);	// every syntax "Serial3" can be change with "Serial1" or "Serial2"

void setup()  
{ 
  while(!Serial);
  Serial.begin(115200);
  Serial.println("\n[ Hardware Serial ]\n");

  // set the data rate for the sensor serial port
  //					--> 9600 / 19200 / 28800 / 38400 / 48000 / 57600 / 67200 / 76800 / 86400 / 96000 / 105600 / 115200
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