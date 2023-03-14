/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
#ifndef __RMP_CNTL_H__
#define __RMP_CNTL_H__

//! \file   ~modules/rmpcntl/src/float32/hercules/rmp_cntl.h
//! \brief  Contains the public interface to the
//!         Ramp Control module routines
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "sys_common.h"


//!
//! \defgroup RAMPGEN

//!
//! \ingroup RAMPGEN
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

// **************************************************************************
// the typedefs

//! \brief Defines the Ramp Control object
//!
typedef struct {
    float32_t targetValue; 		// Input: Target input (pu)
    uint32_t rampDelayMax;		// Parameter: Maximum delay rate
    float32_t rampLowLimit;		// Parameter: Minimum limit (pu)
    float32_t rampHighLimit;	// Parameter: Maximum limit (pu)
    uint32_t rampDelayCount; 	// Variable: Incremental delay
    float32_t setpointValue;	// Output: Target output (pu)
    float32_t stepSize;			// Output: Target output (pu)
    uint32_t equalFlag;			// Output: Flag output
} RMPCNTL_Obj;

//! \brief Defines the Ramp Control object handle
//!
typedef RMPCNTL_Obj *RMPCNTL_handle;

// **************************************************************************
// the function prototypes

//! \brief           Function to initialize the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
RMPCNTL_handle RMPCNTL_init(void *pMemory, const size_t numBytes);


//! \brief           Function to setup the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
void RMPCNTL_Setup(RMPCNTL_handle rmpCntlHandle);


//! \brief           Function to Set the TargetValue of the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
//! \param [in]		targetValue			The new TargetValue for the Ramp Control Module
inline void RMPCNTL_Set_TargetValue(RMPCNTL_handle rmpCntlHandle, float32_t targetValue)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    rmpCntlObj->targetValue = targetValue;
}


//! \brief           Function to Get TargetValue for the Ramp Control Module
//! \param [in]      rmpCntlHandle	The Handle for the Ramp Control Module
//! \return			float32_t				The TargetValue for the Ramp Control Module
inline float32_t RMPCNTL_Get_TargetValue(RMPCNTL_handle rmpCntlHandle)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    return rmpCntlObj->targetValue;
}


//! \brief           Function to Set the RampDelayMax of the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
//! \param [in]		rampDelayMax		The new RampDelayMax value for the Ramp Control Module
inline void RMPCNTL_Set_RampDelayMax(RMPCNTL_handle rmpCntlHandle, uint32_t rampDelayMax)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    rmpCntlObj->rampDelayMax = rampDelayMax;
}


//! \brief           Function to Get RampDelayMax for the Ramp Control Module
//! \param [in]      rmpCntlHandle	The Handle for the Ramp Control Module
//! \return			uint32_t			The RampDelayMax value for the Ramp Control Module
inline uint32_t RMPCNTL_Get_RampDelayMax(RMPCNTL_handle rmpCntlHandle)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    return rmpCntlObj->rampDelayMax;
}


//! \brief           Function to Set the RampLowLimit of the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
//! \param [in]		rampLowLimit	The new RampLowLimit value for the Ramp Control Module
inline void RMPCNTL_Set_RampLowLimit(RMPCNTL_handle rmpCntlHandle, float32_t rampLowLimit)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    rmpCntlObj->rampLowLimit = rampLowLimit;
}


//! \brief           Function to Get RampLowLimit for the Ramp Control Module
//! \param [in]      rmpCntlHandle	The Handle for the Ramp Control Module
//! \return			float32_t				The RampLowLimit value for the Ramp Control Module
inline float32_t RMPCNTL_Get_RampLowLimit(RMPCNTL_handle rmpCntlHandle)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    return rmpCntlObj->rampLowLimit;
}


//! \ingroup         RMPCNTL_Set_RampHighLimit
//! \fn              void RMPCNTL_Set_RampHighLimit(RMPCNTL_handle rmpCntlHandle, float32_t RampHighLimit)
//! \brief           Function to Set the RampLowLimit of the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
//! \param [in]		rampHighLimit	The new RampHighLimit value for the Ramp Control Module
inline void RMPCNTL_Set_RampHighLimit(RMPCNTL_handle rmpCntlHandle, float32_t rampHighLimit)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    rmpCntlObj->rampHighLimit = rampHighLimit;
}


