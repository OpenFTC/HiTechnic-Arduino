#include "Arduino.h"
#include "HT_Controller.h"
#include "Wire.h"

HT_Controller::HT_Controller(uint8_t addr)
{
    this->i2cAddr = addr;
}

void HT_Controller::write8(uint8_t reg, uint8_t val)
{
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}

void HT_Controller::writeMultiple(uint8_t reg, uint8_t data[], uint8_t len)
{
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.write(data, len);
    Wire.endTransmission();
}

uint8_t HT_Controller::read8(uint8_t reg)
{
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(i2cAddr, 1);
    return Wire.read();
}

void HT_Controller::readMultiple(uint8_t reg, uint8_t num, uint8_t* out)
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

void HT_Controller::getManufacturer(uint8_t* out)
{
    readMultiple(REGISTER_MFR, NUM_MFR_BYTES, out); //Read the bytes from the controller
    out[NUM_MFR_BYTES] = 0; //Add that null char. NB: we don't need to '+1' the index because arrays start at 0, not 1
}

void HT_Controller::getSensorType(uint8_t* out)
{
    readMultiple(REGISTER_SENSOR_TYPE, NUM_SENSOR_TYPE_BYTES, out); //Read the bytes from the controller
    out[NUM_SENSOR_TYPE_BYTES] = 0; //Add that null char. NB: we don't need to '+1' the index because arrays start at 0, not 1
}

