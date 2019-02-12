#include "Arduino.h"

#ifndef Utils_h
#define Utils_h

class Utils
{
    public:
        boolean test = true;
        static void writeToI2cRegister(uint8_t addr, uint8_t reg, uint8_t data);
        static void writeToI2cRegisters(uint8_t addr, uint8_t reg, uint8_t data[], uint8_t len);
};

#endif
