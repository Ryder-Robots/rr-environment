#include <dlib/logger.h>
#include <rrenvironment/wiring.hpp>

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

int main() {
    return 0;
}