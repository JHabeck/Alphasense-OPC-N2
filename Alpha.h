/*
Alpha.h - library for operating optical particle counter OPC-N2 from Alphasense using an Arduino Uno.
 
 Written by Joseph Habeck (habec021@umn.edu) on 6/24/18.
*/

#ifndef Alpha_h
#define Alpha_h

// include Arduino SPI library
#include <SPI.h>

// particle data (all bins) structure
struct particleData
{
    int bin0;
    int bin1;
    int bin2;
    int bin3;
    int bin4;
    int bin5;
    int bin6;
    int bin7;
    int bin8;
    int bin9;
    int bin10;
    int bin11;
    int bin12;
    int bin13;
    int bin14;
    int bin15;
    
};

// define class
class alpha
{
    public:
        // commands
        bool setupSPI(int SSpin);
        bool on(int SSpin);
        bool off(int SSpin);
        particleData getData(int convert, int SSpin);
    
    private:
        uint16_t twoBytes2int(byte LSB, byte MSB);
        float fourBytes2float(byte val0, byte val1, byte val2, byte val3);
};


#endif /* Alpha_h */
