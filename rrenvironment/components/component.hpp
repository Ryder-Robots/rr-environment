/**************************************************************************************
 * Component can be either an observation, this is the base class.
 **************************************************************************************/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <nlohmann/json.hpp>
#include <wiringPi.h>

using json = nlohmann::json;

class Component {
    public:
        virtual void run(json& action_io);

        virtual void setup(json& config);
};

#endif