/***************************************************
 * Wiring class to connect with raspberry PI using
 * wiring PI, and BDM ping numbering.
 ***************************************************/

#ifndef _WIRINGGPIO_HPP_
#define _WIRINGGPIO_HPP_

#include <dlib/logger.h>
#include <wiringPi.h>
#include "rrenvironment/wiring.hpp"

namespace rrenv {
    // binds to wiring PI library.
    class WiringGpio : public Wiring {
    public: 
         
         // configures to BDM pin number which will work for RF robot hardware.
        void initilize();

        void pin_mode(int pin, int mode);

        void digital_write(int pin, int value);

        void pmw_write(int pin, int value);

        long digital_read(int pin);

        void pull_up_down_ctl(int pin, int pun) {
            pullUpDnControl(pin, pun);
        }
    };
}

#endif