//! \brief           Function to Get RampHighLimit for the Ramp Control Module
//! \param [in]      rmpCntlHandle	The Handle for the Ramp Control Module
//! \return			float32_t				The RampHighLimit value for the Ramp Control Module
inline float32_t RMPCNTL_Get_RampHighLimit(RMPCNTL_handle rmpCntlHandle)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    return rmpCntlObj->rampHighLimit;
}


//! \brief           Function to Set the RampDelayCount of the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
//! \param [in]		rampDelayCount		The new RampDelayCount value for the Ramp Control Module
inline void RMPCNTL_Set_RampDelayCount(RMPCNTL_handle rmpCntlHandle, uint32_t rampDelayCount)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    rmpCntlObj->rampDelayCount = rampDelayCount;
}


//! \brief           Function to Get RampDelayCount for the Ramp Control Module
//! \param [in]      rmpCntlHandle	The Handle for the Ramp Control Module
//! \return			uint32_t			The RampDelayCount value for the Ramp Control Module
inline uint32_t RMPCNTL_Get_RampDelayCount(RMPCNTL_handle rmpCntlHandle)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    return rmpCntlObj->rampDelayCount;
}


//! \brief           Function to Set the SetpointValue of the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
//! \param [in]		setpointValue	The new SetpointValue for the Ramp Control Module
inline void RMPCNTL_Set_SetpointValue(RMPCNTL_handle rmpCntlHandle, float32_t setpointValue)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    rmpCntlObj->setpointValue = setpointValue;
}


//! \brief           Function to Get SetpointValue for the Ramp Control Module
//! \param [in]      rmpCntlHandle	The Handle for the Ramp Control Module
//! \return			float32_t				The SetpointValue for the Ramp Control Module
inline float32_t RMPCNTL_Get_SetpointValue(RMPCNTL_handle rmpCntlHandle)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    return rmpCntlObj->setpointValue;
}


//! \brief           Function to Set the EqualFlag of the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
//! \param [in]		EqualFlag		The new EqualFlag value for the Ramp Control Module
inline void RMPCNTL_Set_EqualFlag(RMPCNTL_handle rmpCntlHandle, uint32_t equalFlag)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    rmpCntlObj->equalFlag = equalFlag;
}


//! \brief           Function to Get EqualFlag for the Ramp Control Module
//! \param [in]      rmpCntlHandle	The Handle for the Ramp Control Module
//! \return			uint32_t			The EqualFlag value for the Ramp Control Module
inline uint32_t RMPCNTL_Get_EqualFlag(RMPCNTL_handle rmpCntlHandle)
{
    RMPCNTL_Obj *rmpCntlObj = (RMPCNTL_Obj *)rmpCntlHandle;
    return rmpCntlObj->equalFlag;
}


//! \brief           Function to run the RMPCntl Calculations
//! \param [in/out]  rmpCntlHandle	The Handle for the Ramp Control Module
inline void RMPCNTL_Calc(RMPCNTL_handle rmpCntlHandle)
{
	RMPCNTL_Obj *rmpCntl = (RMPCNTL_Obj *)rmpCntlHandle;

    if (fabs(rmpCntl->targetValue - rmpCntl->setpointValue) > rmpCntl->stepSize)
    {
        rmpCntl->rampDelayCount += 1;
        if (rmpCntl->rampDelayCount >= rmpCntl->rampDelayMax)
        {
            if (rmpCntl->targetValue >= rmpCntl->setpointValue)
            {
                rmpCntl->setpointValue += rmpCntl->stepSize;
                if (rmpCntl->setpointValue > rmpCntl->rampHighLimit)
                    rmpCntl->setpointValue = rmpCntl->rampHighLimit;
                rmpCntl->rampDelayCount = 0;
            }
            else
            {
                rmpCntl->setpointValue -= rmpCntl->stepSize;
                if (rmpCntl->setpointValue < rmpCntl->rampLowLimit)
                    rmpCntl->setpointValue = rmpCntl->rampLowLimit;
                rmpCntl->rampDelayCount = 0;
            }
        }
    }
    else rmpCntl->equalFlag = 0x7FFFFFFF;


}


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // __RMP_CNTL_H__
