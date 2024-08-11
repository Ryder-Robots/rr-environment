/**********************************************************
 * With the exception of mutex, all routines in this library
 * MUST be re-entrant.
 */

#include <rrenvironment/wiring/wiringi2c.hpp>

dlib::logger dlog_i2c("rr-environment");

namespace rrenv
{

    int WiringI2C::linkDevice(const int devId)
    {
        int fd = wiringPiI2CSetup(devId);
        if (fd == -1)
        {
            dlog_i2c << dlib::LERROR << "Failed to init I2C communication.\n";

            throw std::runtime_error("Failed to init I2C communication");
        }
        dlog_i2c << dlib::LINFO << "I2C communication successfully setup for device: " << devId;
        return fd;
    }

    void WiringI2C::sendData(const int fd, const uint8_t data_to_send)
    {
        // Send data to micro-controller.
        wiringPiI2CWrite(fd, data_to_send);
        dlog_i2c << dlib::LDEBUG << "Sent data: " << (int)data_to_send << "\n";
    }

    uint8_t WiringI2C::readData(const int fd)
    {
        uint8_t result = 0;
        // Read data from micro-controller
        if ((result = wiringPiI2CRead(fd)) == -1)
        {
            dlog_i2c << dlib::LERROR << "could not read data for device:" << fd;
        }
        return result;
    }

    void WiringI2C::sendBlockData(const int fd, const uint8_t *data_to_send)
    {
        uint8_t blocks2send = sizeof(data_to_send) / sizeof(uint8_t);

        dlog_i2c << dlib::LDEBUG << "sending " << blocks2send << " to device " << fd;
        sendData(fd, blocks2send);

        for (int i = 0; i < blocks2send; i++)
        {
            sendData(fd, data_to_send[i]);
        }
    }

    uint8_t* WiringI2C::readDataBlock(const int fd, const size_t data_to_read_sz)
    {
        uint8_t *buf = static_cast<uint8_t *>(malloc(data_to_read_sz));
        
        // Get actual size of result.
        uint8_t result = readData(fd);
        if (result != data_to_read_sz) {
            dlog_i2c << dlib::LWARN << "size of result data_to_read_sz is different";
        }

        int blocks = result / sizeof(uint8_t);
        for (int i = 0; i < blocks; i++) 
        {
            buf[i] = readData(fd);
        }
        return buf;
    }

}