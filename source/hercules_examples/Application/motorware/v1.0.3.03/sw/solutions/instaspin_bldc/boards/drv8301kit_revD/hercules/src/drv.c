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
//! \file   ~/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/tms570ls1227/src/drv.c
//! \brief  Contains the various functions related to the DRV object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/src/drv.h"
#include "solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/src/gui.h"

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
ECMP_Obj gECMP;


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
	spiInit();  //Initialize SPI module
	adcInit();	//Initialize ADC module
	rtiInit();	//Initialize RTI module

	//delay 50ms while HET starts up
	rtiResetCounter(rtiCOUNTER_BLOCK0);
	rtiStartCounter(rtiCOUNTER_BLOCK0);
	while(rtiGetCurrentTick(rtiCOMPARE0) < 50000);
	rtiStopCounter(rtiCOUNTER_BLOCK0);

	drv->ecmpHandle = ECMPInit(&gECMP, sizeof(gECMP));
	ECMPSetup(drv->ecmpHandle);
	(*(volatile unsigned int *)(0xFFFFFF0C))=1;
	(*(volatile unsigned int *)(0xFFFFFF04))=1;
	/* avoid TPS65381 to transit to ACTIVE operating state */
	while(!ecmpStayinDIAGState(drv->ecmpHandle));
	// while(wait); /* set cursor to next line to continue - prevents reset chain */
	while(!ecmpGetWriteAccess(drv->ecmpHandle));
	sciInit();
	if(ecmpReadRegister(drv->ecmpHandle, RD_SAFETY_STAT5) == 0x04)
	{
		PutText(drv->ecmpHandle, "TPS65381 is NOT in DIAG state, toggle IGN!\n\r");
	    while(1);
	}
	PutText(drv->ecmpHandle, "1 - Enable Watchdog\n\r");
	PutText(drv->ecmpHandle, "2 - Enable Motor\n\r");
	PutText(drv->ecmpHandle, "3 - Start Motor in Duty Cycle Mode\n\r");
	PutText(drv->ecmpHandle, "4 - Start Motor in Current Mode\n\r");
	PutText(drv->ecmpHandle, "5 - Start Motor in Velocity Mode\n\r");
	PutText(drv->ecmpHandle, "6 - Start Motor in Cascade (Current + Velocity) Mode\n\r");
	PutText(drv->ecmpHandle, "7 - Stop Motor\n\r");
	PutText(drv->ecmpHandle, "8 - Toggle Watchdog Diagnostics Flag\n\r");

	//delay 50ms
	rtiResetCounter(rtiCOUNTER_BLOCK0);
	rtiStartCounter(rtiCOUNTER_BLOCK0);
	while(rtiGetCurrentTick(rtiCOMPARE0) < 500000);
	rtiStopCounter(rtiCOUNTER_BLOCK0);

	// Set IO to enable DRV8301
	gioSetDirection(gioPORTA, 0x00000010U);
	gioSetBit(gioPORTA, 4, 1);

	//wait until a command from HyperTermal to force the TPS65381 device into active mode
	while((GetChar(drv->ecmpHandle)!='1') && (!gGUIObj.TPSFlag));

	PutText(drv->ecmpHandle, "Start Watchdog\r\n");
	//delay 50ms
	rtiResetCounter(rtiCOUNTER_BLOCK0);
	rtiStartCounter(rtiCOUNTER_BLOCK0);
	while(rtiGetCurrentTick(rtiCOMPARE0) < 500000);
	rtiStopCounter(rtiCOUNTER_BLOCK0);
	/* select desired WD mode - time in mu seconds */
	ecmpWdQaInit(drv->ecmpHandle, 45000, 18000);
	ecmpWdStart(drv->ecmpHandle);
	//delay 50ms
	rtiResetCounter(rtiCOUNTER_BLOCK0);
	rtiStartCounter(rtiCOUNTER_BLOCK0);
	while(rtiGetCurrentTick(rtiCOMPARE0) < 500000);
	rtiStopCounter(rtiCOUNTER_BLOCK0);
	while(gioGetBit(gioPORTA, 4)==0);


	(*(volatile unsigned int *)(0xFFFFFF0C))=0;
	//delay 50ms while DRV8301 powers up
	rtiResetCounter(rtiCOUNTER_BLOCK0);
	rtiStartCounter(rtiCOUNTER_BLOCK0);
	while(rtiGetCurrentTick(rtiCOMPARE0) < 500000);
	rtiStopCounter(rtiCOUNTER_BLOCK0);
	drv->ecmpHandle->DiagFlag = 0;
	// initialize connection between the CTRL and PWM modules
	drv->gPwmData.Tabc.value[0] = 0;
	drv->gPwmData.Tabc.value[1] = 0;
	drv->gPwmData.Tabc.value[2] = 0;

	// initialize pwm module
	drv->pwmHandle[0] = PWM_init((void *)PWM_ePWM2_BASE_ADDR,sizeof(PWM_Obj));
	drv->pwmHandle[1] = PWM_init((void *)PWM_ePWM3_BASE_ADDR,sizeof(PWM_Obj));
	drv->pwmHandle[2] = PWM_init((void *)PWM_ePWM4_BASE_ADDR,sizeof(PWM_Obj));

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

	// setup the PWMs
	DRV_setupPwms(handle, T, vCNT_SCALE);

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
	drv->ecmpHandle = &gECMP;


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

