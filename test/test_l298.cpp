 /**********************************************************************************
  * Test wiringPiSetupGpio
  **********************************************************************************/
 
#include <cstdio>
#include <map>
#include "rrenvironment/actions.hpp"
#include "rrenvironment/rr_logger_hook.hpp"
#include "rrenvironment/wiring.hpp"

using namespace dlib;
dlib::logger dlog("test_l298");

// Bind to mock Wiring pi library, note you do not have to inilise wiring to use this library.
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

int main() {
    RrLoggerHook hook("/dev/stdout");
    set_all_logging_output_hooks(hook);
   
    dlog.set_level(LALL);
    
    dlog << LINFO << "testing L298";

    WiringPiMock wiring =  WiringPiMock();    
    rrenv::L298 l298 = rrenv::L298();

    wiring.initilize();

    std::map<std::string, int> config = {
        {"IN1", 23}, {"IN2", 24},{"IN3", 27},{"IN4", 17},{"ENA", 12},{"ENB", 13}
    };
    
    l298.setup(config, wiring);

    std::map<std::string, int> args = {};
    l298.run(args, wiring);
    dlog << LINFO << "finished testing";
    return 0;
}
