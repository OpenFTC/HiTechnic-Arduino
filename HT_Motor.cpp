#include "HT_Motor.h"
#include "HiTecMC.h"
#include "Arduino.h"

/*
 * -------------------------------------------------------------------------------
 * Constructor
 * -------------------------------------------------------------------------------
 */

HT_Motor::HT_Motor(HiTecMC* controller, boolean port)
{
    this->controller = controller;
    this->port = port;
}

void HT_Motor::setPower(int8_t power)
{
    controller->setMotorPower(port, power);
}

/*
 * -------------------------------------------------------------------------------
 * Mode
 * -------------------------------------------------------------------------------
 */

void HT_Motor::setRunMode(HiTecMC::RunMode mode)
{
    controller->setMotorRunMode(port, mode);
}

/*
 * -------------------------------------------------------------------------------
 * PID Control
 * -------------------------------------------------------------------------------
 */

void HT_Motor::setPidCoeffs(uint8_t kP, uint8_t kI, uint8_t kD)
{
    controller->setMotorPIDCoeffs(port, kP, kI, kD);
}

void HT_Motor::setPCoeff(uint8_t kP)
{
    controller->setMotorPCoeff(port, kP);
}

void HT_Motor::setICoeff(uint8_t kI)
{
    controller->setMotorPCoeff(port, kI);
}

void HT_Motor::setDCoeff(uint8_t kD)
{
    controller->setMotorPCoeff(port, kD);
}

