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
 * @file    impulse.h
 * @author  Texas Instruments (C) Copyright 2012 (Assisted by D3 Engineering Tech Team)
 * @date    5-7-2012
 * @version 1.0
 * @brief   This is the header file for the Impulse Module
 */
#ifndef __IMPULSE_H__
#define __IMPULSE_H__

// Includes
#include "modules/types/src/32b/types.h"

// Defines
#define IMPULSE_PERIOD_DEFAULT	1000
#define IMPULSE_OUT_DEFAULT		0
#define IMPULSE_COUNTER_DEFAULT 0

// Typedefs
typedef struct {
    uint32_t  period;		// Input: Period of output impulse in a number of sampling cycles (Q0)
    uint32_t  out;      		// Output: Impulse generator output - Q0 (0x00000000 or 0x00007FFF)
    uint32_t  counter;   	// Variable: Impulse generator counter (Q0)
} IMPULSE;

typedef IMPULSE *IMPULSE_handle;

// Globals

// Function Prototypes
/*!
 * @ingroup         IMPULSE_Setup
 * @fn              void IMPULSE_Setup(IMPULSE_handle impulseHandle)
 * @brief           Function to setup the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 */
void IMPULSE_Setup(IMPULSE_handle impulseHandle);

/*!
 * @ingroup         IMPULSE_Set_Period
 * @fn              void IMPULSE_Set_Period(IMPULSE_handle impulseHandle, uint32_t Period)
 * @brief           Function to set the period of the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @param [in]		period			The new period to be set
 */
void IMPULSE_Set_Period(IMPULSE_handle impulseHandle, uint32_t Period);

/*!
 * @ingroup         IMPULSE_Get_Period
 * @fn              uint32_t IMPULSE_Get_Period(IMPULSE_handle impulseHandle)
 * @brief           Function to get the period of the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @return			uint32_t			The period for the Impulse Module
 */
uint32_t IMPULSE_Get_Period(IMPULSE_handle impulseHandle);

/*!
 * @ingroup         IMPULSE_Set_Out
 * @fn              void IMPULSE_Set_Out(IMPULSE_handle impulseHandle, uint32_t Out)
 * @brief           Function to set the Output the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @param [in]		Out				The new Output to be set
 */
void IMPULSE_Set_Out(IMPULSE_handle impulseHandle, uint32_t Out);

/*!
 * @ingroup         IMPULSE_Get_Out
 * @fn              uint32_t IMPULSE_Get_Out(IMPULSE_handle impulseHandle)
 * @brief           Function to get the Output of the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @return			uint32_t			The Output of the Impulse Module
 */
uint32_t IMPULSE_Get_Out(IMPULSE_handle impulseHandle);

/*!
 * @ingroup         IMPULSE_Set_Counter
 * @fn              void IMPULSE_Set_Counter(IMPULSE_handle impulseHandle, uint32_t Counter)
 * @brief           Function to set the Counter of the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @param [in]		Counter			The new Counter value to be set
 */
void IMPULSE_Set_Counter(IMPULSE_handle impulseHandle, uint32_t Counter);

/*!
 * @ingroup         IMPULSE_Get_Counter
 * @fn              uint32_t IMPULSE_Get_Counter(IMPULSE_handle impulseHandle)
 * @brief           Function to get the Counter value for the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @return			uint32_t			The Counter value of the Impulse Module
 */
uint32_t IMPULSE_Get_Counter(IMPULSE_handle impulseHandle);

/*!
 * @ingroup         IMPULSE_Calc
 * @fn              void IMPULSE_Calc(IMPULSE_handle v)
 * @brief           Function to run the Impulse Module
 * @param [in/out]  v		Handler for the Impulse Module
 */
inline void IMPULSE_Calc(IMPULSE_handle v)
{
    v->counter++;    /* Increment the skip counter*/

    if (v->counter >= v->period)
    {
        v->out = 0x00007FFF;
        v->counter = 0;        /* Reset counter*/
    }
    else
    {
        v->out = 0x00000000;
    }
}

#endif // __IMPULSE_H__
