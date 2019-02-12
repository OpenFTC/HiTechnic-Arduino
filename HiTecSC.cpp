#include "Arduino.h"
#include "HiTecSC.h"
#include "Utils.h"

HiTecSC::HiTecSC(DaisyChainPosition pos) : HT_Controller(pos)
{
    this->i2cAddr = 0x05;
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

