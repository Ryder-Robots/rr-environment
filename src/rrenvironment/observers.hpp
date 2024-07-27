/***********************************************************************
 * Observers are an acton that returns a result.
 ***********************************************************************/

#ifndef OBSERVERS_HPP
#define OBSERVERS_HPP

#include <map>
#include <string>
#include <dlib/logger.h>
#include <rrenvironment/wiring.hpp>

dlib::logger dlog_b("_OBSERVERS_HPP_");

namespace rrenv {

    class Observers {
    public:
        virtual void setup(std::map<std::string, int>  &config, Wiring &wiring) = 0;
        virtual std::map<std::string, long> run(std::map<std::string, int> &args, Wiring &wiring) = 0;
    };
}

#endif