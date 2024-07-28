 /**********************************************************************************
  * Test wiringPiSetupGpio
  **********************************************************************************/
 
#include <cstdio>
#include <map>
#include "rrenvironment/actions.hpp"
#include "rrenvironment/rr_logger_hook.hpp"
#include "rrenvironment/wiring.hpp"
#include "rrenvironment/actions/l298.hpp"
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

void shouldThrowException(rrenv::Wiring &wiring, rrenv::Actions &action) {
    bool exceptionThrown = false;
    std::map<std::string, int> args = {};
    try {
        action.run(args, wiring);
    } catch (...) {
        exceptionThrown = true;
    }

    if (!exceptionThrown) {
        throw "FAILED TEST (should of thrown an exception)";
    }
}

void shouldExecuteCorrectly(rrenv::Wiring &wiring, rrenv::Actions &action) {
    std::map<std::string, int> args = {{"IN1", 1}, {"IN2", 0}, {"IN3", 1}, {"IN4", 0}, {"ENA", 350}, {"ENB", 350}};
    action.run(args, wiring);
}

void shouldSetPwm(rrenv::Wiring &wiring, rrenv::Actions &action) {
    std::map<std::string, int> args = {{"IN1", 1}, {"IN2", 0}, {"IN3", 1}, {"IN4", 0}, {"ENA", 2000}, {"ENB", -1}};
    action.run(args, wiring);
}


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

    // Test one just through an exception.
    shouldThrowException(wiring, l298);
    shouldExecuteCorrectly(wiring, l298);
    shouldSetPwm(wiring, l298);

    dlog << LINFO << "finished testing";
    return 0;
}
