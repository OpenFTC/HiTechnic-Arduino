#include "HiTechnicMotor.h"
#include "HiTechnicDcMotorController.h"
#include "Arduino.h"

/*
 * -------------------------------------------------------------------------------
 * Constructor
 * -------------------------------------------------------------------------------
 */

HiTechnicMotor::HiTechnicMotor(HiTechnicDcMotorController* controller, boolean port)
{
    this->controller = controller;
    this->port = port;
}

void HiTechnicMotor::setPower(int8_t power)
{
    controller->setMotorPower(port, power);
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

