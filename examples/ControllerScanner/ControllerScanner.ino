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
    
    tryMotorController(DaisyChainPosition::FIRST);
    tryMotorController(DaisyChainPosition::SECOND);
    tryMotorController(DaisyChainPosition::THIRD);
    tryMotorController(DaisyChainPosition::FOURTH);
    tryMotorController(DaisyChainPosition::NONE);

    tryServoController(DaisyChainPosition::FIRST);
    tryServoController(DaisyChainPosition::SECOND);
    tryServoController(DaisyChainPosition::THIRD);
    tryServoController(DaisyChainPosition::FOURTH);
    tryServoController(DaisyChainPosition::NONE);

    if(!somethingFound)
    {
        Serial.println("--> oof, nothing was found :(\nCheck your wiring and make sure you set the I2C speed to 9600Hz");
    }

    Serial.println("Retrying in 5 seconds");

    delay(5000);
}

void tryMotorController(DaisyChainPosition pos)
{
    HiTechnicDcMotorController controller(pos);

    char type[HiTechnicController::NUM_SENSOR_TYPE_CHARS];
    controller.getSensorType(type);
    
    String str(type);

    if(str.equals("MotorCon"))
    {
        Serial.print("--> Motor controller at daisy chain address ");

        if(pos == DaisyChainPosition::NONE)
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

void tryServoController(DaisyChainPosition pos)
{
    HiTechnicServoController controller(pos);

    char type[HiTechnicController::NUM_SENSOR_TYPE_CHARS];
    controller.getSensorType(type);
    
    String str(type);

    if(str.equals("ServoCon"))
    {
        Serial.print("--> Servo controller at daisy chain address ");
        
        if(pos == DaisyChainPosition::NONE)
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
