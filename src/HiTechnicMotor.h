#include "HiTechnicDcMotorController.h"
#include "Arduino.h"

#ifndef HiTechnicMotor_h
#define HiTechnicMotor_h

class HiTechnicMotor
{
    public:
        HiTechnicMotor(HiTechnicDcMotorController* controller, HiTechnicDcMotorController::MotorPort port);
        void setPower(int8_t power);
        void setPidCoeffs(uint8_t kP, uint8_t kI, uint8_t kD);
        void setPCoeff(uint8_t kP);
        void setICoeff(uint8_t kI);
        void setDCoeff(uint8_t kD);
        void setRunMode(HiTechnicDcMotorController::RunMode mode);
        int32_t getCurrentPosition();

    private:
        HiTechnicDcMotorController::MotorPort port;
        HiTechnicDcMotorController* controller;
};

#endif
