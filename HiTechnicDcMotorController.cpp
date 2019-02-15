#include "Arduino.h"
#include "HiTechnicDcMotorController.h"
#include "Wire.h"
#include "Utils.h"

HiTechnicDcMotorController::HiTechnicDcMotorController(DaisyChainPosition pos) : HiTechnicController(pos)
{
    this->i2cAddr = 0x05;
}

/*
 * Set the power for both motors at the same time;
 * saves bus time over calling setMotorPower() twice,
 * once for each motor
 */
void HiTechnicDcMotorController::setMotorPowers(int8_t power1, int8_t power2)
{
    int8_t data[2] = {power1, power2};
    Utils::writeToI2cRegisters(i2cAddr, REGISTER_MOTOR_1_POWER, data, 2);
   
    /*Wire.beginTransmission(i2cAddr); //We're talking to the guy at i2cAddr
    Wire.write(REGISTER_MOTOR_1_POWER); //We're going to start writing into the memory at the motor 1 power register
    Wire.write(power1); //Write out the first motor power
    Wire.write(power2); //Because the motor power 2 register is right after the motor power 1 register, we can just immediatly write the motor power 2 byte
    Wire.endTransmission(); //Actually send it out over the bus*/
}

/*
 * Set the power for an indiviudal motor
 */
void HiTechnicDcMotorController::setMotorPower(boolean port, int8_t power)
{
    if(!port)
    {
        write8(REGISTER_MOTOR_1_POWER, power);
    }
    else
    {
        Utils::writeToI2cRegister(i2cAddr, REGISTER_MOTOR_2_POWER, power);
    }
    
    /*Wire.beginTransmission(i2cAddr); //We're talking to the guy at i2cAddr

    if(!port) //Port 1
    {
        Wire.write(REGISTER_MOTOR_1_POWER); //We're going to write into the memory at the motor 1 power register
    }
    else      //Port 2
    {
        Wire.write(REGISTER_MOTOR_2_POWER); //We're going to write into the memory at the motor 2 power register
    }
    
    Wire.write(power); //Write out the motor power
    Wire.endTransmission(); //Actually send it out over the bus*/
}

void HiTechnicDcMotorController::setMotorPIDCoeffs(boolean port, uint8_t kP, uint8_t kI, uint8_t kD)
{
    if(!port) //Port 1
    {
        uint8_t pid[] = {kP, kI, kD};
        writeMultiple(REGISTER_MOTOR_1_P_COEFF, pid, 3);
    }
    else //Port 2
    {
        uint8_t pid[] = {kP, kI, kD};
        writeMultiple(REGISTER_MOTOR_2_P_COEFF, pid, 3);
    }
}

void HiTechnicDcMotorController::setMotorPCoeff(boolean port, uint8_t kP)
{
    if(!port) //Port 1
    {
        write8(REGISTER_MOTOR_1_P_COEFF, kP);
    }
    else //Port 2
    {
        write8(REGISTER_MOTOR_2_P_COEFF, kP);
    }
}

void HiTechnicDcMotorController::setMotorICoeff(boolean port, uint8_t kI)
{
    if(!port) //Port 1
    {
        write8(REGISTER_MOTOR_1_I_COEFF, kI);
    }
    else //Port 2
    {
        write8(REGISTER_MOTOR_2_I_COEFF, kI);
    }
}

void HiTechnicDcMotorController::setMotorDCoeff(boolean port, uint8_t kD)
{
    if(!port) //Port 1
    {
        write8(REGISTER_MOTOR_1_D_COEFF, kD);
    }
    else //Port 2
    {
        write8(REGISTER_MOTOR_2_D_COEFF, kD);
    }
}

void HiTechnicDcMotorController::setMotorRunMode(boolean port, RunMode mode)
{
    
}

/*uint16_t HiTechnicDcMotorController::getBatteryVoltage()
{
    Wire.beginTransmission(i2cAddr); //We're talking to the guy at i2cAddr
    Wire.write(REGISTER_BATTERY_VOLTAGE_HIGH_BYTE); //We're going to read from this memory address
    Wire.endTransmission
}*/

