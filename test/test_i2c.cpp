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
    int fd = wiring.link_device(RR_ADDR_I2C_MC1, RR_IO_MOTORS, 0x00);

    std::map<uint8_t, int>  addr2file = wiring.get_i2c_addr2file_map();

    if (addr2file[RR_ADDR_I2C_MC1] == fd) {
        dlog << LINFO << "has map to file reference";
    }
    else 
    {
        return 1;
    }

    std::map<uint8_t, uint8_t> io2addr_map = wiring.get_i2c_io2addr_map();
    if (io2addr_map[RR_IO_MOTORS] == RR_ADDR_I2C_MC1) {
        dlog << LINFO << "has io to addr reference";
    }
    else 
    {
        return 1;
    }

    std::list<uint8_t> data = {72};
    rrenv::RrIoTx rtx = rrenv::RrIoTx();
    rtx._io = RR_IO_MOTORS;
    rtx._bytes = data;
    wiring.send_block_data(rtx);



    // wiring.sendData(i2c008, 72);
    // unsigned int result = wiring.readData(i2c008);
    // dlog << LINFO << "result:" << result;

    // std::list<uint8_t> data = {72, 80, 81};

    // wiring.sendDataBlock(i2c008, data);
    // std::list<uint8_t> blockResult = wiring.readDataBlock(i2c008, 1);
    // dlog << LINFO << "blockResult:" << (int) blockResult.front();

    // (result == 72) ? dlog << LINFO << "successfully got one byte back" : perror("can not send bytes");

    return 0;
}