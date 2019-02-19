#include "Arduino.h"
#include "HiTechnicServo.h"
#include "HiTechnicServoController.h"

/*
 * -------------------------------------------------------------------------------
 * Constructor
 * -------------------------------------------------------------------------------
 */
HiTechnicServo::HiTechnicServo(HiTechnicServoController* controller, HiTechnicServoController::ServoPort port)
{
    this->controller = controller;
    this->port = port;
}

/*
 * -------------------------------------------------------------------------------
 * Position
 * -------------------------------------------------------------------------------
 */

void HiTechnicServo::setPosition(uint8_t pos)
{
    controller->setServoPosition(port, pos);
}

