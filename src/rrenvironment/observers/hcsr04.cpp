/*!
 * Implementation for HCSR04 ultra sonic sensor. The sensor will send out an ultra-sonic frequency as echo
 * then recieve it back as trigger. It will then measure the time it took in milliseconds and return this
 * value within the rv map of the run() routine.
 * 
 * TODO: manage the state changes through interupts not using while loops. (too processor intensive.)
 */

#include <rrenvironment/observers/hcsr04.hpp>


dlib::logger dlog_b("HCSR-04");

namespace rrenv {
    Hcsr04::Hcsr04() : 
        TRIG("TRIG"),
        ECHO("ECHO")
    {
        dlog_b << dlib::LINFO << "initialised HCSR04 driver";
    }



    void Hcsr04::setup(std::map<std::string, int>  &config, Wiring &wiring) {
        wiring.pin_mode(config[TRIG], OUTPUT);
        wiring.pin_mode(config[ECHO], INPUT);

        if (config[TRIG] != 0) {
            wiring.pull_up_down_ctl(config[TRIG], PUD_DOWN);
        }
        wiring.pull_up_down_ctl(config[ECHO], PUD_DOWN);
        dlog_b << dlib::LINFO << "HCSR04 configured for input";
    }

    /*************************************************************************************************
     * Note that if the argument trig = 0 then do not trigger just record the time when we recieved
     * the signal, this to allow for multiple sonars to be on the same board using the same trigger.
     * 
     * This cuts down on wires, and reduces the complexity by making it hardware driven.
     ************************************************************************************************/
    void Hcsr04::run(std::map<std::string, int> &args, std::map<std::string, long> &rv, Wiring &wiring) {

        dlib::auto_mutex lock(_mtx);
        // Give the trigger some time to exeucte (around 10 milliseconds)
        if (args[TRIG] != 0) {
            dlog_b << dlib::LINFO << "sent trigger";
            wiring.digital_write(_trig_pin, HIGH);
            delay(10);
            wiring.pull_up_down_ctl(_trig_pin, PUD_DOWN);
        }

        volatile long now = micros();
        volatile long startTime = micros();
        while (wiring.digital_read(_echo_pin) == LOW && micros() - now < HCSR_04_TIMEOUT);
        while (wiring.digital_read(_echo_pin) == HIGH);
        volatile long endTime = micros();
        wiring.pull_up_down_ctl(_echo_pin, PUD_DOWN);

        // Dont bother calculating the difference, do it in the policy. Because of the delay above
        // which could skew the result. Want to take the start tie only from the sensor(s) that has
        // trig > 1.
        rv["startTime"] = startTime;
        rv["endTime"] =  endTime;
        _mtx.unlock();
    }
}