/************************************************
 * General interface to interact with actions.
 ************************************************/

#ifndef ABSTRACTACTION_HPP
#define ABSTRACTACTION_HPP

#include <string>
#include <map>

#include "dlib/threads.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class RrEnvironment {
    public:
        void setup_threadpool(dlib::thread_pool& tp);

        /*
         * Sets hardware observation class.
         */
        void add_hw_observer(const unsigned int oid, const string hw_class, const map<std::string, int>&  config);

        /*
         * set hw action and add it to list.
         */
        void add_hw_action(const unsigned int oid, const string hw_class, const map<std::string, int>&  config);

        /*
         * Execute actions.
         */
        void execute_actions(const dlib::future<map<std::string, json>> args);

        void get_observations(const dlib::future<map<std::string, json>> observations);
};

#endif
