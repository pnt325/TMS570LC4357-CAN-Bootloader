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

//! \file   ~/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137/src/drv.h
//! \brief  Contains public interface to various functions related
//!         to the DRV object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes


// **************************************************************************
// the modules

#include "solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137/src/ctrl.h"
#include "modules/smopos/src/float32/smopos.h"
#include "modules/voltcalc/src/float32/volt_calc.h"
#include "modules/types/src/32b/controller_data_types.h"


// **************************************************************************
// the drivers

#include "drivers/gio/src/32b/hercules/tms570ls3137/gio.h"
#include "drivers/adc/src/32b/hercules/tms570ls3137/adc.h"
#include "drivers/rti/src/32b/hercules/tms570ls3137/rti.h"
#include "drivers/qep/src/32b/hercules/tms570ls3137/qep.h"
#include "drivers/pwm/src/32b/hercules/tms570ls3137/pwm.h"
#include "drivers/het/src/32b/hercules/tms570ls3137/het.h"

//!
//! \defgroup DRV

//!
//! \ingroup DRV
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines


// **************************************************************************
// the typedefs


//! \brief Defines the PWM data
//!
typedef struct _DRV_PwmData_t_
{
  MATH_vec3  Tabc;      //!< the PWM time-durations for each motor phase

} DRV_PwmData_t;


//! \brief Defines the commutation mode
//!
typedef enum {
    RAMP_COMMUTATION_MODE,		// Use ramp generator output
    ENCODER_COMMUTATION_MODE,   // Use encoder output
    SENSORLESS_COMMUTATION_MODE,// Use sliding mode observer output
    LOCK_ROTOR_MODE				// Lock rotor mode for encoder-motor offset calibration
} Commutation_Mode_t;


