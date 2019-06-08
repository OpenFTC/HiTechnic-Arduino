/*
 * Copyright (c) 2019 FTC team 4634 FROGbots
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdint.h>
#include "HiTechnicServoController.h"

/*
 * Constructor
 */
HiTechnicServoController::HiTechnicServoController(DaisyChainPosition pos) : HiTechnicController(pos)
{
    /* Nothing to see here, move along :P */
}

//--------------------------------------------------------------------------------
// Position
//--------------------------------------------------------------------------------

/*
 * Set the position for a servo
 */
void HiTechnicServoController::setServoPosition(ServoPort port, uint8_t pos)
{
    //Rather than a switch statement, just offset from the base mem addr
    write8(REGISTER_SERVO_1_POS + (int)port, pos);

    commandedPositions[port] = pos;
}

/*
 * Get the last commanded position of a servo
 */
uint8_t HiTechnicServoController::getServoPosition(ServoPort port)
{
    return commandedPositions[port];
}

//--------------------------------------------------------------------------------
// Enable / disable PWM
//--------------------------------------------------------------------------------

/*
 * Enable the servos
 * Parameter 'noTimeout' enables or disables 10-second no-comms timeout
 */
void HiTechnicServoController::enablePwm(bool noTimeout)
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

/*
 * Disable the servos
 */
void HiTechnicServoController::disablePwm()
{
     write8(REGISTER_ENABLE_PWM, PWM_DISABLED);
}

//--------------------------------------------------------------------------------
// Misc
//--------------------------------------------------------------------------------

/*
 * Sets the step time
 */
void HiTechnicServoController::setStepTime(uint8_t t)
{
    clipSigned8(&t, 0, 15);

    write8(REGISTER_STEP_TIME, t);
}
