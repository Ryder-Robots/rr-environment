/**************************************************************************************
 * Component can be either an observation, this is the base class.
 **************************************************************************************/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <map>
#include <string>
#include <wiringPi.h>

#include <dlib/logger.h>

dlib::logger dlog("L298"); 

namespace rrevironment {

    #define IN1 "IN1";
    #define IN2 "IN2";
    #define IN3 "IN3";
    #define IN4 "IN4";
    #define ENA "ENA";
    #define ENB "ENB";

    class Actions {
    public:
        virtual void setup(std::map<std::string, int>  config);

        /**
         * run is executed within the thread. Args a list of values that used when running.
         */
        virtual void run(std::map<std::string, int> &args);
    };

    class L298 : public Actions {
        void setup(std::map<std::string, int>  config) {

        }

        void run(std::map<std::string, int> &args) {

        }
    };
}

#endif