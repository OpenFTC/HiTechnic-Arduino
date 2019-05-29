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

#include "HiTechnicMotor.h"
#include "HiTechnicDcMotorController.h"
#include "Arduino.h"

/*
 * -------------------------------------------------------------------------------
 * Constructor
 * -------------------------------------------------------------------------------
 */
HiTechnicMotor::HiTechnicMotor(HiTechnicDcMotorController* controller, HiTechnicDcMotorController::MotorPort port)
{
    this->controller = controller;
    this->port = port;
}

HiTechnicDcMotorController* HiTechnicMotor::getController()
{
    return controller;
}

/*
 * -------------------------------------------------------------------------------
 * Power
 * -------------------------------------------------------------------------------
 */

void HiTechnicMotor::setPower(int8_t power)
{
    if(rev) //reverse
    {
        controller->setMotorPower(port, -power);
    }
    else //forwards
    {
        controller->setMotorPower(port, power);
    }
}

int32_t HiTechnicMotor::getCurrentPosition()
{
    if(rev) //reverse
    {
        return -(controller->getMotorCurrentPosition(port));
    }
    else //forwards
    {
        return controller->getMotorCurrentPosition(port);
    }
}

bool HiTechnicMotor::isBusy()
{
    return controller->isMotorBusy(port);
}

void HiTechnicMotor::setTargetPosition(int32_t tPos)
{
    controller->setMotorTargetPosition(port, tPos);
}

void HiTechnicMotor::setZeroPowerBehavior(HiTechnicDcMotorController::ZeroPowerBehavior b)
{
    controller->setMotorZeroPowerBehavior(port, b);
}

void HiTechnicMotor::setDirection(Direction dir)
{
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
 * -------------------------------------------------------------------------------
 * Mode
 * -------------------------------------------------------------------------------
 */

void HiTechnicMotor::setRunMode(HiTechnicDcMotorController::RunMode mode)
{
    controller->setMotorRunMode(port, mode);
}

/*
 * -------------------------------------------------------------------------------
 * PID Control
 * -------------------------------------------------------------------------------
 */

void HiTechnicMotor::setPidCoeffs(uint8_t kP, uint8_t kI, uint8_t kD)
{
    controller->setMotorPIDCoeffs(port, kP, kI, kD);
}

void HiTechnicMotor::setPCoeff(uint8_t kP)
{
    controller->setMotorPCoeff(port, kP);
}

void HiTechnicMotor::setICoeff(uint8_t kI)
{
    controller->setMotorPCoeff(port, kI);
}

void HiTechnicMotor::setDCoeff(uint8_t kD)
{
    controller->setMotorPCoeff(port, kD);
}
