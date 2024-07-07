/************************************************
 * General interface to interact with actions.
 ************************************************/

#ifndef ABSTRACTACTION_HPP
#define ABSTRACTACTION_HPP

#include <nlohmann/json.hpp>
#include <string.h>
#include <map>

using json = nlohmann::json;
using string = std::string

class RrEnvironment {
    public:
        /*
         * sets hardware configuration.
         */
        void setup_hw(const unsigned int oid, const string hw_class, const json config);

        /*
         * links environment to threadpool.
         */
        void setup_thread_pool(thread_pool& tp);

        /*
         * sets the next request to process.
         */
        void set_request(unsigned int oid, dlib::future<json>& action_io);


        /******************************************************************
         * trigger all queued actions. The results will be transferred to 
         * json future task.
         ******************************************************************/
        void trigger();


    private:

        // 

        // executes an indivual action.
        void execute_action(unsigned int oid, dlib::future<json>& action_io);
};

#endif
