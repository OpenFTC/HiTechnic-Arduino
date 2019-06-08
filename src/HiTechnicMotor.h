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
#include "HiTechnicDcMotorController.h"

#ifndef HiTechnicMotor_h
#define HiTechnicMotor_h

class HiTechnicMotor
{
    public:
        HiTechnicMotor(HiTechnicDcMotorController* controller, HiTechnicDcMotorController::MotorPort port);
        enum class Direction {FORWARD = 0, REVERSE};
        void setPower(int8_t power);
        void setPidCoeffs(uint8_t kP, uint8_t kI, uint8_t kD);
        void setPCoeff(uint8_t kP);
        void setICoeff(uint8_t kI);
        void setDCoeff(uint8_t kD);
        void setRunMode(HiTechnicDcMotorController::RunMode mode);
        void setTargetPosition(int32_t tPos);
        bool isBusy();
        int32_t getCurrentPosition();
        void setZeroPowerBehavior(HiTechnicDcMotorController::ZeroPowerBehavior b);
        void setDirection(Direction dir);
        HiTechnicDcMotorController* getController();

    private:
        HiTechnicDcMotorController::MotorPort port;
        HiTechnicDcMotorController* controller;
        bool rev = false;
};

#endif
