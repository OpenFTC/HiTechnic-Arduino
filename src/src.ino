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
    someMotor2.setRunMode(HiTechnicDcMotorController::RunMode::RUN_TO_POSITION);
    someMotor2.setTargetPosition(2000);
    someMotor2.setDirection(HiTechnicMotor::Direction::FORWARD);
}

void loop()
{
    //Serial.print("Voltage: ");
    //Serial.println(mc1.getBatteryVoltageFloat());

    someMotor2.setPower(5);

    Serial.print("Enc1: ");
    Serial.println(someMotor2.getCurrentPosition());
    Serial.print("Busy: ");
    Serial.println(someMotor2.isBusy());
    delay(250);
}
