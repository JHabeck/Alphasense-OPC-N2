#include <SPI.h>

int SSpin = 1;                 // slave select pin (SPI data line pin)
float clkSpeed = 1.00E6;         // SPI clock speed 
int first = 1;

void setup() {
  Serial.begin(9600);
  pinMode(SSpin, OUTPUT);

}

void loop() {




}

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

