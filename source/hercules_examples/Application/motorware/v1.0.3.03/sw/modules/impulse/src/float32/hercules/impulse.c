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
 * @file    impulse.c
 * @author  Texas Instruments (C) Copyright 2012 (Assisted by D3 Engineering Tech Team)
 * @date    5-7-2012
 * @version 1.0
 * @brief   This file contains all Impulse Functions: Setup, Sets, and Gets.
 */

#include "impulse.h"

/*!
 * @ingroup         IMPULSE_Setup
 * @fn              void IMPULSE_Setup(IMPULSE_handle impulseHandle)
 * @brief           Function to setup the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 */
void IMPULSE_Setup(IMPULSE_handle impulseHandle)
{
    IMPULSE_Set_Period(impulseHandle, IMPULSE_PERIOD_DEFAULT);
    IMPULSE_Set_Out(impulseHandle, IMPULSE_OUT_DEFAULT);
    IMPULSE_Set_Counter(impulseHandle, IMPULSE_COUNTER_DEFAULT);
}

/*!
 * @ingroup         IMPULSE_Set_Period
 * @fn              void IMPULSE_Set_Period(IMPULSE_handle impulseHandle, uint32_t Period)
 * @brief           Function to set the period of the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @param [in]		period			The new period to be set
 */
void IMPULSE_Set_Period(IMPULSE_handle impulseHandle, uint32_t period)
{
    IMPULSE *impulseObj = (IMPULSE *)impulseHandle;
    impulseObj->period = period;
}

/*!
 * @ingroup         IMPULSE_Get_Period
 * @fn              uint32_t IMPULSE_Get_Period(IMPULSE_handle impulseHandle)
 * @brief           Function to get the period of the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @return			uint32_t			The period for the Impulse Module
 */
uint32_t IMPULSE_Get_Period(IMPULSE_handle impulseHandle)
{
    IMPULSE *impulseObj = (IMPULSE *)impulseHandle;
    return impulseObj->period;
}

/*!
 * @ingroup         IMPULSE_Set_Out
 * @fn              void IMPULSE_Set_Out(IMPULSE_handle impulseHandle, uint32_t Out)
 * @brief           Function to set the Output the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @param [in]		Out				The new Output to be set
 */
void IMPULSE_Set_Out(IMPULSE_handle impulseHandle, uint32_t out)
{
    IMPULSE *impulseObj = (IMPULSE *)impulseHandle;
    impulseObj->out = out;
}

/*!
 * @ingroup         IMPULSE_Get_Out
 * @fn              uint32_t IMPULSE_Get_Out(IMPULSE_handle impulseHandle)
 * @brief           Function to get the Output of the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @return			uint32_t			The Output of the Impulse Module
 */
uint32_t IMPULSE_Get_Out(IMPULSE_handle impulseHandle)
{
    IMPULSE *impulseObj = (IMPULSE *)impulseHandle;
    return impulseObj->out;
}

/*!
 * @ingroup         IMPULSE_Set_Counter
 * @fn              void IMPULSE_Set_Counter(IMPULSE_handle impulseHandle, uint32_t Counter)
 * @brief           Function to set the Counter of the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @param [in]		Counter			The new Counter value to be set
 */
void IMPULSE_Set_Counter(IMPULSE_handle impulseHandle, uint32_t counter)
{
    IMPULSE *impulseObj = (IMPULSE *)impulseHandle;
    impulseObj->counter = counter;
}

/*!
 * @ingroup         IMPULSE_Get_Counter
 * @fn              uint32_t IMPULSE_Get_Counter(IMPULSE_handle impulseHandle)
 * @brief           Function to get the Counter value for the Impulse Module
 * @param [in]      impulseHandle	The Handle for the Impulse Module
 * @return			uint32_t			The Counter value of the Impulse Module
 */
uint32_t IMPULSE_Get_Counter(IMPULSE_handle impulseHandle)
{
    IMPULSE *impulseObj = (IMPULSE *)impulseHandle;
    return impulseObj->counter;
}
