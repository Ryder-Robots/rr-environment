/*******************************************************************************
 * Mock class for wiring.
 *******************************************************************************/

#include "rrenvironment/wiring.hpp"

dlib::logger dlog_m("WiringMock");

namespace rrenv {

        void WiringPiMock::initilize() {
            dlog_m << dlib::LINFO << "initializing using mock engine";
         }

        void WiringPiMock::pin_mode(int pin, int mode) {
            dlog_m << dlib::LINFO << "pin:" << pin << " mode" << mode;
        }

        void WiringPiMock::digital_write(int pin, int value) {
            dlog_m << dlib::LINFO << "pin:" << pin << " mode" << value;
        }

        void WiringPiMock::pmw_write(int pin, int value) {
            dlog_m << dlib::LINFO << "pin:" << pin << " mode" << value;
        }
}