//! \brief Defines the driver (DRV) object
//!
typedef struct _DRV_Obj_
{

  RAMPGEN_Handle 	rampgenHandle;	//<! the handle for the RAMPGEN object
  RAMPGEN_Obj 		rampgen;		//<! the RAMPGEN object

  QEP_HET_Handle	qepHETHandle;	//<! the handle for the QEP HET Count object
  QEP_HET_Obj		qepHETObj;		//<! the QEP HET Count object

  QEP_HET_Handle	qepIndexHandle; //<! the handle for the QEP HET Index object
  QEP_HET_Obj		qepIndexObj;	//<! the QEP HET Index object

  QEP_Handle		qepHandle;		//<! the handle for the QEP object
  QEP_Obj			qepObj;			//<! the QEP object

  SPEED_FR_Handle   speed_frHandle;	//!< the handle for the speed_fr object
  SPEED_FR_Obj 	   	speed_fr;		//!< the speed_fr object

  CTRL_Handle 		ctrlHandle;		//<! the handle for the CTRL object
  CTRL_Obj 			ctrl;			//<! the CTRL object

  SMO_POS_Handle	smoPosHandle;	//<! the handle for the SMOPOS object
  SMO_POS_Obj		smoPos;			//<! the SMOPOS  object

  VOLT_CALC_Handle	voltCalcHandle;	//<! the handle for the VOLTCALC object
  VOLT_CALC_Obj		voltCalc;		//<! the VOLTCALC object

  SPEED_EST_Handle  speed_estHandle;//!< the handle for the speed_est object
  SPEED_EST_Obj 	speed_est;		//!< the speed_est object

  PWM_Handle    	pwmHandle[3];   //<! the handle for the PWM objects

  PWM_SYNC_Handle	pwmSyncHandle;  //<! the handle for the PWM Sync object

  DRV_PwmData_t 	gPwmData;		//!< (wire) Connection between the CTRL and PWM modules
  int32_t 			PWMPeriod;		//!< PWM signal period
  MATH_vec2 		currentAB;		//!< (wire) Connection between the CTRL and ADC modules
  ADC_Data_t		adcData;		//!< (wire) Connection between the SMO, VOLT and ADC modules
  adcData_t 		AdcResults1[16];// Buffer for ADC conversion results
  adcData_t 		AdcResults2[16];// Buffer for ADC conversion results
  MATH_vec2 		uAlpha_Beta;	//!< (wire) Connection between the VOLTCALC and SMOPOS modules
  uint32_t			POSCNT_Value;	//<! (wire) connection between QEP HET and QEP modules


  ElecPos_Data_t	elecPos1;		//!< QEP electrical angle
  ElecPos_Data_t	elecPos2;		//!< SMO electrical angle
  ElecPos_Data_t	elecPos3;		//!< (wire) Connection of electrical angle to control module
  float32_t			switchOffset;	//!< Electrical angle offset during Commutation switch

  int32_t 			cal_offset_A;	//!< Calibration offset phase A current
  int32_t 			cal_offset_B;	//!< Calibration offset phase B current
  float32_t 		adc_current_gain_A;	//!< Phase A adc current measurement gain
  float32_t 		adc_current_gain_B;	//!< Phase B adc current measurement gain


  Commutation_Mode_t 	commutationMode;//!< Current motor commutation mode
  Commutation_Mode_t	prevCommutation;//!< previous motor commutation mode
  FOC_Control_Type_t 	currCtrlType;	//!< Current FOC control mode
  FOC_Control_Type_t 	prevCtrlType;	//!< Previous FOC control mode


  float32_t 		SpeedEncoder;	//!< Encoder base speed feedback
  float32_t 		SpeedSMO;		//!< SMO based speed feedback
  float32_t 		currentSpd;		//!< current motor speed
  float32_t 		SwitchOverSpdFwd;	//!< Encoder-SMO speed feedback switchover threshold Fwd direction
  float32_t 		SwitchOverSpdRev;	//!< Encoder-SMO speed feedback switchover threshold Rev direction


  int32_t			newIndexValue;	//!< Current value of index counter variable
  int32_t			prevIndexValue;	//!< Previous value of index counter variable
  int32_t			offsetLatch;	//!< Flag to indicate latching in of motor-encoder index offset
  int32_t			firstIndexEvaluation;	//!< Flag to indicate completion of first evaluation of index find routine
  int32_t			indexFoundFlag;	//!< Flag to indicate that a QEP index pulse has been encountered
  int32_t			calibrateAngle; //!< Calibration offset recoreded by auto calibration routine


  int32_t			encoderFaultReg;	//!< Flag to indicate encoder fault condition
  int32_t			faultTimer;			//!< Timer to evaluate encoder fault condition
  int32_t			encoderFaultTripTime;//!< Time threshold for encoder fault detection
  float32_t 		spdFaultThreshold;	//!< Zero speed threshold
  float32_t			previousTheta;		//Previous value of encoder electric angle for fault detection

  uint32_t			rtiCounterValue;	//RTI counter value corresponding to isr service time
  float32_t			rtiBenchmarkTime;	//RTI benchmark time

  uint32_t			gdFaultStatus;		//DRV 8301 fault status
  uint32_t			bridgeFaultFlg;		//!< Gate driver bridge fault flag
  uint32_t			overVoltageFlg;		//!< Gate driver over voltage flag
  uint32_t			overTempFlg;		//!< Gate driver over temperature flag
  uint32_t			firstFaultRstEval;	//!< Flag to indicate first attempt to reset motor fault during index find
  uint32_t			faultDisableFlag;	//!< Flag to indicate controller has been reset upon occurance of motor fault

  uint32_t			enableFlg;			//!< Controller enable flag


}DRV_Obj;


//! \brief Defines the DRV handle
//!
typedef struct DRV_Obj   *DRV_Handle;


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
//! \param[in] het_vCNT_SCALE	HET count value for PWM period setup
//! \param[in] commMode    Motor commutation mode
//! \return    The driver (DRV) object handle
DRV_Handle DRV_init(void *pMemory,const size_t numBytes, const float32_t period, const int32_t het_vCNT_SCALE, Commutation_Mode_t commMode);

