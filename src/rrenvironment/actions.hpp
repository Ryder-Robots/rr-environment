/**************************************************************************************
 * Actions are defined below.
 **************************************************************************************/

#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <map>
#include <dlib/logger.h>
#include "rrenvironment/wiring.hpp"

namespace rrenv {

    class Actions {
    public:
        virtual void setup(std::map<std::string, int>  &config, Wiring &wiring) {}

        /**
         * run is executed within the thread. Args a list of values that used when running.
         */
        virtual void run(std::map<std::string, int> &args, Wiring &wiring) {}
    }; 
}
#endif
