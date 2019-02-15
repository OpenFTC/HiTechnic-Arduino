#include "Arduino.h"
#include "HiTechnicController.h"

#ifndef HiTechnicServoController_h
#define HiTechnicServoController_h

#define REGISTER_SERVO_POS_BASE 0x41
#define REGISTER_SERVO_1_POS 0x42
#define REGISTER_SERVO_2_POS 0x43
#define REGISTER_SERVO_3_POS 0x44
#define REGISTER_SERVO_4_POS 0x45
#define REGISTER_SERVO_5_POS 0x46
#define REGISTER_SERVO_6_POS 0x47
#define REGISTER_ENABLE_PWM 0x48
#define PWM_DISABLED 255
#define PWM_ENABLED 0

class HiTechnicServoController : public HiTechnicController
{
    public:
        HiTechnicServoController(DaisyChainPosition pos);
        enum class ServoPort {SERVO_PORT_1 = 1, SERVO_PORT_2, SERVO_PORT_3, SERVO_PORT_4, SERVO_PORT_5, SERVO_PORT_6};
        void setServoPosition(ServoPort port, uint8_t pos);
        void setPwmEnabled(boolean en);

    private:
       // uint8_t i2cAddr = 0;
};

#endif