//! \brief     Setup the driver module to default values
//! \param[in] handle  	   		The driver (DRV) handle
//! \param[in] commMode    		Motor commutation mode
//! \param[in] period	   		FOC, period
//! \param[in] het_vCNT_SCALE	HET count value for PWM period setup
void DRV_setup(DRV_Handle handle, Commutation_Mode_t ecMode, const float32_t ISRperiod, const int32_t het_vCNT_SCALE);

//! \brief     Runs the routine to find the next occurance of the QEP index pulse
//! \param[in] handle      The drv handle
inline void DRV_find_index(DRV_Handle handle);

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


//! \brief     Runs the DRV object
//! \param[in] handle    The driver (DRV) handle
inline void DRV_run(DRV_Handle handle)
{
  DRV_Obj *obj = (DRV_Obj *)handle;

  // ------------------------------------------------------------------------------
  // Reset and Start the RTI for the control loop time measurement
  // ------------------------------------------------------------------------------
  rtiResetCounter(rtiCOUNTER_BLOCK0);
  rtiStartCounter(rtiCOUNTER_BLOCK0);

  // ------------------------------------------------------------------------------
  // Update gate driver fault status and protect system
  // ------------------------------------------------------------------------------
  DRV_update_gdFaultStatus(handle);
  if (obj->faultDisableFlag == 0) {
	  CTRL_change_Control_Mode(drv.ctrlHandle, DISABLED);
	  obj->faultDisableFlag  = 1;
  }

  // ------------------------------------------------------------------------------
  // Encoder-SMO automatic switchover logic
  // ------------------------------------------------------------------------------
  if ((CTRL_get_Control_Mode(obj->ctrlHandle) == SPEED_CTRL) && (fabsf(obj->currentSpd) >= obj->SwitchOverSpdFwd)) {
	  obj->commutationMode = SENSORLESS_COMMUTATION_MODE;
  }
  else if ((CTRL_get_Control_Mode(obj->ctrlHandle) == SPEED_CTRL) && (fabsf(obj->currentSpd) < obj->SwitchOverSpdRev)) {
	  obj->commutationMode = ENCODER_COMMUTATION_MODE;
  }


  // ------------------------------------------------------------------------------
  // Update encoder fault flag
  // ------------------------------------------------------------------------------
  if ((CTRL_get_Control_Mode(obj->ctrlHandle) == SPEED_CTRL) && (fabsf(CTRL_get_spd(obj->ctrlHandle)) >= obj->spdFaultThreshold)) {

	  // Detect if encoder theta has changed from previous execution
	  if (fabsf((obj->elecPos1.ElecTheta) - obj->previousTheta) == 0.0) {

		  //Update fault register
		  if (obj->faultTimer >= obj->encoderFaultTripTime) {
			  obj->encoderFaultReg = 1;	// Set encoder fault
			  obj->faultTimer = 0;		// Reset fault timer
		  }

		  obj->faultTimer++;
	  }
	  else {
		  obj->faultTimer = 0;		// Reset fault timer
		  obj->encoderFaultReg = 0;	// Clear fault register
	  }

	  obj->previousTheta = obj->elecPos1.ElecTheta;
  }

  // ------------------------------------------------------------------------------
  // Check for encoder fault condition and protect system
  // ------------------------------------------------------------------------------
  if ((CTRL_get_Control_Mode(obj->ctrlHandle) == SPEED_CTRL) && (obj->commutationMode == ENCODER_COMMUTATION_MODE)) {

	  //Protect system if in encoder commutation mode
	  if (obj->encoderFaultReg == 1)
		  CTRL_change_Control_Mode(drv.ctrlHandle, DISABLED);
	  	  obj->indexFoundFlag = 0;
  }

  // ------------------------------------------------------------------------------
  // Check for change in control mode from disabled to torque control/speed control
  // ------------------------------------------------------------------------------
  // Latch in change of control mode
  if ((obj->prevCtrlType == DISABLED) && ((obj->currCtrlType == SPEED_CTRL)
		  || (obj->currCtrlType  == TORQUE_CTRL))) {

//	  // Attempt to clear motor fault condition
	  if ((obj->gdFaultStatus != 3) && (obj->firstFaultRstEval == 0)) {
		  DRV_gdFaultReset(handle);
		  obj->firstFaultRstEval = 1;
	  }
	  else if ((obj->gdFaultStatus != 3) && (obj->firstFaultRstEval == 1)) {
		  obj->prevCtrlType = obj->currCtrlType;
	  }

	  DRV_find_index(handle);

	  // Terminate search for index, once index is located
	  if ( (obj->indexFoundFlag == 1)) {
		  obj->prevCtrlType = obj->currCtrlType;
	  }

  }
  else {
	  obj->prevCtrlType = obj->currCtrlType;
	  obj->currCtrlType = CTRL_get_Control_Mode(obj->ctrlHandle);
	  obj->firstFaultRstEval = 0;
  }

  // ------------------------------------------------------------------------------
  // Update electrical angle and speed feedback based on commutation mode
  // ------------------------------------------------------------------------------

  if (obj->commutationMode == RAMP_COMMUTATION_MODE) {
	  RAMPGEN_setFreq(obj->rampgenHandle, CTRL_get_spd(obj->ctrlHandle));
  	  RAMPGEN_run(obj->rampgenHandle, &obj->elecPos3.ElecTheta);

  	  //Update previous commutation state
  	  obj->prevCommutation = RAMP_COMMUTATION_MODE;

  }
  else if (obj->commutationMode == ENCODER_COMMUTATION_MODE) {

	  obj->elecPos3.Dir =  obj->elecPos1.Dir;
	  obj->elecPos3.ElecTheta = obj->elecPos1.ElecTheta;

	  // Update speed feedback
	  obj->currentSpd = (-1)*obj->SpeedEncoder;

	  // Update previous commutation state
	  obj->prevCommutation = ENCODER_COMMUTATION_MODE;

  }
  else if (obj->commutationMode == SENSORLESS_COMMUTATION_MODE) {

	  // Calculate the offset value between encoder and SMO
	  if (obj->prevCommutation == ENCODER_COMMUTATION_MODE)
		  obj->switchOffset = obj->elecPos3.ElecTheta - obj->elecPos2.ElecTheta ;

	  // Add constant offset to SMO output
	  obj->elecPos3.ElecTheta = obj->elecPos2.ElecTheta + obj->switchOffset;

	   // Bound elecTheta
	   if (obj->elecPos3.ElecTheta  < 0)
		   obj->elecPos3.ElecTheta  = obj->elecPos3.ElecTheta  + 1;
	   else if (obj->elecPos3.ElecTheta  > 1)
		   obj->elecPos3.ElecTheta = obj->elecPos3.ElecTheta - 1;

	  // Update speed feedback
	  obj->currentSpd = (-1)*obj->SpeedSMO;

	  //Update previous commutation state
	  obj->prevCommutation = SENSORLESS_COMMUTATION_MODE;

  }
  else if (obj->commutationMode == LOCK_ROTOR_MODE) {
	  obj->elecPos3.ElecTheta  = 0.5; // Alteranatively could be set to 0.0
	  	  	  	  	  	  	  	  	  // Done for phase alignment with Anehiem motor
  }

  // ------------------------------------------------------------------------------
  // Run FOC controller
  // ------------------------------------------------------------------------------

  // Update ADC object
  adcGetData(adcREG1, adcGROUP1, obj->AdcResults1);
  obj->adcData.I.value[0] = ((obj->AdcResults1[0].value<<4)-obj->cal_offset_A)*obj->adc_current_gain_A; //ileg1.ImeasA_f;
  obj->adcData.I.value[1] = ((obj->AdcResults1[2].value<<4)-obj->cal_offset_B)*obj->adc_current_gain_B; //ileg1.ImeasB_f;
  obj->adcData.I.value[2] = 0;

  obj->currentAB.value[0] = obj->adcData.I.value[0];
  obj->currentAB.value[1] = obj->adcData.I.value[1];

  //DC bus voltage
  obj->adcData.dcBusV = (obj->AdcResults1[1].value)*0.00024414;

  // read in QEP data from HET
  QEP_read_POSCNT(obj->qepHETHandle, &obj->POSCNT_Value);

  // Update QEP object
  QEP_run(obj->qepHandle, &obj->elecPos1, &obj->POSCNT_Value);

  // run the speed_fr module
  SPEED_FR_run(obj->speed_frHandle, obj->elecPos1.ElecTheta, &obj->SpeedEncoder);

  // update control object
  CTRL_run(obj->ctrlHandle, &obj->currentAB, &obj->elecPos3, obj->currentSpd, &obj->gPwmData.Tabc);

  // update total motor current
  obj->adcData.iTotal =  sqrtf( ((obj->ctrl.iDs_Qs.value[0])*(obj->ctrl.iDs_Qs.value[0])) + ((obj->ctrl.iDs_Qs.value[1])*(obj->ctrl.iDs_Qs.value[1])) );

  // convert pwm values from _IQ to _IQ15 and write the PWM data
  PWM_write_Cmp(obj->pwmHandle[0], (int16_t)(obj->gPwmData.Tabc.value[0]*32768), (int16_t) obj->PWMPeriod);
  PWM_write_Cmp(obj->pwmHandle[1], (int16_t)(obj->gPwmData.Tabc.value[1]*32768), (int16_t) obj->PWMPeriod);
  PWM_write_Cmp(obj->pwmHandle[2], (int16_t)(obj->gPwmData.Tabc.value[2]*32768), (int16_t) obj->PWMPeriod);

  //sync the PWMs and ADC
  PWM_Sync(obj->pwmSyncHandle);

  // update voltCalc object
  VOLT_CALC_run(obj->voltCalcHandle , &obj->adcData, &obj->ctrl.Tabc, &obj->uAlpha_Beta);

  // update smoPos object
  SMO_POS_run(obj->smoPosHandle, &obj->uAlpha_Beta, &obj->ctrl.iAlpha_Beta, &obj->elecPos2);

  // run the speed_est module
  SPEED_EST_run(obj->speed_estHandle, obj->elecPos2.ElecTheta, &obj->SpeedSMO);

  // ------------------------------------------------------------------------------
  // Stop the RTI for the control loop time measurement
  // ------------------------------------------------------------------------------
  rtiStopCounter(rtiCOUNTER_BLOCK0);
  obj->rtiCounterValue = rtiGetCurrentTick(rtiCOMPARE0);
  obj->rtiBenchmarkTime = obj->rtiCounterValue * (10E-6); 	// 1 tick corresponds to 1us

  return;
} // end of DRV_run() function


