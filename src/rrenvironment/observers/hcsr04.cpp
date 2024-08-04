/*!
 * Implementation for HCSR04 ultra sonic sensor. The sensor will send out an ultra-sonic frequency as echo
 * then recieve it back as trigger. It will then measure the time it took in milliseconds and return this
 * value within the rv map of the run() routine.
 * 
 * Speed of sound at 20 degrees celius, in meters per second is 343
 */

#include <rrenvironment/observers/hcsr04.hpp>


dlib::logger dlog_b("rr-environment");

namespace rrenv {
    Hcsr04::Hcsr04() : 
        TRIG("TRIG"),
        ECHO("ECHO"),
        BITMASK("BITMASK"),
        _mtx()
    {
        dlog_b << dlib::LINFO << "initialised HCSR04 driver";
    }



    void Hcsr04::setup(std::map<std::string, int>  &config, Wiring &wiring) {
    
        _trig_pin = config[TRIG];
        _echo_pin = config[ECHO];


        if (config[TRIG] != 0) {
            dlog_b << dlib::LINFO << "setting up trigger pin for ultrasonc to: " << _trig_pin; 
            wiring.pull_up_down_ctl(_trig_pin, PUD_DOWN);
            wiring.pin_mode(_trig_pin, OUTPUT);
            dlog_b << dlib::LINFO << "setup complete";
        }
                
        wiring.pin_mode(_echo_pin, INPUT);
        wiring.pull_up_down_ctl(_echo_pin, PUD_DOWN);
        dlog_b << dlib::LINFO << "HCSR04 configured for input";

        dlog_b << dlib::LDEBUG << "setting bitmask";
        // setting up callback.
        if (!config.count(BITMASK)) {
            dlog_b << dlib::LFATAL << "bitmask is not set";
            throw std::runtime_error("bitMask is not set");
        }

        _bit_mask = config[BITMASK];
        if (wiring.isr(_bit_mask, INT_EDGE_RISING, config[BITMASK]) < 0) {
            throw std::runtime_error("unable to create ISR to pin using bitmask");
        }
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
            dlog_b << dlib::LDEBUG << "sending trigger to GPIO:" << _trig_pin;
            wiring.digital_write(_trig_pin, HIGH);
            delay(10);
            wiring.pull_up_down_ctl(_trig_pin, PUD_DOWN);
            dlog_b << dlib::LDEBUG << "sent trigger";
        }

        volatile long startTime = micros();
        for (int i = 0; i < HCSR_04_TIMEOUT; i++) {
            delay(10);
            if (wiring.checkIsr(_bit_mask)) {
                dlog_b << dlib::LDEBUG << "recieved ultrasonic ping";
                wiring.pull_up_down_ctl(_echo_pin, PUD_DOWN);
                break;
            }
        }
        volatile long endTime = micros();

        // Dont bother calculating the difference, do it in the policy. Because of the delay above
        // which could skew the result. Want to take the start tie only from the sensor(s) that has
        // trig > 1.
        rv["startTime"] = startTime;
        rv["endTime"] =  endTime;

        dlog_b << dlib::LINFO << "startTime: " << startTime << " endTime: " << endTime;
        _mtx.unlock();
    }
}