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

HiTechnicDcMotorController mc1(HiTechnicController::DAISY_CHAIN_POSITION_SECOND);
HiTechnicMotor someMotor(&mc1, HiTechnicDcMotorController::MotorPort::MOTOR_PORT_1);
HiTechnicMotor someMotor2(&mc1, HiTechnicDcMotorController::MotorPort::MOTOR_PORT_2);

HiTechnicServoController sc1(HiTechnicController::DAISY_CHAIN_POSITION_FIRST);
HiTechnicServo someServo(&sc1, HiTechnicServoController::SERVO_PORT_2);

void setup()
{
    Serial.begin(115200); //set up serial
    while(!Serial);

    Serial.println("\nHello");
    
    Wire.begin(); //join the i2c bus
    
    sc1.enablePwm(false); //enable without disabling the timeout

    someMotor.setRunMode(HiTechnicDcMotorController::RunMode::STOP_AND_RESET_ENCODER);
    someMotor.setRunMode(HiTechnicDcMotorController::RunMode::RUN_WITHOUT_ENCODER);
    someMotor.setZeroPowerBehavior(HiTechnicDcMotorController::ZeroPowerBehavior::BRAKE);
    someMotor.setDirection(HiTechnicMotor::Direction::FORWARD);
    someMotor.setPower(0);
    someMotor.setTargetPosition(4634);
    someMotor.getController()->setTimeoutEnabled(false);
}

void loop()
{
    someMotor.setPower(scale(analogRead(A0), 0, 1023, -1, 1));
    int32_t enc = someMotor.getCurrentPosition();
    Serial.println(enc);

    delay(250);
}

float scale(float n, float x1, float x2, float y1, float y2) {
        double a = (y1 - y2) / (x1 - x2);
        double b = y1 - x1 * (y1 - y2) / (x1 - x2);
        return a * n + b;
}
