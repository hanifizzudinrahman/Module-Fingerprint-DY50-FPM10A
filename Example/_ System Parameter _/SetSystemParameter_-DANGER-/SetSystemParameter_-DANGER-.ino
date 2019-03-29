#include <Adafruit_Fingerprint.h>

// Serial3		==> Tx (White) = 14		==> Rx (Green) = 15
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial3);

int p;

void setup()  
{ 
  while(!Serial);
  Serial.begin(115200);
  Serial.println("\n[ Set System Parameter ]\n");

  // set the data rate for the sensor serial port
  finger.begin(115200);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  
	//	==> 4 = Baudrate
	//	==> 5 = Security Level
	// 	==> 6 = Data Package Length
  uint8_t para = 4; 
	//	--> [4], BAUDRATE = content * 9600	[ content = 1/2/3/4/5/6/7/8/9/10/11/12 ]
	//					--> 9600 / 19200 / 28800 / 38400 / 48000 / 57600 / 67200 / 76800 / 86400 / 96000 / 105600 / 115200
	//	--> [5], [ content = 1/2/3/4/5 ]
	// 	--> [6], [ content = 0 (32 bytes) / 1 (64 bytes) / 2 (128 bytes) / 3 (256 bytes)
  uint8_t content = 1; 
  Serial.print("\n==> SetSysParameter ");
  p = finger.SetSysPara(para, content);    
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("SUKSES ");
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
  
  Serial.print("\n==> ReadSysParameter ");
   p = finger.ReadSysPara();    
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("SUKSES ");
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