//! \brief     Starts the FOC control algorithm
//! \param[in] handle          		The drv handle
inline void DRV_FOC_start(DRV_Handle handle)
{
	DRV_Obj *obj = (DRV_Obj *)handle;


	adcStartConversion(adcREG1, adcGROUP1);

	// Reset controller
	QEP_Clear_Index(obj->qepIndexHandle);
	RMPCNTL_Set_TargetValue(obj->ctrl.rmpCntlHandle, (0.0) );
	RMPCNTL_Set_SetpointValue(obj->ctrl.rmpCntlHandle, (0.0) );
	PID_setIntegrator(obj->ctrl.pidHandle_Id, (0.0) );
	PID_setIntegrator(obj->ctrl.pidHandle_Iq, (0.0) );
	PID_setIntegrator(obj->ctrl.pidHandle_spd, (0.0) );
	CTRL_change_Control_Mode(drv.ctrlHandle, DISABLED);
	obj->currCtrlType = DISABLED;
	obj->prevCtrlType = DISABLED;

	hetREG1->DIR    = 0x401B8515U;		// Change direction of PWM pins to outputs

	return;
}

//! \brief     Stops the FOC control algorithm
//! \param[in] handle          		The drv handle
inline void DRV_FOC_stop(DRV_Handle handle)
{
	DRV_Obj *obj = (DRV_Obj *)handle;

	adcStopConversion(adcREG1, adcGROUP1);	// Stop ADC
	adcStopConversion(adcREG1, adcGROUP2);

	// This assumes that the PWM pins have pull downs selected and enabled
	hetREG1->DIR    = 0x401B8404U;		// Change direction of PWM pins to inputs

	QEP_Clear_Index(obj->qepIndexHandle);
	PWM_disable(obj->pwmHandle[0]);		// Disable PWM A leg
	PWM_disable(obj->pwmHandle[1]);		// Disable PWM B leg
	PWM_disable(obj->pwmHandle[2]);		// Disable PWM C leg

	return;
}


