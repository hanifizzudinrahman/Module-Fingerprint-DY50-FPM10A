
// TX = White, RX = Green
// ==> Serial3 	Tx = 14, Rx = 15 		==> Serial2  Tx = 17 , Rx = 16		==> Serial1	Tx = 18 , Rx = 19 
 
void setup() { 
  // put your setup code here, to run once:
  
  // set the data rate for the sensor serial port
  //					--> 9600 / 19200 / 28800 / 38400 / 48000 / 57600 / 67200 / 76800 / 86400 / 96000 / 105600 / 115200
  Serial3.begin(9600);		// every syntax "Serial3" can be change with "Serial1" or "Serial2"
  Serial.begin(57600);
}
 
void loop() {
  
  while (Serial.available())
    Serial3.write(Serial.read());	
  while (Serial3.available())
    Serial.write(Serial3.read());
}
