#include <Adafruit_Fingerprint.h>

// Serial3		==> Tx (White) = 14		==> Rx (Green) = 15
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial3);

uint8_t id;
int p;

void setup()  
{
  Serial.begin(115200);
  while (!Serial);
  delay(100);
  
  Serial.println("\n[ Enroll + Show Templete ]\n");

  // set the data rate for the sensor serial port
  //	==> especially, in [ Show Image Templete ], only can use baudrate
			//	--> 76800 [ Serial.begin(1000000 / 2000000) ]
			//	--> 67200 [ Serial.begin(230400 / 250000 / 500000 / 1000000 / 2000000) ]
			//	--> 57600 [ Serial.begin(230400 --> 2000000) ]
			//  --> ...
			//	--> ...
			//	--> 9600 [ Serial.begin(38400 --> 2000000) ]
  finger.begin(9600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
}

uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void loop()                     // run over and over again
{
  Serial.println("Ready to Show Fingerprint!");
  Serial.println("Please type Free Number :");
  id = readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  Serial.print("Show  ID #");
  Serial.println(id);
  
  getFingerprintEnroll();
}

uint8_t getFingerprintEnroll() {

  p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
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
    downloadFingerprintImageTemplate(id); 
	
	p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("\n\nImage converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  downloadFingerprintTemplate(id);
}

uint8_t downloadFingerprintImageTemplate(uint16_t id)
{
  uint8_t p;
      
  Serial.print("\n==> Attempting to get Image #"); Serial.println(id);
  p = finger.downImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("Image "); Serial.print(id); Serial.println(" transferring:");
      break;
   default:
      Serial.print("Unknown error "); Serial.println(p);
      return p;
  }

  Serial.println("Decoding packet...");
  
  // Filtering The Packet
  	 int a = 0, x = 2;
	 Serial.print("\nuint8_t packet1[] = {");

  while(1)
  {
			  if (a >= 139)
				{
				  a=0;
				  Serial.print("};\nuint8_t packet");Serial.print(x);Serial.print("[] = {");
				  x++;
				}
			  else
			  {	
				if (Serial3.available()) 
				{
					printHex(Serial3.read(), 2);Serial.print(" ");
					a++;
				}
			  }
			  if (x == 290)
				  break;
  }
}

uint8_t downloadFingerprintTemplate(uint16_t id)
{      
  Serial.print("==> Attempting to get Templete #"); Serial.println(id);
  p = finger.getModel();
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
  while (i <= 554 ) { 
      if (Serial3.available()) {
          bytesReceived[i++] = Serial3.read();
      }
  }
  Serial.println("Decoding packet...");
  
  // Filtering The Packet
  int a = 0, x = 3;;
  Serial.print("uint8_t packet2[] = {");
  for (int i = 10; i <= 554; ++i) {
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
         Serial.print("0x"); printHex(bytesReceived[i-1] , 2); Serial.print(", ");
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