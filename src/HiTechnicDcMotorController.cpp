#include "Arduino.h"
#include "HiTechnicDcMotorController.h"
#include "Wire.h"

/*
 * -------------------------------------------------------------------------------
 * Constructor
 * -------------------------------------------------------------------------------
 */
HiTechnicDcMotorController::HiTechnicDcMotorController(DaisyChainPosition pos) : HiTechnicController(pos)
{
    /* Nothing to see here, move along :P */
}

/*
 * Set the power for both motors at the same time;
 * saves bus time over calling setMotorPower() twice,
 * once for each motor
 */
void HiTechnicDcMotorController::setMotorPowers(int8_t power1, int8_t power2)
{
    clipSigned8(&power1, MIN_MOTOR_POWER, MAX_MOTOR_POWER);
    clipSigned8(&power2, MIN_MOTOR_POWER, MAX_MOTOR_POWER);

    if((power1 == 0) && !m1Brake) //do we need to float?
    {
        power1 = -128;
    }

    if((power2 == 0) && !m2Brake) //do we need to float?
    {
        power2 = -128;
    }
    
    int8_t data[2] = {power1, power2};
    writeMultiple(REGISTER_MOTOR_1_POWER, data, 2);
}

/*
 * Set the power for an indiviudal motor
 */
void HiTechnicDcMotorController::setMotorPower(MotorPort port, int8_t power)
{
    clipSigned8(&power, MIN_MOTOR_POWER, MAX_MOTOR_POWER);
    
    if(!(int)port) //Port 1
    {
        if((power == 0) && !m1Brake) //do we need to float?
        {
           power = -128;
        }
        
        write8(REGISTER_MOTOR_1_POWER, power);
    }
    else //Port 2
    {
        if((power == 0) && !m2Brake) //do we need to float?
        {
           power = -128;
        }
        
        write8(REGISTER_MOTOR_2_POWER, power);
    }
}

void HiTechnicDcMotorController::setMotorTargetPosition(MotorPort port, int32_t tPos)
{
    if(!(int)port) //Port 1
    {
        writeSigned32(REGISTER_MOTOR_1_TARGET_POSITION_HIGH_BYTE, tPos);
    }
    else //Port 2
    {
        writeSigned32(REGISTER_MOTOR_2_TARGET_POSITION_HIGH_BYTE, tPos);
    }
}

int32_t HiTechnicDcMotorController::getMotorTargetPosition(MotorPort port)
{
    if(!(int)port) //Port 1
    {
        return readSigned32(REGISTER_MOTOR_1_TARGET_POSITION_HIGH_BYTE);
    }
    else //Port 2
    {
        return readSigned32(REGISTER_MOTOR_2_TARGET_POSITION_HIGH_BYTE);
    }
}

boolean HiTechnicDcMotorController::isMotorBusy(MotorPort port)
{
    /*
     * We could actually talk to the hardware, but we replicate what the SDK does
     * Besides, then we don't have to worry about the 50ms issue.
     */
    return abs(getMotorTargetPosition(port) - getMotorCurrentPosition(port)) > BUSY_THRESHOLD;
}

void HiTechnicDcMotorController::setMotorPIDCoeffs(MotorPort port, uint8_t kP, uint8_t kI, uint8_t kD)
{
    if(!(int)port) //Port 1
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

void HiTechnicDcMotorController::setMotorPCoeff(MotorPort port, uint8_t kP)
{
    if(!(int)port) //Port 1
    {
        write8(REGISTER_MOTOR_1_P_COEFF, kP);
    }
    else //Port 2
    {
        write8(REGISTER_MOTOR_2_P_COEFF, kP);
    }
}

void HiTechnicDcMotorController::setMotorICoeff(MotorPort port, uint8_t kI)
{
    if(!(int)port) //Port 1
    {
        write8(REGISTER_MOTOR_1_I_COEFF, kI);
    }
    else //Port 2
    {
        write8(REGISTER_MOTOR_2_I_COEFF, kI);
    }
}

void HiTechnicDcMotorController::setMotorDCoeff(MotorPort port, uint8_t kD)
{
    if(!(int)port) //Port 1
    {
        write8(REGISTER_MOTOR_1_D_COEFF, kD);
    }
    else //Port 2
    {
        write8(REGISTER_MOTOR_2_D_COEFF, kD);
    }
}

void HiTechnicDcMotorController::setMotorRunMode(MotorPort port, RunMode mode)
{
    if(!(int)port) //Port 1
    {
        m1Mode ^= MOTOR_MODE_MASK_SELECTION; //use an XOR to clear the bits
        m1Mode |= (uint8_t)mode; //Now set the bits for the mode the user actually wants
        
        write8(REGISTER_MOTOR_1_MODE, m1Mode);

        //This is what the SDK does but for some reason it doesn't work here
        //while((read8(REGISTER_MOTOR_1_MODE) & (uint8_t)MOTOR_MODE_MASK_SELECTION) != (uint8_t)mode)
        //    ; //Wait for the mode switch to actually happen

        delay(50); //Not sure how else to do this other than just blindly wait :(
    }
    else //Port 2
    {
        m2Mode ^= MOTOR_MODE_MASK_SELECTION; //use an XOR to clear the bits
        m2Mode |= (uint8_t)mode; //Now set the bits for the mode the user actually wants
        
        write8(REGISTER_MOTOR_2_MODE, m2Mode);
        
        //This is what the SDK does but for some reason it doesn't work here
        //while((read8(REGISTER_MOTOR_2_MODE) & (uint8_t)MOTOR_MODE_MASK_SELECTION) != (uint8_t)mode)
        //    ; //Wait for the mode switch to actually happen

        delay(50); //Not sure how else to do this other than just blindly wait :(
    }
}

int32_t HiTechnicDcMotorController::getMotorCurrentPosition(MotorPort port)
{
    if(!(int)port) //Port 1
    {
        return readSigned32(REGISTER_MOTOR_1_ENC_HIGH_BYTE);
    }
    else //Port 2
    {
        return readSigned32(REGISTER_MOTOR_2_ENC_HIGH_BYTE);
    }
}

void HiTechnicDcMotorController::setMotorZeroPowerBehavior(MotorPort port, ZeroPowerBehavior b)
{
    if(!(int)port) //Port 1
    {
        m1Brake = (int)b;
    }
    else //Port 2
    {
        m2Brake = (int)b;
    }
}

uint16_t HiTechnicDcMotorController::getBatteryVoltage()
{
    uint16_t voltage = 0;

    uint8_t bytes[2];

    readMultiple(REGISTER_BATTERY_VOLTAGE_HIGH_BYTE, 2, bytes);

    voltage |= bytes[0] << 2;
    voltage |= bytes[1];
    
    return voltage*20;
}

float HiTechnicDcMotorController::getBatteryVoltageFloat()
{
    return getBatteryVoltage() / 1000.0;
}