//! \brief     Gets adcData
//! \param[in] handle          The drv handle
//! \return    adcData (phase current and voltage data)
inline ADC_Data_t DRV_get_adcData(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return(drv->adcData);
}


//! \brief     Runs routine to calculate encoder-motor calibration offset
//! \param[in] handle          		The drv handle
//! \param[in] calibrationEnable	Enable flag for calibration routine
inline int32_t DRV_run_calibration(DRV_Handle handle, int32_t calibrationEnable) {

	DRV_Obj *drv = (DRV_Obj *) handle;

	if (calibrationEnable == 1) {

		if ((QEP_Read_Index(drv->qepIndexHandle) == 0x00000000U) && (drv->offsetLatch == 0))  {

			//Ramp commutate motor to encounter index pulse
			drv->commutationMode = RAMP_COMMUTATION_MODE;
			CTRL_change_Control_Mode(drv->ctrlHandle, OPEN_DUTY_CYCLE);
			CTRL_set_duty(drv->ctrlHandle, (0.0), (0.1));
			CTRL_set_spd(drv->ctrlHandle, (0.05));

			if (drv->firstIndexEvaluation == 0) {
				RAMPGEN_setExecutionCount(drv->rampgenHandle,0);
				drv->firstIndexEvaluation = 1;
			}
			else if (RAMPGEN_getExecutionCount(drv->rampgenHandle) >= 0x3000) {
				drv->encoderFaultReg = 1;
				drv->firstIndexEvaluation = 0;
				RAMPGEN_setExecutionCount(drv->rampgenHandle,0);
			}

		}
		//Check to see if index has been encountered
		else if ((QEP_Read_Index(drv->qepIndexHandle) == 0x00000100U) && (drv->offsetLatch == 0)) {

			//Lock rotor to 0 degree position
			drv->commutationMode = LOCK_ROTOR_MODE;
			CTRL_set_duty(drv->ctrlHandle,(0.0), (0.0));
			CTRL_set_spd(drv->ctrlHandle, (0.0));
			CTRL_change_Control_Mode(drv->ctrlHandle, TORQUE_CTRL);
			CTRL_set_current(drv->ctrlHandle, (0.3), (0.0));
			drv->calibrateAngle = drv->qepHandle->rawTheta;
			drv->offsetLatch = 1;
		}
		else if (drv->offsetLatch == 1) {
			drv->calibrateAngle = drv->qepHandle->rawTheta;
		}

	}
	else if ((calibrationEnable == 0)  && (drv->offsetLatch == 1) ) {

		//Assign calibration angle and reset state of controller
		CTRL_set_spd(drv->ctrlHandle, (0.0));
		CTRL_set_current(drv->ctrlHandle,(0.0), (0.0));
		drv->commutationMode = ENCODER_COMMUTATION_MODE;

		//Handle case where zero pole pair is on the negative side of index pulse
		if ((drv->calibrateAngle >= 2*drv->qepHandle->lineCounts) && (drv->calibrateAngle <= 4*drv->qepHandle->lineCounts))
			drv->calibrateAngle = 4*drv->qepHandle->lineCounts - drv->calibrateAngle;
		QEP_set_calibratedAngle(drv->qepHandle, drv->calibrateAngle);
		drv->offsetLatch = 0;
		drv->firstIndexEvaluation = 0;
	}

	return(drv->calibrateAngle);
}


