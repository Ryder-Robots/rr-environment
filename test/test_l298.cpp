 /**********************************************************************************
  * Test wiringPiSetupGpio
  **********************************************************************************/
 

#include <map>
#include "rrenvironment/Actions.hpp"

using namespace dlib;
using namespace std;

class my_hook
{
public:
    my_hook(
    ) 
    {
        fout.open("my_log_file.txt");
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

        // But only log messages that are of LINFO priority or higher to the console.
        if (ll >= LINFO)
            cout << ll << " ["<<thread_id<<"] " << logger_name << ": " << message_to_log << endl;
    }

private:
    ofstream fout;
};

int main() {
    my_hook hook;
    set_all_logging_output_hooks(hook);
    logger dlog("test_l298");
    dlog.set_level(LALL);

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
    
    return 0;
}