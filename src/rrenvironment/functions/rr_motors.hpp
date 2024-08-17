/************************************************************
 * Defines motor layout,  this class is used for front left/back right 
 * motors.
 * 
 * And a second class is is used for front right/ back left.
 */


#ifndef RR_MOTORS_HPP
#define RR_MOTORS_HPP

#include <rrenvironment/functions/function.hpp>

#define RR_MOTOR_FLAG_IN1 b00000001  // Toggle IN1 HIGH or LOW
#define RR_MOTOR_FLAG_IN2 b00000010  // Toggle IN2 HIGH or LOW
#define RR_MOTOR_FLAG_IN3 b00000100  // Toggle IN3 HIGH or LOW
#define RR_MOTOR_FLAG_IN4 b00001000  // Toggle IN3 HIGH or LOW

namespace rrenv {
    class RrMotors : public RrFunction
    {
    private:
        /* data */
        uint16_t  _ena;
        uint16_t  _enb;
        uint8_t  _flags;
    public:
        RrMotors(RrWiringI2C wiring):
            _cmd{RR_ADDR_I2C_MC1},
            _addr{RR_IO_MOTORS_A}
        ;
        ~RrMotors();
    };
}

#endif