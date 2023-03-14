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
#ifndef _DRV_H_
#define _DRV_H_

//! \file   ~/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/tms570ls1227/src/drv.h
//! \brief  Contains public interface to various functions related
//!         to the DRV object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.

// **************************************************************************
// the includes

// **************************************************************************
// the modules
#include "modules/types/src/32b/controller_data_types.h"
#include "modules/instaspin_bldc/src/float32/hercules/champion/InstaSPIN_BLDC.h"
#include "modules/mod6/src/float32/hercules/mod6_cnt.h"
#include "modules/rmp3/src/float32/hercules/rmp3cntl.h"
#include "modules/speed_pr/src/float32/hercules/speed_pr.h"
#include "modules/impulse/src/float32/hercules/impulse.h"
#include "modules/rmpcntl/src/float32/hercules/rmp_cntl.h"
#include "modules/dlog/src/float32/hercules/DLOG.h"
#include "modules/pid/src/float32/hercules/pid.h"
#include "modules/ecmp/src/float32/champion/ecmp.h"

// **************************************************************************
// the drivers

#include "drivers/gio/src/32b/hercules/champion/gio.h"
#include "drivers/adc/adc_bldc/src/32b/hercules/champion/adc.h"
#include "drivers/rti/src/32b/hercules/champion/rti.h"
#include "drivers/pwm/pwm_bldc/src/32b/hercules/champion/epwm.h"
#include "drivers/het/pwm_bldc/src/32b/hercules/champion/het.h"
#include "drivers/spi/src/32b/hercules/champion/spi.h"



//!
//! \defgroup DRV

//!
//! \ingroup DRV
//@{

