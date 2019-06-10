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
#include "Arduino.h"
#include "HiTechnicController.h"
#include "Wire.h"

/* 
 *  Constructor
 */
HiTechnicController::HiTechnicController(DaisyChainPosition pos)
{
    this->i2cAddr = (int)pos; //figure out which I2C addr we need to talk to
}

//--------------------------------------------------------------------------------
// Functions to get some data that's common to both the MC and SC
//--------------------------------------------------------------------------------

void HiTechnicController::getManufacturer(uint8_t* out)
{
    readMultiple(REGISTER_MFR, NUM_MFR_BYTES, out); //Read the bytes from the controller
    out[NUM_MFR_BYTES] = 0; //Add that null char. NB: we don't need to '+1' the index because arrays start at 0, not 1
}

void HiTechnicController::getSensorType(uint8_t* out)
{
    readMultiple(REGISTER_SENSOR_TYPE, NUM_SENSOR_TYPE_BYTES, out); //Read the bytes from the controller
    out[NUM_SENSOR_TYPE_BYTES] = 0; //Add that null char. NB: we don't need to '+1' the index because arrays start at 0, not 1
}

//--------------------------------------------------------------------------------
// I2C single/multiple byte write commands for registers
//--------------------------------------------------------------------------------

/*
 *   ===  HARDWARE SPECIFIC  ===
 * 
 * Write a single byte to a given register
 */
void HiTechnicController::write8(uint8_t reg, uint8_t val)
{
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}

/*
 *    ===  HARDWARE SPECIFIC  ===
 * 
 * Write multiple bytes, starting from a given register
 */
void HiTechnicController::writeMultiple(uint8_t reg, uint8_t data[], uint8_t len)
{
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.write(data, len);
    Wire.endTransmission();
}

/*
 * Write a 32-bit integer, starting at a given register
 */
void HiTechnicController::write32(uint8_t reg, uint32_t data)
{
    uint8_t bytes[4];
    int32ToByteArray(data, bytes);
    writeMultiple(reg, bytes, 4);
}

//--------------------------------------------------------------------------------
// I2C single/multiple byte read commands for registers
//--------------------------------------------------------------------------------

/*
 *    ===  HARDWARE SPECIFIC  ===
 * 
 * Read a single byte from a given register
 */
uint8_t HiTechnicController::read8(uint8_t reg)
{
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(i2cAddr, (uint8_t)1);
    return Wire.read();
}

/*
 *    ===  HARDWARE SPECIFIC  ===
 *    
 * Read multiple bytes, starting from a given register
 */
void HiTechnicController::readMultiple(uint8_t reg, uint8_t num, uint8_t* out)
{
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(i2cAddr, num);

    for(int i = 0; i < num; i++)
    {
        out[i] = Wire.read();
    }
}

/*
 * Read a 32-bit integer, starting from a given register
 */
uint32_t HiTechnicController::read32(uint8_t reg)
{
    uint8_t bytes[4];
    readMultiple(reg, 4, bytes);
    return byteArrayToInt32(bytes);
}

//--------------------------------------------------------------------------------
// Utility Functions
//--------------------------------------------------------------------------------

/*
 * Convert a 4-element byte array into a 32-bit integer
 */
uint32_t HiTechnicController::byteArrayToInt32(uint8_t* bytes)
{
    uint32_t i = 0;

    /*
     * Apparently, doing a shift greater than the width
     * of a uint8_t does not implicitly cast to a wider
     * type, so we need to manually cast it.
     */
    
    i |= (uint32_t) bytes[0] << 24;
    i |= (uint32_t) bytes[1] << 16;
    i |= (uint32_t) bytes[2] << 8;
    i |= (uint32_t) bytes[3];

    return i;
}

/*
 * Convert a 32-bit integer into a 4-element byte array
 */
void HiTechnicController::int32ToByteArray(uint32_t theInt, uint8_t* out)
{
    out[0] = theInt >> 24;
    out[1] = theInt >> 16;
    out[2] = theInt >> 8;
    out[3] = theInt;
}

/*
 * Clip a signed 8-bit integer to minimum and maximum bound
 */
void HiTechnicController::clipSigned8(int8_t* val, int8_t min, int8_t max)
{
    if(*val > max)
    {
        *val = max;
    }
    else if(*val < min)
    {
        *val = min;
    }
}

/*
 * Clip a floating point number to a minimum and maximum bound
 */
void HiTechnicController::clipFloat(float* val, float min, float max)
{
    if(*val > max)
    {
        *val = max;
    }
    else if(*val < min)
    {
        *val = min;
    }
}

/*
 *    ===  HARDWARE SPECIFIC  ==
 *    
 * Sleeps for a set amount of milliseconds
 */
void HiTechnicController::sleep(uint32_t ms)
{
    delay(ms);
}

