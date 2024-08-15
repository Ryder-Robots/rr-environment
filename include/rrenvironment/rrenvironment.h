#ifndef RRENVIRONMENT_H
#define RRENVIRONMENT_H

#include <stdint.h>
#include <string>

/*************************************************************
 * Values used to predict how to perform some sort of action.
 *************************************************************/
#define RR_IO_ULTRA_SONIC 0x01  /* ultra sonic */
#define RR_IO_ACCEL       0x02  /* acelometer  */
#define RR_IO_GYRO        0x03  /* Gyroscrope */
#define RR_IO_CAMERA      0x04  /* Camera input */
#define RR_IO_MOTORS      0x05  /* Motors */
#define RR_IO_MOTOR_ACT   0x06  /* Motor Actuator */
#define RR_IO_BATTERY     0x07  /* Get battery health */

class rr_io {
    public:
    uint8_t io;
    std::map<string, float> txrx;
};

class rr_result {
    public:
    int   _reward; // this can be a negative value, indicating a penalty
    rr_io _state;  // last known state  
};


// Send a action or list of actions,  and recieve response from fat controller
std::list<rr_result> sendAndRecieve(std::list<rr_io> actions);


// Anything below this line will be deleted in the future.

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
#define RR_ADDR_I2C_00008 0x0008
#define RR_ADDR_I2C_00009 0x0009
#define RR_ADDR_I2C_0000a 0x000a
#define RR_AADR_I2C_0000b 0x000b
#define RR_ADDR_I2C_0000c 0x000c
#define RR_ADDR_I2C_0000d 0x000d




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
    uint16_t forward;
    uint16_t port;
    uint16_t starbroad;
    uint16_t stern;
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
    uint8_t opt;
    uint8_t ea; // Hbridge A - EA (multiple value by 4 in microprocessor)
    uint8_t eb; // Hbridge A - EB (multiple value by 4 in microprocessor)
    uint8_t ec; // Hbridge B - EA (multiple value by 4 in microprocessor)
    uint8_t ed; // Hbridge B - EB (multiple value by 4 in microprocessor)
} HbridgeArgs_t;


#endif
