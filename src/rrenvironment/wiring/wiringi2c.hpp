/************************************************************************
 * Basic I2C bus implenentation,  not fully featured.
 */

#ifndef WIRINGI2C_HPP
#define WIRINGI2C_HPP

#include <list>
#include <map>
#include <stdint.h>
#include <iostream>
#include <exception>
#include <dlib/logger.h>
#include <wiringPiI2C.h>
#include <rrenvironment/rrenvironment.h>

namespace rrenv {

    // Format of data to send to MC
    class rr_io_tx {
    public:
        uint8_t addr; // I2C address as defined above.
        uint8_t io;   // this must be a value a RR_IO
        std::list<uint8_t> bytes; // bytes to send the microprocessor
    };

    // what comes back form the MC
    class rr_io_rx {
    public:
        uint8_t io;   // this must be a value a RR_IO
        std::list<uint8_t> bytes; // bytes recieved from micro processor.
    };

    class RrWiringI2C {
    public:
        RrWiringI2C();

        // Send and recieve data from micro-processor.
        rr_io_rx txRx(const rr_io_tx& request);
    
    private:
        void sendBlockData(const rr_io_tx& request);

        rr_io_rx receiveBlockData(uint8_t addr);

        // send 8 bits of unsigned data to bus directed at a given handle.
        void sendData(const int fd,  const uint8_t data_to_send);

        // receive 8 bits of data from a given bus.
        uint8_t readData(const int fd);

        // Retruns file hanlde given the address.
        int linkDevice(const u_int8_t addr);

        // Map of FD set by linkDevice
        std::map<uint8_t, int> _fdMap;
    };
}

#endif