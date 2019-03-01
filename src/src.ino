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
HiTechnicServo someServo(&sc1, HiTechnicServoController::SERVO_PORT_1);

void setup()
{
    Serial.begin(9600); //set up serial
    while(!Serial);

    Serial.println("\nHello");
    
    Wire.begin(); //join the i2c bus
    
    sc1.enablePwm(false); //enable without disabling the timeout

    someMotor2.setRunMode(HiTechnicDcMotorController::RunMode::STOP_AND_RESET_ENCODER);
    someMotor2.setRunMode(HiTechnicDcMotorController::RunMode::RUN_USING_ENCODER);
    someMotor2.setDirection(HiTechnicMotor::Direction::FORWARD);
    someMotor2.setPower(20);
    someMotor2.getController()->setTimeoutEnabled(false);
}

void loop()
{
    //Serial.print("Voltage: ");
    //Serial.println(mc1.getBatteryVoltageFloat());

    //someMotor2.setPower(5);

    /*Serial.print("Enc1: ");
    Serial.println(someMotor2.getCurrentPosition());
    Serial.print("Busy: ");
    Serial.println(someMotor2.isBusy());*/
    delay(250);
}
