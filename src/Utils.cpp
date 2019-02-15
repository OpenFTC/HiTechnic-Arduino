#include "Arduino.h"
#include "Utils.h"
#include "Wire.h"

static void Utils::writeToI2cRegister(uint8_t addr, uint8_t reg, uint8_t data)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

static void Utils::writeToI2cRegisters(uint8_t addr, uint8_t reg, uint8_t data[], uint8_t len)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(data, len);
    Wire.endTransmission();
}

