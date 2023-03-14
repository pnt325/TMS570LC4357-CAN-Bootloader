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
/*!
 * @file    rmp3cntl.h
 * @author  Texas Instruments (C) Copyright 2012 (Assisted by D3 Engineering Tech Team)
 * @date    5-7-2012
 * @version 1.0
 * @brief   This is the header file for the RMP3 Control Module
 */
#ifndef __RMP3_CNTL_H__
#define __RMP3_CNTL_H__

// Includes
#include "modules/types/src/32b/types.h"

// Defines
#define RMP3_DESIRED_IN_DEFAULT		0
#define RMP3_DELAY_DEFAULT			0
#define RMP3_DELAY_COUNT_DEFAULT	0
#define RMP3_OUT_DEFAULT			0
#define RMP3_MIN_DEFAULT			0x00000050
#define RMP3_DONE_FLAG_DEFAULT		0

// Typedefs
typedef struct {
    uint32_t desiredInput; 		// Input: Desired ramp input (Q0) - independently with global Q
    uint32_t ramp3Delay;			// Parameter: Ramp3 delay expressed in no of sampling period (Q0) - independently with global Q
    uint32_t ramp3DelayCount;	// Variable: Counter for rmp3 delay (Q0) - independently with global Q
    int32_t out;					// Output: Ramp3 output (Q0) - independently with global Q
    int32_t ramp3Min;	    	// Parameter: Minimum ramp output (Q0) - independently with global Q
    uint32_t ramp3DoneFlag;		// Output: Flag output (Q0) - independently with global Q
} RMP3;

typedef RMP3 *RMP3_handle;

// Globals

// Function Prototypes
/*!
 * @ingroup         RMP3_Setup
 * @fn              void RMP3_Setup(RMP3_handle rmp3Handle)
 * @brief           Function to setup the Ramp3 Module
 * @param [in/out]  rmp3Handle		The Handle for the Ramp3 Module
 */
void RMP3_Setup(RMP3_handle rmp3Handle);

/*!
 * @ingroup         RMP3_Set_DesiredIn
 * @fn              void RMP3_Set_DesiredIn(RMP3_handle rmp3Handle, uint32_t DesiredInput)
 * @brief           Function to Set the DesiredInput of the Ramp3 Module
 * @param [in/out]  rmp3Handle		The Handle for the Ramp3 Module
 * @param [in]		desiredInput	The new DesiredInput for the Ramp3 Module
 */
void RMP3_Set_DesiredIn(RMP3_handle rmp3Handle, uint32_t desiredInput);

/*!
 * @ingroup         RMP3_Get_DesiredIn
 * @fn              uint32_t RMP3_Get_DesiredIn(RMP3_handle rmp3Handle)
 * @brief           Function to Get DesiredInput for the Ramp3 Module
 * @param [in]      rmp3Handle		The Handle for the Ramp3 Module
 * @return			uint32_t			The DesiredInput for the Ramp3 Module
 */
uint32_t RMP3_Get_DesiredIn(RMP3_handle rmp3Handle);

/*!
 * @ingroup         RMP3_Set_Delay
 * @fn              void RMP3_Set_Delay(RMP3_handle rmp3Handle, uint32_t Ramp3Delay)
 * @brief           Function to Set the Ramp3Delay of the Ramp3 Module
 * @param [in/out]  rmp3Handle		The Handle for the Ramp3 Module
 * @param [in]		ramp3Delay		The new Ramp3Delay for the Ramp3 Module
 */
void RMP3_Set_Delay(RMP3_handle rmp3Handle, uint32_t ramp3Delay);

/*!
 * @ingroup         RMP3_Get_Delay
 * @fn              uint32_t RMP3_Get_DesiredIn(RMP3_handle rmp3Handle)
 * @brief           Function to Get DesiredInput for the Ramp3 Module
 * @param [in]      rmp3Handle		The Handle for the Ramp3 Module
 * @return			uint32_t			The DesiredInput for the Ramp3 Module
 */
uint32_t RMP3_Get_Delay(RMP3_handle rmp3Handle);

/*!
 * @ingroup         RMP3_Set_DelayCount
 * @fn              void RMP3_Set_DelayCount(RMP3_handle rmp3Handle, uint32_t Ramp3DelayCount)
 * @brief           Function to Set the Ramp3DelayCount of the Ramp3 Module
 * @param [in/out]  rmp3Handle		The Handle for the Ramp3 Module
 * @param [in]		ramp3DelayCount	The new Ramp3DelayCount for the Ramp3 Module
 */
