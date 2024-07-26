 /**********************************************************************************
  * Test wiringPiSetupGpio
  **********************************************************************************/
 
#include <cstdio>
#include <map>
#include "rrenvironment/Actions.hpp"

using namespace dlib;
using namespace std;

class my_hook
{
public:
    my_hook(string fname) 
    {
        fout.open(fname, std::ios_base::app);
    }

    void log (
        const string& logger_name,
        const log_level& ll,
        const uint64 thread_id,
        const char* message_to_log
    )
    {
        // Log all messages from any logger to our log file.
        fout << ll << " ["<<thread_id<<"] " << logger_name << ": " << message_to_log << endl;
        cout << ll << " ["<<thread_id<<"] " << logger_name << ": " << message_to_log << endl;
    }

private:
    ofstream fout;
};


using namespace dlib;
dlib::logger dlog("test_l298");

int main() {
    my_hook hook("stdout");
    set_all_logging_output_hooks(hook);
   
    dlog.set_level(LALL);
    
    dlog << LINFO << "TEST !";

    rrenv::WiringPiMock wiring = rrenv::WiringPiMock();    
    rrenv::L298 l298 = rrenv::L298();

    wiring.initilize();
    l298.initialize(wiring);

    std::map<std::string, int> config = {
        {"IN1", 23}, {"IN2", 24},{"IN3", 27},{"IN4", 17},{"ENA", 12},{"ENB", 13}
    };
    
    l298.setup(config);

    // std::map<std::string, int> args = {};
    // l298->run(args);
    dlog.auto_flush();
    return 0;
}