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
        void initilize() override;

        void pin_mode(int pin, int mode) override;

        void digital_write(int pin, int value) override;

        void pmw_write(int pin, int value) override;

        long digital_read(int pin) override;

        void pull_up_down_ctl(int pin, int pun) override;

        int isr(unsigned int bitRegister, int mode, int pin) override;
    };
}

#endif