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
#include "HiTechnicMotor.h"
#include "HiTechnicDcMotorController.h"

/*
 * Constructor
 */
HiTechnicMotor::HiTechnicMotor(HiTechnicDcMotorController* controller, HiTechnicDcMotorController::MotorPort port)
{
    this->controller = controller;
    this->port = port;
}

//--------------------------------------------------------------------------------
// Power
//--------------------------------------------------------------------------------

/*
 * Set the power for this motor
 */
void HiTechnicMotor::setPower(float power)
{
    /*
     * NB: We handle the direction in software,
     * just like the SDK does
     */
  
    if(rev) //reverse
    {
        controller->setMotorPower(port, -power);
    }
    else //forwards
    {
        controller->setMotorPower(port, power);
    }
}

/*
 * Get the current power of this motor
 */
float HiTechnicMotor::getPower()
{
    return controller->getMotorPower(port);
}

//--------------------------------------------------------------------------------
// Encoder
//--------------------------------------------------------------------------------

/*
 * Get the encoder value of this motor
 */
int32_t HiTechnicMotor::getCurrentPosition()
{
    /*
     * NB: We handle the direction in software,
     * just like the SDK does
     */
  
    if(rev) //reverse
    {
        return -(controller->getMotorCurrentPosition(port));
    }
    else //forwards
    {
        return controller->getMotorCurrentPosition(port);
    }
}

//--------------------------------------------------------------------------------
// Modes and behaviors
//--------------------------------------------------------------------------------

/*
 * Set the run mode of this motor
 */
void HiTechnicMotor::setMode(HiTechnicDcMotorController::RunMode mode)
{
    controller->setMotorMode(port, mode);
}

/*
 * Get the current run mode of this motor
 */
HiTechnicDcMotorController::RunMode HiTechnicMotor::getMode()
{
    return controller->getMotorMode(port);
}

/*
 * Set the zero power behavior of this motor
 */
void HiTechnicMotor::setZeroPowerBehavior(HiTechnicDcMotorController::ZeroPowerBehavior b)
{
    controller->setMotorZeroPowerBehavior(port, b);
}

/*
 * Get the current zero power behavior of this motor
 */
HiTechnicDcMotorController::ZeroPowerBehavior HiTechnicMotor::getZeroPowerBehavior()
{
    return controller->getMotorZeroPowerBehavior(port);
}

/*
 * Set the direction of this motor
 */
void HiTechnicMotor::setDirection(Direction dir)
{
    /*
     * NB: We handle the direction in software,
     * just like the SDK does
     */
  
    if((int)dir) //reverse
    {
        rev = true;
    }
    else //forwards
    {
        rev = false;
    }
}

/*
 * Get the current direction of this motor
 */
HiTechnicMotor::Direction HiTechnicMotor::getDirection()
{
    /*
     * NB: We handle the direction in software,
     * just like the SDK does
     */
    return (Direction)rev;
}

//--------------------------------------------------------------------------------
// Functions related to RTP mode
//-------------------------------------------------------------------------------

/*
 * Set the encoder value this motor will target in RTP mode
 */
void HiTechnicMotor::setTargetPosition(int32_t tPos)
{
    controller->setMotorTargetPosition(port, tPos);
}

/*
 * Get the encoder value this motor will target in RTP mode
 */
int32_t HiTechnicMotor::getTargetPosition()
{
    return controller->getMotorTargetPosition(port);
}

/*
 * Find out whether a motor is NOT yet at its target position
 */
bool HiTechnicMotor::isBusy()
{
    return controller->isMotorBusy(port);
}

//--------------------------------------------------------------------------------
// PID params for closed-loop modes
//--------------------------------------------------------------------------------

/*
 * Set the PID coefficients for this motor
 */
void HiTechnicMotor::setPIDCoeffs(uint8_t kP, uint8_t kI, uint8_t kD)
{
    controller->setMotorPIDCoeffs(port, kP, kI, kD);
}

/*
 * Get the current PID coefficients for this motor
 */
void HiTechnicMotor::getPIDCoeffs(uint8_t* out)
{
    controller->getMotorPIDCoeffs(port, out);
}

//--------------------------------------------------------------------------------
// Misc.
//--------------------------------------------------------------------------------

/*
 * Get a pointer to the controller this motor is attached to
 */
HiTechnicDcMotorController* HiTechnicMotor::getController()
{
    return controller;
}
