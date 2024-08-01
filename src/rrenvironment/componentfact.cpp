/************************************************************************
 * 
 * Components (observers and actions) factory.
 */

#include <rrenvironment/componentfact.hpp>

using namespace std;

dlib::logger dlog_c("rr-environment");

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
                this->_observers.insert(std::make_pair(obs, new Hcsr04()));
                break;
            default: 
                dlog_c  << dlib::LFATAL << "unknown class";
                throw runtime_error("unknown classType");
                break;
        }
        _observers[obs]->setup(config, wiring);

        dlog_c << LDEBUG << "observer map now has " << _observers.size();
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

    //TODO: wrap these into a try catch statement, to avoid breaking stuff.
    Actions* ComponentsFactory::getAction(string act) {
        return _actions[act]; 
    }

    Observers* ComponentsFactory::getObserver(string obs) {

        dlog_c << LDEBUG << "observer map now has " << _observers.size();

        Observers* o = _observers[obs];
        dlog_c << LDEBUG << "observer found";
        return o;
    }
}
