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
 * @file    speed_pr.h
 * @author  Texas Instruments (C) Copyright 2012 (Assisted by D3 Engineering Tech Team)
 * @date    5-7-2012
 * @version 1.0
 * @brief   This is the header file for the Speed Measurement Module
 */

#ifndef __SPEED_PR_H__
#define __SPEED_PR_H__

// Includes
#include "modules/types/src/32b/types.h"

// Defines
#define SPEED_NEW_TIMESTAMP_DEFAULT	0
#define SPEED_OLD_TIMESTAMP_DEFAULT	0
#define SPEED_CUR_TIMESTAMP_DEFAULT	0
#define SPEED_SCALER_DEFAULT		260
#define SPEED_EVENT_PERIOD_DEFAULT	0
#define SPEED_INPUT_SELECT_DEFAULT	0
#define SPEED_OUTPUT_DEFAULT		0
#define SPEED_BASE_RPM_DEFAULT		1800
#define SPEED_OUTPUT_RPM_DEFAULT	0

// Typedefs
typedef struct {
    uint32_t newTimeStamp;  	// Variable : New 'Timestamp' corresponding to a capture event (Q0) - independently with global Q
    uint32_t oldTimeStamp;  	// Variable : Old 'Timestamp' corresponding to a capture event (Q0) - independently with global Q
    uint32_t curTimeStamp; 	   	// Input : Current 'Timestamp' corresponding to a capture event (Q0) - independently with global Q
    uint32_t speedScaler;    	// Parameter :  Scaler converting 1/N cycles to a GLOBAL_Q speed (Q0) - independently with global Q
    int32_t eventPeriod;    	// Input/Variable :  Event Period (Q0) - independently with global Q
    int16_t inputSelect;       // Input : Input selection between TimeStamp (InputSelect=0) and EventPeriod (InputSelect=1)
    float32_t speed;             	// Output :  speed in per-unit
    uint32_t baseRPM;         	// Parameter : Scaler converting GLOBAL_Q speed to rpm (Q0) speed - independently with global Q
    int32_t speedRPM;        	// Output : speed in r.p.m. (Q0) - independently with global Q
} SPEED_MEAS_CAP;       	// Data type created

/*
Note that SpeedScaler = 60*f/rmp_max
where f = CLK_freq/(128*N), N = number of teeth in sprocket
and 128 is pre-determined prescaler of timer 2 (used by capture)
*/

typedef SPEED_MEAS_CAP *SPEED_MEAS_CAP_handle;

// Globals

// Function Prototypes
/*!
 * @ingroup         SPEED_MEAS_CAP_Setup
 * @fn              void SPEED_MEAS_CAP_Setup(SPEED_MEAS_CAP_handle speedHandle)
 * @brief           Function to setup Speed Measurement Module
 * @param [in/out]  speedHandle		The Handle for the Speed Measurement Module
 */
void SPEED_MEAS_CAP_Setup(SPEED_MEAS_CAP_handle speedHandle);

/*!
 * @ingroup         SPEED_MEAS_CAP_Set_NewTimeStamp
 * @fn              void SPEED_MEAS_CAP_Set_NewTimeStamp(SPEED_MEAS_CAP_handle speedHandle, uint32_t NewTimeStamp)
 * @brief           Function to Set the New Timestamp of the Speed Measurement Module
 * @param [in/out]  speedHandle			The Handle for the Speed Measurement Module
 * @param [in]		newTimeStamp		The new New Timestamp for the Speed Measurement Module
 */
void SPEED_MEAS_CAP_Set_NewTimeStamp(SPEED_MEAS_CAP_handle speedHandle, uint32_t NewTimeStamp);

/*!
 * @ingroup         SPEED_MEAS_CAP_Get_NewTimeStamp
 * @fn              uint32_t SPEED_MEAS_CAP_Get_NewTimeStamp(SPEED_MEAS_CAP_handle speedHandle)
 * @brief           Function to Get the New Timestamp for the Speed Measurement Module
 * @param [in]      speedHandle			The Handle for the Speed Measurement Module
 * @return			uint32_t				The New Timestamp for the Speed Measurement Module
 */
uint32_t SPEED_MEAS_CAP_Get_NewTimeStamp(SPEED_MEAS_CAP_handle speedHandle);

/*!
 * @ingroup         SPEED_MEAS_CAP_Set_OldTimeStamp
 * @fn              void SPEED_MEAS_CAP_Set_OldTimeStamp(SPEED_MEAS_CAP_handle speedHandle, uint32_t OldTimeStamp)
 * @brief           Function to Set the Old Timestamp of the Speed Measurement Module
 * @param [in/out]  speedHandle			The Handle for the Speed Measurement Module
 * @param [in]		oldTimeStamp		The new Old Timestamp for the Speed Measurement Module
 */
void SPEED_MEAS_CAP_Set_OldTimeStamp(SPEED_MEAS_CAP_handle speedHandle, uint32_t OldTimeStamp);

