/************************************************************************* 
 * L298 driver, H circuit driver for motors.
 *************************************************************************/

#ifndef _L298_HPP
#define _L298_HPP

#include <map>
#include <string>
#include <exception>
#include <wiringPi.h>
#include <dlib/threads.h>
#include <rrenvironment/rr_logger_hook.hpp>
#include "rrenvironment/actions.hpp"

namespace rrenv {
    class L298 : public Actions {

    public:
        L298();

        const std::string IN1;
        const std::string IN2;
        const std::string IN3;
        const std::string IN4;
        const std::string ENA;
        const std::string ENB;

        static const int MIN_PWM_VAL = 0;
        static const int MAX_PWM_VAL = 1024;

        /*
         * Sets up the pin layout
         */
        void setup(std::map<std::string, int>  &config, Wiring &_wiring);

        /**
         * Send action to L298 motor.
         */
        void run(std::map<std::string, int> &args, Wiring &_wiring) ;

    private:
        int _in1;
        int _in2;
        int _in3;
        int _in4;

        int _ena;
        int _enb;

        dlib::mutex _mtx;

        int setValidPwm(int pwmValue);
    };
}

#endif