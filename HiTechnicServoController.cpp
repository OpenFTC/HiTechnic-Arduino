#include "Arduino.h"
#include "HiTechnicServoController.h"
#include "Utils.h"

HiTechnicServoController::HiTechnicServoController(DaisyChainPosition pos) : HiTechnicController(pos)
{
    this->i2cAddr = 0x05;
}

void HiTechnicServoController::setServoPosition(ServoPort port, uint8_t pos)
{
    //Rather than a switch statement, just offset from the base mem addr
    Utils::writeToI2cRegister(i2cAddr, REGISTER_SERVO_POS_BASE + (int)port, pos);
}

void HiTechnicServoController::setPwmEnabled(boolean en)
{
    if(en)
    {
        Utils::writeToI2cRegister(i2cAddr, REGISTER_ENABLE_PWM, PWM_ENABLED);
    }
    else
    {
        Utils::writeToI2cRegister(i2cAddr, REGISTER_ENABLE_PWM, PWM_DISABLED);
    }
}

