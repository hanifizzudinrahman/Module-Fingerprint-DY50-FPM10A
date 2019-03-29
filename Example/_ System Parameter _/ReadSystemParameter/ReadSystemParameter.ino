#include <Adafruit_Fingerprint.h>

// Serial3		==> Tx (White) = 14		==> Rx (Green) = 15
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial3);

int p;

void setup()  
{ 
  while(!Serial);
  Serial.begin(115200);
  Serial.println("\n[ Read System Parameter ]\n");

  // set the data rate for the sensor serial port
  // HIGH baudrate must use Hardware Serial (Serial3 / Serial2 / Serial1)
  //					--> 9600 / 19200 / 28800 / 38400 / 48000 / 57600 / 67200 / 76800 / 86400 / 96000 / 105600 / 115200
  finger.begin(9600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  
  Serial.print("\n==> ReadSysParameter ");
   p = finger.ReadSysPara();    
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("SUKSES ");
	  Serial.print("Check at RX and TX Manual");
      Serial.read();
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_BADPACKET:
      Serial.println("Bad packet");
      return p;      
    default:
      return p;
  }  
}

void loop()
{}


