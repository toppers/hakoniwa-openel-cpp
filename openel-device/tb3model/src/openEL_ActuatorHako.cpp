
#include "openel_common.hpp"
#include "openel_impl_private.hpp"
#include "openEL_ActuatorHako.hpp"
#include <iostream>
#include <string.h>
#include "geometry_msgs/pdu_ctype_Twist.h"

std::string ActuatorHako::strDevName = "ActuatorHako";

std::vector<std::string> ActuatorHako::strFncLst =
{
    "Init",
    "ReInit",
    "Finalize",
    "AddObserver",
    "RemoveObserver",
    "SetValue",
    "GetValue"
};

Property ActuatorHako::ActuatorHako_property;

ReturnCode ActuatorHako::fncInit(HALComponent *pHALComponent)
{
    std::cout<< "ActuatorHako::fncInit()" << std::endl;
    return HAL_OK;
}

ReturnCode ActuatorHako::fncReInit(HALComponent *pHALComponent)
{
   return HAL_OK;
}

ReturnCode ActuatorHako::fncFinalize(HALComponent *pHALComponent)
{
    std::cout<< "ActuatorHako::fncFinalize()" << std::endl;
    if (pHALComponent->hALId.instanceId == MOTOR_RIGHT) {
    }
    return HAL_OK;
}

ReturnCode ActuatorHako::fncAddObserver(HALComponent *pHALComponent, HALObserver **halObserver)
{
    //TODO
    return HAL_OK;
}

ReturnCode ActuatorHako::fncRemoveObserver(HALComponent *pHALComponent, HALObserver **halObserver)
{
    //TODO
    return HAL_OK;
}

ReturnCode ActuatorHako::fncGetProperty(HALComponent *pHALComponent, Property **property)
{
    ActuatorHako_property.deviceName = strDevName;
    ActuatorHako_property.functionList = strFncLst;
    (**property).functionList.resize(strFncLst.size());
    **property = ActuatorHako_property;

    return HAL_OK;
}

ReturnCode ActuatorHako::fncGetTime(HALComponent *pHALComponent, int32_t **timeValue)
{
    //TODO

    //**timeValue = (unsigned int)millis();

    return HAL_OK;
}

ReturnCode ActuatorHako::fncGetValueList(HALComponent *pHALComponent, HALFLOAT_T **valueList, int32_t **num)
{
    //TODO
    return HAL_ERROR;
}

ReturnCode ActuatorHako::fncGetTimedValueList(HALComponent *pHALComponent, HALFLOAT_T **valueList, int32_t **timeValue, int32_t **num)
{
    //TODO
    return HAL_ERROR;
}

ReturnCode ActuatorHako::fncSetValue(HALComponent *pHALComponent, Request request, HALFLOAT_T value)
{
    Hako_Twist pdu_msg;
    bool ret = false;
    ReturnCode retCode = HAL_OK;

    if (pHALComponent->hALId.instanceId >= InstanceNum)
    {
        return HAL_ERROR;
    }
    switch (request)
    {
    case Request::HAL_REQUEST_POSITION_CONTROL:
        //TODO
        //setEncoder((int32_t)value, pHALComponent->hALId.instanceId);
        break;
    case Request::HAL_REQUEST_VELOCITY_CONTROL:
        memset((char*)&pdu_msg, 0, sizeof(Hako_Twist));
        (void)hako_pdu_read_data(HAKO_PDU_CHANNEL_CMDVEL, (char*)&pdu_msg, sizeof(Hako_Twist));
        if (pHALComponent->hALId.instanceId == MOTOR_LEFT) {
            pdu_msg.linear.x = value;
        }
        else {
            pdu_msg.angular.z = value;
        }
        ret = hako_pdu_write_data(HAKO_PDU_CHANNEL_CMDVEL,  (char*)&pdu_msg, sizeof(Hako_Twist));
        //if (ret) {
        //    std::cout<< "ActuatorHako::publish() : ret = " << ret << std::endl;
        //}
        break;
    case Request::HAL_REQUEST_TORQUE_CONTROL:
        break;
    default:
        retCode = HAL_ERROR;
        break;
    }

    return retCode;
}

ReturnCode ActuatorHako::fncGetValue(HALComponent *pHALComponent, Request request, HALFLOAT_T **value)
{
    int32_t wheel;
    int16_t sp;
    ReturnCode retCode = HAL_OK;

    if (pHALComponent->hALId.instanceId >= InstanceNum)
    {
        return HAL_ERROR;
    }

    switch (request)
    {
    case Request::HAL_REQUEST_POSITION_CONTROL:
        //getEncoder(&wheel, pHALComponent->hALId.instanceId);
        //**value = (float)wheel;
        break;
    case Request::HAL_REQUEST_VELOCITY_CONTROL:
        //getSpeed(&sp, pHALComponent->hALId.instanceId);
        //**value = (float)sp;
        break;
    case Request::HAL_REQUEST_TORQUE_CONTROL:
        break;
    default:
        retCode = HAL_ERROR;
        break;
    }

    return retCode;
}

ReturnCode ActuatorHako::fncNop(HALComponent *pHALComponent, HAL_ARGUMENT_T *pCmd)
{
    return HAL_ERROR;
}

ReturnCode ActuatorHako::fncDeviceVendorSpec(HALComponent *pHALComponent, HAL_ARGUMENT_T *pCmd, HAL_ARGUMENT_DEVICE_T *pCmdDev)
{
    return HAL_ERROR;
}

HAL_FNCTBL_T HalActuatorHakoTbl =
{
    ActuatorHako::fncInit,			/* 0x00 */
    ActuatorHako::fncReInit,			/* 0x01 */
    ActuatorHako::fncFinalize,		/* 0x02 */
    ActuatorHako::fncAddObserver,		/* 0x03 */
    ActuatorHako::fncRemoveObserver,		/* 0x04 */
    ActuatorHako::fncGetProperty,		/* 0x05 */
    ActuatorHako::fncGetTime,		/* 0x06 */
    ActuatorHako::fncNop,			/* 0x07 */
    ActuatorHako::fncNop,			/* 0x08 */
    ActuatorHako::fncNop,			/* 0x09 */
    ActuatorHako::fncNop,			/* 0x0A */
    ActuatorHako::fncNop,			/* 0x0B */
    ActuatorHako::fncNop,			/* 0x0C */
    ActuatorHako::fncNop,			/* 0x0D */
    ActuatorHako::fncNop,			/* 0x0E */
    ActuatorHako::fncNop,			/* 0x0F */
    ActuatorHako::fncNop,			/* 0x10 */
    ActuatorHako::fncNop,			/* 0x11 */
    ActuatorHako::fncNop,			/* 0x12 */
    ActuatorHako::fncNop,			/* 0x13 */
    ActuatorHako::fncNop,			/* 0x14 */
    ActuatorHako::fncNop,			/* 0x15 */
    ActuatorHako::fncNop,			/* 0x16 */
    ActuatorHako::fncNop,			/* 0x17 */
    ActuatorHako::fncSetValue,		/* 0x18 */
    ActuatorHako::fncGetValue,		/* 0x19 */
    ActuatorHako::fncGetValueList,	/* 0x1A */
    ActuatorHako::fncGetTimedValueList,	/* 0x1B */
    ActuatorHako::fncDeviceVendorSpec,	/* 0x1C */
    ActuatorHako::fncDeviceVendorSpec,	/* 0x1D */
    ActuatorHako::fncDeviceVendorSpec,	/* 0x1E */
    ActuatorHako::fncDeviceVendorSpec,	/* 0x1F */
};
