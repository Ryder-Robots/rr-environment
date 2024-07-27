/************************************************************************************
 * Driver for the HCSR04 ultrasonic sensor,  please note that the
 * return value is travel time in micro-seconds (one millionth of a second)
 * to compute into distance,  something like the following formula can be used.
 * 
 * distanceMeters = 100*((travelTimeUsec/1000000.0)*340.29)/2; (disance in meters)
 ************************************************************************************/

#ifndef _HCSR04_HPP_ 
#define _HCSR04_HPP_

#include <wiringPi.h>
#include <rrenvironment/observers.hpp>

namespace rrenv {
    class Hcsr04 : public Observers {

    public:
        const std::string TRIG;
        const std::string ECHO;

        // Just a large number,  more than resonable, which means that something is very far away.
        const int HCSR_04_TIMEOUT = 10000000;

        Hcsr04() : 
            TRIG("TRIG"),
            ECHO("ECHO")
        {
            dlog_b << dlib::LINFO << "initialised HCSR04 driver";
        }



        void setup(std::map<std::string, int>  &config, Wiring &wiring) {
            wiring.pin_mode(config[TRIG], OUTPUT);
            wiring.pin_mode(config[ECHO], INPUT);
            dlog_b << dlib::LINFO << "HCSR04 configured for input";
        }

        /*************************************************************************************************
         * Note that if the argument trig = 0 then do not trigger just record the time when we recieved
         * the signal, this to allow for multiple sonars to be on the same board using the same trigger.
         * 
         * This cuts down on wires, and reduces the complexity by making it hardware driven.
         ************************************************************************************************/
        std::map<std::string, long> run(std::map<std::string, int> &args, Wiring &wiring) {

            // Give the trigger some time to exeucte (around 10 milliseconds)
            if (args[TRIG] != 0) {
                dlog_b << dlib::LINFO << "sent trigger";
                wiring.digital_write(_trig_pin, HIGH);
                delay(10);
                wiring.digital_write(_trig_pin, LOW);
            }

            volatile long startTime = micros();
            while (wiring.digital_read(_echo_pin) == HIGH);
            volatile long endTime = micros();

            // Dont bother calculating the difference, do it in the policy. Because of the delay above
            // which could skew the result. Want to take the start tie only from the sensor(s) that has
            // trig > 1.
            std::map<std::string, long> rv = {{"start_time", startTime}, {"end_time", endTime}};
            return rv;
        }
    private:
        int _trig_pin = 0;
        int _echo_pin = 0;
    };
}

#endif