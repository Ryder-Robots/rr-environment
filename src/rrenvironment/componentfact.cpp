/************************************************************************
 * 
 * Components (observers and actions) factory.
 */

#include <rrenvironment/componentfact.hpp>

using namespace std;

dlib::logger dlog_c("COMPONENT_FACTORY");

namespace rrenv {

    /*!
     * Add observer to observers map.
     *
     *  @param classType described in header.
     *  @param obs unique name to retrieve the object later
     *  @param observers map.
     */
     void ComponentsFactory::createObserver(const int classType, string obs, std::map<string, int> &config, Wiring& wiring) {
        switch (classType)
        {
            case RRC_HCSR04:
                _observers[obs] = new Hcsr04();
                break;
            default: 
                dlog_c  << dlib::LFATAL << "unknown class";
                throw runtime_error("unknown classType");
                break;
        }
        _observers[obs]->setup(config, wiring);
    }

    /*!
    * Add action to actions map.
    *
    * @param class type to add
    * @param reference name
    * @param configuration
    * @param actions map
    * @param wiring class
    */
    void ComponentsFactory::createAction(
        const int classType, 
        string act, 
        std::map<string, int> &config, 
        Wiring& wiring
    ) {   

        switch (classType)
        {
        case RRC_L298:
            _actions[act] = new L298();
            break;
        default: 
            dlog_c  << dlib::LFATAL << "unknown class";
            throw runtime_error("unknown classType");
            break;
        }

        // perform configuration.
        _actions[act]->setup(config, wiring);
    }

    Actions ComponentsFactory::get_action(string act) {
        return Actions(*_actions[act]); 
    }
}
