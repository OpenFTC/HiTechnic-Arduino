#include "Arduino.h"
#include "HiTechnicController.h"

#ifndef HiTecMC_h
#define HiTecMC_h

#define REGISTER_MOTOR_1_POWER 0x45
#define REGISTER_MOTOR_2_POWER 0x46
#define REGISTER_BATTERY_VOLTAGE_HIGH_BYTE 0x54
#define REGISTER_MOTOR_1_P_COEFF 0x57
#define REGISTER_MOTOR_1_I_COEFF 0x58
#define REGISTER_MOTOR_1_D_COEFF 0x59

#define REGISTER_MOTOR_2_P_COEFF 0x5B
#define REGISTER_MOTOR_2_I_COEFF 0x5C
#define REGISTER_MOTOR_2_D_COEFF 0x5D

class HiTechnicDcMotorController : public HiTechnicController
{
    public:
        HiTechnicDcMotorController(DaisyChainPosition pos);
        enum class RunMode {RUN_WITHOUT_ENCODER, RUN_USING_ENCODER, RUN_TO_POSITION, STOP_AND_RESET_ENCODER};
        void setMotorPowers(int8_t power1, int8_t power2);
        void setMotorPower(boolean port, int8_t power);
        void setMotorPIDCoeffs(boolean port, uint8_t kP, uint8_t kI, uint8_t kD);
        void setMotorPCoeff(boolean port, uint8_t kP);
        void setMotorICoeff(boolean port, uint8_t kI);
        void setMotorDCoeff(boolean port, uint8_t kD);
        void setMotorRunMode(boolean port, RunMode mode);
};

#endif
