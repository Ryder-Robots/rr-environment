/*******************************************
 * Interface for functions.
 */

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <rrenvironment/rrenvironment.h>
#include <rrenvironment/wiring/wiringi2c.hpp>

namespace rrenv {
    class RrFunction {
    public:
        void set_wiring(const RrWiringI2C &wiring) 
        {
            _wiring = wiring;
        }

        virtual RrIo send_and_recieve(RrIo request);
        RrWiringI2C _wiring;
        uint8_t      _cmd;   // Function to use.
        uint8_t      _addr;  // Address of micro-controller.
    };
}

#endif