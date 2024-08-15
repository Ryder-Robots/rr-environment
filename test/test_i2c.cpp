#include <dlib/logger.h>
#include <rrenvironment/rrenvironment.h>
#include <rrenvironment/rr_logger_hook.hpp>
#include <rrenvironment/wiring/wiringi2c.hpp>

using namespace dlib;

dlib::logger dlog("rr-environment");

int main() {
    RrLoggerHook hook("/dev/stdout");
    set_all_logging_output_hooks(hook);
    dlog.set_level(LALL);
    dlog << LINFO << "start testing";

    rrenv::WiringI2C wiring = rrenv::WiringI2C();
    int i2c008 = wiring.linkDevice(RR_ADDR_I2C_00008);
    wiring.sendData(i2c008, 72);
    unsigned int result = wiring.readData(i2c008);
    dlog << LINFO << "result:" << result;

    std::list<uint8_t> data = {72, 80, 81};

    wiring.sendDataBlock(i2c008, data);
    std::list<uint8_t> blockResult = wiring.readDataBlock(i2c008, 1);
    dlog << LINFO << "blockResult:" << (int) blockResult.front();

    // (result == 72) ? dlog << LINFO << "successfully got one byte back" : perror("can not send bytes");

    return 0;
}