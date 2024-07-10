/**************************************************************************************
 * Actions are defined below.
 **************************************************************************************/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <map>
#include <string>
#include <dlib/logger.h>
#include <dlib/threads.h>
#include "rrenvironment/Wiring.hpp"

dlib::logger dlog("L298"); 

namespace rrevnv {

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

    public:

        const std::string IN1;
        const std::string IN2;
        const std::string IN3;
        const std::string IN4;
        const std::string ENA;
        const std::string ENB;

        static const int MIN_PWM_VAL = 0;
        static const int MAX_PWM_VAL = 1024;

        L298(rrevnv::Wiring wiring) : 
            IN1("IN1"),
            IN2("IN2"),
            IN3("IN3"),
            IN4("IN4"),
            ENA("ENA"),
            ENB("ENB"),
            _wiring(wiring)
        {
            dlog << dlib::LINFO << "initialised L298 driver";
        }

        /*
         * Sets up the pin layout
         */
        void setup(std::map<std::string, int>  config) {
            try {
                dlog << dlib::LINFO << "configuring L298";
                pinMode(config[IN1], OUTPUT);
                _in1 = config[IN1];
                pinMode(config[IN2], OUTPUT);
                _in2 = config[IN2];
                pinMode(config[ENA], PWM_OUTPUT);
                _ena = config[ENA];

                pinMode(config[IN3], OUTPUT);
                _in3 = config[IN3];
                pinMode(config[IN4], OUTPUT);
                _in4 = config[IN4];
                pinMode(config[ENB], PWM_OUTPUT);
                _enb = config[ENB];

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
            try {
                //TODO: check that values are within acceptable range.
                for (auto it = args.begin(); it != args.end(); ++it) {

                }

                dlib::auto_mutex lock(_mtx);
                digitalWrite(_in1, args[IN1]);
                digitalWrite(_in2, args[IN2]);

                digitalWrite(_in3, args[IN3]);
                digitalWrite(_in4, args[IN4]);

                // range is 0 to 1024
                pwmWrite(_ena, args[ENA]);
                pwmWrite(_enb, args[ENB]);
                _mtx.unlock();
            } catch (...) {
                dlog << dlib::LERROR << "motor could not get sent a message";
            }
        }
    private:
        int _in1;
        int _in2;
        int _in3;
        int _in4;

        int _ena;
        int _enb;
        Wiring _wiring;

        dlib::mutex _mtx;
    };

    /**********************************************************************
     * Constants for L298 drivers.
     **********************************************************************/
    // const std::string L298::IN1 = "IN1";
    // const std::string L298::IN2 = "IN2";
    // const std::string L298::IN3 = "IN3";
    // const std::string L298::IN4 = "IN4";
    // const std::string L298::ENA = "ENA";
    // const std::string L298::ENB = "ENB";
}

#endif