/*
 * Common logging hook that can be used to create custom log output. For Raspberry pi, 
 * the requirement is to use ofstream to write to stdout,  not sure why but it doesn't
 * seem to work otherwise.
 */

#ifndef RR_LOGGER_HOOK_HPP_
#define RR_LOGGER_HOOK_HPP_

#include <nlohmann/json.hpp>
#include <dlib/logger.h>

using namespace dlib;
using namespace std;

dlib::logger dlog("rr-environment");

class RrLoggerHook
{
public:

    RrLoggerHook(string fname) 
    {
        // Append to log file
        fout.open(fname, std::ios_base::app);
    }

    void log (
        const string& logger_name,
        const log_level& ll,
        const uint64 thread_id,
        const char* message_to_log
    )
    {
        std::time_t t = std::time(nullptr);
        nlohmann::json j;
        j["level"] = ll.name;
        j["name"] = logger_name;
        j["thread_id"] = thread_id;
        j["epoch"] = t;
        j["message"] = message_to_log;

        // Log all messages from any logger to our log file.
        fout << j.dump() << endl;
    }

private:
    ofstream fout;
};

#endif