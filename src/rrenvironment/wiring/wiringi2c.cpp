/**********************************************************
 * With the exception of mutex, all routines in this library
 * MUST be re-entrant.
 */

#include <rrenvironment/wiring/wiringi2c.hpp>

dlib::logger dlog_i2c("rr-environment");

namespace rrenv
{
    RrWiringI2C::RrWiringI2C():
    _addr2fd_map{},
    _func2addr_map{},
    _func2cmd_map{}
    {}

    // close all the file descriptors.
    RrWiringI2C::~RrWiringI2C() {
        
        for (auto it : _addr2fd_map)
        {
            close(it.second);
        }
    }

    std::map<uint8_t, int> RrWiringI2C::get_i2c_addr2file_map()
    {
        return _addr2fd_map;
    }

    std::map<uint8_t, uint8_t> RrWiringI2C::get_i2c_io2addr_map()
    {
        return _func2addr_map;
    }



    /**
     * Register a linked to device to the internal map.
     */
    int RrWiringI2C::link_device(const u_int8_t addr, const uint8_t io, const uint8_t reg)
    {
        if (_addr2fd_map.count(addr) == 0) {
            int fd = wiringPiI2CSetup(addr);
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
        _func2cmd_map.try_emplace(io, reg);
        return _addr2fd_map[addr];
    }

    void RrWiringI2C::send_block_data(const RrIoTx &request)
    {
        dlog_i2c << dlib::LDEBUG << "sending bytes to device: " << std::hex << _func2addr_map[request._io];
        int fd = _addr2fd_map[_func2addr_map[request._io]];
        uint8_t reg = _func2cmd_map[request._io];

        uint8_t *data = new uint8_t[request._bytes.size()];
        copy(request._bytes.begin(),request._bytes.end(), data);

        if (wiringPiI2CWriteBlockData(fd, reg, data, request._bytes.size()) != 0) 
        {
            dlog_i2c << dlib::LERROR << "unable to send data: " << strerror(errno);
            throw std::runtime_error("unable to send data");
        }
    }

}



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