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
