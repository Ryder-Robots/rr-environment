/**********************************************************************
 * Wiring classes.
 **********************************************************************/
#ifndef _WIRING_HPP_
#define _WIRING_HPP_

#include <wiringPi.h>

namespace rrevnv {
    class Wiring {
    public: 
        virtual void pin_mode(int pin, int mode) {}

        virtual void digital_write(int pin, int value) {}

        virtual void pmw_write(int pin, int value) {}
    };

    class WiringPiWiring : public Wiring {
    public: 
        void pin_mode(int pin, int mode) {
            return pinMode(pin, mode);
        }

        void digital_write(int pin, int value) {
            digitalWrite(pin, value);
        }

        void pmw_write(int pin, int value) {
            pwmWrite(pin, value);
        }
    };
}

#endif