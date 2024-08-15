/*************************************************************************
 * Header file designed for micro-processors to configure themselves.
 *************************************************************************/

#ifndef RR_MICROPROCESSORS_H
#define RR_MICROPROCESSORS_H

#include <stdint.h>
#include <list>

/*******************************************************************
 * Structures and headers that maintain registers for underlying
 * micro-processors.
 *******************************************************************/
//////////////////////////////////////////////////////////////////////////
// I2C register address
//////////////////////////////////////////////////////////////////////////

#define RR_ADDR_I2C_MC1 0x08 /* Actuators, LEDs, Battery and Motors */ 
#define RR_ADDR_I2C_MC2 0x09 /* Ultrasonic and GPS */
#define RR_ADDR_I2C_MS3 0x68 /* Gyroscope and accelometer */

// Structure to send data to environment, used by Fat Controller
class rr_io_tx {
public:
    uint8_t addr; // I2C address as defined above.
    uint8_t io;   // this must be a value a RR_IO
    std::list<uint8_t> bytes; // bytes to send the microprocessor
};

class rr_io_rx {
    uint8_t io;   // this must be a value a RR_IO
    std::list<uint8_t> bytes; // bytes recieved from micro processor.
};


#endif