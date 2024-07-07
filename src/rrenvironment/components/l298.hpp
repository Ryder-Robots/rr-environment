/*******************************************************************************
 * Creates an interface to L298 motor driver.
 *******************************************************************************/

#ifndef L298
#define L298

#include <string.h>
#include <dlib/logger.h>
#include "component.hpp"

const std::string IN1 = "IN1";
const std::string IN2 = "IN2";
const std::string IN3 = "IN3";
const std::string IN4 = "IN4";
const std::string ENA = "ENA";
const std::string ENB = "ENB";

class L298 : public Component {

    public:
        void setup(json& config) {
            
            dlog << LINFO << "configuring L298";

            pinMode(get_config_value(IN1, json), OUTPUT);
            pinMode(get_config_value(IN2, json), OUTPUT);
            pinMode(get_config_value(ENA, json), PWM_OUTPUT);

            pinMode(get_config_value(IN3, json), OUTPUT);
            pinMode(get_config_value(IN4, json), OUTPUT);
            pinMode(get_config_value(ENB, json), PWM_OUTPUT);

            dlog << LINFO << "finished configuring L298";
        }

        void run(json& action_io) {
            // int in1, int in2, int in3,  int in4, int ena, int enb
        }

    private:
        unsigned int get_config_value(const string key, const json config) {
            if (config[key].is_number()) {
                throw 1;
            }
            return (unsigned int) config[key];
        }
};

#endif