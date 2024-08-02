/***************************************************
 * Wiring class to connect with raspberry PI using
 * wiring PI, and BDM ping numbering.
 ***************************************************/


#include "rrenvironment/wiring/wiringgpio.hpp"


// Create a logger specific for this
dlib::logger dlog_gpio("rr-environment");

// This is a special variable do not access it directory.
/*****************************************************************************
 *  RR_OBS_RX is used to reflect that a wire is either pulled down or pulled 
 *  depending on how the wire interupt is defined.
 */

static volatile long  RR_OBS_RX = 0;

namespace rrenv {
        // configures to BDM pin number which will work for RF robot hardware.
         void WiringGpio::initilize() {
            dlog_gpio << dlib::LINFO << "initializing using BDM (GPIO) pin layout";
            RR_OBS_RX = 0;
            if (wiringPiSetupGpio() < 0) {
               dlog_gpio << dlib::LFATAL << "unable to set up wiring SDK (wiringPi)";
            }
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

         long WiringGpio::digital_read(int pin) {
            return digital_read(pin);
         }

         void WiringGpio::pull_up_down_ctl(int pin, int pun) {
             pullUpDnControl(pin, pun);
         }
}
