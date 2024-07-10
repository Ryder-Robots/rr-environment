 /**********************************************************************************
  * Test wiringPiSetupGpio
  **********************************************************************************/
 
 #include "rrenvironment/Actions.hpp"
 #include <map>
 #include <wiringPi.h>

int main() {
    wiringPiSetupGpio();
    // rrevnv::Actions* l298 = new rrevnv::L298();

    // std::map<std::string, int> config = {
    //     {"IN1", 23}, {"IN2", 24},{"IN3", 27},{"IN4", 17},{"ENA", 12},{"ENB", 13}
    // };
    // l298->setup(config);

    // std::map<std::string, int> args = {};
    // l298->run(args);
    
    return 0;
}