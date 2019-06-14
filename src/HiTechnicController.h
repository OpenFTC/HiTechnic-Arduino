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

#ifndef HiTechnicController_h
#define HiTechnicController_h

class HiTechnicController
{
    public:
        enum class DaisyChainPosition {FIRST = 0x01, SECOND = 0x02, THIRD = 0x03, FOURTH = 0x04, NONE = 0x05};
        
        HiTechnicController(DaisyChainPosition pos);
        void getManufacturer(uint8_t* out);
        void getSensorType(uint8_t* out);

    protected:
        void write8(uint8_t reg, uint8_t val);
        void writeMultiple(uint8_t reg, uint8_t data[], uint8_t len);
        void write32(uint8_t reg, uint32_t data);
        uint8_t read8(uint8_t reg);
        void readMultiple(uint8_t reg, uint8_t num, uint8_t* out);
        uint32_t read32(uint8_t reg);
        uint32_t byteArrayToInt32(uint8_t* bytes);
        void int32ToByteArray(uint32_t theInt, uint8_t* out);
        void clipSigned8(int8_t* val, int8_t min, int8_t max);
        void clipFloat(float* val, float min, float max);
        void sleep(uint32_t ms);
    
    private:
        uint8_t i2cAddr;

        static const uint8_t NUM_MFR_BYTES = 8;
        static const uint8_t REGISTER_MFR = 0x08;
        static const uint8_t REGISTER_SENSOR_TYPE = 0x10;
        static const uint8_t NUM_SENSOR_TYPE_BYTES = 8;

    public:
        static const uint8_t NUM_SENSOR_TYPE_CHARS = NUM_SENSOR_TYPE_BYTES + 1; //Account for null char
        static const uint8_t NUM_MFR_CHARS = NUM_MFR_BYTES + 1; //Account for null char
    
};

#endif
