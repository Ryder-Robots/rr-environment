 /**********************************************************************************
  * Test wiringPiSetupGpio
  **********************************************************************************/
 
#include <cstdio>
#include <map>
#include "rrenvironment/Actions.hpp"
#include "rrenvironment/rr_logger_hook.hpp"

using namespace dlib;
dlib::logger dlog("test_l298");

int main() {
    RrLoggerHook hook("/dev/stdout");
    set_all_logging_output_hooks(hook);
   
    dlog.set_level(LALL);
    
    dlog << LINFO << "testing L298";

    rrenv::WiringPiMock wiring = rrenv::WiringPiMock();    
    rrenv::L298 l298 = rrenv::L298();

    wiring.initilize();
    l298.initialize(wiring);

    std::map<std::string, int> config = {
        {"IN1", 23}, {"IN2", 24},{"IN3", 27},{"IN4", 17},{"ENA", 12},{"ENB", 13}
    };
    
    l298.setup(config);

    std::map<std::string, int> args = {};
    l298.run(args);
    dlog << LINFO << "finished testing";
    return 0;
}
