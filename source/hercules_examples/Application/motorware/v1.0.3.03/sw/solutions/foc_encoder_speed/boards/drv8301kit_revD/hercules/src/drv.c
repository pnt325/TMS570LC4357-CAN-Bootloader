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
//! \file   ~/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/src/drv.c
//! \brief  Contains the various functions related to the DRV object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "drv.h"
#include "solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/gui.h"

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
	spiInit();  //Initialize SPI module
	adcInit();	//Initialize ADC module
	rtiInit();	//Initialize RTI module


	drv->ecmpHandle = ECMPInit(&drv->ecmpObj, sizeof(drv->ecmpObj));
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
	PutText(drv->ecmpHandle, "3 - Start calibration\n\r");
	PutText(drv->ecmpHandle, "4 - Disable calibration\n\r");
	PutText(drv->ecmpHandle, "5 - Go to speed mode\n\r");
	PutText(drv->ecmpHandle, "6 - Set speed to 0.5\n\r");
	PutText(drv->ecmpHandle, "7 - Set speed to 0\n\r");
	PutText(drv->ecmpHandle, "8 - Toggle Watchdog Diagnostics Flag\n\r");

	//delay 50ms
	rtiResetCounter(rtiCOUNTER_BLOCK0);
	rtiStartCounter(rtiCOUNTER_BLOCK0);
	while(rtiGetCurrentTick(rtiCOMPARE0) < 50000);
	rtiStopCounter(rtiCOUNTER_BLOCK0);

	// Set IO to enable DRV8301
	gioSetDirection(gioPORTA, 0x00000010U);
	gioSetBit(gioPORTA, 4, 1);

	//wait until a command from HyperTermal to force the TPS65381 device into active mode
	//later change to GUI update
	while((GetChar(drv->ecmpHandle)!='1') && (!gGUIObj.TPSFlag));

	PutText(drv->ecmpHandle, "Start Watchdog\r\n");
	/* select desired WD mode - time in mu seconds */
	ecmpWdQaInit(drv->ecmpHandle, 45000, 18000);
	ecmpWdStart(drv->ecmpHandle);
	while(gioGetBit(gioPORTA, 4)==0);


	(*(volatile unsigned int *)(0xFFFFFF0C))=0;
	//delay 50ms while DRV8301 powers up
	rtiResetCounter(rtiCOUNTER_BLOCK0);
	rtiStartCounter(rtiCOUNTER_BLOCK0);
	while(rtiGetCurrentTick(rtiCOMPARE0) < 500000);
	rtiStopCounter(rtiCOUNTER_BLOCK0);
	drv->ecmpHandle->DiagFlag = 0;
	// initialize rampgen handle
	drv->rampgenHandle = RAMPGEN_init(&drv->rampgen,sizeof(drv->rampgen));

	// initialize QEP handle
	drv->qepHandle = QEP_init((void *)QEP_BASE_ADDR2, sizeof(QEP_Obj));

	// initialize ENC handle
	drv->encHandle = ENC_init((void *)&drv->encObj, sizeof(drv->encObj), 1000, 4, 0, 1);

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
	drv->pwmHandle[0] = PWM_init((void *)PWM_ePWM2_BASE_ADDR,sizeof(PWM_Obj));
	drv->pwmHandle[1] = PWM_init((void *)PWM_ePWM3_BASE_ADDR,sizeof(PWM_Obj));
	drv->pwmHandle[2] = PWM_init((void *)PWM_ePWM4_BASE_ADDR,sizeof(PWM_Obj));

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

	// setup the PWMs
	DRV_setupPwms(handle, ISRperiod, het_vCNT_SCALE);

	// setup the QEP
	DRV_setupEQep(handle);

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
	drv->newIndexValue = 0;
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


//void DRV_setupPwms(DRV_Handle handle,const uint_least16_t systemFreq_MHz,const float32_t pwmPeriod_usec)
void DRV_setupPwms(DRV_Handle handle, const float32_t ISRperiod, const int32_t het_vCNT_SCALE)
{
  DRV_Obj   *obj = (DRV_Obj *)handle;
  uint16_t   halfPeriod_cycles = ((ISRperiod*het_vCNT_SCALE)/2)*128;
  uint8_t    cnt;

  PWM_setOneShotTrip(obj->pwmHandle[0]); // Disable PWM A Leg
  PWM_setOneShotTrip(obj->pwmHandle[1]); // Disable PWM A Leg
  PWM_setOneShotTrip(obj->pwmHandle[2]); // Disable PWM A Leg

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
      PWM_setDeadBandOutputMode(obj->pwmHandle[cnt],PWM_DeadBandOutputMode_Bypass);
      PWM_setDeadBandPolarity(obj->pwmHandle[cnt],PWM_DeadBandPolarity_EPWMxA_EPWMxB);

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


//! \brief     Sets up the eQEP (enhanced encoder module)
//! \param[in] handle          The driver (DRV) handle
void DRV_setupEQep(DRV_Handle handle)
{
  DRV_Obj   *obj = (DRV_Obj *)handle;

  // setup the EQEP Decode Control Register (QDECCTL)
  QEP_clear_decode_control(obj->qepHandle);
  QEP_set_QEP_source(obj->qepHandle,QEP_Qsrc_Quad_Count_Mode);
  QEP_set_ext_clock_rate(obj->qepHandle,QEP_Xcr_2x_Res);
  QEP_set_A_polarity(obj->qepHandle,QEP_Qap_No_Effect);
  QEP_set_B_polarity(obj->qepHandle,QEP_Qbp_No_Effect);
  QEP_set_index_polarity(obj->qepHandle,QEP_Qip_Inverted);


  // setup the EQEP Control Register (QEPCTL)
  QEP_clear_qep_control(obj->qepHandle);
  QEP_set_emu_control(obj->qepHandle,QEPCTL_Freesoft_Unaffected_Halt);
  QEP_set_posn_count_reset_mode(obj->qepHandle,QEPCTL_Pcrm_Index_Reset);
  QEP_set_index_event_init(obj->qepHandle, QEPCTL_Iei_Rising_Falling_Edge_Init);
  QEP_set_index_event_latch(obj->qepHandle, QEPCTL_Iel_Falling_Edge);
  QEP_enable_counter(obj->qepHandle);
  QEP_set_capture_latch_mode(obj->qepHandle,QEPCTL_Qclm_Latch_on_Unit_Timeout);
  QEP_enable_unit_timer(obj->qepHandle);

  // setup the EQEP Position-Compare Control Register
  QEP_disable_posn_compare(obj->qepHandle);

  // setup the EQEP qual period register (QUPRD)
  QEP_set_unit_period(obj->qepHandle, 800000);

  // setup the EQEP Capture Control Register (QCAPCTL)
  QEP_clear_cap_control(obj->qepHandle);
  QEP_set_unit_posn_prescale(obj->qepHandle,QCAPCTL_Upps_Div_32_Prescale);
  QEP_set_capture_prescale(obj->qepHandle,QCAPCTL_Ccps_Capture_Div_128);
  QEP_enable_capture(obj->qepHandle);

  // setupt the EQEP max count register (QPOSMAX);
  QEP_clear_posn_counter(obj->qepHandle);
  QEP_set_max_posn_count(obj->qepHandle, 4000);

  // Clear the index interrupt for calibration
  QEP_clear_interrupt_flag(obj->qepHandle, QEINT_Iel);

  return;
}  // end of DRV_setupEQep() function

// end of file
