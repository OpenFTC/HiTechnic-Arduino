#include "Arduino.h"
#include "HiTecSC.h"

#ifndef HT_Servo_h
#define HT_Servo_h

class HT_Servo
{
    public:
        HT_Servo(HiTecSC* controller, HiTecSC::ServoPort port);
        void setPosition(uint8_t pos);

    private:
        HiTecSC* controller;
        HiTecSC::ServoPort port;
};

#endif
