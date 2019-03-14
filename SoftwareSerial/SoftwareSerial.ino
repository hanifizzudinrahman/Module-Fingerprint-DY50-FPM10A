#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

// pin #11 is IN from sensor (GREEN wire)
// pin #10 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(11, 10);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{ 
  while(!Serial);
  Serial.begin(57600);
  mySerial.println("Fingerprint template extractor");

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