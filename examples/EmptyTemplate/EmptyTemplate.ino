#include "HiTechnicController.h"
#include "HiTechnicDcMotorController.h"
#include "HiTechnicMotor.h"
#include "HiTechnicServoController.h"
#include "HiTechnicServo.h"
#include "Wire.h"

#define PRESCALAR 4
#define TWI_FREQ 37390L

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
