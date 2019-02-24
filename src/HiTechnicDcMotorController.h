#include "Arduino.h"
#include "HiTechnicController.h"

#ifndef HiTechnicDcMotorController_h
#define HiTechnicDcMotorController_h

#define REGISTER_MOTOR_1_POWER 0x45
#define REGISTER_MOTOR_2_POWER 0x46
#define MIN_MOTOR_POWER -100
#define MAX_MOTOR_POWER 100

#define REGISTER_MOTOR_1_ENC_HIGH_BYTE 0x4C
#define REGISTER_MOTOR_2_ENC_HIGH_BYTE 0x50

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
        uint16_t getBatteryVoltage();
        float getBatteryVoltageFloat();

    private:
        bool m1Brake = false;
        bool m2Brake = false;
};

#endif
