#include "Arduino.h"
#include "HiTecSC.h"
#include "Utils.h"

HiTecSC::HiTecSC(uint8_t i2cAddr) : HT_Controller(i2cAddr)
{
    this->i2cAddr = i2cAddr;
}

void HiTecSC::setServoPosition(uint8_t port, uint8_t pos)
{
    if(port < 1 || port > 6)
    {
        return; //invalid
    }

    //Rather than a switch statement, just offset from the base mem addr
    Utils::writeToI2cRegister(i2cAddr, REGISTER_SERVO_POS_BASE + port, pos);
}

void HiTecSC::setPwmEnabled(boolean en)
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

