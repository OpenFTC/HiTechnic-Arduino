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
