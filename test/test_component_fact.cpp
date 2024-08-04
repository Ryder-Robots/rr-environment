#include <map>

#include <dlib/logger.h>
#include <rrenvironment/wiring.hpp>
#include <rrenvironment/rr_logger_hook.hpp>
#include <rrenvironment/componentfact.hpp>
#include <rrenvironment/wiring/wiringgpio.hpp>

using namespace dlib;

dlib::logger dlog("rr-environment");

class WiringPiMock : public rrenv::Wiring {
public: 
    void initilize() {
        dlog << dlib::LINFO << "initializing using mock engine";
    }

    void pin_mode(int pin, int mode) {
        dlog << dlib::LINFO << "pin:" << pin << " mode:" << mode;
    }

    void digital_write(int pin, int value) {
        dlog << dlib::LINFO << "pin:" << pin << " value:" << value;
    }

    void pmw_write(int pin, int value) {
        dlog << dlib::LINFO << "pin:" << pin << " value:" << value;
    }

    long digital_read(int pin) {
        return 1;
    }
};

using namespace rrenv;

int main() {
    RrLoggerHook hook("/dev/stdout");
    set_all_logging_output_hooks(hook);
    dlog.set_level(LALL);
    dlog << LINFO << "start testing";

    ComponentsFactory fact = ComponentsFactory();

    // motor A 
    std::map<string, int> configA = {
        {"IN1", GPIO_4}, 
        {"IN2", GPIO_17}, 
        {"ENA", PWM_0_12}, 
        {"IN3", GPIO_27}, 
        {"IN4", GPIO_22}, 
        {"ENB", PWM_0_18}
    };

    std::map<string, int> configB = {
        {"IN1", GPIO_23}, 
        {"IN2", GPIO_24}, 
        {"ENA", PWM_1_13}, 
        {"IN3", GPIO_25}, 
        {"IN4", GPIO_8},
        {"ENB", PWM_1_19}};

    std::map<string, int> ultraSonic1 = {
        {"TRIG", GPIO_6}, {"ECHO", GPIO_5}, {"BITMASK", 0b0001}
    };

    std::map<string, int> ultraSonic2 = {
        {"TRIG", 0},      {"ECHO", GPIO_6}, {"BITMASK", 0b0010}
    };

    std::map<string, int> ultraSonic3 = {
        {"TRIG", 0},     {"ECHO", GPIO_16}, {"BITMASK", 0b0100}
    };

    // std::map<string, Actions> actions = {};
    // std::map<string, Observers> observers = {};
    //Wiring mock = WiringPiMock();
    WiringGpio mock = WiringGpio();
    mock.initilize();

    fact.createAction(RRC_L298, "motorA", configA, mock);
    fact.createAction(RRC_L298, "motorB", configB, mock);
    fact.createObserver(RRC_HCSR04, "ultraSonic1", ultraSonic1, mock);
    // fact.createObserver(RRC_HCSR04, "ultraSonic2", ultraSonic2, mock);
    // fact.createObserver(RRC_HCSR04, "ultraSonic3", ultraSonic3, mock);

    std::map<string, int> args = {{"TRIG", 1}};
    std::map<string, long> result = {};
    fact.getObserver("ultraSonic1")->run(args, result, mock);

    // args["TRIG"] = 0;
    // fact.getObserver("ultraSonic2")->run(args, result, mock);
    // fact.getObserver("ultraSonic3")->run(args, result, mock);

     std::map<string, int> actionArgs = {{"IN1", HIGH}, {"IN2", LOW}, {"ENA", 350}, {"IN3", HIGH}, {"IN4", LOW}, {"ENB", 350}};
    fact.getAction("motorA")->run(actionArgs, mock);

    dlog << LINFO << "finish testing";
    return 0;
}