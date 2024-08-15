/*****************************************************************************
 * Used to communicate with a device attached to the system.
 * 
 * Does not assume what the underlying bus is.
 *****************************************************************************/

#ifndef WIRINGMC_HPP
#define WIRINGMC_HPP

#include <rrenvironment/rrenvironment.h>

namespace rrenv {
    template <typename T, typename R, typename W> class WiringMc {

        // Create required communications to the bus
        virtual void init(W wiring);

        // Send transmission data to micro-controller, and recieve back data. This will
        // address  the micro-controller by function only.
        virtual R sendRecieveFunc(uint8_t func, T transmit);

        // close communication with the bus.
        virtual void close();
    };
}

#endif