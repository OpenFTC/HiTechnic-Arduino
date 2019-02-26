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

#include "Arduino.h"
#include "HiTechnicController.h"

#ifndef HiTechnicDcMotorController_h
#define HiTechnicDcMotorController_h

class HiTechnicDcMotorController : public HiTechnicController
{
    public:
        HiTechnicDcMotorController(DaisyChainPosition pos);
        enum class RunMode {RUN_WITHOUT_ENCODER = 0x00, RUN_USING_ENCODER = 0x01, RUN_TO_POSITION = 0x02, STOP_AND_RESET_ENCODER = 0x03};
        enum class ZeroPowerBehavior {FLOAT = 0, BRAKE};
        enum class MotorPort {MOTOR_PORT_1 = 0, MOTOR_PORT_2};
        void setMotorPowers(int8_t power1, int8_t power2);
        void setMotorPower(MotorPort port, int8_t power);
        void setMotorPIDCoeffs(MotorPort port, uint8_t kP, uint8_t kI, uint8_t kD);
        void setMotorPCoeff(MotorPort port, uint8_t kP);
        void setMotorICoeff(MotorPort port, uint8_t kI);
        void setMotorDCoeff(MotorPort port, uint8_t kD);
        void setMotorRunMode(MotorPort port, RunMode mode);
        void setMotorZeroPowerBehavior(MotorPort port, ZeroPowerBehavior b);
        int32_t getMotorCurrentPosition(MotorPort port);
        void setMotorTargetPosition(MotorPort port, int32_t tPos);
        int32_t getMotorTargetPosition(MotorPort port);
        boolean isMotorBusy(MotorPort port);
        uint16_t getBatteryVoltage();
        float getBatteryVoltageFloat();

    private:
        bool m1Brake = false;
        bool m2Brake = false;

        uint8_t m1Mode = 0x00;
        uint8_t m2Mode = 0x00;

        static const uint8_t REGISTER_MOTOR_1_POWER = 0x45;
        static const uint8_t REGISTER_MOTOR_2_POWER = 0x46;
        static const uint8_t REGISTER_MOTOR_1_MODE = 0x44;
        static const uint8_t REGISTER_MOTOR_2_MODE = 0x47;
        static const uint8_t MOTOR_MODE_MASK_SELECTION = 0x03;
        static const uint8_t MIN_MOTOR_POWER = -100;
        static const uint8_t MAX_MOTOR_POWER = 100;
        static const uint8_t REGISTER_MOTOR_1_ENC_HIGH_BYTE = 0x4C;
        static const uint8_t REGISTER_MOTOR_2_ENC_HIGH_BYTE = 0x50;
        static const uint8_t REGISTER_MOTOR_1_TARGET_POSITION_HIGH_BYTE = 0x40;
        static const uint8_t REGISTER_MOTOR_2_TARGET_POSITION_HIGH_BYTE = 0x48;
        static const uint8_t BUSY_THRESHOLD = 5; //per SDK
        static const uint8_t REGISTER_BATTERY_VOLTAGE_HIGH_BYTE = 0x54;
        static const uint8_t REGISTER_MOTOR_1_P_COEFF = 0x57;
        static const uint8_t REGISTER_MOTOR_1_I_COEFF = 0x58;
        static const uint8_t REGISTER_MOTOR_1_D_COEFF = 0x59;
        static const uint8_t REGISTER_MOTOR_2_P_COEFF = 0x5B;
        static const uint8_t REGISTER_MOTOR_2_I_COEFF = 0x5C;
        static const uint8_t REGISTER_MOTOR_2_D_COEFF = 0x5D;
};

#endif
