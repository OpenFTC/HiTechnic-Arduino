#include "Arduino.h"
#include "HiTechnicServoController.h"

/*
 * -------------------------------------------------------------------------------
 * Constructor
 * -------------------------------------------------------------------------------
 */
HiTechnicServoController::HiTechnicServoController(DaisyChainPosition pos) : HiTechnicController(pos)
{
    /* Nothing to see here, move along :P */
}

void HiTechnicServoController::setServoPosition(ServoPort port, uint8_t pos)
{
    //Rather than a switch statement, just offset from the base mem addr
    write8(REGISTER_SERVO_1_POS + (int)port, pos);

    commandedPositions[port] = pos;
}

uint8_t HiTechnicServoController::getServoPosition(ServoPort port)
{
    return commandedPositions[port];
}

void HiTechnicServoController::enablePwm(boolean noTimeout)
{
    if(noTimeout)
    {
        write8(REGISTER_ENABLE_PWM, PWM_ENABLED_NTO);
    }
    else
    {
        write8(REGISTER_ENABLE_PWM, PWM_ENABLED);
    }
}

void HiTechnicServoController::disablePwm()
{
     write8(REGISTER_ENABLE_PWM, PWM_DISABLED);
}
