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
 * Write multiple bytes, starting from a given register
 */
void HiTechnicController::writeMultiple(uint8_t reg, uint8_t data[], uint8_t len)
{
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.write(data, len);
    Wire.endTransmission();
}

//--------------------------------------------------------------------------------
// I2C single/multiple byte read commands for registers
//--------------------------------------------------------------------------------

/*
 * Read a single byte from a given register
 */
uint8_t HiTechnicController::read8(uint8_t reg)
{
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(i2cAddr, 1);
    return Wire.read();
}

/*
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
 * Read a signed integer, starting from a given register
 */
int32_t HiTechnicController::readSigned32(uint8_t reg)
{
    uint8_t bytes[4];
    readMultiple(reg, 4, bytes);
    return byteArrayToSigned32bitInt(bytes);
}

/*
 * Read an unsigned integer, starting from a given register
 */
uint32_t HiTechnicController::readUnsigned32(uint8_t reg)
{
    uint8_t bytes[4];
    readMultiple(reg, 4, bytes);
    return byteArrayToUnsigned32bitInt(bytes);
}

//--------------------------------------------------------------------------------
// Utility Functions
//--------------------------------------------------------------------------------

/*
 * Convert a 4-element byte array into a signed integer
 */
int32_t HiTechnicController::byteArrayToSigned32bitInt(uint8_t* bytes)
{
    int32_t i = 0;
    
    i |= bytes[0] << 24;
    i |= bytes[1] << 16;
    i |= bytes[2] << 8;
    i |= bytes[3];

    return i;
}

/*
 * Convert a 4-element byte array into an unsigned integer
 */
uint32_t HiTechnicController::byteArrayToUnsigned32bitInt(uint8_t* bytes)
{
    uint32_t i = 0;
    
    i |= bytes[0] << 24;
    i |= bytes[1] << 16;
    i |= bytes[2] << 8;
    i |= bytes[3];

    return i;
}

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