//void DRV_setupPwms(DRV_Handle handle,const uint_least16_t systemFreq_MHz,const float32_t pwmPeriod_usec)
void DRV_setupPwms(DRV_Handle handle, const float32_t ISRperiod, const int32_t het_vCNT_SCALE)
{
  DRV_Obj   *obj = (DRV_Obj *)handle;
  uint16_t   halfPeriod_cycles = ((ISRperiod*het_vCNT_SCALE)/2)*128;
  uint8_t    cnt;

	PWM_setOneShotTrip(obj->pwmHandle[0]);// Disable PWM A leg
	PWM_setOneShotTrip(obj->pwmHandle[1]);// Disable PWM B leg
	PWM_setOneShotTrip(obj->pwmHandle[2]);// Disable PWM C leg

  for(cnt=0;cnt<3;cnt++)
    {
      // setup the Time-Base Control Register (TBCTL)
      PWM_setCounterMode(obj->pwmHandle[cnt],PWM_CounterMode_UpDown);
      PWM_disableCounterLoad(obj->pwmHandle[cnt]);
      PWM_setPeriodLoad(obj->pwmHandle[cnt],PWM_PeriodLoad_Immediate);
      PWM_setSyncMode(obj->pwmHandle[cnt],PWM_SyncMode_EPWMxSYNC);
      PWM_setHighSpeedClkDiv(obj->pwmHandle[cnt],PWM_HspClkDiv_by_1);
      PWM_setClkDiv(obj->pwmHandle[cnt],PWM_ClkDiv_by_1);
      PWM_setPhaseDir(obj->pwmHandle[cnt],PWM_PhaseDir_CountUp);
      PWM_setRunMode(obj->pwmHandle[cnt],PWM_RunMode_FreeRun);

      // setup the Timer-Based Phase Register (TBPHS)
      PWM_setPhase(obj->pwmHandle[cnt],0);

      // setup the Time-Base Counter Register (TBCTR)
      PWM_setCount(obj->pwmHandle[cnt],0);

      // setup the Time-Base Period Register (TBPRD)
      // set to zero initially
      PWM_setPeriod(obj->pwmHandle[cnt],0);

      // setup the Counter-Compare Control Register (CMPCTL)
      PWM_setLoadMode_CmpA(obj->pwmHandle[cnt],PWM_LoadMode_Zero);
      PWM_setLoadMode_CmpB(obj->pwmHandle[cnt],PWM_LoadMode_Zero);
      PWM_setShadowMode_CmpA(obj->pwmHandle[cnt],PWM_ShadowMode_Shadow);
      PWM_setShadowMode_CmpB(obj->pwmHandle[cnt],PWM_ShadowMode_Shadow);

      // setup the Action-Qualifier Output A Register (AQCTLA)
      PWM_setActionQual_CntUp_CmpA_PwmA(obj->pwmHandle[cnt],PWM_ActionQual_Set);
      PWM_setActionQual_CntDown_CmpA_PwmA(obj->pwmHandle[cnt],PWM_ActionQual_Clear);

      // setup the Dead-Band Generator Control Register (DBCTL)
      PWM_setDeadBandOutputMode(obj->pwmHandle[cnt],PWM_DeadBandOutputMode_EPWMxA_Rising_EPWMxB_Falling);
      PWM_setDeadBandPolarity(obj->pwmHandle[cnt],PWM_DeadBandPolarity_EPWMxB_Inverted);

      // setup the Dead-Band Rising Edge Delay Register (DBRED)
      PWM_setDeadBandRisingEdgeDelay(obj->pwmHandle[cnt],DRV_PWM_DBRED_CNT);

      // setup the Dead-Band Falling Edge Delay Register (DBFED)
      PWM_setDeadBandFallingEdgeDelay(obj->pwmHandle[cnt],DRV_PWM_DBFED_CNT);
      // setup the PWM-Chopper Control Register (PCCTL)
      PWM_disableChopping(obj->pwmHandle[cnt]);

      // setup the Trip Zone Select Register (TZSEL)
      PWM_disableTripZones(obj->pwmHandle[cnt]);
    }


  // setup the Event Trigger Selection Register (ETSEL)
  PWM_disableInt(obj->pwmHandle[0]);
  PWM_setSocAPulseSrc(obj->pwmHandle[0],PWM_SocPulseSrc_CounterEqualZero);
  PWM_enableSocAPulse(obj->pwmHandle[0]);


  // setup the Event Trigger Prescale Register (ETPS)
  PWM_setSocAPeriod(obj->pwmHandle[0],PWM_SocPeriod_FirstEvent);


  // setup the Event Trigger Clear Register (ETCLR)
  PWM_clearIntFlag(obj->pwmHandle[0]);
  PWM_clearSocAFlag(obj->pwmHandle[0]);


  // since the PWM is configured as an up/down counter, the period register is set to one-half
  // of the desired PWM period
  PWM_setPeriod(obj->pwmHandle[0],halfPeriod_cycles);
  PWM_setPeriod(obj->pwmHandle[1],halfPeriod_cycles);
  PWM_setPeriod(obj->pwmHandle[2],halfPeriod_cycles);

  return;
}  // end of DRV_setupPwms() function


// end of file
