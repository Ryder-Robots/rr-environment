# I2C Bus communication

* RR Environment is always set as the "master" device for I2C communciation.
* Packets currently use wiringPiI2C in order to connect to the I2C bus. 


Uses BSD SMBus to create packets on Twin Wire (TW) otherwise known as I2C.

Packet structure is as follows:

1. Address - uint8_t
2. size    - uint8_t
3. data    - uint8_t[]

Note that WiringPi imposes a limit of 32 bits.  Not sure why that limit is imposeed. However
future versions may swit to using smb LINUX functinos directly in order to avoid this limit, and ensure that the library is not tied to WiringPi.