/****************************************************************************************
 * ! 
 * Implenmentation for L298 driver.
 * 
 * L298 drivers will drive two DC motors. 
 * 
 * Values associated with DC motor A, are:
 *    EN1 (either HIGH or LOW),  EN2 (either HIGH or LOW), ENA value between 0 to 1024 that corresponds 
 *    to pulses (PWM), or in real terms voltage to send to motor A,  for example 350 will mean 3.5 volt.s
 *    
 * Value assocated with DC motor B, are:  
 *  *    EN3 (either HIGH or LOW),  EN4 (either HIGH or LOW), ENB value between 0 to 1024 that corresponds 
 *      to pulses (PWM), or in real terms voltage to send to motor A,  for example 350 will mean 3.5 volt.s
 * 
 * Note that the value EN the value will determine the polority, for example if EN1=HIGH, and EN2=LOW the motor
 * will spin clockwise.  if EN1=LOW, EN2=HIGH motor will turn anti-clockwise. If EN1=LOW, EN2=LOW motor is effecitvely
 * off.
 *****************************************************************************************/

#include <rrenvironment/actions/l298.hpp>

dlib::logger dlog_a("rr-environment");

namespace rrenv {

    L298::L298() : 
        IN1("IN1"),
        IN2("IN2"),
        IN3("IN3"),
        IN4("IN4"),
        ENA("ENA"),
        ENB("ENB")
    {
        dlog_a << dlib::LINFO << "initialised L298 driver";
    }

    /*!
     * setup pins and perform pulldowns.
     *
     * @param map containing pins IN1, IN2, IN3, IN4, ENA, and ENB, this should map tp GPIO numbers on board.
     * @param wiring class to use. 
     */
    void L298::setup(std::map<std::string, int>  &config, Wiring &_wiring) {
        dlog_a << dlib::LINFO << "setting up driver";
        try {
            dlog_a << dlib::LINFO << "configuring L298";
            _wiring.pin_mode(config[IN1], OUTPUT);
            _in1 = config[IN1];
            _wiring.pin_mode(config[IN2], OUTPUT);
            _in2 = config[IN2];
            _wiring.pin_mode(config[ENA], PWM_OUTPUT);
            _ena = config[ENA];

            _wiring.pin_mode(config[IN3], OUTPUT);
            _in3 = config[IN3];
            _wiring.pin_mode(config[IN4], OUTPUT);
            _in4 = config[IN4];
            _wiring.pin_mode(config[ENB], PWM_OUTPUT);
            _enb = config[ENB];

            int pd[] = {config[IN1], config[IN2], config[IN3], config[IN4], config[ENA], config[ENB]};
            for (int i : pd) {
                _wiring.pull_up_down_ctl(i, PUD_DOWN);
            }
            
            dlog_a << dlib::LINFO << "finished configuring L298";
        } catch (const exception &e) {
            dlog_a << dlib::LFATAL << "unable to configure motor " << e.what();
            throw runtime_error("could not set up motor");
        }
    }

    /*!
     * send a command to motor associated with this driver (note this class is thread safe).
     *
     * @param values of EN1, EN2, EN3, EN4, ENA, and ENB
     * @param wiring class
     */
    void L298::run(std::map<std::string, int> &args, Wiring &_wiring) {
   
        // check to see igf all value have been set for running the motor.
        const string keys[6] = {IN1, IN2, IN3, IN4, ENA, ENB};
        for (auto k : keys) {
            if (args.find(k) == args.end()) {
                dlog_a << dlib::LERROR << "missing critical key";
                throw runtime_error("missing critical key for L298");
            }
        }

        try {
            // If argument is set but it out of range,  this is not an error. If just means
            // we set defaults minimum or max,
            args[ENA] = setValidPwm(args[ENA]);
            args[ENB] = setValidPwm(args[ENB]);

            dlib::auto_mutex lock(_mtx);
            _wiring.digital_write(_in1, args[IN1]);
            _wiring.digital_write(_in2, args[IN2]);

            _wiring.digital_write(_in3, args[IN3]);
            _wiring.digital_write(_in4, args[IN4]);

            // range is 0 to 1024
            _wiring.pmw_write(_ena, args[ENA]);
            _wiring.pmw_write(_enb, args[ENB]);
        } catch (const exception& e) {
            dlog_a << dlib::LERROR << "could not send l298 message :" << e.what();
        }
        _mtx.unlock();
    }

    int L298::setValidPwm(int pwmValue) {
        int result = pwmValue;
        if (pwmValue < MIN_PWM_VAL) {
            result = MIN_PWM_VAL;
        }
        if (pwmValue > MAX_PWM_VAL) {
                result = MAX_PWM_VAL;
        }
        return result;
    }
}