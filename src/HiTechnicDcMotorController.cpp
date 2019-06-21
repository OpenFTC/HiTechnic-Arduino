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
// Power
//--------------------------------------------------------------------------------

/*
 * Set the power for a motor
 */
void HiTechnicDcMotorController::setMotorPower(MotorPort port, float power)
{
    clipFloat(&power, API_MOTOR_POWER_MIN, API_MOTOR_POWER_MAX);

    /*
     * Convert from floating point -1 to 1
     * to integer -100 to 100
     */
    int8_t scaledPower = power * 100.0;
    
    if(!(int)port) //Port 1
    {
        if((scaledPower == 0) && !m1Brake) //do we need to float?
        {
           scaledPower = MOTOR_POWER_FLOAT;
        }
        
        write8(REGISTER_MOTOR_1_POWER, scaledPower);
    }
    else //Port 2
    {
        if((scaledPower == 0) && !m2Brake) //do we need to float?
        {
           scaledPower = MOTOR_POWER_FLOAT;
        }
        
        write8(REGISTER_MOTOR_2_POWER, scaledPower);
    }
}

/*
 * Get the current power of a motor
 */
float HiTechnicDcMotorController::getMotorPower(MotorPort port)
{
    int8_t pow;
  
    if(!(int)port) //Port 1
    {
        pow = read8(REGISTER_MOTOR_1_POWER);
    }
    else //Port 2
    {
        pow = read8(REGISTER_MOTOR_2_POWER);
    }

    /*
     * Convert from integer -100 to 100 
     * to floating point -1 to 1
     */
    return pow / 100.0;
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
void HiTechnicDcMotorController::setMotorMode(MotorPort port, RunMode mode)
{
    if(!(int)port) //Port 1
    {
        m1Mode &= ~MOTOR_MODE_MASK_SELECTION; //use an AND with an inverted mask to clear the bits
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
        m2Mode &= ~MOTOR_MODE_MASK_SELECTION; //use an AND with an inverted mask to clear the bits
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
 * Get the current run mode of a motor
 */
HiTechnicDcMotorController::RunMode HiTechnicDcMotorController::getMotorMode(MotorPort port)
{
    uint8_t rawMode;
  
    if(!(int)port) //Port 1
    {
        rawMode = read8(REGISTER_MOTOR_1_MODE);
    }
    else //Port 2
    {
        rawMode = read8(REGISTER_MOTOR_2_MODE);
    }

    rawMode &= MOTOR_MODE_MASK_SELECTION; //Clear the bits we don't care about

    return (RunMode)rawMode;
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
 * Get the current zero power behavior of a motor
 */
HiTechnicDcMotorController::ZeroPowerBehavior HiTechnicDcMotorController::getMotorZeroPowerBehavior(MotorPort port)
{    
    if(!(int)port) //Port 1
    {
        return (ZeroPowerBehavior)m1Brake;
    }
    else //Port 2
    {
        return (ZeroPowerBehavior)m2Brake;
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
        //Set the bits
        m1Mode |= NTO_BIT;
        m2Mode |= NTO_BIT;
    }
    else
    {
        //Use an AND with an inverted mask to clear the bits
        m1Mode &= ~NTO_BIT;
        m2Mode &= ~NTO_BIT;
    }

    /*
     * The mode registers for motors 1 and 2 are not contiguous, so
     * we cannot simply do a 2-byte write at the register for motor 1
     */
    write8(REGISTER_MOTOR_1_MODE, m1Mode);
    write8(REGISTER_MOTOR_2_MODE, m2Mode);
}

/*
 * Reset the controller to a fresh power-up state,
 * except for the encoders which are not reset in
 * order to mirror the behavior of the SDK
 */
void HiTechnicDcMotorController::reset()
{
    setTimeoutEnabled(true);

    setMotorPower(MotorPort::PORT_1, 0);
    setMotorPower(MotorPort::PORT_2, 0);
    
    setMotorMode(MotorPort::PORT_1, RunMode::RUN_WITHOUT_ENCODER);
    setMotorMode(MotorPort::PORT_2, RunMode::RUN_WITHOUT_ENCODER);
    
    setMotorPIDCoeffs(MotorPort::PORT_1, DEFAULT_P_COEFF, DEFAULT_I_COEFF, DEFAULT_D_COEFF);
    setMotorPIDCoeffs(MotorPort::PORT_2, DEFAULT_P_COEFF, DEFAULT_I_COEFF, DEFAULT_D_COEFF);

    setMotorTargetPosition(MotorPort::PORT_1, 0);
    setMotorTargetPosition(MotorPort::PORT_2, 0);
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
// PID params for closed-loop modes
//--------------------------------------------------------------------------------

/*
 * Set the PID coefficients for a motor
 */
void HiTechnicDcMotorController::setMotorPIDCoeffs(MotorPort port, uint8_t kP, uint8_t kI, uint8_t kD)
{
    uint8_t pid[] = {kP, kI, kD};
  
    if(!(int)port) //Port 1
    {
        writeMultiple(REGISTER_MOTOR_1_P_COEFF, pid, 3);
    }
    else //Port 2
    {
        writeMultiple(REGISTER_MOTOR_2_P_COEFF, pid, 3);
    }
}

/*
 * Get the current PID coefficients for a motor
 */
void HiTechnicDcMotorController::getMotorPIDCoeffs(MotorPort port, uint8_t* out)
{
    if(!(int)port) //Port 1
    {
        readMultiple(REGISTER_MOTOR_1_P_COEFF, 3, out);
    }
    else //Port 2
    {
        readMultiple(REGISTER_MOTOR_2_P_COEFF, 3, out);
    }
}

//--------------------------------------------------------------------------------
// Battery voltage
//--------------------------------------------------------------------------------

/*
 * Get the battery voltage in millivolts
 */
uint16_t HiTechnicDcMotorController::getBatteryVoltageMillivolts()
{
    uint16_t voltage = 0;

    uint8_t bytes[2];

    readMultiple(REGISTER_BATTERY_VOLTAGE_HIGH_BYTE, 2, bytes);

    voltage |= bytes[0] << NUM_SIGNIFICANT_BITS_BATTERY_VOLTAGE_LOW_BYTE;
    voltage |= bytes[1];
    
    return voltage * BATTERY_VOLTAGE_12_BIT_RESOLUTION_MV;
}

/*
 * Get the battery voltage as a floating-point value in volts
 */
float HiTechnicDcMotorController::getBatteryVoltage()
{
    return getBatteryVoltageMillivolts() / 1000.0;
}