#ifdef __cplusplus
extern "C"
{
#endif

// **************************************************************************
// the defines


#define VOLTAGE         0           //open-loop volage mode only
#define CURRENT         1           //closed-loop current control
#define VELOCITY        2           //closed-loop velocity control
#define CASCADE         3           //cascaded closed-loop velocity->current control
#define DISABLED		4			//disabled mode, all PWMs off
#define fs              20000.0		//Interrupt
#define PWM_FREQUENCY   20			//PWM Frequency
#define COMMUTATES_PER_E_REV 6.0	//Commutations per electrical revolution
#define T               1.0/fs		//Interrupt period
#define WC_CAL          100.0		//Calibration filter cutoff
#define TC_CAL          1/WC_CAL	//Time constant for cutoff
#define WC_SPD  1200.0				//Cutoff for speed display filter
#define TC_SPD  1/WC_SPD			//Time constant for speed display filter
#define vCNT_SCALE 	610000			//scaling constant based on system clock divided by 128

// HET States for PWM logic
#define ALL_PHASES_OFF	0x401BA000
#define PHASE_A_OFF		0x401BA550
#define PHASE_B_OFF		0x401BA505
#define PHASE_C_OFF		0x401BA055

//! \brief Defines the PWM deadband falling edge delay count (system clocks)
//!
#define DRV_PWM_DBFED_CNT         10        //


//! \brief Defines the PWM deadband rising edge delay count (system clocks)
//!
#define DRV_PWM_DBRED_CNT         10        //

// **************************************************************************
// the typedefs


//! \brief Defines the PWM data
//!
typedef struct _DRV_PwmData_t_
{
    MATH_vec3 Tabc;      //!< the PWM time-durations for each motor phase

} DRV_PwmData_t;

//! \brief Defines the driver (DRV) object
//!
typedef struct _DRV_Obj_
{
    //PWM_Handle 			pwmISync;

    PWM_Handle 			pwmHandle[3];

    //PWM_SYNC_Handle 	pwmSyncHandle;

    float32_t 			currentSync;

    uint32_t 			hetIOstate;

    DRV_PwmData_t 		gPwmData;

    ADC_Data_t 			adcData;
    adcData_t 			AdcResults1[16];
    adcData_t 			AdcResults2[16];

    int32_t 			cal_offset_A;
    int32_t 			cal_offset_B;

    float32_t 			iqVaIn;
    float32_t 			iqVbIn;
    float32_t 			iqVcIn;
    float32_t 			iDCFdbk;

    uint32_t 			rtiCounterValue;
    float32_t 			rtiBenchmarkTime;

    uint32_t			gdFaultStatus;
    uint32_t			bridgeFaultFlg;
    uint32_t			overVoltageFlg;
    uint32_t			overTempFlg;
    uint32_t			firstFaultRstEval;
    uint32_t			faultDisableFlag;

    H_MOD6CNT 			mod6Handle;
    RMP3_handle 		rmp3Handle;
    SPEED_MEAS_CAP_handle speedHandle;
    H_INSTASPIN_BLDC 	instaHandle;
    IMPULSE_handle 		impulseHandle;
    PID_Handle 			pidSpdHandle;
    PID_Handle 			pidIDCHandle;
    RMPCNTL_handle 		rmpCntlHandle;
    ECMP_handle			ecmpHandle;

    int8_t				SCI_Command;
    int32_t				ADC_INT_ENA;
    int32_t				Process_WDA;
    uint16_t			SPI3_RXDATA[4];

    int32_t 			isrTicker;
    uint32_t 			virtualTimer;
    uint16_t 			previousState;
    uint16_t 			speedLoopFlag;
    uint32_t 			cmtnPeriodTarget;
    uint32_t 			cmtnPeriodSetpt;
    uint32_t 			rampDelay;
    uint16_t 			closedCommutationFlag;
    uint32_t 			bemfTrigCnt;
    uint32_t 			bemfLastTrigCnt;
    uint16_t 			goodTrigCnt;
    uint16_t 			goodTrigCntTrip;
    uint16_t 			controlMode;
    uint16_t 			currCtrlType;
    uint16_t 			prevCtrlType;
    uint16_t 			calibrateFlag;
    uint16_t 			calibrateTime;
    uint16_t 			runBLDCInt;
    float32_t 			rampStartRate;
    float32_t 			rampEndRate;
    int16_t 			dLogCurrElementIndex;
    float32_t			iDCOffset;
    float32_t 			speedRef;
    float32_t 			calFiltGain;
    float32_t 			spdFiltGain;
    float32_t 			dFuncTesting;
    float32_t 			iqDuty;
    float32_t 			iRef;
    float32_t 			dFuncRun;
    float32_t 			commErrorMax;
    float32_t 			ref;
    float32_t 			currentDisplay;
    float32_t 			dFuncStartup;
    float32_t		 	currentStartup;
    float32_t 			threshold;
    float32_t 			currentKp;
    float32_t 			velocityKp;
    float32_t 			iMax;
    float32_t 			speed;
    int32_t 			speedRPM;
    int32_t 			beginStartRPM;
    int32_t 			endStartRPM;
    uint16_t 			currentMode;
    uint16_t 			velocityMode;
    uint16_t 			resetFault;
    uint16_t 			poles;
    uint16_t 			currentKi;
    uint16_t 			velocityKi;
    uint16_t 			currentKd;
    uint16_t 			velocityKd;
    uint16_t 			prescaler;
    uint16_t 			baseFreq;
    uint16_t 			rampUpTime;
    uint16_t 			tripCnt;
    uint16_t 			advancedStartup;
    int16_t 			overVoltage;
    int16_t 			drvFaultFlag;
    int16_t 			drvOTWFlag;
    int16_t 			enableFlag;
    float32_t 			vDCBus;
    float32_t 			maxVDC;
    float32_t 			minVDC;
    float32_t 			floatCounter;
    float32_t 			pidSpdValue;
    float32_t 			pidIDCValue;
    int16_t				tpsFlag;

} DRV_Obj;

//! \brief Defines the DRV handle
//!
typedef struct DRV_Obj *DRV_Handle;

// **************************************************************************
// the globals

//! \brief Defines the DRV object
//!
extern DRV_Obj drv;

// **************************************************************************
// the function prototypes

//! \brief     Initializes the driver (DRV) object
//! \param[in] pMemory     A pointer to the memory for the driver object
//! \param[in] numBytes    The number of bytes allocated for the driver object, bytes
//! \param[in] period	   FOC, period
//! \return    The driver (DRV) object handle
DRV_Handle DRV_init(void *pMemory, const size_t numBytes, const float32_t period);

//! \brief     Sets up the driver module to default values
//! \param[in] handle  	   The driver (DRV) handle
//! \param[in] period	   FOC, period
void DRV_setup(DRV_Handle handle, const float32_t period);

/*!
 * @ingroup         Generate_Outputs
 * @fn              void Generate_Outputs(DRV_Handle drvHandle)
 * @brief           Function to determine the duty cycle and output necessary PWMs
 * @param [in]  drvHandle	The Handler for the DRV System
 * @param [in]  drvHandle	The Handler for the DRV System
 * @param [in]  duty		The commanded duty cycle for the pwm
 * @param [in]  state		The commutation state
 * @param [out]  pwmData_out		The switching waveforms in duty cycle
 * @param [out]  currentSyncOut		The duty cycle of the current sampling (used if ADC2 is used for Itotal sampling)
 * @param [out]  hetIOstateOut		The active IO for the PWM signals (one phase has to be disabled)
 */
void Generate_Outputs(DRV_Handle drvHandle, float32_t duty, int32_t state, MATH_vec3 *pwmData_out, float32_t *currentSyncOut, uint32_t *hetIOstateOut);

//! \brief     	Updates the gate driver fault status
//! \param[in] 	handle			The drv handle
inline void DRV_update_gdFaultStatus(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	drv->gdFaultStatus = (gioGetPort(gioPORTB) >> 2);
	drv->gdFaultStatus &= 0x00000003; //BIT 1: Faultn, BIT 0: OCTWn

	// Latch in fault conditions
	switch(drv->gdFaultStatus){
    	case 0:	//Over temperature latched shutdown
    		drv->bridgeFaultFlg = 0;
    		drv->overVoltageFlg = 0;
    		drv->overTempFlg = 1;
    		break;
    	case 1:	//Over current or undervoltage latched shutdown
    		drv->bridgeFaultFlg = 1;
    		drv->overVoltageFlg = 0;
    		drv->overTempFlg = 0;
    		break;
    	case 2:	//Over temperature warning
    		drv->bridgeFaultFlg = 0;
    		drv->overVoltageFlg = 0;
    		drv->overTempFlg = 1;
    		break;
    	case 3:	//No fault condition
    		drv->bridgeFaultFlg = 0;
    		drv->overVoltageFlg = 0;
    		drv->overTempFlg = 0;
    		break;
        default:
        	break;
	}

}

//! \brief     	Resets gate driver and clears gate driver fault
//! \param[in] 	handle			The drv handle
inline void DRV_gdFaultReset(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	// Dessert EN_GATE for 5uS to reset gate driver
	gioSetBit(gioPORTA, 4, 0);

	rtiResetCounter(rtiCOUNTER_BLOCK0);
	rtiStartCounter(rtiCOUNTER_BLOCK0);
	while(rtiGetCurrentTick(rtiCOMPARE0) < 4);	//1 ticks = 1uS
	rtiStopCounter(rtiCOUNTER_BLOCK0);

	gioSetBit(gioPORTA, 4, 1);

	// Clear fault flags
	drv->bridgeFaultFlg = 0;
	drv->overVoltageFlg = 0;
	drv->overTempFlg = 0;
	drv->faultDisableFlag  = 0;

}


//! \brief     	Handles resets and stopping the motor.
//! \param[in] 	handle			The drv handle
inline void DRV_EnableMotor(DRV_Handle handle)
{
    DRV_Obj *drv = (DRV_Obj *) handle;

    if(drv->enableFlag == FALSE)
    {
        drv->runBLDCInt=0;

        //shut down all PWMs
    	PWM_setOneShotTrip(drv->pwmHandle[0]);// Disable PWM A leg
    	PWM_setOneShotTrip(drv->pwmHandle[1]);// Disable PWM B leg
    	PWM_setOneShotTrip(drv->pwmHandle[2]);// Disable PWM C leg
        //hetREG1->DIR = ALL_PHASES_OFF; JPB

        // Reset any falts
        DRV_gdFaultReset(handle);

        //zero all displayed variables when disabled
        drv->speedRPM = 0;
        drv->speedHandle->speedRPM = 0;
        drv->speedHandle->speed = 0;
        drv->currentDisplay = 0;
        drv->calibrateFlag = 0;
        drv->instaHandle->vaOffset = 0;
        drv->instaHandle->vbOffset = 0;
        drv->instaHandle->vcOffset = 0;
        drv->iDCOffset = 0.5;
        drv->speedLoopFlag = FALSE;
    }
    // if motor type is not defined
    if((drv->enableFlag == TRUE) && (drv->runBLDCInt == FALSE))
    {
        // Read drv_SpeedRef Only when you have enabled the motor
        drv->speedRef = drv->ref;

        if((drv->runBLDCInt == 0) && (drv->drvFaultFlag == 0))
        {
            drv->speedHandle->inputSelect = 0;
            drv->speedHandle->baseRPM = 120 * (drv->baseFreq / drv->poles);
            drv->speedHandle->speedScaler = (uint32_t)(PWM_FREQUENCY / (1 * (float32_t)drv->baseFreq * 0.001));
            drv->speedHandle->inputSelect = 0;
            drv->speedHandle->newTimeStamp = 0;
            drv->speedHandle->oldTimeStamp = 0;
            drv->speedHandle->eventPeriod = 0;
            drv->speedHandle->speed = 0;
            drv->virtualTimer = 0;

            drv->rmpCntlHandle->equalFlag = 0;
            drv->rmpCntlHandle->rampDelayCount = 0;
            drv->rmpCntlHandle->targetValue = 0;

            //The speed at the end of the ramp should always be greater than the speed at the beginning of the ramp
            if(drv->endStartRPM > drv->beginStartRPM)
            {
                drv->rampStartRate = (PWM_FREQUENCY * 1000) * 60.0 / drv->beginStartRPM /
                                         COMMUTATES_PER_E_REV / (drv->poles / 2.0);
                drv->rampEndRate = (PWM_FREQUENCY * 1000) * 60.0 / drv->endStartRPM /
                                       COMMUTATES_PER_E_REV / (drv->poles / 2.0);
            }
            else
            {
                drv->rampStartRate = (PWM_FREQUENCY * 1000) * 60.0 / 50 / COMMUTATES_PER_E_REV / (drv->poles / 2.0);
                drv->rampEndRate = (PWM_FREQUENCY * 1000) * 60.0 / 100 /  COMMUTATES_PER_E_REV / (drv->poles / 2.0);
            }

            drv->cmtnPeriodTarget = drv->rampEndRate;
            drv->cmtnPeriodSetpt = drv->rampStartRate;
            drv->rmp3Handle->ramp3Delay = (uint32_t)(((float32_t)drv->rampUpTime * 0.001) /
                                            ((float32_t)(drv->cmtnPeriodSetpt - drv->cmtnPeriodTarget) * T));
            drv->rmp3Handle->desiredInput = drv->cmtnPeriodTarget;
            drv->rmp3Handle->out = drv->cmtnPeriodSetpt;
            drv->rmp3Handle->ramp3Min = drv->cmtnPeriodTarget;
            drv->rmp3Handle->ramp3DelayCount = 0;
            drv->rmp3Handle->ramp3DoneFlag = 0;

            drv->impulseHandle->counter = 0;
            drv->impulseHandle->out = 0;

            drv->mod6Handle->counter = 0;

            drv->speedLoopFlag = FALSE;

            drv->pidIDCHandle->Ui = 0;
            drv->pidIDCHandle->refValue = 0;
            drv->pidIDCHandle->fbackValue = 0;

            drv->pidSpdHandle->Ui = 0;
            drv->pidSpdHandle->refValue = 0;
            drv->pidSpdHandle->fbackValue = 0;

            drv->dFuncRun = drv->dFuncStartup;
            drv->bemfTrigCnt = 0;
            drv->bemfLastTrigCnt = 0;
            drv->goodTrigCnt = 0;
            drv->closedCommutationFlag = 0;
            drv->instaHandle->vInt = 0;

            //set control_mode based on check box settings from drv object
            //VOLTAGE		0			//open-loop volage mode only
            //CURRENT		1			//closed-loop current control
            //VELOCITY		2			//closed-loop velocity control
            //CASCADE		3			//cascaded closed-loop velocity->current control
            //DISABLED		4			//Motor is disabled
            //velocity loop check box writes either 0 (disabled) or 2 (enabled)
            //current loop check box writes either 0 (disabled) or 1 (enabled)
            drv->controlMode = drv->velocityMode + drv->currentMode;

            drv->runBLDCInt=1;

        }
    }
}


//! \brief     Runs the DRV object
//! \param[in] handle    The driver (DRV) handle
inline void DRV_run(DRV_Handle handle)
{
    DRV_Obj *obj = (DRV_Obj *) handle;

    // ------------------------------------------------------------------------------
    // Reset and Start the RTI for the control loop time measurement
    // ------------------------------------------------------------------------------
    rtiResetCounter(rtiCOUNTER_BLOCK0);
    rtiStartCounter(rtiCOUNTER_BLOCK0);

    // Update ADC object
    adcGetData(adcREG1, adcGROUP1, obj->AdcResults1);
    //adcGetData(adcREG1, adcGROUP2, obj->AdcResults2);

    // ------------------------------------------------------------------------------
    // Update gate driver fault status and protect system
    // ------------------------------------------------------------------------------
    DRV_update_gdFaultStatus(handle);
    if (obj->faultDisableFlag == 0) {
  	  obj->controlMode = DISABLED;
  	  obj->faultDisableFlag  = 1;
    }

    // ------------------------------------------------------------------------------
    // Check for change in control mode from disabled to torque control/speed control
    // ------------------------------------------------------------------------------
    // Latch in change of control mode
    if (obj->prevCtrlType != obj->currCtrlType ) {
    	// Attempt to clear motor fault condition
    	if ((obj->gdFaultStatus != 3) && (obj->firstFaultRstEval == 0)) {
  		  DRV_gdFaultReset(handle);
  		  obj->firstFaultRstEval = 1;
    	}
    	else if ((obj->gdFaultStatus != 3) && (obj->firstFaultRstEval == 1)) {
  		  obj->prevCtrlType = obj->currCtrlType;
    	}
  		obj->prevCtrlType = obj->currCtrlType;
    }
    else {
  	  obj->prevCtrlType = obj->controlMode;
  	  obj->currCtrlType = obj->controlMode;
  	  obj->firstFaultRstEval = 0;
    }

    //Get the DC Bus Volage
    obj->vDCBus = (((float32_t)obj->AdcResults1[2].value) * 0.00024414);

    // ------------------------------------------------------------------------------
    // Run the InstaSpin Algorithm
    // ------------------------------------------------------------------------------
    if (obj->runBLDCInt == 1)
    {
        if (obj->calibrateFlag)
        {
            /* From TMS570_InstaSPIN */
            // Get BEMF Values
            obj->iqVaIn = (((float32_t)obj->AdcResults1[5].value) * 0.00024414) - obj->instaHandle->vaOffset;
            obj->iqVbIn = (((float32_t)obj->AdcResults1[1].value) * 0.00024414) - obj->instaHandle->vbOffset;
            obj->iqVcIn = (((float32_t)obj->AdcResults1[3].value) * 0.00024414) - obj->instaHandle->vcOffset;

            // LPF to average the calibration offsets
            // Use the offsets calculated here to initialize BemfA_offset, BemfB_offset
            // and BemfC_offset so that they are used for the remaining build levels
            obj->instaHandle->vaOffset = (obj->calFiltGain * obj->iqVaIn) + obj->instaHandle->vaOffset;
            obj->instaHandle->vbOffset = (obj->calFiltGain * obj->iqVbIn) + obj->instaHandle->vbOffset;
            obj->instaHandle->vcOffset = (obj->calFiltGain * obj->iqVcIn) + obj->instaHandle->vcOffset;

            obj->iDCOffset = (obj->calFiltGain * obj->iDCFdbk) + obj->iDCOffset;

            // Turn Off All PWMs
        	PWM_setOneShotTrip(obj->pwmHandle[0]);// Disable PWM A leg
        	PWM_setOneShotTrip(obj->pwmHandle[1]);// Disable PWM B leg
        	PWM_setOneShotTrip(obj->pwmHandle[2]);// Disable PWM C leg
            //hetREG1->DIR = ALL_PHASES_OFF; JPB

            obj->calibrateFlag++;
            obj->calibrateFlag &= obj->calibrateTime;
        }
        else
        {
            /* From TMS570_InstaSPIN */
            // Get BEMF Values
            obj->iqVaIn = ((float32_t)obj->AdcResults1[5].value) * 0.00024414;
            obj->iqVbIn = ((float32_t)obj->AdcResults1[1].value) * 0.00024414;
            obj->iqVcIn = ((float32_t)obj->AdcResults1[3].value) * 0.00024414;

            // Connect inputs of the MOD6 module and call the Modulo 6 counter function.
            if (obj->ref > (0.0))
            {
                obj->mod6Handle->cntDirection = (1.0);
            }
            else
            {
                obj->mod6Handle->cntDirection = (-1.0);
            }

            obj->previousState = obj->mod6Handle->counter;
            MOD6CNT_Calc(obj->mod6Handle);

            // Connect inputs of the SPEED_PR module and call the speed calculation function.
            // While counting up we want positive speed
            if ((obj->mod6Handle->counter == 5) && (obj->previousState == 4) && (obj->mod6Handle->trigInput))
            {
                obj->speedHandle->curTimeStamp = obj->virtualTimer;
                SPEED_MEAS_CAP_Calc(obj->speedHandle);
                obj->speedLoopFlag = TRUE;
            }
            // While counting down we want negative speed
            else if ((obj->mod6Handle->counter == 0) && (obj->previousState == 1) && (obj->mod6Handle->trigInput))
            {
                obj->speedHandle->curTimeStamp = obj->virtualTimer;
                SPEED_MEAS_CAP_Calc(obj->speedHandle);
                obj->speedHandle->speed = (obj->speedHandle->speed * (-1.0));
                obj->speedHandle->speedRPM = (obj->speedHandle->speedRPM * (-1.0));
                obj->speedLoopFlag = TRUE;
            }

            // Connect inputs of the INSTASPIN_BLDC module and call the INSTASPIN_BLDC function.
            obj->instaHandle->vag = obj->iqVaIn - obj->instaHandle->vaOffset; // Adjust for offset of Va_in
            obj->instaHandle->vbg = obj->iqVbIn - obj->instaHandle->vbOffset; // Adjust for offset of Vb_in
            obj->instaHandle->vcg = obj->iqVcIn - obj->instaHandle->vcOffset; // Adjust for offset of Vc_in
            obj->instaHandle->state = obj->mod6Handle->counter;            // Update the state
            InstaSPIN_BLDC_Calc(obj->instaHandle);
            obj->mod6Handle->trigInput = obj->instaHandle->commTrig;

            if ((obj->closedCommutationFlag == 0) || (obj->speedLoopFlag == FALSE))
            {
                // Connect inputs of the RMP3 module and call the Ramp control 3 function
                RMP3_Calc(obj->rmp3Handle);

                // Connect inputs of the IMPULSE module and call the Impulse function.
                obj->impulseHandle->period = obj->rmp3Handle->out;
                IMPULSE_Calc(obj->impulseHandle);

                // Connect inputs of the MOD6 module and call the Modulo 6 counter function.
                obj->mod6Handle->trigInput = obj->impulseHandle->out;

                if (obj->advancedStartup)
                {
                    // When the BEMF signals it's time to commutate, compare against the forced commutation period
                    if (obj->instaHandle->commTrig)
                    {
                        obj->bemfLastTrigCnt = obj->bemfTrigCnt;
                        obj->bemfTrigCnt = 0;
                        // Check if the forced commutation period and the BEMF commutation period
                        // are within the allowed error window
                        if (labs(obj->bemfLastTrigCnt - obj->impulseHandle->period) < obj->goodTrigCntTrip)
                        {
                            obj->goodTrigCnt++;
                        }
                        else
                        {
                            obj->goodTrigCnt = 0;
                        }
                        obj->bemfLastTrigCnt = 0;
                    }
                    else
                    {
                        obj->bemfTrigCnt++;
                    }
                    // Check if there are enough commutation matches to switch to closed commutation mode
                    if (obj->goodTrigCnt > obj->tripCnt)
                    {
                        obj->closedCommutationFlag = 1;
                    }
                }
                // If we're not using advanced startup just switch to closed commutation mode at the end of the startup ramp.
                else if (obj->rmp3Handle->ramp3DoneFlag != 0)
                {
                	obj->closedCommutationFlag = 1;
                }
            }
            switch (obj->controlMode)
            {
                case VOLTAGE:
                    if (obj->closedCommutationFlag == 0)
                    {
                        obj->speedLoopFlag = 1; //no need to wait for speed feedback update in this mode.
                        obj->rmpCntlHandle->setpointValue = (obj->dFuncStartup * obj->mod6Handle->cntDirection);

                    }
                    else
                    {
                        // Connect inputs of the RMP module and call the Ramp control function.
                        obj->rmpCntlHandle->targetValue = obj->ref;
                        RMPCNTL_Calc(obj->rmpCntlHandle);
                    }
                    // Connect inputs of the PWM_DRV module and call the PWM signal generation update function.
                    Generate_Outputs(handle, obj->rmpCntlHandle->setpointValue, obj->instaHandle->state, &obj->gPwmData.Tabc, &obj->currentSync, &obj->hetIOstate);
                    break;
                case CURRENT:
                    obj->iRef = obj->ref;
                    if (obj->closedCommutationFlag == 0)
                    {
                        obj->speedLoopFlag = 1;
                        // Use startup current during initial ramp
                        obj->iRef = (obj->currentStartup * obj->mod6Handle->cntDirection);
                    }
                    // Connect inputs of the PID_REG3 module and call the PID current controller function.
                    PID_run(obj->pidIDCHandle, obj->iRef, obj->iDCFdbk, &obj->pidIDCValue);
                    Generate_Outputs(handle, obj->pidIDCValue, obj->instaHandle->state, &obj->gPwmData.Tabc, &obj->currentSync, &obj->hetIOstate);
                    break;
                case VELOCITY:
                    obj->speedRef = obj->ref;
                    // Connect inputs of the PID_REG3 module and call the PID current controller function.
                    // Switch from fixed duty-cycle or controlled Speed duty-cycle by SpeedLoopFlag variable
                    if ((obj->closedCommutationFlag == 0) || (obj->speedLoopFlag == FALSE))
                    {
                        obj->iqDuty = (obj->dFuncStartup * obj->mod6Handle->cntDirection); // Fixed duty-cycle
                    }
                    else
                    {
                        PID_run(obj->pidSpdHandle, obj->speedRef, obj->speedHandle->speed, &obj->pidSpdValue);
                        obj->iqDuty = obj->pidSpdValue;
                    }
                    // Generate the PWM and Reset outputs
                    Generate_Outputs(handle, obj->iqDuty, obj->instaHandle->state, &obj->gPwmData.Tabc, &obj->currentSync, &obj->hetIOstate);
                    break;
                case CASCADE:
                    obj->speedRef = obj->ref;
                    if ((obj->closedCommutationFlag == 0) || (obj->speedLoopFlag == FALSE))
                    {
                        PID_run(obj->pidIDCHandle, (obj->currentStartup * obj->mod6Handle->cntDirection), obj->iDCFdbk, &obj->pidIDCValue);
                    }
                    else
                    {
                        // Connect Speed PID output to IDC PID input
                        PID_run(obj->pidSpdHandle, obj->speedRef, obj->speedHandle->speed, &obj->pidSpdValue);
                        PID_run(obj->pidIDCHandle, obj->pidSpdValue, obj->iDCFdbk, &obj->pidIDCValue);
                    }
                    Generate_Outputs(handle, obj->pidIDCValue, obj->instaHandle->state, &obj->gPwmData.Tabc, &obj->currentSync, &obj->hetIOstate);
                    break;
                default:
                    // Connect inputs of the PWM_DRV module and call the PWM signal generation update function.
                    Generate_Outputs(handle, OFF, obj->instaHandle->state, &obj->gPwmData.Tabc, &obj->currentSync, &obj->hetIOstate);
                    break;
            }

            // convert pwm values from float to int16 and write the PWM data
            PWM_write_CmpA(obj->pwmHandle[0],(int16_t)(obj->gPwmData.Tabc.value[0]*32768));
            PWM_write_CmpA(obj->pwmHandle[1],(int16_t)(obj->gPwmData.Tabc.value[1]*32768));
            PWM_write_CmpA(obj->pwmHandle[2],(int16_t)(obj->gPwmData.Tabc.value[2]*32768));
            //PWM_write_Cmp(obj->pwmHandle[0], (int16_t) (obj->gPwmData.Tabc.value[0] * 32768));
            //PWM_write_Cmp(obj->pwmHandle[1], (int16_t) (obj->gPwmData.Tabc.value[0] * 32768));
            //PWM_write_Cmp(obj->pwmHandle[2], (int16_t) (obj->gPwmData.Tabc.value[1] * 32768));
            //PWM_write_Cmp(obj->pwmHandle[3], (int16_t) (obj->gPwmData.Tabc.value[1] * 32768));
            //PWM_write_Cmp(obj->pwmHandle[4], (int16_t) (obj->gPwmData.Tabc.value[2] * 32768));
            //PWM_write_Cmp(obj->pwmHandle[5], (int16_t) (obj->gPwmData.Tabc.value[2] * 32768));
            //PWM_write_Cmp(obj->pwmISync, (int16_t) (obj->currentSync * 32768));

            //sync the PWMs and ADC
            //PWM_Sync(obj->pwmSyncHandle);
            //hetREG1->DIR = obj->hetIOstate;

            //DC bus current
        	switch (obj->instaHandle->state) {
        	case 0:
        	case 1:
        		// positive current in A
        		obj->iDCFdbk = ((obj->AdcResults1[0].value << 4) - obj->cal_offset_A) * 0.0000305176;
        		break;

        	case 2:
        	case 3:
        		// positive current in B
        		obj->iDCFdbk = ((obj->AdcResults1[4].value << 4) - obj->cal_offset_B) * 0.0000305176;
        		break;

        	case 4:
        		// negative current in A
        		obj->iDCFdbk = ((obj->AdcResults1[0].value << 4) - obj->cal_offset_A) * -0.0000305176;
        		break;

        	case 5:
        		// negative current in B
        		obj->iDCFdbk = ((obj->AdcResults1[4].value << 4) - obj->cal_offset_B) * -0.0000305176;
        		break;
        	default:
        		obj->iDCFdbk = 0.0;
        	}

            //Filter the displayed speed
            obj->speed = (obj->spdFiltGain * (obj->speedHandle->speed - obj->speed)) + obj->speed;
            obj->speedRPM = (obj->speedHandle->baseRPM * obj->speed);

            obj->floatCounter = (float) obj->mod6Handle->counter;

            // Increase virtual timer and force 15 bit wrap around
            obj->virtualTimer++;
            obj->virtualTimer &= 0x00007FFF;

            obj->currentDisplay = obj->iDCFdbk;
            obj->instaHandle->intThreshold = obj->threshold;
        }
    }

    // ------------------------------------------------------------------------------
    // Stop the RTI for the control loop time measurement
    // ------------------------------------------------------------------------------
    rtiStopCounter(rtiCOUNTER_BLOCK0);
    obj->rtiCounterValue = rtiGetCurrentTick(rtiCOMPARE0);
    obj->rtiBenchmarkTime = obj->rtiCounterValue * 0.001; 	// 1 tick corresponds to 1ms
    return;
} // end of DRV_run() function

/*!
 * @ingroup         Generate_Outputs
 * @fn              void Generate_Outputs(DRV_Handle drvHandle)
 * @brief           Function to determine the duty cycle and output necessary PWMs
 * @param [in]  drvHandle	The Handler for the DRV System
 * @param [in]  drvHandle	The Handler for the DRV System
 * @param [in]  duty		The commanded duty cycle for the pwm
 * @param [in]  state		The commutation state
 * @param [out]  pwmData_out		The switching waveforms in duty cycle
 * @param [out]  currentSyncOut		The duty cycle of the current sampling (used if ADC2 is used for Itotal sampling)
 * @param [out]  hetIOstateOut		The active IO for the PWM signals (one phase has to be disabled)
 */
inline void Generate_Outputs(DRV_Handle drvHandle, float32_t duty, int32_t state, MATH_vec3 *pwmData_out, float32_t *currentSyncOut, uint32_t *hetIOstateOut)
{
    float32_t posDuty = duty;
    float32_t negDuty = duty * -1;
    static int32_t prevState;

    // center the current sample pulse in the center of the PWM on time
    *currentSyncOut = (float32_t)(posDuty*0.5);

    //Ensure there is no cross talk when switching states
    if(state != prevState)
    {
    	PWM_setOneShotTrip(drv.pwmHandle[0]);// Disable PWM A leg
    	PWM_setOneShotTrip(drv.pwmHandle[1]);// Disable PWM B leg
    	PWM_setOneShotTrip(drv.pwmHandle[2]);// Disable PWM C leg
    }
    else
    {
		switch (state)
		{
			case (0):
				// Phase C is off
				PWM_clearOneShotTrip(drv.pwmHandle[0]);// Enable PWM A leg
				PWM_clearOneShotTrip(drv.pwmHandle[1]);// Enable PWM B leg
				PWM_setOneShotTrip(drv.pwmHandle[2]);// Disable PWM C leg

				pwmData_out->value[1] = posDuty;	// Phase B
				pwmData_out->value[0] = negDuty;	// Phase A
				break;
			case (1):
				// Phase B is off
				PWM_clearOneShotTrip(drv.pwmHandle[0]);// Enable PWM A leg
				PWM_setOneShotTrip(drv.pwmHandle[1]);// Disable PWM B leg
				PWM_clearOneShotTrip(drv.pwmHandle[2]);// Enable PWM C leg

				pwmData_out->value[2] = posDuty;	// Phase C
				pwmData_out->value[0] = negDuty;	// Phase A
				break;
			case (2):
				// Phase A is off
				PWM_setOneShotTrip(drv.pwmHandle[0]);// Disable PWM A leg
				PWM_clearOneShotTrip(drv.pwmHandle[1]);// Enable PWM B leg
				PWM_clearOneShotTrip(drv.pwmHandle[2]);// Enable PWM C leg

				pwmData_out->value[2] = posDuty;	// Phase C
				pwmData_out->value[1] = negDuty;	// Phase B
				break;
			case (3):
				// Phase C is off
				PWM_clearOneShotTrip(drv.pwmHandle[0]);// Enable PWM A leg
				PWM_clearOneShotTrip(drv.pwmHandle[1]);// Enable PWM B leg
				PWM_setOneShotTrip(drv.pwmHandle[2]);// Disable PWM C leg

				pwmData_out->value[0] = posDuty;	// Phase A
				pwmData_out->value[1] = negDuty;	// Phase B
				break;
			case (4):
				// Phase B is off
				PWM_clearOneShotTrip(drv.pwmHandle[0]);// Enable PWM A leg
				PWM_setOneShotTrip(drv.pwmHandle[1]);// Disable PWM B leg
				PWM_clearOneShotTrip(drv.pwmHandle[2]);// Enable PWM C leg

				pwmData_out->value[0] = posDuty;	// Phase A
				pwmData_out->value[2] = negDuty;	// Phase C
				break;
			case (5):
				// Phase A is off
				PWM_setOneShotTrip(drv.pwmHandle[0]);// Disable PWM A leg
				PWM_clearOneShotTrip(drv.pwmHandle[1]);// Enable PWM B leg
				PWM_clearOneShotTrip(drv.pwmHandle[2]);// Enable PWM C leg

				pwmData_out->value[1] = posDuty;	// Phase B
				pwmData_out->value[2] = negDuty;	// Phase C
				break;
		}
    }
    prevState = state;
} // end of Generate_Outputs() function

//! \brief     	Gets the status of the controller enable flag
//! \param[in] 	handle  	The controller (CTRL) handle
//! \return		EnableFlg  	Current value of enable flag
inline uint16_t DRV_get_Enable(DRV_Handle handle)
{
    DRV_Obj *obj = (DRV_Obj *) handle;

    return (obj->enableFlag);
}

//! \brief     Starts the Motor Controller
//! \param[in] handle          		The drv handle
inline void DRV_Motor_start(DRV_Handle handle)
{
    DRV_Obj *obj = (DRV_Obj *)handle;

    //QEP_Clear_Index(obj->qepIndexHandle);
    adcStartConversion(adcREG1, adcGROUP1);
	PWM_clearOneShotTrip(obj->pwmHandle[0]);// Enable PWM A leg
	PWM_clearOneShotTrip(obj->pwmHandle[1]);// Enable PWM B leg
	PWM_clearOneShotTrip(obj->pwmHandle[2]);// Enable PWM C leg

    //if ((hetREG1->GCR & 1) == 0)
    //    hetREG1->GCR = 0x00030001U;	// Start HET

    return;
}

//! \brief     Stops the Motor Controller (Not used in this project)
//! \param[in] handle          		The drv handle
inline void DRV_Motor_stop(DRV_Handle handle)
{
    DRV_Obj *obj = (DRV_Obj *) handle;

    //hetREG1->GCR = 0x00030000U;							// Stop HET
    //hetREG1->DOUT = 0x000A0000U;						// Set PWM signals
    adcStopConversion(adcREG1, adcGROUP1);				// Stop ADC
    adcStopConversion(adcREG1, adcGROUP2);

    //QEP_Clear_Index(obj->qepIndexHandle);
    //obj->gPwmData.Tabc.value[0] = 31 << 7;				// Clear the PWM Compares
    //obj->gPwmData.Tabc.value[1] = 31 << 7;				// Clear the PWM Compares
    //obj->gPwmData.Tabc.value[2] = 31 << 7;				// Clear the PWM Compares
	PWM_setOneShotTrip(obj->pwmHandle[0]);// Disable PWM A leg
	PWM_setOneShotTrip(obj->pwmHandle[1]);// Disable PWM B leg
	PWM_setOneShotTrip(obj->pwmHandle[2]);// Disable PWM C leg

    return;
}

//! \brief     Gets adcData
//! \param[in] handle          The drv handle
//! \return    adcData (phase current and voltage data)
inline ADC_Data_t DRV_get_adcData(DRV_Handle handle)
{
    DRV_Obj *drv = (DRV_Obj *) handle;

    return (drv->adcData);
}

//! \brief     Gets rtiBenchmarkTime value
//! \param[in] handle			The drv handle
//! \return    rtiBenchmarkTime Current value of rti based FOC isr service time
inline float32_t DRV_get_rtiBenchmarkTime(DRV_Handle handle)
{
    DRV_Obj *drv = (DRV_Obj *) handle;

    return (drv->rtiBenchmarkTime);
}


//! \brief     	Gets the status of the driver bridgeFaultFlg
//! \param[in] 	handle		The drv handle
//! \return		EnableFlg  	Current value of bridgeFaultFlg
inline uint32_t DRV_get_bridgeFaultFlg(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return( drv->bridgeFaultFlg);
}

//! \brief     	Gets the status of the driver overVoltageFlg
//! \param[in] 	handle		The drv handle
//! \return		EnableFlg  	Current value of overVoltageFlg
inline uint32_t DRV_get_overVoltageFlg(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return( drv->overVoltageFlg);
}

//! \brief     	Gets the status of the driver overTempFlg
//! \param[in] 	handle		The drv handle
//! \return		EnableFlg  	Current value of overTempFlg
inline uint32_t DRV_get_overTempFlg(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return( drv->overTempFlg);
}

//! \brief     Sets up the PWMs (Pulse Width Modulators)
//! \param[in] handle          The driver (DRV) handle
//! \param[in] ISRperiod  	   ISR period in sec
//! \param[in] het_vCNT_SCALE  The scaler to the timer
void DRV_setupPwms(DRV_Handle handle, const float32_t ISRperiod, const int32_t het_vCNT_SCALE);

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif // end of _DRV_H_ definition
