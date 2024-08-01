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
    void ComponentsFactory::createObserver(
        const int classType, 
        string obs, 
        std::map<string, int> &config, 
        std::map<string, Observers>& observers, 
        Wiring& wiring
    ) {
        switch (classType)
        {
        case RRC_HCSR04:
            observers[obs] = Hcsr04();
            break;
        default: 
            dlog_c << dlib::LFATAL << "unknown class";
            throw runtime_error("unknown classType");
            break;
        }

        // perform configuration.
        observers[obs].setup(config, wiring);
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
        std::map<string, Actions>& actions,
        Wiring& wiring
    ) {   

        switch (classType)
        {
        case RRC_L298:
            actions[act] = L298();
            break;
        default: 
            dlog_c  << dlib::LFATAL << "unknown class";
            throw runtime_error("unknown classType");
            break;
        }

        // perform configuration.
        actions[act].setup(config, wiring);
    }
}
