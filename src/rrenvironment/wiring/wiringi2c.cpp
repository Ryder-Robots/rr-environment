/**********************************************************
 * With the exception of mutex, all routines in this library
 * MUST be re-entrant.
 */

#include <rrenvironment/wiring/wiringi2c.hpp>

dlib::logger dlog_i2c("rr-environment");

namespace rrenv
{
    RrWiringI2C::RrWiringI2C() : _addr2fd_map{},
                                 _func2addr_map{},
                                 _func2cmd_map{}
    {
    }

    // close all the file descriptors.
    RrWiringI2C::~RrWiringI2C()
    {

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

    std::map<uint8_t, uint8_t> RrWiringI2C::get_i2c_io2reg_map()
    {
        return _func2cmd_map;
    }

    /**
     * Register a linked to device to the internal map.
     */
    int RrWiringI2C::link_device(const u_int8_t addr, const uint8_t io, const uint8_t reg)
    {
        if (_addr2fd_map.count(addr) == 0)
        {
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

    void RrWiringI2C::send_block_data(const RrIoTxRx &request)
    {
        dlog_i2c << dlib::LDEBUG << "sending bytes to device: " << std::hex << _func2addr_map[request._io];
        int fd = _addr2fd_map[_func2addr_map[request._io]];
        uint8_t reg = _func2cmd_map[request._io];
        uint8_t *data = new uint8_t[I2C_SMBUS_BLOCK_MAX];

        auto offset = 0;
        auto remainder = request._bytes.size();
        while (remainder > 0)
        {
            int sz = (remainder < I2C_SMBUS_BLOCK_MAX) ? remainder : I2C_SMBUS_BLOCK_MAX;
            for (int i = 0; i < sz; i++)
            {
                data[i] = request._bytes.at(offset++);
                remainder--;
            }
            if (wiringPiI2CWriteBlockData(fd, reg, data, request._bytes.size() + 2) != 0)
            {
                dlog_i2c << dlib::LERROR << "unable to send data: " << strerror(errno);
                throw std::runtime_error("unable to send data");
            }
        }
    }

    RrIoTxRx RrWiringI2C::receive_block_data(const uint8_t cmd, const size_t sz)
    {
        int fd = _addr2fd_map[_func2addr_map[cmd]];
        uint8_t reg = _func2cmd_map[cmd];
        uint8_t values[sz + 2] = {0};

        int rv = wiringPiI2CReadBlockData(fd, reg, values, sz + 2);

        dlog_i2c << dlib::LDEBUG << "got " << rv << " back from blockData read";

        if (rv != (sz + 2)) {
            dlog_i2c << dlib::LWARN << " returned bytes size, and argued byte are different"; 
        }

        int n = sizeof(values) / sizeof(values[0]);
        std::vector<uint8_t> vec(values, values + n);

        RrIoTxRx rx = RrIoTxRx(cmd, vec);
        return rx;
    }

}
