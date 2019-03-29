#include <Adafruit_Fingerprint.h>

// Serial3		==> Tx (White) = 14		==> Rx (Green) = 15
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial3);

void setup()  
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println("\n[ Show Templete FULL ]\n");

  // set the data rate for the sensor serial port
  // HIGH baudrate must use Hardware Serial (Serial3 / Serial2 / Serial1)
  finger.begin(115200);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }

  // Try to get the templates for fingers 1 through 10
  for (int finger = 1; finger <= 10; finger++) {
    downloadFingerprintTemplate(finger);
  }
}

uint8_t downloadFingerprintTemplate(uint16_t id)
{
  Serial.print("Attempting to load #"); Serial.println(id);
  int p = finger.loadModel(id);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("Template "); Serial.print(id); Serial.println(" loaded");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    default:
      Serial.print("Unknown error "); Serial.println(p);
      return p;
  }

  Serial.print("Attempting to get #"); Serial.println(id);
  p = finger.getModel();       // FP_UPLOAD = UPCHAR 0x08  -getModel() for Char Buffer 1 and getM odel2() for Char Buffer 2-
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("Template "); Serial.print(id); Serial.println(" transferring:");
      break;
   default:
      Serial.print("Unknown error "); Serial.println(p);
      return p;
  }

  uint8_t bytesReceived[900];

  int i = 0;
  while (i <= 900 ) {
      if (Serial3.available()) {
          bytesReceived[i++] = Serial3.read();
      }
  }
  Serial.println("Decoding packet...");

  // Filtering The Packet
  int a = 0, x = 3;
  Serial.print("uint8_t packet2[] = {");
  for (int i = 10; i <= 832; ++i) {
      a++;
      if (a >= 129)
        {
          i+=10;
          a=0;
          Serial.println("};");Serial.print("uint8_t packet");Serial.print(x);Serial.print("[] = {");
		  x++;
        }
      else
      {
         Serial.print("0x"); printHex(bytesReceived[i-1] , 2); Serial.print(", ");//Serial.print("/"); 
      }
  }
  Serial.println("};");
  Serial.println("COMPLETED\n");
}



void printHex(int num, int precision) {
    char tmp[16];
    char format[128];
 
    sprintf(format, "%%.%dX", precision);
 
    sprintf(tmp, format, num);
    Serial.print(tmp);
}

void loop()
{}

