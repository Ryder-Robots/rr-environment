/**************************************************************************************
 * Actions are defined below.
 **************************************************************************************/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <map>
#include <string>
#include <wiringPi.h>
#include <dlib/logger.h>

dlib::logger dlog("L298"); 

namespace rrevironment {

    #define IN1 "IN1"
    #define IN2 "IN2"
    #define IN3 "IN3"
    #define IN4 "IN4"
    #define ENA "ENA"
    #define ENB "ENB"

    class Actions {
    public:
        virtual void setup(std::map<std::string, int>  config) {}

        /**
         * run is executed within the thread. Args a list of values that used when running.
         */
        virtual void run(std::map<std::string, int> &args) {}
    };

    /**
     * L298 Driver, DC motors 
     */
    class L298 : public Actions {

        /*
         * Sets up the pin layout
         */
        void setup(std::map<std::string, int>  config) {
            try {
                dlog << dlib::LINFO << "configuring L298";
                pinMode(config[IN1], OUTPUT);
                pinMode(config[IN2], OUTPUT);
                pinMode(config[ENA], PWM_OUTPUT);

                pinMode(config[IN3], OUTPUT);
                pinMode(config[IN4], OUTPUT);
                pinMode(config[ENB], PWM_OUTPUT);

                dlog << dlib::LINFO << "finished configuring L298";
            } catch (...) {
                dlog << dlib::LFATAL << "unable to configure motor";
                throw "RR_MOTOR_EXCEPTION";
            }
        }

        /**
         * Send action to L298 motor.
         */
        void run(std::map<std::string, int> &args) {

        }
    };
}

#endif