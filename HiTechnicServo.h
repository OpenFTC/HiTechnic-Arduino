#include "Arduino.h"
#include "HiTechnicServoController.h"

#ifndef HiTechnicServo_h
#define HiTechnicServo_h

class HiTechnicServo
{
    public:
        HiTechnicServo(HiTechnicServoController* controller, HiTechnicServoController::ServoPort port);
        void setPosition(uint8_t pos);

    private:
        HiTechnicServoController* controller;
        HiTechnicServoController::ServoPort port;
};

#endif
