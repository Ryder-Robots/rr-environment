# FUNCTIONS

Functions can be observers or actions that use I2C (with exception of camera) to speak to
micro-processor or other devices in order to achieve some goal. 

Functions are identified by a uint8_t mask that is defined in rrenvironment.h

| CODE REFERENCE     | MASK | DESCRIPTION        |
| :----------------- | :--- | :----------------- |
| RR_IO_ULTRA_SONIC  |0x01  | ultra sonic        |
| RR_IO_ACCEL        |0x02  | acelometer         |
| RR_IO_GYRO         |0x03  | Gyroscrope         |
| RR_IO_CAMERA       |0x04  | Camera input       |
| RR_IO_MOTORS       |0x05  | Motors             |
| RR_IO_MOTOR_ACT    |0x06  | Motor Actuator     |
| RR_IO_BATTERY      |0x07  | Get battery health |

The functions responsibility is to translate an incomming map into bytes that can be 
quickly translated over an I2C bus, less space the better. 

Functions do not need to get too close to the hardware, that is the job of the micro-processor.
However they can and should perform any translations for results.

Calling objects communicate to the environment via std::map<std::string, float> each function
is expected to have an argument map return a response using the following struture for input 
and output.

```
class RrIO {
    uint8_t REF;                           // see table above
    std::map<std::string, float> payload;  // arguments or results.
};
```