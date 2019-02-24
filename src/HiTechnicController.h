#include "Arduino.h"

#ifndef HiTechnicController_h
#define HiTechnicController_h

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
        int32_t readSigned32(uint8_t reg);
        uint32_t readUnsigned32(uint8_t reg);
        int32_t byteArrayToSigned32bitInt(uint8_t* bytes);
        uint32_t byteArrayToUnsigned32bitInt(uint8_t* bytes);
        void clipSigned8(int8_t* val, int8_t min, int8_t max);
    
    private:
        uint8_t i2cAddr;

        static const uint8_t NUM_MFR_BYTES = 8;
        static const uint8_t REGISTER_MFR = 0x08;
        static const uint8_t REGISTER_SENSOR_TYPE = 0x10;
        static const uint8_t NUM_SENSOR_TYPE_BYTES = 8;
};

#endif
