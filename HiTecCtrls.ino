#include "HiTecMC.h"
#include "HT_Motor.h"
#include "HiTecSC.h"
#include "HT_Servo.h"
#include "Wire.h"
#include "Utils.h"

#define PRESCALAR 4
#define TWI_FREQ 37390L

HiTecMC* mc1 = new HiTecMC(HT_Controller::DaisyChainPosition::FIRST);
HT_Motor* someMotor = new HT_Motor(mc1, 0);

HiTecSC* sc1 = new HiTecSC(HT_Controller::DaisyChainPosition::SECOND);
HT_Servo* someServo = new HT_Servo(sc1, HiTecSC::ServoPort::SERVO_PORT_1);

void setup()
{
    Serial.begin(9600);
    while(!Serial);
    Wire.begin();
    sc1->setPwmEnabled(true);
    mc1->setMotorRunMode(true, HiTecMC::RunMode::STOP_AND_RESET_ENCODER);
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

