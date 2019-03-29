#include <Adafruit_Fingerprint.h>

// Serial3		==> Tx (White) = 14		==> Rx (Green) = 15
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial3);

void setup()  
{
  Serial.begin(115200);
  while (!Serial);
  delay(100);

  Serial.println("\n[ Deleting All Fingerprint Templates! ]\n");

  // set the data rate for the sensor serial port
  // HIGH baudrate must use Hardware Serial (Serial3 / Serial2 / Serial1)
  finger.begin(115200);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  
  Serial.println("\nPress 'Y' key to continue");

  while (1) {
    if (Serial.available() && (Serial.read() == 'Y')) {
      break;
    }
  }
  
  finger.emptyDatabase();

  Serial.println("Now database is empty :)");
}

void loop() {
}