//! \brief     Runs the routine to find the next occurance of the QEP index pulse
//! \param[in] handle          		The drv handle
inline void DRV_find_index(DRV_Handle handle) {

	DRV_Obj *drv = (DRV_Obj *) handle;

	if (drv->indexFoundFlag == 0) {
		//Ramp commutate motor to encounter index pulse
		drv->commutationMode = RAMP_COMMUTATION_MODE;
		CTRL_change_Control_Mode(drv->ctrlHandle, OPEN_DUTY_CYCLE);
		CTRL_set_duty(drv->ctrlHandle, (0.0), (0.1));
		CTRL_set_spd(drv->ctrlHandle, (0.05));
	}

	// Update index count state
	if (drv->firstIndexEvaluation == 0) {
		drv->newIndexValue = QEP_Read_Index(drv->qepIndexHandle);
		drv->prevIndexValue = drv->newIndexValue;
		drv->firstIndexEvaluation = 1;
		RAMPGEN_setExecutionCount(drv->rampgenHandle,0);
	}
	else {
		drv->newIndexValue = QEP_Read_Index(drv->qepIndexHandle);
		if ((drv->newIndexValue - drv->prevIndexValue) >= 128) {
			drv->indexFoundFlag = 1;
			drv->firstIndexEvaluation = 0;
			drv->commutationMode = ENCODER_COMMUTATION_MODE;
			RAMPGEN_setExecutionCount(drv->rampgenHandle,0);
		}
		else if (RAMPGEN_getExecutionCount(drv->rampgenHandle) >= 0x5DC0) {
			drv->encoderFaultReg = 1;
			drv->currCtrlType = CTRL_get_Control_Mode(drv->ctrlHandle);
			drv->prevCtrlType = drv->currCtrlType;
			drv->firstIndexEvaluation = 0;
			RAMPGEN_setExecutionCount(drv->rampgenHandle,0);
		}
		drv->prevIndexValue = drv->newIndexValue;
	}
}


