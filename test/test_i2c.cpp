#include <dlib/logger.h>
#include <rrenvironment/rrenvironment.h>
#include <rrenvironment/rr_logger_hook.hpp>
#include <rrenvironment/wiring/wiringi2c.hpp>
#include <rrenvironment/microprocessor.h>

using namespace dlib;

dlib::logger dlog("rr-environment");

int main() 
{
    RrLoggerHook hook("/dev/stdout");
    set_all_logging_output_hooks(hook);
    dlog.set_level(LALL);
    dlog << LINFO << "start testing";

    rrenv::RrWiringI2C wiring = rrenv::RrWiringI2C();
    int fd = wiring.link_device(RR_ADDR_I2C_MC2, RR_IO_MOTOR_A, RR_IO_MOTOR_A);

    std::map<uint8_t, int>  addr2file = wiring.get_i2c_addr2file_map();

    if (addr2file[RR_ADDR_I2C_MC2] == fd) {
        dlog << LINFO << "has map to file reference";
    }
    else 
    {
        return 1;
    }

    std::map<uint8_t, uint8_t> io2addr_map = wiring.get_i2c_io2addr_map();
    if (io2addr_map[RR_IO_MOTOR_A] == RR_ADDR_I2C_MC2) {
        dlog << LINFO << "has io to addr reference";
    }
    else 
    {
        return 1;
    }

    std::vector<uint8_t> data = {4, 3, 2, 1};
    rrenv::RrIoTxRx rtx = rrenv::RrIoTxRx(RR_IO_MOTOR_A, data);
    wiring.send_block_data(rtx);
    rrenv::RrIoTxRx response = wiring.receive_block_data(RR_IO_MOTOR_A, 4);

    for (auto i : response._bytes) {
        dlog << LINFO << "bytes : " << i;
    }

    return 0;
}