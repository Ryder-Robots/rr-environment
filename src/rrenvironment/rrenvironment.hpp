/************************************************
 * General interface to interact with actions.
 ************************************************/

#ifndef ABSTRACTACTION_HPP
#define ABSTRACTACTION_HPP

#include <nlohmann/json.hpp>

class RrEnvironment {
    public:
        void setup(Json );
        void set_request();
}



#endif
