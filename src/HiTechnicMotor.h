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
        enum class Direction {FORWARD = 0, REVERSE = 1};
        
        HiTechnicMotor(HiTechnicDcMotorController* controller, HiTechnicDcMotorController::MotorPort port);
        void setPower(float power);
        float getPower();
        int32_t getCurrentPosition();
        void setMode(HiTechnicDcMotorController::RunMode mode);
        HiTechnicDcMotorController::RunMode getMode();
        void setZeroPowerBehavior(HiTechnicDcMotorController::ZeroPowerBehavior b);
        HiTechnicDcMotorController::ZeroPowerBehavior getZeroPowerBehavior();
        void setDirection(Direction dir);
        Direction getDirection();
        void setTargetPosition(int32_t tPos);
        int32_t getTargetPosition();
        bool isBusy();
        void setPIDCoeffs(uint8_t kP, uint8_t kI, uint8_t kD);
        void getPIDCoeffs(uint8_t* out);
        HiTechnicDcMotorController* getController();

    private:
        HiTechnicDcMotorController* controller;
        HiTechnicDcMotorController::MotorPort port;
        bool rev = false;
};

#endif
