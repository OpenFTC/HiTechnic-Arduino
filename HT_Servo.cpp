#include "Arduino.h"
#include "HT_Servo.h"
#include "HiTecSC.h"

HT_Servo::HT_Servo(HiTecSC* controller, uint8_t port)
{
    this->controller = controller;
    this->port = port;
}

void HT_Servo::setPosition(uint8_t pos)
{
    controller->setServoPosition(port, pos);
}

