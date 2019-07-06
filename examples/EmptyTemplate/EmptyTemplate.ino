#include "HiTechnicController.h"
#include "HiTechnicDcMotorController.h"
#include "HiTechnicMotor.h"
#include "HiTechnicServoController.h"
#include "HiTechnicServo.h"
#include "Wire.h"

using DaisyChainPosition = HiTechnicController::DaisyChainPosition;
using MotorPort = HiTechnicDcMotorController::MotorPort;
using RunMode = HiTechnicDcMotorController::RunMode;
using ZeroPowerBehavior = HiTechnicDcMotorController::ZeroPowerBehavior;
using Direction = HiTechnicMotor::Direction;
using ServoPort = HiTechnicServoController::ServoPort;

#define PRESCALAR 4
#define TWI_FREQ 37390L

/*
 * ================================================================
 * Begin user code
 * ================================================================
 */

void setup()
{
    /*
     * Set up serial
     */
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Serial is up");

    /*
     * Enable I2C
     */
    Wire.begin();
}

void loop()
{
    
}
