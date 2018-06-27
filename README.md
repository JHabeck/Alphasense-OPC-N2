# Alphasense-OPC-N2

Arduino C++ library for operating optical particle counter OPC-N2 from Alphasense.

Commands included are:

    -- OPC_on()      - turn OPC on (laser and fan)
    -- OPC_off()     - turn OPC off (laser and fan)
    -- OPC_getData() - read count/s per bin, sample flow rate (sfr), and sampling period (sp) from histogram, then reset histogram

Note that communication is via SPI. More commands for the sensor are available.

Pin Layout:

    -- SS   --> pin 10
    -- MOSI --> pin 11
    -- MISO --> pin 12
    -- SCK  --> pin 13
    
NOTES:

    -- C++ code for this library is written for the Arduino UNO
    -- OPC is slave device, Arduino is master
    -- OPC is MSB first
    -- OPC is SPI Mode 1 device
    -- Clock frequency is set to 300 kHz

	
