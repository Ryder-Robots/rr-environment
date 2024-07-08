/************************************************
 * General interface to interact with actions.
 ************************************************/

#ifndef ABSTRACTACTION_HPP
#define ABSTRACTACTION_HPP

#include <string>
#include <map>

using namespace std;

class RrEnvironment {
    public:
        /*
         * Sets hardware observation class.
         */
        void add_hw_observer(const unsigned int oid, const string hw_class, const map<std::string, int>&  config);

        /*
        * set hw action and add it to list.
         */
        void add_hw_action(const unsigned int oid, const string hw_class, const map<std::string, int>&  config);

};

#endif
