# Alphasense-OPC-N2

Arduino C++ library for operating optical particle counter OPC-N2 from Alphasense.

Commands included are:

    -- OPC_on()      - Turn on the OPC laser and fan. Returns 1 if successful.
    -- OPC_off()     - Turn off the OPC laser and fan. Returns 1 if successful.
    -- OPC_getData() - read count/s per bin, sample flow rate (sfr), and sampling period (sp) from histogram, then reset histogram

All communication is via SPI logic lines. NOTE THAT THE SPI LOGIC LINES REQUIRE 3v3 VOLTAGE SUPPLY!

Pin Layout (Arduino):

    -- SS   --> pin 10
    -- MOSI --> pin 11
    -- MISO --> pin 12
    -- SCK  --> pin 13
    
Pin Layout (OPC):

    -- Vcc  --> pin 1
    -- SCK  --> pin 2
    -- MISO --> pin 3
    -- MOSI --> pin 4
    -- SS   --> pin 5
    -- GND  --> pin 6
    NOTE: pin 1 on the OPC is closest to the USB micro connector.
    
NOTES:

    -- C++ code for this library is written for the Arduino UNO
    -- OPC is slave device, Arduino is master
    -- OPC is MSB first
    -- OPC is SPI Mode 1 device
    -- Clock frequency is set to 300 kHz

	
