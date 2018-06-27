/*
Alpha.cpp

Written by Joseph Habeck (habec021@umn.edu) on 6/24/18.

 */

#include <stdio.h>
#include <Alpha.h>

// Combine two bytes into a 16-bit unsigned int
uint16_t alpha::twoBytes2int(byte LSB, byte MSB)
{
    uint16_t int_val = ((MSB << 8) | LSB);
    return int_val;
}

// Return an IEEE754 float from an array of 4 bytes
float alpha::fourBytes2float(byte val0, byte val1, byte val2, byte val3)
{
    union u_tag
    {
    byte b[4];
    float val;
    } u;
    
    u.b[0] = val0;
    u.b[1] = val1;
    u.b[2] = val2;
    u.b[3] = val3;
    
    return u.val;
}

// Setup SPI
bool alpha::setupSPI(int SSpin)
{
    Serial.println("Initializing SPI...");
    
    SPI.begin();                                            // intialize SPI in Arduino
    pinMode(SSpin, OUTPUT);
    digitalWrite(SSpin, HIGH);
    Serial.println("\n");
    delay(10000);
}

// Turn OPC ON
bool alpha::on(int SSpin)
{
    int i = 0;
    byte command[] = {0x03, 0x00};                          // "ON" command bytes
    byte inData[2];                                         // initialize array for return bytes
    int expected[] = {243, 3};                              // return bytes (0xF3, 0x03)
    bool OPC;                                               // OPC is initially off (0 - off; 1 - on)
    
    // command OPC on while its off
    while (OPC==0)
    {
        i=i+1;
        if (i==1)
        {
            Serial.println("Sending 'ON' command to OPC...(1st attempt)");
        }
        if (i==2)
        {
            Serial.println("Sending 'ON' command to OPC...(2nd attempt)");
        }
        if (i==3)
        {
            Serial.println("Sending 'ON' command to OPC...(3rd attempt)");
        }
        
        // SPI transaction
        SPI.begin();                                                        // intialize SPI in Arduino
        SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE1));     // begin transaction
        digitalWrite(SSpin, LOW);                                           // write slave pin low
        inData[0] = SPI.transfer(command[0]);                               // send command byte
        delay(10);                                                          // delay betwen command and follow byte
        inData[1] = SPI.transfer(command[1]);                               // send follow byte
        digitalWrite(SSpin, HIGH);                                          // write slave pin high
        SPI.endTransaction();                                               // end transaction
        
        // check if bytes were received
        if (inData[0] == expected[0] & inData[1] == expected[1])
        {
            OPC = 1;
            Serial.println("Command sucessful - OPC powered on!");
        }
        else
        {
            OPC = 0;
            Serial.println("Return bytes:");
            Serial.println(inData[0]);
            Serial.println(inData[1]);
            Serial.println("Transaction failed.");
            
            if (i==1)
            {
                Serial.println("Attempting command again in 15s...");
                Serial.println("\n");
                delay(15000);
            }
            if (i==2)
            {
                Serial.println("Resetting OPC, please wait 65s...");
                Serial.println("\n");
                delay(65000);
            }
            if (i==3)
            {
                Serial.println("Commands unsucessful... closing SPI bus.");
                Serial.println("\n");
                SPI.end();
                while(1);
            }
         }
     }
    return OPC;
}

bool alpha::off(int SSpin)
{
    byte command[] = {0x03, 0x01};                        // "off" command bytes
    byte inData[2];
    int expected[] = {243, 3};                            // return bytes (0xF3, 0x03)
    bool OPC=1;                                           // OPC assumed on
    
    while (OPC==1)
    {
        Serial.println("Turning OPC off...");
        SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE1));
        digitalWrite(SSpin, LOW);                        // write slave pin low
        inData[0] = SPI.transfer(command[0]);            // send command byte
        delay(100);
        inData[1] = SPI.transfer(command[1]);            // send follow byte
        digitalWrite(SSpin, HIGH);                       // write slave pin high
        
        
        if (inData[0] == expected[0] & inData[1] == expected[1])
        {
            OPC = 0;
            Serial.println("Commands received - OPC powered off!");
            SPI.end();                               // end SPI communication
        }
        else
        {
            OPC = 1;
            Serial.println("Transaction failed.");
            Serial.println("OPC resetting... wait 65 secs");
            delay(65000);
        }
    }
    
    return OPC;
}

