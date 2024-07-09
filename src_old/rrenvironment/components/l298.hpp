/*******************************************************************************
 * Creates an interface to L298 motor driver.
 *******************************************************************************/

#ifndef L298
#define L298

#include <string>
#include <map>
#include <dlib/logger.h>
#include "rrenvironment/components/component.hpp"

#define MAX_PWM 1024

const std::string IN1 = "IN1";
const std::string IN2 = "IN2";
const std::string IN3 = "IN3";
const std::string IN4 = "IN4";
const std::string ENA = "ENA";
const std::string ENB = "ENB";

using namespace std;

class L298 : public Component {

    public:
        void setup(const map<std::string, int>& config) {
            
            dlog << LINFO << "configuring L298";

            pinMode(get_config_value(IN1, config), OUTPUT);
            pinMode(get_config_value(IN2, config), OUTPUT);
            pinMode(get_config_value(ENA, config), PWM_OUTPUT);

            pinMode(get_config_value(IN3, config), OUTPUT);
            pinMode(get_config_value(IN4, config), OUTPUT);
            pinMode(get_config_value(ENB, config), PWM_OUTPUT);

            dlog << LINFO << "finished configuring L298";
        }

        void run(const map<std::string, int>&  action_io) {
            try {
                digitalWrite(_in1, get_config_value(IN1, action_io));
                digitalWrite(_in2, get_config_value(IN2, action_io));

                digitalWrite(_in3, get_config_value(IN3, action_io));
                digitalWrite(_in4, get_config_value(IN4, action_io));

                // range is 0 to 1024
                pwmWrite(_ena, get_config_value_pwm(ENA, action_io));
                pwmWrite(_enb, get_config_value_pwm(ENB, action_io));
            } catch {

                return action_io;

            }

            //TODO: set action_io to success reponse.
        }

    private:
        unsigned int _in1;
        unsigned int _in2;
        unsigned int _in3;
        unsigned int _in4;
        unsigned int _ena;
        unsigned int _enb;

        unsigned int get_config_value(const string key, const map<std::string, int>&  config) {
            if (config[key].is_number() && (int) config[key] > -1) {
                dlog << LFATAL << "unable to L298 missing key '" << key << "'";
                throw 1;
            }
            return (unsigned int) config[key];
        }

        unsigned int get_config_value_pwm(const string key, const map<std::string, int>&  config) {
            unsigned val = get_config_value(key, config);

            if (val > MAX_PWM) {
                val = MAX_PWM;
            }

            return val;
        }
};

#endif