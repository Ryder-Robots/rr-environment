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
#include <rrenvironment/microprocessor.h>

namespace rrenv {

    // Format of data to send to MC
    class rr_io_tx {
    public:
        uint8_t _addr; // I2C address as defined above.
        uint8_t _io;   // this must be a value a RR_IO
        std::list<uint8_t> _bytes; // bytes to send the microprocessor
    };

    // what comes back form the MC
    class rr_io_rx {
    public:
        uint8_t _io;               // this must be a value a RR_IO
        std::list<uint8_t> _bytes; // bytes recieved from micro processor.
    };

    class RrWiringI2C {
    public:
        RrWiringI2C();

        // Send and recieve data from micro-processor.
        rr_io_rx tx_rx(const rr_io_tx& request);

        // Get Addresses.
        std::map<std::pair<uint8_t, uint8_t>, int> get_addresses();
    
    // protected:
        void send_block_data(const rr_io_tx& request);

        rr_io_rx receive_block_data(uint8_t addr);

        // send 8 bits of unsigned data to bus directed at a given handle.
        void send_data(const int fd,  const uint8_t data_to_send);

        // receive 8 bits of data from a given bus.
        uint8_t recieve_data(const int fd);

        // Retruns file hanlde given the address.
        int link_device(const uint8_t addr, const uint8_t io);

    private:
        // maps file reference to device address, and IO function
        // the keys are <address, io_fuction> = file identifier.
        std::map<std::pair<uint8_t, uint8_t>, int> _fd_map;
    };
}

#endif