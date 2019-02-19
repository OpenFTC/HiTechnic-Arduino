#include "Arduino.h"

#ifndef HiTechnicController_h
#define HiTechnicController_h

#define NUM_MFR_BYTES 8
#define REGISTER_MFR 0x08
#define REGISTER_SENSOR_TYPE 0x10
#define NUM_SENSOR_TYPE_BYTES 8

class HiTechnicController
{
    public:
        enum DaisyChainPosition {DAISY_CHAIN_POSITION_FIRST = 0x01, DAISY_CHAIN_POSITION_SECOND, DAISY_CHAIN_POSITION_THIRD, DAISY_CHAIN_POSITION_FOURTH, DAISY_CHAIN_POSITION_NONE};
        HiTechnicController(DaisyChainPosition pos);
        void getManufacturer(uint8_t* out);
        void getSensorType(uint8_t* out);

    protected:
        void write8(uint8_t reg, uint8_t val);
        void writeMultiple(uint8_t reg, uint8_t data[], uint8_t len);
        uint8_t read8(uint8_t reg);
        void readMultiple(uint8_t reg, uint8_t num, uint8_t* out);
    
    private:
        uint8_t i2cAddr;
};

#endif
