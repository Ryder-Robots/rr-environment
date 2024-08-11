/************************************************************************
 * Basic I2C bus implenentation,  not fully featured.
 */

#ifndef WIRINGI2C_HPP
#define WIRINGI2C_HPP

#include <stdint.h>
#include <iostream>
#include <exception>
#include <dlib/logger.h>
#include <wiringPiI2C.h>
#include <rrenvironment/rrenvironment.h>

namespace rrenv {
    class WiringI2C {
    public:

        // Retruns file hanlde given the devId.
        int linkDevice(const int devId);

        // send 8 bits of unsigned data to bus directed at a given handle.
        void sendData(const int df,  const uint8_t data_to_send);

        // receive 8 bits of data from a given bus.
        uint8_t readData(const int fd);

        // CAVEAT: This is not using i2c register block data at this stage, its simply
        // sending 8 bits at a time for the device.
        void sendBlockData(const int fd, const uint8_t *data_to_send);

        // CAVEAT: This is not using i2c register block data at this stage, its simply
        // siply reads 8 bits of data at a time.
        uint8_t *readDataBlock(const int fd, const size_t data_to_read_sz);
    };
}

#endif