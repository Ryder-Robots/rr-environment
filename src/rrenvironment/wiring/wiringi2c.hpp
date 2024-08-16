/************************************************************************
 * Basic I2C bus implenentation,  not fully featured.
 */

#ifndef WIRINGI2C_HPP
#define WIRINGI2C_HPP

#include <list>
#include <map>
#include <stdint.h>
#include <iostream>
#include <unistd.h>
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

        ~RrWiringI2C();

        // Send and recieve data from micro-processor.
        rr_io_rx tx_rx(const rr_io_tx& request);

        // Get Addresses and their file descriptors
        std::map<uint8_t, int> get_i2c_addr2file_map();

        // Get functions and their address addresses
        std::map<uint8_t, uint8_t> get_i2c_io2addr_map();
    
        void send_block_data(const rr_io_tx& request);

        rr_io_rx receive_block_data(uint8_t addr);

        // send 8 bits of unsigned data to bus directed at a given handle.
        void send_data(const int fd,  const uint8_t data_to_send);

        // receive 8 bits of data from a given bus.
        uint8_t recieve_data(const int fd);

        // Retruns file hanlde given the address.
        int link_device(const uint8_t addr, const uint8_t io);

    private:
        // Address points to file descriptor
        std::map<uint8_t, int> _addr2fd_map;

        // Point funciton to address
        std::map<uint8_t, uint8_t> _func2addr_map;

    };
}

#endif