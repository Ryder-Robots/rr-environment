/****************************************************
 * Test ultrasonic driver.
 *****************************************************/

#include <dlib/logger.h>
#include <rrenvironment/wiring.hpp>
#include <rrenvironment/observers/hcsr04.hpp>
#include <rrenvironment/rr_logger_hook.hpp>
#include <rrenvironment/observers/hcsr04.hpp>

using namespace dlib;
logger dlog("test_hcsr04");

// May neeed to do a little more to this get some better testing.
class WiringPiMock : public rrenv::Wiring {
public: 


    void initilize() {
        dlog << dlib::LINFO << "initializing using mock engine";
    }

    void pin_mode(int pin, int mode) {
        dlog << dlib::LINFO << "pin:" << pin << " mode:" << mode;
    }

    void digital_write(int pin, int value) {
        dlog << dlib::LINFO << "pin:" << pin << " value:" << value;
    }

    void pmw_write(int pin, int value) {
        dlog << dlib::LINFO << "pin:" << pin << " value:" << value;
    }
};

void shouldBypassTrigger(rrenv::Wiring &wiring, rrenv::Observers &observer) {
    std::map<std::string, int> args = {{"TRIG", 0}};
    std::map<std::string, long> result = {};

     observer.run(args, result, wiring);

     dlog << LINFO << "startTime:" << result["startTime"];
}

int main() {
    RrLoggerHook hook("/dev/stdout");
    set_all_logging_output_hooks(hook);
    dlog.set_level(LALL);
    dlog << LINFO << "testing HCSR04";

    WiringPiMock wiring =  WiringPiMock();
    rrenv::Hcsr04 hcsr04 = rrenv::Hcsr04();

    // Just set the PINS to 23, and 24, if a real pin layout is needed (not mock), then change them.
    std::map<std::string, int> config = {
        {"TRIG", 23}, {"ECHO", 24}
    };
    hcsr04.setup(config, wiring);

    shouldBypassTrigger(wiring, hcsr04);

    dlog << LINFO << "finished testing";
    return 0;
}