#include "Arduino.h"
#include "HiTechnicController.h"

#ifndef HiTechnicServoController_h
#define HiTechnicServoController_h

class HiTechnicServoController : public HiTechnicController
{
    public:
        HiTechnicServoController(DaisyChainPosition pos);
        enum ServoPort {SERVO_PORT_1 = 0, SERVO_PORT_2, SERVO_PORT_3, SERVO_PORT_4, SERVO_PORT_5, SERVO_PORT_6};
        void setServoPosition(ServoPort port, uint8_t pos);
        void enablePwm(boolean noTimeout);
        void disablePwm();
        void setStepTime(uint8_t t);
        uint8_t getServoPosition(ServoPort port);

    private:
        uint8_t commandedPositions[6] = {0,0,0,0,0,0};

        static const uint8_t REGISTER_SERVO_1_POS = 0x42; //servo 6 reg -> 0x47
        static const uint8_t REGISTER_ENABLE_PWM = 0x48;
        static const uint8_t REGISTER_STEP_TIME = 0x41;
        static const uint8_t PWM_DISABLED = 255;
        static const uint8_t PWM_ENABLED = 0;
        static const uint8_t PWM_ENABLED_NTO = 0xAA;
};

#endif
