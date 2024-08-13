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

    std::array<uint8_t, 3> data = {'a', 'b', 'c'};

    wiring.sendBlockData(i2c008, data.data());
    result = wiring.readData(i2c008);
    dlog << LINFO << "result:" << result;
    result = wiring.readData(i2c008);
    dlog << LINFO << "result:" << result;
    result = wiring.readData(i2c008);
    dlog << LINFO << "result:" << result;
    result = wiring.readData(i2c008);
    dlog << LINFO << "result:" << result;


    // (result == 72) ? dlog << LINFO << "successfully got one byte back" : perror("can not send bytes");

    return 0;
}