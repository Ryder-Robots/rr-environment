/*!
 * \file wiringi2c.hpp
 * \brief Basic I2C bus implenentation,  not fully featured.
 * 
 * I2C (TW) for debian is based of the BSD SMBus protocol 
 * https://man.freebsd.org/cgi/man.cgi?query=smbus&sektion=4&n=1
 * 
 * A packaet layout of the bus looks like
 * https://www.kernel.org/doc/html/latest/i2c/smbus-protocol.html
 * https://e2e.ti.com/support/microcontrollers/msp-low-power-microcontrollers-group/msp430/f/msp-low-power-microcontroller-forum/685262/msp430-smbus-smbus-library-compatabilty-mlx90615
 */

#ifndef WIRINGI2C_HPP
#define WIRINGI2C_HPP

#include <list>
#include <map>
#include <stdint.h>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <exception>
#include <iterator>
#include <dlib/logger.h>
#include <wiringPiI2C.h>
#include <rrenvironment/rrenvironment.h>
#include <rrenvironment/microprocessor.h>

namespace rrenv {

    #define I2C_SMBUS_BLOCK_MAX 4

    /*!
     * \def rr_io_tx cmd  = rr_io_tx()
     *
     * Sends command to the SMBus. _bytes must be populated with no more than 32 bytes
     * in the order that is expected by the device or micro-processor. Byte are to sent
     * using MSb
     */
    class RrIoTxRx {
    public:
        RrIoTxRx(const uint8_t io, const std::vector<uint8_t> bytes):
            _tp{},
            _trace_id{},
            _span_id{} 
        {
            _io = io;
            _bytes = bytes;
        }

        // time that the request was sent.
        std::chrono::time_point<std::chrono::system_clock> _tp; 
        std::hash<std::string> _trace_id;  // indicates where the request originally came from
        std::hash<std::string> _span_id;   // indicates what subsysterms this request has touched.
        uint8_t _io;                       // this must be a value a RR_IO
        std::vector<uint8_t> _bytes;       // bytes to send the microprocessor
    };

    /*
     * links to I2C bus.
     */
    class RrWiringI2C {
    public:
        RrWiringI2C();

        ~RrWiringI2C();

        /*!
         * creates device link to a micro-controller that is using addres 'addr'. 
         *
         * \param addr I2C address of device or micro-controller
         * \param cmd  IO command defined in rrenvironment.h that device can perform.
         * \param reg  internal register that the device will use when it can perform more than
         *             one command.
         * \return file descriptor for device
         */
        int link_device(const uint8_t addr, const uint8_t cmd, const uint8_t reg);

        /*!
         * sends request to I2C device or micro-processor.
         *
         * \param request request to send to device.
         * \return response from device.
         */
        RrIoTxRx tx_rx(const RrIoTxRx &request);

        /*!
         * list of registered addresses, and their associated file descrptors.
         */
        std::map<uint8_t, int> get_i2c_addr2file_map();

        /*!
         * list of commands and its associated I2C address
         */
        std::map<uint8_t, uint8_t> get_i2c_io2addr_map();

        /*!
         * list of commands and its assocated register for device.
         */
        std::map<uint8_t, uint8_t> get_i2c_io2reg_map();
    
        void send_block_data(const RrIoTxRx &request);

        RrIoTxRx receive_block_data(const uint8_t cmd, const size_t sz);

    private:
        // Address points to file descriptor
        std::map<uint8_t, int> _addr2fd_map;

        // Point funciton to address
        std::map<uint8_t, uint8_t> _func2addr_map;

        // Points function to micro-proessor register, 
        // registers can be repeated.
        std::map<uint8_t, uint8_t> _func2cmd_map;
    };
}

#endif