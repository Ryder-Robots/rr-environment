 /**********************************************************************************
  * Test wiringPiSetupGpio
  **********************************************************************************/
 

#include <map>
#include "rrenvironment/Actions.hpp"

int main() {
    rrenv::WiringPiMock wiring = rrenv::WiringPiMock();
    rrenv::Actions l298 = rrenv::L298();

    wiring.initilize();
    l298.initialize(wiring);

    std::map<std::string, int> config = {
        {"IN1", 23}, {"IN2", 24},{"IN3", 27},{"IN4", 17},{"ENA", 12},{"ENB", 13}
    };
    
    l298.setup(config);

    // std::map<std::string, int> args = {};
    // l298->run(args);
    
    return 0;
}