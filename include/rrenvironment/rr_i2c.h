/*******************************************************************
 * Structures and headers that maintain registers for underlying
 * micro-processors.
 *******************************************************************/

#ifndef RR_I2C_H
#define RR_I2C_H

// Ultra Sonic registers can use a micro-processor, or be an I2C address on their own.
// if they're a register then three are available. However if using a micro-processor, 
// it should handle all three ultra-sonics and use address RR_REG_I2C_US
#define RR_REG_I2C_US   0x0008
#define RR_REG_I2C_US2  0x000a
#define RR_REG_I2C_US3  0x000c

// Motor Driver
#define RR_REG_I2C_H_BRIDGE 0x000d

// Set the bitmask after all three UCs have returned, regardless of this is three sepearte
// units or handled in a Micro-Processor.
#define RR_US_BITMASK 0b00000001

#endif