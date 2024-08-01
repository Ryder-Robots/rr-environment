/***********************************************************************
 * Observers are an acton that returns a result.
 ***********************************************************************/

#ifndef OBSERVERS_HPP
#define OBSERVERS_HPP

#include <map>
#include <string>
#include <dlib/logger.h>
#include <rrenvironment/wiring.hpp>

namespace rrenv {

    class Observers {
    public:
        virtual void setup(std::map<std::string, int>  &config, Wiring &wiring) = 0;
        virtual void run(std::map<std::string, int> &args, std::map<std::string, long> &rv,  Wiring &wiring) = 0;
    };
}

#endif