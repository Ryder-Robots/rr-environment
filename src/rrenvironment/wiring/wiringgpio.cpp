/***************************************************
 * Wiring class to connect with raspberry PI using
 * wiring PI, and BDM ping numbering.
 ***************************************************/


#include "rrenvironment/wiring/wiringgpio.hpp"


// Create a logger specific for this
dlib::logger dlog_gpio("WiringGpio");

namespace rrenv {

        // configures to BDM pin number which will work for RF robot hardware.
         void WiringGpio::initilize() {
            dlog_gpio.set_level(dlib::LALL);
            dlog_gpio << dlib::LINFO << "initializing using BDM (GPIO) pin layout";
            wiringPiSetupGpio();
         }

         void WiringGpio::pin_mode(int pin, int mode) {
            return pinMode(pin, mode);
         }

         void WiringGpio::digital_write(int pin, int value) {
            digitalWrite(pin, value);
         }
        
         void WiringGpio::pmw_write(int pin, int value) {
            pwmWrite(pin, value);
         }
}
