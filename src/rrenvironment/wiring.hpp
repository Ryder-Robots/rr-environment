/**********************************************************************
 * Wiring classes.
 * 
 * The default is GPIO (BDM), however there is an interface for testing
 * and because WiringPI will be deprecated and we may need some other 
 * way of interacting with this PI hardware.
 **********************************************************************/
#ifndef _WIRING_HPP_
#define _WIRING_HPP_

namespace rrenv {
    class Wiring {
    public: 

        virtual void initilize() {}

        virtual void pin_mode(int pin, int mode) {}

        virtual void digital_write(int pin, int value) {}

        virtual void pmw_write(int pin, int value) {}
   
        virtual long digital_read(int pin) {return 0;}

        virtual void pull_up_down_ctl(int pin, int pun) {}
    };
}

#endif
