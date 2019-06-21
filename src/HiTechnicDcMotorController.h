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
#include "HiTechnicController.h"

#ifndef HiTechnicDcMotorController_h
#define HiTechnicDcMotorController_h

class HiTechnicDcMotorController : public HiTechnicController
{
    public:
        enum class RunMode {RUN_WITHOUT_ENCODER = 0x00, RUN_USING_ENCODER = 0x01, RUN_TO_POSITION = 0x02, STOP_AND_RESET_ENCODER = 0x03};
        enum class ZeroPowerBehavior {FLOAT = 0, BRAKE = 1};
        enum class MotorPort {PORT_1 = 0, PORT_2 = 1};

        HiTechnicDcMotorController(DaisyChainPosition pos);
        void setMotorPower(MotorPort port, float power);
        float getMotorPower(MotorPort port);
        int32_t getMotorCurrentPosition(MotorPort port);
        void setMotorMode(MotorPort port, RunMode mode);
        RunMode getMotorMode(MotorPort port);
        ZeroPowerBehavior getMotorZeroPowerBehavior(MotorPort port);
        void setMotorZeroPowerBehavior(MotorPort port, ZeroPowerBehavior b);
        void setTimeoutEnabled(bool timeoutEnabled);
        void setMotorTargetPosition(MotorPort port, int32_t tPos);
        int32_t getMotorTargetPosition(MotorPort port);
        bool isMotorBusy(MotorPort port);
        void setMotorPIDCoeffs(MotorPort port, uint8_t kP, uint8_t kI, uint8_t kD);
        void getMotorPIDCoeffs(MotorPort port, uint8_t* out);
        uint16_t getBatteryVoltageMillivolts();
        float getBatteryVoltage();
        void reset();

        static const uint8_t DEFAULT_P_COEFF = 128;
        static const uint8_t DEFAULT_I_COEFF = 64;
        static const uint8_t DEFAULT_D_COEFF = 184;
        

    private:
        static const uint8_t REGISTER_MOTOR_1_POWER = 0x45;
        static const uint8_t REGISTER_MOTOR_2_POWER = 0x46;
        static const uint8_t REGISTER_MOTOR_1_MODE = 0x44;
        static const uint8_t REGISTER_MOTOR_2_MODE = 0x47;
        static const uint8_t MOTOR_MODE_MASK_SELECTION = 0x03;
        static const uint8_t NTO_BIT = 0x10;
        static constexpr float API_MOTOR_POWER_MIN = -1;
        static constexpr float API_MOTOR_POWER_MAX = 1;
        static const uint8_t MOTOR_POWER_FLOAT = -128;
        static const uint8_t REGISTER_MOTOR_1_ENC_HIGH_BYTE = 0x4C;
        static const uint8_t REGISTER_MOTOR_2_ENC_HIGH_BYTE = 0x50;
        static const uint8_t REGISTER_MOTOR_1_TARGET_POSITION_HIGH_BYTE = 0x40;
        static const uint8_t REGISTER_MOTOR_2_TARGET_POSITION_HIGH_BYTE = 0x48;
        static const uint8_t BUSY_THRESHOLD = 5; //per SDK
        static const uint8_t REGISTER_BATTERY_VOLTAGE_HIGH_BYTE = 0x54;
        static const uint8_t NUM_SIGNIFICANT_BITS_BATTERY_VOLTAGE_LOW_BYTE = 2;
        static const uint8_t BATTERY_VOLTAGE_12_BIT_RESOLUTION_MV = 20;
        static const uint8_t REGISTER_MOTOR_1_P_COEFF = 0x57;
        static const uint8_t REGISTER_MOTOR_1_I_COEFF = 0x58;
        static const uint8_t REGISTER_MOTOR_1_D_COEFF = 0x59;
        static const uint8_t REGISTER_MOTOR_2_P_COEFF = 0x5B;
        static const uint8_t REGISTER_MOTOR_2_I_COEFF = 0x5C;
        static const uint8_t REGISTER_MOTOR_2_D_COEFF = 0x5D;

        bool m1Brake = false;
        bool m2Brake = false;
        uint8_t m1Mode = 0x00;
        uint8_t m2Mode = 0x00;
};

#endif
