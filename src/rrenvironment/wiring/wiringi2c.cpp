/**********************************************************
 * With the exception of mutex, all routines in this library
 * MUST be re-entrant.
 */

#include <rrenvironment/wiring/wiringi2c.hpp>

dlib::logger dlog_i2c("rr-environment");

namespace rrenv
{



//     void WiringI2C::sendData(const int fd, const uint8_t data_to_send)
//     {
//         // Send data to micro-controller.
//         wiringPiI2CWrite(fd, data_to_send);
//         dlog_i2c << dlib::LDEBUG << "Sent data: " << (int)data_to_send << "\n";
//     }

//     uint8_t WiringI2C::readData(const int fd)
//     {
//         int result = 0;
//         // Read data from micro-controller
//         if ((result = wiringPiI2CRead(fd)) == EOF)
//         {
//             dlog_i2c << dlib::LDEBUG << "no data for device:";
//         }
//         return (uint8_t) result;
//     }

//     void WiringI2C::sendDataBlock(const int fd, const std::list<uint8_t> &data)
//     {
//         dlog_i2c << dlib::LDEBUG << "sending to device " << fd;

//         for (auto it = data.begin(); it != data.end(); ++it)
//         {
//             sendData(fd, *it);
//         }
//     }

//    std::list<uint8_t> WiringI2C::readDataBlock(const int fd, const size_t sz)
//     {
//         std::list<uint8_t> buf;
//         for (size_t i = 0; i < sz; i++) {
//             buf.push_back((uint8_t) wiringPiI2CRead(fd));
//         }
//         return buf;
//     }


    // Private methods
    RrWiringI2C::RrWiringI2C() 
    {

    }

    /**
     * Register a linked to device to the internal map.
     */
    int RrWiringI2C::link_device(const u_int8_t addr, const uint8_t io)
    {
        int fd = -1;
        if (_addr2fd_map.count(addr) == 0) {
            fd = wiringPiI2CSetup(addr);
            if (fd == -1)
            {
                dlog_i2c << dlib::LERROR << "Failed to init I2C communication.\n";
                throw std::runtime_error("Failed to init I2C communication");
            }
            dlog_i2c << dlib::LINFO << "I2C communication successfully setup for device: " << addr;
            _addr2fd_map[addr] = fd;
            dlog_i2c << dlib::LINFO << "I2C device registered to map";
        }

        _func2addr_map.try_emplace(io, addr);
        return _addr2fd_map[addr];
    }

    std::map<std::pair<uint8_t, uint8_t>, int> RrWiringI2C::get_addresses()
    {
        std::map<std::pair<uint8_t, uint8_t>, int> map;
        return map;
    }

}