particleData alpha::getData(int convert, int SSpin)
{
    particleData dat;                                       // particle data structure
    double conv;
    byte vals[62];
    byte command[] = {0x30, 0x30};
    
    Serial.println("Requesting data...");
    SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE1));
    digitalWrite(SSpin, LOW);
    SPI.transfer(command[0]);
    delay(100);
    
    for (int i=0; i<62; i++)
    {
        vals[i] = SPI.transfer(command[1]);
        delay(.09);
    }
    
    digitalWrite(SSpin, HIGH);
    
    // sample period [s]
    float sp = fourBytes2float(vals[44], vals[45], vals[46], vals[47]);
    
    // sample flow rate [ml/s]
    float sfr = fourBytes2float(vals[36], vals[37], vals[38], vals[39]);
    
    // conversion to concentration [particles/ml]
    if (convert==1)
    {
        conv = sp * sfr;
    }
    // keep as particle-count/sec
    if (convert==0)
    {
        conv = 1;
    }
    
    // data bins [particle count/ml]
    dat.bin0 = twoBytes2int(vals[0], vals[1]) / conv;
    dat.bin1 = twoBytes2int(vals[2], vals[3]) / conv;
    dat.bin2 = twoBytes2int(vals[4], vals[5]) / conv;
    dat.bin3 = twoBytes2int(vals[6], vals[7]) / conv;
    dat.bin4 = twoBytes2int(vals[8], vals[9]) / conv;
    dat.bin5 = twoBytes2int(vals[10], vals[11]) / conv;
    dat.bin6 = twoBytes2int(vals[12], vals[13]) / conv;
    dat.bin7 = twoBytes2int(vals[14], vals[15]) / conv;
    dat.bin8 = twoBytes2int(vals[16], vals[17]) / conv;
    dat.bin9 = twoBytes2int(vals[18], vals[19]) / conv;
    dat.bin10 = twoBytes2int(vals[20], vals[21]) / conv;
    dat.bin11 = twoBytes2int(vals[22], vals[23]) / conv;
    dat.bin12 = twoBytes2int(vals[24], vals[25]) / conv;
    dat.bin13 = twoBytes2int(vals[26], vals[27]) / conv;
    dat.bin14 = twoBytes2int(vals[28], vals[29]) / conv;
    dat.bin15 = twoBytes2int(vals[30], vals[31]) / conv;
    
    // Print data to Arduino serial monitor
    Serial.println("------------------------------------");
    if (convert==1)
    {
        Serial.println("Concentration of particles [particles/ml] per size bin [microns]:");
    }
    if (convert==0)
    {
        Serial.println("Particle count per second [#/s] per size bin [microns]:");
    }
    
    Serial.print("Bin 0 (0.38-0.54): ");
    Serial.println(dat.bin0);
    Serial.print("Bin 1 (0.54-0.78): ");
    Serial.println(dat.bin1);
    Serial.print("Bin 2 (0.78-1.0): ");
    Serial.println(dat.bin2);
    Serial.print("Bin 3 (1.0-1.3): ");
    Serial.println(dat.bin3);
    Serial.print("Bin 4 (1.3-1.6): ");
    Serial.println(dat.bin4);
    Serial.print("Bin 5 (1.6-2.1): ");
    Serial.println(dat.bin5);
    Serial.print("Bin 6 (2.1-3.0): ");
    Serial.println(dat.bin6);
    Serial.print("Bin 7 (3.0-4.0): ");
    Serial.println(dat.bin7);
    Serial.print("Bin 8 (4.0-5.0): ");
    Serial.println(dat.bin8);
    Serial.print("Bin 9 (5.0-6.5): ");
    Serial.println(dat.bin9);
    Serial.print("Bin 10 (6.5-8.0): ");
    Serial.println(dat.bin10);
    Serial.print("Bin 11 (8.0-10.0): ");
    Serial.println(dat.bin11);
    Serial.print("Bin 12 (10.0-12.0): ");
    Serial.println(dat.bin12);
    Serial.print("Bin 13 (12.0-14.0): ");
    Serial.println(dat.bin13);
    Serial.print("Bin 14 (14.0-16.0): ");
    Serial.println(dat.bin14);
    Serial.print("Bin 15 (16.0-17.0): ");
    Serial.println(dat.bin15);
    Serial.print("Sample flow rate [ml/s]: ");
    Serial.println(sfr);
    Serial.print("Sampling period [s]: ");
    Serial.println(sp);
    Serial.println("------------------------------------");
    
    return dat;
}
