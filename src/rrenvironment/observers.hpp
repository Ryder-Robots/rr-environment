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
        virtual void setup(std::map<std::string, int>  &config, Wiring &wiring) {
            dlib::logger dlob_obs("rr-environment");
            dlob_obs << dlib::LWARN << "executing vitural Observers.setup() function,  should this be an implementation?";
        }


        virtual void run(std::map<std::string, int> &args, std::map<std::string, long> &rv,  Wiring &wiring) {
            dlib::logger dlob_obs("rr-environment");
            dlob_obs << dlib::LWARN << "executing vitural Observers.run() function,  should this be an implementation?";
        }
    };
}

#endif