/*
 * Copyright (c) 2019 FTC team 4634 FROGbots
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <HiTechnicServo.h>
#include <HiTechnicDcMotorController.h>
#include <HiTechnicController.h>
#include <HiTechnicMotor.h>
#include <HiTechnicServoController.h>
#include <Wire.h>

#define PRESCALAR 4
#define TWI_FREQ 37390L

boolean somethingFound = false;

void setup()
{
    Serial.begin(9600);
    while(!Serial);
    Wire.begin();
    delay(1000);
}

void loop()
{
    Serial.println("\n------------------------------------------");
    Serial.println("Probing I2C bus for HiTechnic controllers...");
    somethingFound = false;
    
    tryMotorController(HiTechnicController::DaisyChainPosition::FIRST);
    tryMotorController(HiTechnicController::DaisyChainPosition::SECOND);
    tryMotorController(HiTechnicController::DaisyChainPosition::THIRD);
    tryMotorController(HiTechnicController::DaisyChainPosition::FOURTH);
    tryMotorController(HiTechnicController::DaisyChainPosition::NONE);

    tryServoController(HiTechnicController::DaisyChainPosition::FIRST);
    tryServoController(HiTechnicController::DaisyChainPosition::SECOND);
    tryServoController(HiTechnicController::DaisyChainPosition::THIRD);
    tryServoController(HiTechnicController::DaisyChainPosition::FOURTH);
    tryServoController(HiTechnicController::DaisyChainPosition::NONE);

    if(!somethingFound)
    {
        Serial.println("--> oof, nothing was found :(\nCheck your wiring and make sure you set the I2C speed to 9600Hz");
    }

    Serial.println("Retrying in 5 seconds");

    delay(5000);
}

void tryMotorController(HiTechnicController::DaisyChainPosition pos)
{
    HiTechnicDcMotorController controller(pos);

    char type[HiTechnicController::NUM_SENSOR_TYPE_CHARS];
    controller.getSensorType(type);
    
    String str(type);

    if(str.equals("MotorCon"))
    {
        Serial.print("--> Motor controller at daisy chain address ");

        if(pos == HiTechnicController::DaisyChainPosition::NONE)
        {
            Serial.println("NONE");
        }
        else
        {
            Serial.println((int)pos);
        }
        
        somethingFound = true;
    }
}

void tryServoController(HiTechnicController::DaisyChainPosition pos)
{
    HiTechnicServoController controller(pos);

    char type[HiTechnicController::NUM_SENSOR_TYPE_CHARS];
    controller.getSensorType(type);
    
    String str(type);

    if(str.equals("ServoCon"))
    {
        Serial.print("--> Servo controller at daisy chain address ");
        
        if(pos == HiTechnicController::DaisyChainPosition::NONE)
        {
            Serial.println("NONE");
        }
        else
        {
            Serial.println((int)pos);
        }

        somethingFound = true;
    }
}