/*!
 * @ingroup         SPEED_MEAS_CAP_Get_OldTimeStamp
 * @fn              uint32_t SPEED_MEAS_CAP_Get_OldTimeStamp(SPEED_MEAS_CAP_handle speedHandle)
 * @brief           Function to Get the Old Timestamp for the Speed Measurement Module
 * @param [in]      speedHandle			The Handle for the Speed Measurement Module
 * @return			uint32_t				The Old Timestamp for the Speed Measurement Module
 */
uint32_t SPEED_MEAS_CAP_Get_OldTimeStamp(SPEED_MEAS_CAP_handle speedHandle);

/*!
 * @ingroup         SPEED_MEAS_CAP_Set_CurTimeStamp
 * @fn              void SPEED_MEAS_CAP_Set_CurTimeStamp(SPEED_MEAS_CAP_handle speedHandle, uint32_t CurTimeStamp)
 * @brief           Function to Set the Current Timestamp of the Speed Measurement Module
 * @param [in/out]  speedHandle			The Handle for the Speed Measurement Module
 * @param [in]		curTimeStamp		The new Current Timestamp for the Speed Measurement Module
 */
void SPEED_MEAS_CAP_Set_CurTimeStamp(SPEED_MEAS_CAP_handle speedHandle, uint32_t CurTimeStamp);

/*!
 * @ingroup         SPEED_MEAS_CAP_Get_CurTimeStamp
 * @fn              uint32_t SPEED_MEAS_CAP_Get_CurTimeStamp(SPEED_MEAS_CAP_handle speedHandle)
 * @brief           Function to Get the Current Timestamp for the Speed Measurement Module
 * @param [in]      speedHandle			The Handle for the Speed Measurement Module
 * @return			uint32_t				The Current Timestamp for the Speed Measurement Module
 */
uint32_t SPEED_MEAS_CAP_Get_CurTimeStamp(SPEED_MEAS_CAP_handle speedHandle);

/*!
 * @ingroup         SPEED_MEAS_CAP_Set_SpeedScaler
 * @fn              void SPEED_MEAS_CAP_Set_SpeedScaler(SPEED_MEAS_CAP_handle speedHandle, uint32_t SpeedScaler)
 * @brief           Function to Set the SpeedScaler of the Speed Measurement Module
 * @param [in/out]  speedHandle			The Handle for the Speed Measurement Module
 * @param [in]		speedScaler			The new SpeedScaler for the Speed Measurement Module
 */
void SPEED_MEAS_CAP_Set_SpeedScaler(SPEED_MEAS_CAP_handle speedHandle, uint32_t SpeedScaler);

/*!
 * @ingroup         SPEED_MEAS_CAP_Get_SpeedScaler
 * @fn              uint32_t SPEED_MEAS_CAP_Get_SpeedScaler(SPEED_MEAS_CAP_handle speedHandle)
 * @brief           Function to Get the SpeedScaler for the Speed Measurement Module
 * @param [in]      speedHandle			The Handle for the Speed Measurement Module
 * @return			uint32_t				The SpeedScaler for the Speed Measurement Module
 */
uint32_t SPEED_MEAS_CAP_Get_SpeedScaler(SPEED_MEAS_CAP_handle speedHandle);

/*!
 * @ingroup         SPEED_MEAS_CAP_Set_EventPeriod
 * @fn              void SPEED_MEAS_CAP_Set_EventPeriod(SPEED_MEAS_CAP_handle speedHandle, int32_t EventPeriod)
 * @brief           Function to Set the EventPeriod of the Speed Measurement Module
 * @param [in/out]  speedHandle			The Handle for the Speed Measurement Module
 * @param [in]		eventPeriod			The new EventPeriod for the Speed Measurement Module
 */
void SPEED_MEAS_CAP_Set_EventPeriod(SPEED_MEAS_CAP_handle speedHandle, int32_t EventPeriod);

/*!
 * @ingroup         SPEED_MEAS_CAP_Get_EventPeriod
 * @fn              int32_t SPEED_MEAS_CAP_Get_EventPeriod(SPEED_MEAS_CAP_handle speedHandle)
 * @brief           Function to Get the EventPeriod for the Speed Measurement Module
 * @param [in]      speedHandle			The Handle for the Speed Measurement Module
 * @return			int32_t				The EventPeriod for the Speed Measurement Module
 */
int32_t SPEED_MEAS_CAP_Get_EventPeriod(SPEED_MEAS_CAP_handle speedHandle);

/*!
 * @ingroup         SPEED_MEAS_CAP_Set_InputSelect
 * @fn              void SPEED_MEAS_CAP_Set_InputSelect(SPEED_MEAS_CAP_handle speedHandle, int16_t InputSelect)
 * @brief           Function to Set the InputSelect of the Speed Measurement Module
 * @param [in/out]  speedHandle			The Handle for the Speed Measurement Module
 * @param [in]		inputSelect			The new InputSelect for the Speed Measurement Module
 */
void SPEED_MEAS_CAP_Set_InputSelect(SPEED_MEAS_CAP_handle speedHandle, int16_t InputSelect);

