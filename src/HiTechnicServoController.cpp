#include "Arduino.h"
#include "HiTechnicServoController.h"

HiTechnicServoController::HiTechnicServoController(DaisyChainPosition pos) : HiTechnicController(pos)
{

}

void HiTechnicServoController::setServoPosition(ServoPort port, uint8_t pos)
{
    //Rather than a switch statement, just offset from the base mem addr
    write8(REGISTER_SERVO_POS_BASE + (int)port, pos);
}

void HiTechnicServoController::setPwmEnabled(boolean en)
{
    if(en)
    {
        write8(REGISTER_ENABLE_PWM, PWM_ENABLED);
    }
    else
    {
        write8(REGISTER_ENABLE_PWM, PWM_DISABLED);
    }
}

