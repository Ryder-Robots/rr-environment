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

    // GPIO ports that can be used.
    static const int GPIO_4  = 4;
    static const int GPIO_17 = 17;
    static const int GPIO_27 = 27;
    static const int GPIO_22 = 22;
    static const int GPIO_23 = 23;
    static const int GPIO_24 = 24;
    static const int GPIO_25 = 25;
    static const int GPIO_8  = 8;
    static const int GPIO_7  = 7;
    static const int GPIO_5  = 5;
    static const int GPIO_6  = 6;
    static const int GPIO_16 = 16;
    static const int GPIO_26 = 26;
    static const int GPIO_20 = 20;
    static const int GPIO_21 = 21;


    static const int PWM_0_18 = 18; // GPIO 18
    static const int PWM_0_12 = 12; // GPIO 12
    static const int PWM_1_13 = 13; // GPIO 13
    static const int PWM_1_19 = 19; // GPIO 19

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
