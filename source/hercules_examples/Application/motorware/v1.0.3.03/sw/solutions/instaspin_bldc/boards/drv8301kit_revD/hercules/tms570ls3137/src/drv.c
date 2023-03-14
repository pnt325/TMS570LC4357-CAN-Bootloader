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
//! \file   ~/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/tms570ls3137/src/drv.c
//! \brief  Contains the various functions related to the DRV object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/tms570ls3137/src/drv.h"

// **************************************************************************
// the defines


// **************************************************************************
// the globals

DRV_Obj drv;
MOD6CNT gMod6;
RMP3 gRMP3;
SPEED_MEAS_CAP gSpeed;
INSTASPIN_BLDC gInstaSPIN;
IMPULSE gImpulse;
PID_Obj gPIDSpd;
PID_Obj gPIDIDC;
RMPCNTL_Obj gRMPCntl;
STATEFILTER gStateFilter;


// **************************************************************************
// the functions

//! \brief     Initializes the driver (DRV) object
//! \param[in] pMemory     A pointer to the memory for the driver object
//! \param[in] numBytes    The number of bytes allocated for the driver object, bytes
//! \param[in] period	   interrupt period
//! \return    The driver (DRV) object handle
DRV_Handle DRV_init(void *pMemory,const size_t numBytes, const float32_t period)
{
	DRV_Handle drvHandle;
	DRV_Obj *drv;

	if(numBytes < sizeof(DRV_Obj))
	return((DRV_Handle)NULL);

	// assign the handle
	drvHandle = (DRV_Handle)pMemory;

	// assign the object
	drv = (DRV_Obj *)drvHandle;

	// Initializations
	gioInit();	//Initialize GIO module
	adcInit();	//Initialize ADC module
	rtiInit();	//Initialize RTI module

	// initialize the HET
	hetInit();

	//delay 50ms while HET starts up
	rtiResetCounter(rtiCOUNTER_BLOCK0);
	rtiStartCounter(rtiCOUNTER_BLOCK0);
	while(rtiGetCurrentTick(rtiCOMPARE0) < 50000);
	rtiStopCounter(rtiCOUNTER_BLOCK0);

	// Set IO to enable DRV8301
	gioSetDirection(gioPORTA, 0x00000010U);
	gioSetBit(gioPORTA, 4, 1);

	//delay 50ms while DRV8301 powers up
	rtiResetCounter(rtiCOUNTER_BLOCK0);
	rtiStartCounter(rtiCOUNTER_BLOCK0);
	while(rtiGetCurrentTick(rtiCOMPARE0) < 50000);
	rtiStopCounter(rtiCOUNTER_BLOCK0);

	// initialize connection between the CTRL and PWM modules
	drv->gPwmData.Tabc.value[0] = 0;
	drv->gPwmData.Tabc.value[1] = 0;
	drv->gPwmData.Tabc.value[2] = 0;

	// initialize pwm module
	drv->pwmHandle[0] = PWM_init((void *) &(hetRAM1->Instruction[APWMH_HET_OFFSET]),sizeof(PWM_Obj));
	drv->pwmHandle[1] = PWM_init((void *) &(hetRAM1->Instruction[APWML_HET_OFFSET]),sizeof(PWM_Obj));
	drv->pwmHandle[2] = PWM_init((void *) &(hetRAM1->Instruction[BPWMH_HET_OFFSET]),sizeof(PWM_Obj));
	drv->pwmHandle[3] = PWM_init((void *) &(hetRAM1->Instruction[BPWML_HET_OFFSET]),sizeof(PWM_Obj));
	drv->pwmHandle[4] = PWM_init((void *) &(hetRAM1->Instruction[CPWMH_HET_OFFSET]),sizeof(PWM_Obj));
	drv->pwmHandle[5] = PWM_init((void *) &(hetRAM1->Instruction[CPWML_HET_OFFSET]),sizeof(PWM_Obj));

	drv->pwmSyncHandle = PWM_SYNC_init((void *) &(hetRAM1->Instruction[PWM_SYNC_HET_OFFSET]),sizeof(PWM_SYNC_Obj));

	drv->pwmISync = PWM_init((void *) &(hetRAM1->Instruction[PWM_SYNC_CURRENT]),sizeof(PWM_Obj));

	// Setup drv object
	DRV_setup(drvHandle, period);

	return(drvHandle);
} // end of DRV_init() function


//! \brief     Setup the driver module to default values
//! \param[in] handle  	   The driver (DRV) handle
//! \param[in] period	   FOC, period
void DRV_setup(DRV_Handle handle, const float32_t period)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

