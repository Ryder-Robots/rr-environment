/*!
 * Create registered components and add them to a map.
 */

#ifndef COMPONENTSFACT_HPP
#define COMPONENTSFACT_HPP

#include <string>
#include <map>
#include <exception>
#include <dlib/logger.h>
#include <rrenvironment/observers.hpp>
#include <rrenvironment/actions.hpp>
#include <rrenvironment/observers/hcsr04.hpp>
#include <rrenvironment/actions/l298.hpp>
#include <rrenvironment/wiring.hpp>

using namespace std;

namespace rrenv {
    static const int RRC_L298   = 0b00000000;
    static const int RRC_HCSR04 = 0b00000001;

    class ComponentsFactory {
    public:
        // List registered components here.

        void createObserver(const int classType, string obs, std::map<string, int> &config, Wiring& wiring);

        void createAction(const int classType, string act, std::map<string, int> &config, Wiring& wiring);

        Actions get_action(string act);

        Observers get_observer(string obs);

    private:
        std::map<string, Observers*> _observers;
        std::map<string, Actions*> _actions;
    };
}

#endif