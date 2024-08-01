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

using namespace std;

namespace rrenv {
    class ComponentsFactory {
    public:
        // List registered components here.
        static const int RRC_L298   = 0b00000000;
        static const int RRC_HCSR04 = 0b00000001;

        void createObserver(const int classType, string obs, std::map<string, int> &config, std::map<string, Observers>& observer);

        void createAction(const int classType, string act, std::map<string, int> &config, std::map<string, Actions>& action);
    };
}

#endif