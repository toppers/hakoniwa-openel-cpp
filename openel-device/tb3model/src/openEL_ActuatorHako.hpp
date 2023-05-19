#ifndef _OPENEL_ACTUATOR_HAKO_HPP_
#define _OPENEL_ACTUATOR_HAKO_HPP_

#include "Actuator.hpp"

#define MOTOR_ADDRESS    0x3A
#define MOTOR_SPEED_L    0x00
#define MOTOR_SPEED_R    0x02
#define MOTOR_ENCODER_L  0x10
#define MOTOR_ENCODER_R  0x14

#define MOTOR_LENGTH_SPEED   (2)
#define MOTOR_LENGTH_ENCODER (4)


class ActuatorHako : public Actuator
{
private:
    static std::string strDevName;
    static std::vector<std::string> strFncLst;

public:
    static Property ActuatorHako_property;

    static ReturnCode fncInit(HALComponent *pHALComponent);
    static ReturnCode fncReInit(HALComponent *pHALComponent);
    static ReturnCode fncFinalize(HALComponent *pHALComponent);
    static ReturnCode fncAddObserver(HALComponent *pHALComponent, HALObserver **halObserver);
    static ReturnCode fncRemoveObserver(HALComponent *pHALComponent, HALObserver **halObserver);
    static ReturnCode fncGetProperty(HALComponent *pHALComponent, Property **property);
    static ReturnCode fncGetTime(HALComponent *pHALComponent, int32_t **timeValue);
    static ReturnCode fncGetValueList(HALComponent *pHALComponent, HALFLOAT_T **valueList, int32_t **num);
    static ReturnCode fncGetTimedValueList(HALComponent *pHALComponent, HALFLOAT_T **valueList, int32_t **time, int32_t **num);
    static ReturnCode fncSetValue(HALComponent *pHALComponent, Request request, HALFLOAT_T value);
    static ReturnCode fncGetValue(HALComponent *pHALComponent, Request request, HALFLOAT_T **value);
    static ReturnCode fncNop(HALComponent *pHALComponent, HAL_ARGUMENT_T *pCmd);
    static ReturnCode fncDeviceVendorSpec(HALComponent* pHALComponent, HAL_ARGUMENT_T *pCmd, HAL_ARGUMENT_DEVICE_T *pCmdDev);


};

extern HAL_FNCTBL_T HalActuatorHakoTbl;

#endif /* _OPENEL_ACTUATOR_HAKO_HPP_ */