//	// Setup current calibration constants
	drv->cal_offset_A = 0x7FF0;
	drv->cal_offset_B = 0x7FF0;

	drv->ref = 0.3;
	drv->currentDisplay = 0.0;
	drv->dFuncStartup = 0.1;
	drv->currentStartup = 0.1;
	drv->threshold = 0.10;
	drv->currentKp = 0.08982;
	drv->velocityKp = 0.75;
	drv->iMax = 0.95;
	drv->rampUpTime = 25;
	drv->commErrorMax = 1.0;
	drv->tripCnt = 3;
	drv->advancedStartup = 0;

	drv->speedRPM = 0;
	drv->beginStartRPM = 50;
	drv->endStartRPM = 100;

	drv->currentMode = 0;
	drv->velocityMode = 0;
	drv->controlMode = drv->currentMode + drv->velocityMode;
	drv->resetFault = 0;
	drv->poles = 8;
	drv->currentKi = 100;
	drv->velocityKi = 3;
	drv->currentKd = 0;
	drv->velocityKd = 0;
	drv->prescaler = 1;
	drv->runBLDCInt = 0;
	drv->overVoltage = 0;
	drv->drvFaultFlag = 0;
	drv->drvOTWFlag = 0;
	drv->enableFlag = FALSE;
	drv->vDCBus = 0;
	drv->maxVDC = 2880; //1302
	drv->minVDC = 1920;
	drv->floatCounter = 0.0;

	drv->baseFreq =  200;			// Base electrical frequency (Hz)
	drv->rampStartRate = (PWM_FREQUENCY*1000)*60.0/drv->beginStartRPM/COMMUTATES_PER_E_REV/(drv->poles/2.0);
	drv->rampEndRate = (PWM_FREQUENCY*1000)*60.0/drv->endStartRPM/COMMUTATES_PER_E_REV/(drv->poles/2.0);
	drv->cmtnPeriodTarget = drv->rampEndRate;
	drv->cmtnPeriodSetpt = drv->rampStartRate;

	drv->virtualTimer = 0;
	drv->speedLoopFlag = FALSE;
	drv->rampDelay = 1;
	drv->speedRef= 0.0;
	drv->iDCOffset = 0.5;
	drv->iRef = 0.0;
	drv->isrTicker = 0;
	drv->calibrateFlag = 0;
	drv->calibrateTime = 0x7FFF;
	drv->dLogCurrElementIndex = 0;
	drv->bemfTrigCnt = 0;
	drv->bemfLastTrigCnt = 0;
	drv->goodTrigCnt = 0;
	drv->goodTrigCntTrip = 20;
	drv->closedCommutationFlag = 0;

	drv->mod6Handle = &gMod6;
	drv->rmp3Handle = &gRMP3;
	drv->impulseHandle = &gImpulse;
	drv->pidSpdHandle = &gPIDSpd;
	drv->pidIDCHandle = &gPIDIDC;
	drv->instaHandle = &gInstaSPIN;
	drv->speedHandle = &gSpeed;
	drv->rmpCntlHandle = &gRMPCntl;
	drv->instaHandle->stateFilter = &gStateFilter;


	MOD6CNT_Setup(drv->mod6Handle);

	PID_setGains(drv->pidIDCHandle, drv->currentKp, (drv->currentKi * T), (drv->currentKd / T));
	PID_setMinMax(drv->pidIDCHandle, -0.95, 0.95);

	PID_setGains(drv->pidSpdHandle, drv->velocityKp, (drv->velocityKi * T), (drv->velocityKd / T));
	PID_setMinMax(drv->pidSpdHandle, -0.71, 0.71);

	RMP3_Setup(drv->rmp3Handle);
	IMPULSE_Setup(drv->impulseHandle);
	INSTASPIN_Setup(drv->instaHandle);
	SPEED_MEAS_CAP_Setup(drv->speedHandle);
	RMPCNTL_Setup(drv->rmpCntlHandle);

	// Initialize the SPEED_PR module
	drv->speedHandle->inputSelect = 0;
	drv->speedHandle->baseRPM = 120*(drv->baseFreq / drv->poles);
	drv->speedHandle->speedScaler = (uint32_t)(PWM_FREQUENCY / (1 * (float32_t)drv->baseFreq * 0.001));
	SPEED_MEAS_CAP_Calc(drv->speedHandle);

	// Initialize RMPCNTL module
	drv->rmpCntlHandle->rampDelayMax = 1;
	drv->rmpCntlHandle->rampLowLimit = -1.0;
	drv->rmpCntlHandle->rampHighLimit = 1.0;
	RMPCNTL_Calc(drv->rmpCntlHandle);

	// Initialize RMP3 module
	drv->rmp3Handle->desiredInput = drv->cmtnPeriodTarget;
	drv->rmp3Handle->ramp3Delay = (uint32_t)(((float32_t)drv->rampUpTime * 0.001)/((float32_t)(drv->cmtnPeriodSetpt - drv->cmtnPeriodTarget) * T));
	drv->rmp3Handle->out = drv->cmtnPeriodSetpt;
	drv->rmp3Handle->ramp3Min = drv->cmtnPeriodTarget;
	RMP3_Calc(drv->rmp3Handle);

	//Initialize the INSTASPIN_BLDC module
	drv->instaHandle->vaOffset = 0;
	drv->instaHandle->vbOffset = 0;
	drv->instaHandle->vcOffset = 0;
	drv->instaHandle->intThreshold = drv->threshold;

	drv->pidIDCHandle->refValue = drv->ref;
	drv->pidSpdHandle->refValue = drv->ref;

	// Initialize the current offset calibration filter
	drv->calFiltGain = (T / (T + TC_CAL));
	drv->spdFiltGain = (T / (T + TC_SPD));


}


// end of file