//! \brief     Sets/clears encoderFaultReg
//! \param[in] handle			The drv handle
//! \param[in] encoderFaultReg 	Encoder fault register status
inline void DRV_set_encoderFaultReg(DRV_Handle handle, int32_t encoderFaultReg)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	drv->encoderFaultReg = encoderFaultReg;
}

//! \brief     Gets encoderFaultReg status
//! \param[in] handle			The drv handle
//! \return    encoderFaultReg 	Encoder fault register status
inline int32_t DRV_get_encoderFaultReg(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return(drv->encoderFaultReg);
}

//! \brief     Gets encoderFaultReg status
//! \param[in] handle			The drv handle
//! \return    commutationMode 	Current motor commutation mode
inline Commutation_Mode_t DRV_get_commutationMode(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return(drv->commutationMode);
}

//! \brief     Gets rtiBenchmarkTime value
//! \param[in] handle			The drv handle
//! \return    rtiBenchmarkTime Current value of rti based FOC isr service time
inline float32_t DRV_get_rtiBenchmarkTime(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return(drv->rtiBenchmarkTime);
}

//! \brief     Sets SwitchOverSpdFwd
//! \param[in] handle				The drv handle
//! \param[in] SwitchOverSpdFwd 	Forward direction Encoder-SMO switch over threshold
inline void DRV_set_SwitchOverSpdFwd(DRV_Handle handle, float32_t SwitchOverSpdFwd)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	drv->SwitchOverSpdFwd = SwitchOverSpdFwd;
}

//! \brief     Gets SwitchOverSpdFwd value
//! \param[in] handle				The drv handle
//! \return    SwitchOverSpdFwd 	Forward direction Encoder-SMO switch over threshold
inline float32_t DRV_get_SwitchOverSpdFwd(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return(drv->SwitchOverSpdFwd);
}

