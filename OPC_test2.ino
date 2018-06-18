// Test to turn the OPC-N2 "ON"

#include <SPI.h>

int SSpin = 10;                   // slave select pin
int MISOpin = 12;                 

float clkSpeed = 500000;          // SPI clock speed 
SPISettings settings(clkSpeed, MSBFIRST, SPI_MODE1);
byte command[] = {0x03, 0x00};
byte inData[2];
//byte expected[] = {0xF3, 0x03};

void setup() {
  Serial.begin(9600);                      

  SPI.begin();
  digitalWrite(SSpin, HIGH);
  Serial.println("Beginning transaction...");
  SPI.beginTransaction(settings);         // set up sensor SPI 
  delay(10000);
  
  digitalWrite(SSpin, LOW);               // write slave pin low
  inData[0] = SPI.transfer(command[0]);   // send command byte 
  delay(10); 
  inData[1] = SPI.transfer(command[1]);   // send follow byte
  digitalWrite(SSpin, HIGH);              // write slave pin high
  
  Serial.println(inData[0]);              // print return byte
  Serial.println(inData[1]);              // print return byte


  delay(10);
  
  SPI.endTransaction();
  Serial.println("Transaction complete.");
  delay(10000);
}

void loop() {

}


