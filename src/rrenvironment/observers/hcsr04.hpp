/************************************************************************************
 * Driver for the HCSR04 ultrasonic sensor,  please note that the
 * return value is travel time in micro-seconds (one millionth of a second)
 * to compute into distance,  something like the following formula can be used.
 * 
 * distanceMeters = 100*((travelTimeUsec/1000000.0)*340.29)/2; (disance in meters)
 ************************************************************************************/

#ifndef _HCSR04_HPP_ 
#define _HCSR04_HPP_

#include <exception>
#include <wiringPi.h>
#include <rrenvironment/observers.hpp>

namespace rrenv {
    class Hcsr04 : public Observers {

    public:
        const std::string TRIG;
        const std::string ECHO;
        const std::string BITMASK;

        // Give a one 1/10 delay 
        const int HCSR_04_TIMEOUT = 10000;

        Hcsr04();


        void setup(std::map<std::string, int>  &config, Wiring &wiring) override;


        void run(std::map<std::string, int> &args, std::map<std::string, 
            long> &rv, Wiring &wiring) override;
        
    private:
        int _trig_pin = 0;
        int _echo_pin = 0;
        unsigned int _bit_mask = 0;
        dlib::mutex _mtx;
    };
}

#endif