#include <Alpha.h>            // include library

alpha opc;                    // constant of type 'alpha'
int SSpin = 10;               // slave select pin
int i = 1;                    // used for counter

void setup() {
  Serial.begin(9600);
  opc.setupSPI(SSpin);        // set up spi
  opc.on(SSpin);              // turn OPC on

  delay(10000);               // allow time for fan to get up to speed

}

void loop() {
  // read histogram 10 times every 1 second
  if (i<11){
     opc.getData(0, SSpin);   // read histogram and apply no conversions
     delay(1000); 
     i=i+1;
  }
  // after 10 readings, turn off OPC
  else {
    opc.off(SSpin);
    while(1);
  }
}
