#ifndef RRENVIRONMENT_H
#define RRENVIRONMENT_H

#include <stdint.h>

/*******************************************************************
 * Structures and headers that maintain registers for underlying
 * micro-processors.
 *******************************************************************/

//////////////////////////////////////////////////////////////////////////
// I2C register address
//////////////////////////////////////////////////////////////////////////

// Ultra Sonic registers can use a micro-processor, or be an I2C address on their own.
// if they're a register then three are available. However if using a micro-processor, 
// it should handle all three ultra-sonics and use address RR_REG_I2C_US
#define RR_REG_I2C_US   0x0008
#define RR_REG_I2C_US2  0x000a
#define RR_REG_I2C_US3  0x000c
#define RR_REG_I2C_H_BRIDGE 0x000d


//////////////////////////////////////////////////////////////////////////
// Bitmasks used to define when a sensor has completed.
//////////////////////////////////////////////////////////////////////////

// Set the bitmask after all three UCs have returned, regardless of this is three sepearte
// units or handled in a Micro-Processor.
#define RR_BITMASK_US       0b00000001
#define RR_BITMASK_H_BRIDGE 0b00000010

//////////////////////////////////////////////////////////////////////////
// Common structures.
////////////////////////////////////////////////////////////////////////// 

// note that any value of 0, can be one of three conidtions
// too far, too close, or unable tobe detected.
typedef struct UltraSonic_s {
    uint32_t forward;
    uint32_t port;
    uint32_t starbroad;
    uint32_t stern;
} UltraSonic_t;


// IN1 for Hbridge A
#define RR_OPT_HB_IN0 0b00000001

// IN2 for Hbridge A
#define RR_OPT_HB_IN1 0b00000010

// IN3 for Hbridge A
#define RR_OPT_HB_IN2 0b00000100

// IN4 for Hbridge A
#define RR_OPT_HB_IN3 0b00001000

// IN1 for Hbridge B
#define RR_OPT_HB_IN4 0b00001000

// IN2 for Hbridge B
#define RR_OPT_HB_IN5 0b00010000

// IN3 for Hbridge B
#define RR_OPT_HB_IN6 0b00100000

// IN4 for Hbridge B
#define RR_OPT_HB_IN7 0b01000000
typedef struct HbridgeArgs_s {
    uint8_t  opt;
    uint32_t ea; // Hbridge A - EA
    uint32_t eb; // Hbridge A - EB
    uint32_t ec; // Hbridge B - EA
    uint32_t ed; // Hbridge B - EB
} HbridgeArgs_t;


#endif
