/************************************************************************
 * 
 * Components (observers and actions) factory.
 */

#include <rrenvironment/componentfact.hpp>

using namespace std;

dlib::logger dlog_c("COMPONENT_FACTORY");

namespace rrenv {
    void ComponentsFactory::createObserver(const int classType, string obs, std::map<string, int> &config, std::map<string, Observers>& observers) {
        switch (classType)
        {
        case RRC_HCSR04:
            observers[obs] = Hcsr04();
            break;
        default: 
            throw runtime_error("unknown classType");
            break;
        }
    }

    void ComponentsFactory::createAction(const int classType, string obs, std::map<string, int> &config, std::map<string, Actions>& action) {
        // switch (classType)
        // {
        // case RRC_HCSR04:
        //     // actions[obs] = Hcsr04();
        //     break;
        
        // // default:
        // //     break;
        // }       
    }
}
