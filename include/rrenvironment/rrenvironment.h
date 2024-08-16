#ifndef RRENVIRONMENT_H
#define RRENVIRONMENT_H

#include <stdint.h>
#include <string>

/*************************************************************
 * Values used to predict how to perform some sort of action.
 *************************************************************/
#define RR_IO_ULTRA_SONIC 0x01  /* ultra sonic */
#define RR_IO_ACCEL       0x02  /* acelometer  */
#define RR_IO_GYRO        0x03  /* Gyroscrope */
#define RR_IO_CAMERA      0x04  /* Camera input */
#define RR_IO_MOTORS      0x05  /* Motors */
#define RR_IO_MOTOR_ACT   0x06  /* Motor Actuator */
#define RR_IO_BATTERY     0x07  /* Get battery health */

namespace rrenv {
    class rr_io {
        public:
        uint8_t _io;    // IO Function (observer or action) that has produced the current result

        // result,  or requested action. For actions such as RIO_IO_MOTORS this will be the 
        // be the requested action, when recieved back from the fat controller this may vary
        // as the fat controller will perform its own actions.
        std::map<std::string, float> _tx_rx;  
    };

    class rr_result {
        public:
        int   _reward; // this can be a negative value, indicating a penalty
        rr_io _state;  // last known state
        
        // List of all states (observations and actions) that have lead
        // to the current state.
        std::list<rr_io> _episode; 
                    
    };

    // Interface into the fat controller algoritm. 
    class RrEnvironment {
    public:
        // Send a action or list of actions,  and recieve response from fat controller
        std::list<rr_result> send_and_recieve(std::list<rr_io> actions);
    };
}
#endif
