/************************************************************
 * Defines motor layout,  this class is used for front left/back right 
 * motors.
 * 
 * And a second class is is used for front right/ back left.
 * 
 * L298N datasheet can be found at 
 * https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf
 * 
 * CAVIET: 0805 (100nF) capacitor must be connected between some pins 
 * and ground.  View datasheet and add to schematic for more details.
 * 
 * As per section 5.2 ENA, and ENB should be set to 0, pull-downed 
 * to ground, to avoid overloading IC.
 */


#ifndef RR_MOTORS_HPP
#define RR_MOTORS_HPP

#include <rrenvironment/functions/function.hpp>

#define RR_MOTOR_FLAG_IN1 b00000001  // Toggle IN1 HIGH or LOW
#define RR_MOTOR_FLAG_IN2 b00000010  // Toggle IN2 HIGH or LOW
#define RR_MOTOR_FLAG_IN3 b00000100  // Toggle IN3 HIGH or LOW
#define RR_MOTOR_FLAG_IN4 b00001000  // Toggle IN3 HIGH or LOW

namespace rrenv {
    class RrMotor : public RrFunction
    {
    private:
        uint16_t  _ena;  // Value between 0 to 1024 for sense to ENA 
        uint16_t  _enb;  // Value between 0 to 1024 for sense to ENB
        uint8_t  _flags; // Using toggles above defines IN controls
    public:
        RrMotor(RrWiringI2C wiring):
            _addr{RR_ADDR_I2C_MC1} // Link motor to MC1 micro-processor
        ;
        ~RrMotor();
    };
}

#endif