//! \brief     Sets SwitchOverSpdRev
//! \param[in] handle				The drv handle
//! \param[in] SwitchOverSpdRev 	Reverse direction Encoder-SMO switch over threshold
inline void DRV_set_SwitchOverSpdRev(DRV_Handle handle, float32_t SwitchOverSpdRev)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	drv->SwitchOverSpdRev = SwitchOverSpdRev;
}

//! \brief     Gets SwitchOverSpdRev
//! \param[in] handle				The drv handle
//! \return    SwitchOverSpdRev 	Reverse direction Encoder-SMO switch over threshold
inline float32_t DRV_get_SwitchOverSpdRev(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return(drv->SwitchOverSpdRev);
}

//! \brief     	Gets the status of the driver enable flag
//! \param[in] 	handle		The drv handle
//! \return		EnableFlg  	Current value of enable flag
inline uint32_t DRV_get_Enable(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return( drv->enableFlg);
}

//! \brief     	Sets the driver enable flag
//! \param[in] 	handle		The drv handle
//! \param[in] 	EnableFlg  	Current value of enable flag
inline void DRV_set_Enable(DRV_Handle handle, uint32_t EnableFlg )
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	drv->enableFlg = EnableFlg;
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


//! \brief     	Sets the driver cal_offset_A
//! \param[in] 	handle			The drv handle
//! \param[in] 	cal_offset_A  	Value of phase A current calibration offset
inline void DRV_set_cal_offset_A(DRV_Handle handle, int32_t cal_offset_A)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	drv->cal_offset_A = cal_offset_A;
}


//! \brief     	Gets the current value of cal_offset_A
//! \param[in] 	handle			The drv handle
//! \return		cal_offset_A  	Current value of phase A current calibration offset
inline int32_t DRV_get_cal_offset_A(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return( drv->cal_offset_A);
}

//! \brief     	Sets the driver cal_offset_B
//! \param[in] 	handle			The drv handle
//! \param[in] 	cal_offset_B  	Value of phase B current calibration offset
inline void DRV_set_cal_offset_B(DRV_Handle handle, int32_t cal_offset_B)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	drv->cal_offset_B = cal_offset_B;
}


//! \brief     	Gets the current value of cal_offset_B
//! \param[in] 	handle			The drv handle
//! \return		cal_offset_B  	Current value of phase B current calibration offset
inline int32_t DRV_get_cal_offset_B(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return( drv->cal_offset_B);
}

//! \brief     	Sets the phase A adc current measurement gain
//! \param[in] 	handle				The drv handle
//! \param[in] 	adc_current_gain_A	Value of phase A current adc gain
inline void DRV_set_adc_current_gain_A(DRV_Handle handle, float32_t adc_current_gain_A)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	drv->adc_current_gain_A = adc_current_gain_A;
}


//! \brief     	Gets the phase A adc current measurement gain
//! \param[in] 	handle				The drv handle
//! \return		adc_current_gain_A  Current value of phase A current adc gain
inline float32_t DRV_get_adc_current_gain_A(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return( drv->adc_current_gain_A);
}


//! \brief     	Sets the phase B adc current measurement gain
//! \param[in] 	handle				The drv handle
//! \param[in] 	adc_current_gain_B	Value of phase B current adc gain
inline void DRV_set_adc_current_gain_B(DRV_Handle handle, float32_t adc_current_gain_B)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	drv->adc_current_gain_B = adc_current_gain_B;
}


//! \brief     	Gets the phase B adc current measurement gain
//! \param[in] 	handle				The drv handle
//! \return		adc_current_gain_B  Current value of phase B current adc gain
inline float32_t DRV_get_adc_current_gain_B(DRV_Handle handle)
{
	DRV_Obj *drv = (DRV_Obj *) handle;

	return( drv->adc_current_gain_B);
}



#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif // end of _DRV_H_ definition
