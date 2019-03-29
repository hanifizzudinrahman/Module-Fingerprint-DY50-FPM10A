#include <Adafruit_Fingerprint.h>

// Serial3		==> Tx (White) = 14		==> Rx (Green) = 15
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial3);

uint16_t id;
int p;

void setup()  
{
  Serial.begin(115200);
  while (!Serial); 
  delay(100);
  Serial.println("\n[ Match 1:1 ]\n");

  // set the data rate for the sensor serial port
  // HIGH baudrate must use Hardware Serial (Serial3 / Serial2 / Serial1)
  finger.begin(115200);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
}

uint8_t readID(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void loop()                     // run over and over again
{
  Serial.println("Ready to match 1:1 a fingerprint!");
  Serial.println("Please type in the ID # (from 1 to 127) you want to match...");
  id = readID();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  Serial.print("Searching ID #");
  Serial.println(id);
  
  loadFlashMemory(id);
  
  getFingerprintEnroll();
}

uint8_t loadFlashMemory( uint16_t id) {	
  Serial.print("==> Load FlashMemory "); Serial.print(id); Serial.println(" to CharBuffer");
  p = finger.loadModel(id);		// ==> Move Templete to CharBuffer 1
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("Template "); Serial.print(id); Serial.println(" loaded");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    default:
      Serial.print("[ UNKNOWN ERROR ]"); Serial.println(p);
      return p;
  }
}

uint8_t getFingerprintEnroll() {

  p = -1;
  Serial.print("Waiting for valid finger as ID #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("\nImage taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(",");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  p = finger.image2Tz(0x02);       				//   Simpan di Char Buffer 02 (0x02)
  if (p != FINGERPRINT_OK)  return -1;
  Serial.println("Succes image2Tz");
    
   p = finger.matchUpload();  
  if (p != FINGERPRINT_OK)  
  {
	  Serial.print("\t ===??? [ DOESN'T Match ] as ID #");Serial.println(id); Serial.println();
	  delay(500);
	  return -1;  // fingerprint doesn't match
  }
  
  else
  {
	  Serial.print("\t ===>>> [ MATCH !!! ] as ID #");Serial.println(id);
	  delay(500);
  }
  Serial.println();
  return finger.fingerID; 
}