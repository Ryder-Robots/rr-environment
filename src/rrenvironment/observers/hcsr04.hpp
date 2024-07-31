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

        // Gicve a one second delay 
        const int HCSR_04_TIMEOUT = 1000000;

        Hcsr04() : 
            TRIG("TRIG"),
            ECHO("ECHO")
        {
            dlog_b << dlib::LINFO << "initialised HCSR04 driver";
        }



        void setup(std::map<std::string, int>  &config, Wiring &wiring) {
            wiring.pin_mode(config[TRIG], OUTPUT);
            wiring.pin_mode(config[ECHO], INPUT);

            if (config[TRIG] != 0) {
                wiring.pull_up_down_ctl(config[TRIG], PUD_DOWN);
            }
            wiring.pull_up_down_ctl(config[ECHO], PUD_DOWN);
            dlog_b << dlib::LINFO << "HCSR04 configured for input";
        }

        /*************************************************************************************************
         * Note that if the argument trig = 0 then do not trigger just record the time when we recieved
         * the signal, this to allow for multiple sonars to be on the same board using the same trigger.
         * 
         * This cuts down on wires, and reduces the complexity by making it hardware driven.
         ************************************************************************************************/
        void run(std::map<std::string, int> &args, std::map<std::string, long> &rv, Wiring &wiring) {

            dlib::auto_mutex lock(_mtx);
            // Give the trigger some time to exeucte (around 10 milliseconds)
            if (args[TRIG] != 0) {
                dlog_b << dlib::LINFO << "sent trigger";
                wiring.digital_write(_trig_pin, HIGH);
                delay(10);
                wiring.pull_up_down_ctl(_trig_pin, PUD_DOWN);
            }

            volatile long now = micros();
            volatile long startTime = micros();
            while (wiring.digital_read(_echo_pin) == LOW && micros() - now < HCSR_04_TIMEOUT);
            while (wiring.digital_read(_echo_pin) == HIGH);
            volatile long endTime = micros();
            wiring.pull_up_down_ctl(_echo_pin, PUD_DOWN);

            // Dont bother calculating the difference, do it in the policy. Because of the delay above
            // which could skew the result. Want to take the start tie only from the sensor(s) that has
            // trig > 1.
            rv["startTime"] = startTime;
            rv["endTime"] =  endTime;
            _mtx.unlock();
        }
    private:
        int _trig_pin = 0;
        int _echo_pin = 0;
        dlib::mutex _mtx;
    };
}

#endif