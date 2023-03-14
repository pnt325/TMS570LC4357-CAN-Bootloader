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
//! \file   ~/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/rm48l952/src/drv.c
//! \brief  Contains the various functions related to the DRV object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "drv.h"

// **************************************************************************
// the defines


// **************************************************************************
// the globals

DRV_Obj drv;


// **************************************************************************
// the functions

//! \brief     Initializes the driver (DRV) object
//! \param[in] pMemory     A pointer to the memory for the driver object
//! \param[in] numBytes    The number of bytes allocated for the driver object, bytes
//! \param[in] period	   FOC, period
//! \param[in] het_vCNT_SCALE	HET count value for PWM period setup
//! \param[in] commMode    Motor commutation mode
//! \return    The driver (DRV) object handle
DRV_Handle DRV_init(void *pMemory,const size_t numBytes, const float32_t period, const int32_t het_vCNT_SCALE, Commutation_Mode_t commMode)
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


	// initialize rampgen handle
	drv->rampgenHandle = RAMPGEN_init(&drv->rampgen,sizeof(drv->rampgen));

	// initialize QEP HET Count handle
	drv->qepHETHandle = QEP_HET_init((void *) &(hetRAM1->Instruction[QEP_COUNT_HET_OFFSET]),sizeof(drv->qepHETObj));

	// initialize QEP HET Index handle
	drv->qepIndexHandle = QEP_HET_init((void *) &(hetRAM1->Instruction[QEP_INDEX_HET_OFFSET]),sizeof(drv->qepIndexObj));

	// initialize QEP handle
	drv->qepHandle = QEP_init((void *)&drv->qepObj, sizeof(drv->qepObj), 1000, 4, 0, -1);

	// init the speed_fr module
	drv->speed_frHandle = SPEED_FR_init( (void*) &drv->speed_fr, sizeof(drv->speed_fr));

	// initialize the CTRL handle
	drv->ctrlHandle = CTRL_init(&drv->ctrl,sizeof(drv->ctrl), period);

	// init the speed_est module
	drv->speed_estHandle = SPEED_EST_init( (void*) &drv->speed_est, sizeof(drv->speed_est));

	// initialize connection between the CTRL and PWM modules
	drv->gPwmData.Tabc.value[0] = 0;
	drv->gPwmData.Tabc.value[1] = 0;
	drv->gPwmData.Tabc.value[2] = 0;

	// initialize pwm module
	drv->pwmHandle[0] = PWM_init((void *) &(hetRAM1->Instruction[PWMA_HET_OFFSET]),sizeof(PWM_Obj));
	drv->pwmHandle[1] = PWM_init((void *) &(hetRAM1->Instruction[PWMB_HET_OFFSET]),sizeof(PWM_Obj));
	drv->pwmHandle[2] = PWM_init((void *) &(hetRAM1->Instruction[PWMC_HET_OFFSET]),sizeof(PWM_Obj));

	drv->pwmSyncHandle = PWM_SYNC_init((void *) &(hetRAM1->Instruction[PWM_SYNC_HET_OFFSET]),sizeof(PWM_SYNC_Obj));

	// initialize the SMOPOS handle
	drv->smoPosHandle = SMO_POS_init((void *)&drv->smoPos, sizeof(drv->smoPos), 0.36, 0.0002, 38.29, 10.3125, period);

	// initialize the VOLTCALC handle
	drv->voltCalcHandle = VOLT_CALC_init((void *)&drv->voltCalc , sizeof(drv->voltCalc));

	// Setup drv object
	DRV_setup(drvHandle, commMode, period, het_vCNT_SCALE);

	return(drvHandle);
} // end of DRV_init() function


//! \brief     Setup the driver module to default values
//! \param[in] handle  	   		The driver (DRV) handle
//! \param[in] commMode    		Motor commutation mode
//! \param[in] period	   		FOC, period
//! \param[in] het_vCNT_SCALE	HET count value for PWM period setup
void DRV_setup(DRV_Handle handle, Commutation_Mode_t ecMode, const float32_t ISRperiod, const int32_t het_vCNT_SCALE)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	// Setup commutation mode
	drv->commutationMode  = ecMode;

	// Setup PWM period
	drv->PWMPeriod = (128*(ISRperiod*het_vCNT_SCALE + 1));

	// Setup current calibration constants
	drv->cal_offset_A = 0x7FF0;
	drv->cal_offset_B = 0x7FF0;
	drv->adc_current_gain_A = 0.0000305176;
	drv->adc_current_gain_B = 0.0000305176;


	// Setup rampgen module
	RAMPGEN_setup(drv->rampgenHandle, 0.0 , (100 * ISRperiod), 0.0, 1.0, 1.0);

	// Setup speed_fr module
	SPEED_FR_setup(drv->speed_frHandle, ISRperiod, 230, 4, (2 * MATH_PI * 100) );

	// setup speed_est module
	SPEED_EST_setup(drv->speed_estHandle, ISRperiod, 230, 4, (2 * MATH_PI * 100), 0.8, 0.2);

	// Setup encoder-smo switch over speed threshold
	drv->SwitchOverSpdFwd = 0.25;
	drv->SwitchOverSpdRev = 0.17;

	// Setup index pulse counter
	drv->newIndexValue = QEP_Read_Index(drv->qepIndexHandle);
	drv->prevIndexValue = drv->newIndexValue;
	drv->indexFoundFlag = 0;
	drv->firstIndexEvaluation = 0;

	// Setup fault timer for encoder fault detection
	drv->spdFaultThreshold = 0.08;
	drv->encoderFaultTripTime = 0.5/ISRperiod;	// Ticks corresponding to (500 ms)

	// Initialize control type tracking variables
	drv->prevCtrlType = DISABLED;
	drv->currCtrlType = DISABLED;

	// Initialize gate driver
	drv->gdFaultStatus = 0;
	drv->bridgeFaultFlg = 0;
	drv->overVoltageFlg = 0;
	drv->overTempFlg = 0;
	drv->firstFaultRstEval = 0;
	drv->faultDisableFlag = 0;

	// Initialize benchmark timer
	drv->rtiCounterValue = 0;
	drv->rtiBenchmarkTime = 0;



}


// end of file