/*!
 * @ingroup         SPEED_MEAS_CAP_Get_InputSelect
 * @fn              int16_t SPEED_MEAS_CAP_Get_InputSelect(SPEED_MEAS_CAP_handle speedHandle)
 * @brief           Function to Get the InputSelect for the Speed Measurement Module
 * @param [in]      speedHandle			The Handle for the Speed Measurement Module
 * @return			int16_t				The InputSelect for the Speed Measurement Module
 */
int16_t SPEED_MEAS_CAP_Get_InputSelect(SPEED_MEAS_CAP_handle speedHandle);

/*!
 * @ingroup         SPEED_MEAS_CAP_Set_Speed_Output
 * @fn              void SPEED_MEAS_CAP_Set_Speed_Output(SPEED_MEAS_CAP_handle speedHandle, float32_t Speed)
 * @brief           Function to Set the Speed of the Speed Measurement Module
 * @param [in/out]  speedHandle			The Handle for the Speed Measurement Module
 * @param [in]		speed				The new Speed for the Speed Measurement Module
 */
void SPEED_MEAS_CAP_Set_Speed_Output(SPEED_MEAS_CAP_handle speedHandle, float32_t Speed);

/*!
 * @ingroup         SPEED_MEAS_CAP_Get_Speed_Output
 * @fn              float32_t SPEED_MEAS_CAP_Get_Speed_Output(SPEED_MEAS_CAP_handle speedHandle)
 * @brief           Function to Get the Speed for the Speed Measurement Module
 * @param [in]      speedHandle			The Handle for the Speed Measurement Module
 * @return			float32_t					The Speed for the Speed Measurement Module
 */
float32_t SPEED_MEAS_CAP_Get_Speed_Output(SPEED_MEAS_CAP_handle speedHandle);

/*!
 * @ingroup         SPEED_MEAS_CAP_Set_BaseRPM
 * @fn              void SPEED_MEAS_CAP_Set_BaseRPM(SPEED_MEAS_CAP_handle speedHandle, uint32_t BaseRPM)
 * @brief           Function to Set the BaseRPM of the Speed Measurement Module
 * @param [in/out]  speedHandle			The Handle for the Speed Measurement Module
 * @param [in]		baseRPM				The new BaseRPM for the Speed Measurement Module
 */
void SPEED_MEAS_CAP_Set_BaseRPM(SPEED_MEAS_CAP_handle speedHandle, uint32_t BaseRPM);

/*!
 * @ingroup         SPEED_MEAS_CAP_Get_BaseRPM
 * @fn              uint32_t SPEED_MEAS_CAP_Get_BaseRPM(SPEED_MEAS_CAP_handle speedHandle)
 * @brief           Function to Get the BaseRPM for the Speed Measurement Module
 * @param [in]      speedHandle			The Handle for the Speed Measurement Module
 * @return			uint32_t				The BaseRPM for the Speed Measurement Module
 */
uint32_t SPEED_MEAS_CAP_Get_BaseRPM(SPEED_MEAS_CAP_handle speedHandle);

/*!
 * @ingroup         SPEED_MEAS_CAP_Set_OutputRPM
 * @fn              void SPEED_MEAS_CAP_Set_OutputRPM(SPEED_MEAS_CAP_handle speedHandle, int32_t SpeedRPM)
 * @brief           Function to Set the SpeedRPM of the Speed Measurement Module
 * @param [in/out]  speedHandle			The Handle for the Speed Measurement Module
 * @param [in]		speedRPM			The new SpeedRPM for the Speed Measurement Module
 */
void SPEED_MEAS_CAP_Set_OutputRPM(SPEED_MEAS_CAP_handle speedHandle, int32_t SpeedRPM);

/*!
 * @ingroup         SPEED_MEAS_CAP_Get_OutputRPM
 * @fn              int32_t SPEED_MEAS_CAP_Get_OutputRPM(SPEED_MEAS_CAP_handle speedHandle)
 * @brief           Function to Get the SpeedRPM for the Speed Measurement Module
 * @param [in]      speedHandle			The Handle for the Speed Measurement Module
 * @return			int32_t				The SpeedRPM for the Speed Measurement Module
 */
int32_t SPEED_MEAS_CAP_Get_OutputRPM(SPEED_MEAS_CAP_handle speedHandle);

/*!
 * @ingroup         SPEED_MEAS_CAP_Calc
 * @fn              void SPEED_MEAS_CAP_Calc(SPEED_MEAS_CAP_handle v)
 * @brief           Function to run teh Speed Measurement Calculation
 * @param [in/out]  v		The Handle for the Speed Measurement Module
 */
inline void SPEED_MEAS_CAP_Calc(SPEED_MEAS_CAP_handle v)
{
    if (v->inputSelect == 0)
    {
        v->oldTimeStamp = v->newTimeStamp;
        v->newTimeStamp = v->curTimeStamp;
        v->eventPeriod = v->newTimeStamp - v->oldTimeStamp;
        if (v->eventPeriod < 0)
            v->eventPeriod += 32767;
    }

    v->speed = ((float32_t)v->speedScaler) / ((float32_t)v->eventPeriod);

    v->speedRPM = v->baseRPM * v->speed;

}

#endif // __SPEED_PR_H__
