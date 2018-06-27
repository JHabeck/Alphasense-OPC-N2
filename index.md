## Index for functions written to operate the Alphasense OPC-N2.

### void setupSPI(int SSpin):

>Begins Arduino SPI library; writes slave select pin high and initializes it as an output. 

### bool on(int SSpin):

> Turn on the OPC laser and fan.

> Returns 1 if sucessful. 

> The input is the slave select pin on the Arduino.


### bool off(int SSpin):

> Turn off the OPC laser and fan. 

> Returns 1 if sucessful. 

> The input is the slave select pin.

### particleData getData(int convert, int SSpin):

> Reads histogram count/s, sample flow rate, and sampling period, then resets histogram. Inputs are a "conversion toggle" and slave select pin.

> For the conversion toggle: '1' will convert count/s to count/volume (concentration); and '0' will keep it as count/s

> Returns structure of type 'particleData' of the count/s (or count/volume) for each bin.







