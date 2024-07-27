/**************************************************************************************
 * Actions are defined below.
 **************************************************************************************/

#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <map>
#include <dlib/logger.h>
#include "rrenvironment/wiring.hpp"

dlib::logger dlog_a(__FILE__); 

namespace rrenv {

    class Actions {
    public:
        virtual void setup(std::map<std::string, int>  &config, Wiring &wiring) = 0;

        /**
         * run is executed within the thread. Args a list of values that used when running.
         */
        virtual void run(std::map<std::string, int> &args, Wiring &wiring) = 0;
    }; 
}
#endif
