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
    int i2cus = wiring.linkDevice(RR_REG_I2C_US);
    wiring.sendData(i2cus, 72);
    unsigned int result = wiring.readData(i2cus);

    // (result == 72) ? dlog << LINFO << "successfully got one byte back" : perror("can not send bytes");

    return 0;
}