void RMP3_Set_DelayCount(RMP3_handle rmp3Handle, uint32_t ramp3DelayCount);

/*!
 * @ingroup         RMP3_Get_DelayCount
 * @fn              uint32_t RMP3_Get_DelayCount(RMP3_handle rmp3Handle)
 * @brief           Function to Get Ramp3DelayCount for the Ramp3 Module
 * @param [in]      rmp3Handle		The Handle for the Ramp3 Module
 * @return			uint32_t			The Ramp3DelayCount for the Ramp3 Module
 */
uint32_t RMP3_Get_DelayCount(RMP3_handle rmp3Handle);

/*!
 * @ingroup         RMP3_Set_Out
 * @fn              void RMP3_Set_Out(RMP3_handle rmp3Handle, uint32_t Out)
 * @brief           Function to Set the Out of the Ramp3 Module
 * @param [in/out]  rmp3Handle		The Handle for the Ramp3 Module
 * @param [in]		out				The new Out for the Ramp3 Module
 */
void RMP3_Set_Out(RMP3_handle rmp3Handle, uint32_t out);

/*!
 * @ingroup         RMP3_Get_Out
 * @fn              int32_t RMP3_Get_Out(RMP3_handle rmp3Handle)
 * @brief           Function to Get Out for the Ramp3 Module
 * @param [in]      rmp3Handle		The Handle for the Ramp3 Module
 * @return			int32_t			The Out for the Ramp3 Module
 */
int32_t RMP3_Get_Out(RMP3_handle rmp3Handle);

/*!
 * @ingroup         RMP3_Set_Min
 * @fn              void RMP3_Set_Min(RMP3_handle rmp3Handle, uint32_t Ramp3Min)
 * @brief           Function to Set the Min of the Ramp3 Module
 * @param [in/out]  rmp3Handle		The Handle for the Ramp3 Module
 * @param [in]		ramp3Min		The new Min for the Ramp3 Module
 */
void RMP3_Set_Min(RMP3_handle rmp3Handle, uint32_t ramp3Min);

/*!
 * @ingroup         RMP3_Get_Min
 * @fn              int32_t RMP3_Get_Min(RMP3_handle rmp3Handle)
 * @brief           Function to Get the Min for the Ramp3 Module
 * @param [in]      rmp3Handle		The Handle for the Ramp3 Module
 * @return			int32_t			The Min for the Ramp3 Module
 */
int32_t RMP3_Get_Min(RMP3_handle rmp3Handle);

/*!
 * @ingroup         RMP3_Set_DoneFlag
 * @fn              void RMP3_Set_DoneFlag(RMP3_handle rmp3Handle, uint32_t Ramp3DoneFlag)
 * @brief           Function to Set the Done Flag of the Ramp3 Module
 * @param [in/out]  rmp3Handle		The Handle for the Ramp3 Module
 * @param [in]		ramp3DoneFlag	The new Done Flag for the Ramp3 Module
 */
void RMP3_Set_DoneFlag(RMP3_handle rmp3Handle, uint32_t ramp3DoneFlag);

/*!
 * @ingroup         RMP3_Get_DoneFlag
 * @fn              uint32_t RMP3_Get_DoneFlag(RMP3_handle rmp3Handle)
 * @brief           Function to Get the Done Flag for the Ramp3 Module
 * @param [in]      rmp3Handle		The Handle for the Ramp3 Module
 * @return			uint32_t			The Done Flag for the Ramp3 Module
 */
uint32_t RMP3_Get_DoneFlag(RMP3_handle rmp3Handle);

/*!
 * @ingroup         RMP3_Calc
 * @fn             	void RMP3_Calc(RMP3_handle v)
 * @brief           Function to run the RMP3 Calculations
 * @param [in/out]  v	The Handle for the RMP3 Module
 */
inline void RMP3_Calc(RMP3_handle v)
{
    if (v->out == v->desiredInput)
        v->ramp3DoneFlag = 0x7FFFFFFF;
    else
    {

        v->ramp3DelayCount++;

        if (v->ramp3DelayCount >= v->ramp3Delay)
        {
            v->out--;

            if (v->out < v->ramp3Min)
                v->out = v->ramp3Min;

            v->ramp3DelayCount = 0;
        }

    }
}

#endif // __RMP3_CNTL_H__

