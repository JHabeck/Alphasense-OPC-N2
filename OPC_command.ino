#include <SPI.h>

int SSpin = 1;                   // slave select pin (SPI data line pin)
float clkSpeed = 1.00E6;         // SPI clock speed 

void setup() {
  Serial.begin(9600);
  pinMode(SSpin, OUTPUT);

}

void loop() {




}

////////// USER-DEFINED FUNCTIONS TO COMMAND OPC //////////

// Returns status of OPC (1 (on) or 2 (off)) my comparing expected data to the received data
bool command_return(byte array1[], byte array2[], int length)
{
  // Compare two arrays and return a boolean
  bool result = false;

  for (int i = 0; i < length; i++){
    if (array1[i] == array2[i]){
      result = true;
    }
  }

  return result;
}

// Turn OPC on
bool OPC_on(){
  
  byte r[2];
  byte expected[] = {0xF3, 0x03};
  bool OPC_status;
  
  SPI.begin();
  SPI.beginTransaction(SPISettings(clkSpeed, MSBFIRST, SPI_MODE1));
  digitalWrite(SSpin, LOW);
  r[0] = SPI.transfer(0x03);
  digitalWrite(SSpin, HIGH);

  delay(10);

  digitalWrite(SSpin, LOW);
  r[1] = SPI.transfer(0x00);
  digitalWrite(SSpin, HIGH);

  OPC_status = command_return(r, expected, 2);
  return OPC_status;
}

// Turn OPC off
bool OPC_off(){
  
  byte r[2];
  byte expected[] = {0xF3, 0x03};
  bool OPC_status;
  
  SPI.begin();
  SPI.beginTransaction(SPISettings(clkSpeed, MSBFIRST, SPI_MODE1));
  digitalWrite(SSpin, LOW);
  r[0] = SPI.transfer(0x03);
  digitalWrite(SSpin, HIGH);

  delay(10);

  digitalWrite(SSpin, LOW);
  r[1] = SPI.transfer(0x01);
  digitalWrite(SSpin, HIGH);

  OPC_status = command_return(r, expected, 2);
  return OPC_status;
}

