#include "HiTechnicDcMotorController.h"
#include "HiTechnicMotor.h"
#include "HiTechnicServoController.h"
#include "HiTechnicServo.h"
#include "Wire.h"

#define PRESCALAR 4
#define TWI_FREQ 37390L

HiTechnicDcMotorController mc1(HiTechnicController::DAISY_CHAIN_POSITION_FIRST);
HiTechnicMotor someMotor(&mc1, 0);

HiTechnicServoController sc1(HiTechnicController::DAISY_CHAIN_POSITION_SECOND);
HiTechnicServo someServo(&sc1, HiTechnicServoController::SERVO_PORT_1);

void setup()
{
    Serial.begin(9600); //set up serial
    while(!Serial);
    
    Wire.begin(); //join the i2c bus
    
    sc1.setPwmEnabled(true);
    mc1.setMotorRunMode(1, HiTechnicDcMotorController::RunMode::STOP_AND_RESET_ENCODER);
}

void loop()
{
    someMotor.setPower(20);
    someServo.setPosition(100);
    delay(500);
    someServo.setPosition(102);
    someMotor.setPower(30);
    delay(500);
}

