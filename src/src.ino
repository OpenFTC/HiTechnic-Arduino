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

#define PRESCALAR 4
#define TWI_FREQ 37390L

HiTechnicDcMotorController mc1(HiTechnicController::DaisyChainPosition::SECOND);
HiTechnicMotor someMotor(&mc1, HiTechnicDcMotorController::MotorPort::PORT_1);
HiTechnicMotor someMotor2(&mc1, HiTechnicDcMotorController::MotorPort::PORT_2);

HiTechnicServoController sc1(HiTechnicController::DaisyChainPosition::FIRST);
HiTechnicServo someServo(&sc1, HiTechnicServoController::ServoPort::PORT_2);

void setup()
{
    Serial.begin(9600); //set up serial
    while(!Serial);

    Serial.println("\nHello");
    
    Wire.begin(); //join the i2c bus
    
    sc1.enablePwm(false); //enable without disabling the timeout

    someMotor.setRunMode(HiTechnicDcMotorController::RunMode::STOP_AND_RESET_ENCODER);
    someMotor.setZeroPowerBehavior(HiTechnicDcMotorController::ZeroPowerBehavior::FLOAT);
    someMotor.setDirection(HiTechnicMotor::Direction::FORWARD);
    someMotor.setPower(0);
    someMotor.getController()->setTimeoutEnabled(true);

    delay(1000);
}

void loop()
{
    someMotor.setRunMode(HiTechnicDcMotorController::RunMode::RUN_WITHOUT_ENCODER);
    delay(500);

    Serial.println("Open loop");
  
    for(float f = 0; f < 1; f += 0.01)
    {
        //Serial.println(f);
        someMotor.setPower(f);
        dataLog();
        delay(50);
    }

    //----------------------------------------------------------------------------

    someMotor.setPower(0);
    delay(1000);
    someMotor.setRunMode(HiTechnicDcMotorController::RunMode::RUN_USING_ENCODER);

    Serial.println("Closed loop");
  
    for(float f = 0; f < 1; f += 0.01)
    {
        //Serial.println(f);
        someMotor.setPower(f*.76);
        dataLog();
        delay(50);
    }

    while(1);
}

void dataLog()
{
    int32_t enc = someMotor.getCurrentPosition();
    delay(50);
    int32_t enc2 = someMotor.getCurrentPosition();

    int32_t denc = enc2-enc;

    int32_t cps = denc * (1000 / 50);

    int32_t cpm = cps * 60;

    int32_t rpm = cpm / 538;

    Serial.print(-400);  // To freeze the lower limit
    Serial.print(" ");
    Serial.print(400);  // To freeze the upper limit
    Serial.print(" ");
    Serial.println(rpm);
}

float scale(float n, float x1, float x2, float y1, float y2) {
        double a = (y1 - y2) / (x1 - x2);
        double b = y1 - x1 * (y1 - y2) / (x1 - x2);
        return a * n + b;
}
