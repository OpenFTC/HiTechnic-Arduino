#include "HiTechnicDcMotorController.h"
#include "HiTechnicMotor.h"
#include "HiTechnicServoController.h"
#include "HiTechnicServo.h"
#include "Wire.h"

#define PRESCALAR 4
#define TWI_FREQ 37390L

HiTechnicDcMotorController* mc1 = new HiTechnicDcMotorController(HiTechnicController::DAISY_CHAIN_POSITION_FIRST);
HiTechnicMotor* someMotor = new HiTechnicMotor(mc1, 0);

HiTechnicServoController* sc1 = new HiTechnicServoController(HiTechnicController::DAISY_CHAIN_POSITION_SECOND);
HiTechnicServo* someServo = new HiTechnicServo(sc1, HiTechnicServoController::SERVO_PORT_1);

void setup()
{
    Serial.begin(9600);
    while(!Serial);
    Wire.begin();
    sc1->setPwmEnabled(true);
    mc1->setMotorRunMode(true, HiTechnicDcMotorController::RunMode::STOP_AND_RESET_ENCODER);
}

void loop()
{
    someMotor->setPower(20);
    someServo->setPosition(100);
    delay(500);
    someServo->setPosition(102);
    someMotor->setPower(30);
    delay(500);
    
    /*someMotor->setPCoeff(230);
    
    char data[NUM_MFR_BYTES+1]; //We need to +1 to account for the null char
    mc1->getManufacturer(data);
    Serial.print("MFR: ");
    Serial.println(data);

    char data1[NUM_SENSOR_TYPE_BYTES+1]; //We need to +1 to account for the null char
    mc1->getSensorType(data1);
    Serial.print("TYP: ");
    Serial.println(data1);
    delay(500);*/
    
    /*for(int i = -127; i < 128; i++)
    {
        if(i == 0)
        {
            delay(1000);
        }
        someMotor->setPower(i);
        delay(10);
    }

    for(int i = 127; i > -128; i--)
    {
        if(i == 0)
        {
            delay(1000);
        }
        someMotor->setPower(i);
        delay(10);
    }*/
}

