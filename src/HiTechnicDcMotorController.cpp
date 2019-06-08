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

#include <stdint.h>
#include "HiTechnicDcMotorController.h"

/*
 * Constructor
 */
HiTechnicDcMotorController::HiTechnicDcMotorController(DaisyChainPosition pos) : HiTechnicController(pos)
{
    /* Nothing to see here, move along :P */
}

//--------------------------------------------------------------------------------
// Functions for getting/setting motor power
//--------------------------------------------------------------------------------

/*
 * Set the power for both motors at the same time;
 * saves bus time over calling setMotorPower() twice,
 * once for each motor
 */
void HiTechnicDcMotorController::setMotorPowers(int8_t power1, int8_t power2)
{
    clipSigned8(&power1, MOTOR_POWER_MIN, MOTOR_POWER_MAX);
    clipSigned8(&power2, MOTOR_POWER_MIN, MOTOR_POWER_MAX);

    if((power1 == 0) && !m1Brake) //do we need to float?
    {
        power1 = MOTOR_POWER_FLOAT;
    }

    if((power2 == 0) && !m2Brake) //do we need to float?
    {
        power2 = MOTOR_POWER_FLOAT;
    }
    
    int8_t data[2] = {power1, power2};
    writeMultiple(REGISTER_MOTOR_1_POWER, data, 2);
}

/*
 * Set the power for a motor
 */
void HiTechnicDcMotorController::setMotorPower(MotorPort port, int8_t power)
{
    clipSigned8(&power, MOTOR_POWER_MIN, MOTOR_POWER_MAX);
    
    if(!(int)port) //Port 1
    {
        if((power == 0) && !m1Brake) //do we need to float?
        {
           power = MOTOR_POWER_FLOAT;
        }
        
        write8(REGISTER_MOTOR_1_POWER, power);
    }
    else //Port 2
    {
        if((power == 0) && !m2Brake) //do we need to float?
        {
           power = MOTOR_POWER_FLOAT;
        }
        
        write8(REGISTER_MOTOR_2_POWER, power);
    }
}

//--------------------------------------------------------------------------------
// Encoder
//--------------------------------------------------------------------------------

int32_t HiTechnicDcMotorController::getMotorCurrentPosition(MotorPort port)
{
    if(!(int)port) //Port 1
    {
        return read32(REGISTER_MOTOR_1_ENC_HIGH_BYTE);
    }
    else //Port 2
    {
        return read32(REGISTER_MOTOR_2_ENC_HIGH_BYTE);
    }
}

//--------------------------------------------------------------------------------
// Modes and behaviors
//--------------------------------------------------------------------------------

/*
 * Set the run mode for a motor
 */
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

        //We don't use Arduino's delay() function directly so as to be more portable
        sleep(50); //Not sure how else to do this other than just blindly wait :(
    }
    else //Port 2
    {
        m2Mode ^= MOTOR_MODE_MASK_SELECTION; //use an XOR to clear the bits
        m2Mode |= (uint8_t)mode; //Now set the bits for the mode the user actually wants
        
        write8(REGISTER_MOTOR_2_MODE, m2Mode);
        
        //This is what the SDK does but for some reason it doesn't work here
        //while((read8(REGISTER_MOTOR_2_MODE) & (uint8_t)MOTOR_MODE_MASK_SELECTION) != (uint8_t)mode)
        //    ; //Wait for the mode switch to actually happen

        //We don't use Arduino's delay() function directly so as to be more portable
        sleep(50); //Not sure how else to do this other than just blindly wait :(
    }
}

/*
 * Set the zero power behavior for a motor
 */
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

/*
 * Set whether the controller's internal 2500ms no-comms timeout should be activated
 */
void HiTechnicDcMotorController::setTimeoutEnabled(bool enableTimeout)
{
    /*
     * The spec says we need to set the NTO bit on both of the motor
     * mode registers. *shrug*
     */
  
    if(!enableTimeout)
    {
        m1Mode |= NTO_BIT;
        m2Mode |= NTO_BIT;
    }
    else
    {
        m1Mode ^= NTO_BIT;
        m2Mode ^= NTO_BIT;
    }

    /*
     * The mode registers for motors 1 and 2 are not contiguous, so
     * we cannot simply do a 2-byte write at the register for motor 1
     */
    write8(REGISTER_MOTOR_1_MODE, m1Mode);
    write8(REGISTER_MOTOR_2_MODE, m2Mode);
}

//--------------------------------------------------------------------------------
// Functions related to RTP mode
//--------------------------------------------------------------------------------

/*
 * Set the encoder value a motor should target in RTP mode
 */
void HiTechnicDcMotorController::setMotorTargetPosition(MotorPort port, int32_t tPos)
{ 
    if(!(int)port) //Port 1
    {
        write32(REGISTER_MOTOR_1_TARGET_POSITION_HIGH_BYTE, tPos);
    }
    else //Port 2
    {
        write32(REGISTER_MOTOR_2_TARGET_POSITION_HIGH_BYTE, tPos);
    }
}

/*
 * Get the encoder value a motor will target in RTP mode
 */
int32_t HiTechnicDcMotorController::getMotorTargetPosition(MotorPort port)
{
    if(!(int)port) //Port 1
    {
        return read32(REGISTER_MOTOR_1_TARGET_POSITION_HIGH_BYTE);
    }
    else //Port 2
    {
        return read32(REGISTER_MOTOR_2_TARGET_POSITION_HIGH_BYTE);
    }
}

/*
 * Find out whether a motor is NOT yet at its target position
 */
bool HiTechnicDcMotorController::isMotorBusy(MotorPort port)
{
    /*
     * We could actually talk to the hardware, but we replicate what the SDK does
     * Besides, then we don't have to worry about the 50ms issue.
     */
    int32_t err = getMotorTargetPosition(port) - getMotorCurrentPosition(port);

    /*
     * We don't use Arduino's built-in abs() function so as to be more portable
     * to other platforms
     */
    if(err < 0)
    {
        err = -err;
    }
     
    return err > BUSY_THRESHOLD;
}

//--------------------------------------------------------------------------------
// Functions for setting PID params
//--------------------------------------------------------------------------------

/*
 * Set the PID coefficients for a motor
 */
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

/*
 * Set only the P coefficient for a motor
 */
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

/*
 * Set only the I coefficient for a motor
 */
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

/*
 * Set only the D coefficient for a motor
 */
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

//--------------------------------------------------------------------------------
// Battery voltage
//--------------------------------------------------------------------------------

/*
 * Get the battery voltage in millivolts
 */
uint16_t HiTechnicDcMotorController::getBatteryVoltage()
{
    uint16_t voltage = 0;

    uint8_t bytes[2];

    readMultiple(REGISTER_BATTERY_VOLTAGE_HIGH_BYTE, 2, bytes);

    voltage |= bytes[0] << 2;
    voltage |= bytes[1];
    
    return voltage*20;
}

/*
 * Get the battery voltage as a floating-point value in volts
 */
float HiTechnicDcMotorController::getBatteryVoltageFloat()
{
    return getBatteryVoltage() / 1000.0;
}
