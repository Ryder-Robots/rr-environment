/**********************************************************************
 * Wiring classes.
 **********************************************************************/
#ifndef _WIRING_HPP_
#define _WIRING_HPP_

#include <wiringPi.h>
#include <dlib/logger.h>


namespace rrenv {
    class Wiring {
    public: 
        virtual void initilize() {}

        virtual void pin_mode(int pin, int mode) {}

        virtual void digital_write(int pin, int value) {}

        virtual void pmw_write(int pin, int value) {}

    };

    // binds to wiring PI library.
    class WiringPiWiring : public Wiring {
    public: 
         
         // configures to BDM pin number which will work for RF robot hardware.
         void initilize() {
            // dlog_w << dlib::LINFO << "initializing using BDM (GPIO) pin layout";
            wiringPiSetupGpio();
         }

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

    // Bind to mock Wiring pi library, note you do not have to inilise wiring to use this library.
    class WiringPiMock : public Wiring {
   public: 

        void initilize() {
            // dlog_w << dlib::LINFO << "initializing using mock engine";
         }

        void pin_mode(int pin, int mode) {
            // dlog_w << dlib::LINFO << "pin:" << pin << " mode" << mode;
        }

        void digital_write(int pin, int value) {
            // dlog_w << dlib::LINFO << "pin:" << pin << " mode" << value;
        }

        void pmw_write(int pin, int value) {
            // dlog_w << dlib::LINFO << "pin:" << pin << " mode" << value;
        }
    };

}

#endif