#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

// pin #11 is IN from sensor (GREEN wire)
// pin #10 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(11, 10);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{ 
  while(!Serial);
  Serial.begin(115200);
  mySerial.println("\n[ Software Serial ]\n");

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