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
#ifndef _CTRL_H_
#define _CTRL_H_

//! \file   ~/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137/src/ctrl.h
//! \brief  Contains public interface to various functions related
//!         to the FOC object
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "modules/types/src/32b/controller_data_types.h"

// **************************************************************************
// the modules

#include "modules/clarke/src/float32/clarke.h"
#include "modules/park/src/float32/park.h"
#include "modules/ipark/src/float32/ipark.h"
#include "modules/svgen/src/float32/svgen.h"
#include "modules/pid/src/float32/pid.h"
#include "modules/rampgen/src/float32/rampgen.h"
#include "modules/speed_fr/src/float32/speed_fr.h"
#include "modules/speed_est/src/float32/speed_est.h"
#include "modules/rmpcntl/src/float32/hercules/rmp_cntl.h"

//!
//! \defgroup DRV

//!
//! \ingroup DRV
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the typedefs


//! \brief Defines the FOC control modes
//!
typedef enum
{
  DISABLED = 0,
  OPEN_DUTY_CYCLE,
  TORQUE_CTRL,
  SPEED_CTRL
} FOC_Control_Type_t;


//! \brief Defines the object to prescale a PID loop
//!
typedef struct _CTRL_Prescaler_t_
{
	uint16_t count;
	uint16_t max;
}CTRL_Prescaler_t;


//! \brief Defines the control (CTRL) object
//!
typedef struct _CTRL_Obj_
{

	CLARKE_Handle      clarkeHandle;		//!< the handle for the voltage Clarke transform
	CLARKE_Obj         clarke;              //!< the voltage Clarke transform object

	PARK_Handle        parkHandle;          //!< the handle for the Park object
	PARK_Obj           park;                //!< the Park transform object

	PID_Handle         pidHandle_Id;        //!< the handle for the Id PID controller
	PID_Obj            pid_Id;              //!< the Id PID controller object

	PID_Handle         pidHandle_Iq;        //!< the handle for the Iq PID controller
	PID_Obj            pid_Iq;              //!< the Iq PID controller object

	RMPCNTL_handle	   rmpCntlHandle;		//!< the handle for the speed ramp controller
	RMPCNTL_Obj        rmpCntl;             //!< the speed ramp controller object

	PID_Handle         pidHandle_spd;       //!< the handle for the speed PID controller
	PID_Obj            pid_spd;             //!< the speed PID controller object
	CTRL_Prescaler_t   spdPrescaler;		//!< the speed PID prescaler object

	IPARK_Handle       iparkHandle;         //!< the handle for the inverse Park transform
	IPARK_Obj          ipark;               //!< the inverse Park transform object

	SVGEN_Handle       svgenHandle;         //!< the handle for the space vector generator
	SVGEN_Obj          svgen;               //!< the space vector generator object

	MATH_vec2          iAlpha_Beta;         //!< (wire) Connection between the Clarke and Park

	MATH_vec2          iDs_Qs;              //!< (wire) Connection between the Park and Control loops

	MATH_vec2		   vDs_Qs;				//!< (wire) Connection between control loops and iPark

	MATH_vec2		   vAlpha_Beta;			//!< (wire) Connection between iPark and SVgen

	MATH_vec3		   Tabc;				//!< (wire) Connection between SVgen and output Q15 PWM values, in floating point values

	float32_t			T;					//!< Period of ISR running controller

	FOC_Control_Type_t 	ctrlType;			//!< Current FOC control mode

	float32_t			IdRef;				//!< Id current reference

	float32_t			IqRef;				//!< Iq current reference

	float32_t			VdRef;				//!< Vd duty reference (OPEN_DUTY_CYCLE mode)

	float32_t			VqRef;				//!< Vd duty reference (OPEN_DUTY_CYCLE mode)

	float32_t			spdRef;				//!< speed reference

}CTRL_Obj;


//! \brief Defines the FOC handle
//!
typedef struct CTRL_Obj   *CTRL_Handle;


// **************************************************************************
// the globals


// **************************************************************************
// the function prototypes

//! \brief      Changes FOC control mode
//! \param[in]  handle  The controller (CTRL) handle
//! \param[in]  mode  	Control mode
inline void CTRL_change_Control_Mode(CTRL_Handle handle, FOC_Control_Type_t mode )
{
	CTRL_Obj *obj = (CTRL_Obj *)handle;

	if( obj->ctrlType == mode ){
		return; 	// do nothing if the mode is already what it was set to
	}else{
		switch (mode){
		case DISABLED:
			obj->ctrlType = DISABLED;
			PID_setIntegrator(obj->pidHandle_Id, (0.0) );
			PID_setIntegrator(obj->pidHandle_Iq, (0.0) );
			PID_setIntegrator(obj->pidHandle_spd, (0.0) );
			break;
		case OPEN_DUTY_CYCLE:

			obj->ctrlType = OPEN_DUTY_CYCLE;
			break;
		case TORQUE_CTRL:
			PID_setIntegrator(obj->pidHandle_Id, (0.0) );
			PID_setIntegrator(obj->pidHandle_Iq, (0.0) );

			obj->ctrlType = TORQUE_CTRL;
			break;
		case SPEED_CTRL:
			PID_setIntegrator(obj->pidHandle_Id, (0.0) );
			PID_setIntegrator(obj->pidHandle_Iq, (0.0) );
			PID_setIntegrator(obj->pidHandle_spd, (0.0) );

			obj->ctrlType = SPEED_CTRL;
			break;

		default:
			break;
		}
	}// end else
}// function end

//! \brief     	Sets the speed reference command
//! \param[in]  handle  The controller (CTRL) handle
//! \param[in]  spd    	Value of speed command (pu)
inline void CTRL_set_spd(CTRL_Handle handle, float32_t spd)
{
	CTRL_Obj *obj = (CTRL_Obj *)handle;
	obj->spdRef = spd;
}

//! \brief     	Gets the current speed reference command
//! \param[in]  handle  The controller (CTRL) handle
//! \return  	spd     Value of speed command (pu)
inline float32_t CTRL_get_spd(CTRL_Handle handle)
{
	CTRL_Obj *obj = (CTRL_Obj *)handle;
	return( obj->spdRef);
}

//! \brief      Sets the Open-loop duty cycle
//! \param[in]  handle  The controller (CTRL) handle
//! \param[in]  Vd      Vd Duty Cycle (pu)
//! \param[in]  Vq      Vq Duty Cycle (pu)
inline void CTRL_set_duty(CTRL_Handle handle, float32_t Vd, float32_t Vq)
{
	CTRL_Obj *obj = (CTRL_Obj *)handle;
	obj->VqRef = Vq;
	obj->VdRef = Vd;
}

//! \brief      Sets the Open-loop Current
//! \param[in]  handle  The controller (CTRL) handle
//! \param[in]  Id      Id current (pu)
//! \param[in]  Iq      Iq current (pu)
inline void CTRL_set_current(CTRL_Handle handle, float32_t Id, float32_t Iq)
{
	CTRL_Obj *obj = (CTRL_Obj *)handle;
	obj->IqRef = Iq;
	obj->IdRef = Id;
}

//! \brief      Gets current FOC control mode
//! \param[in] 	handle  The controller (CTRL) handle
//! \return		The current control mode
inline FOC_Control_Type_t CTRL_get_Control_Mode(CTRL_Handle handle )
{
	CTRL_Obj *obj = (CTRL_Obj *)handle;

	return( obj->ctrlType);
}


//! \brief      Set the Id PID parameters
//! \param[in]  handle  The controller (CTRL) handle
//! \param[in]  Kp      Value of Kp - Unitless
//! \param[in]  Ki      Value of Ki - Units: 1/s
//! \param[in]  Kd      Value of Kd - Units: s
inline void CTRL_setPID_Id_param(CTRL_Handle handle, float32_t Kp, float32_t Ki, float32_t Kd)
{
	CTRL_Obj *obj = (CTRL_Obj *)handle;
	PID_setGains( obj->pidHandle_Id, Kp, (Ki * obj->T ), (Kd / obj->T ) );
}

//! \brief     	Sets the Iq PID parameters
//! \param[in]  handle  The controller (CTRL) handle
//! \param[in]  Kp      Value of Kp - Unitless
//! \param[in]  Ki      Value of Ki - Units: 1/s
//! \param[in]  Kd      Value of Kd - Units: s
inline void CTRL_setPID_Iq_param(CTRL_Handle handle, float32_t Kp, float32_t Ki, float32_t Kd)
{
	CTRL_Obj *obj = (CTRL_Obj *)handle;
	PID_setGains( obj->pidHandle_Iq, Kp, (Ki * obj->T ), (Kd / obj->T ) );
}

//! \brief     	Set the spd PID parameters
//! \param[in]  handle  The controller (CTRL) handle
//! \param[in]  Kp      Value of Kp - Unitless
//! \param[in]  Ki      Value of Ki - Units: 1/s
//! \param[in]  Kd      Value of Kd - Units: s
inline void CTRL_setPID_spd_param(CTRL_Handle handle, float32_t Kp, float32_t Ki, float32_t Kd)
{
	CTRL_Obj *obj = (CTRL_Obj *)handle;
	float32_t prescaled_T = obj->T * obj->spdPrescaler.max;

	PID_setGains( obj->pidHandle_spd, Kp, (Ki * prescaled_T ), (Kd / prescaled_T ) );
}

//! \brief      Sets the period of controller
//! \param[in]  handle	The controller (CTRL) handle
//! \param[in] 	period  Period of controller (float32)
inline void CTRL_setPeriod(CTRL_Handle handle, float32_t period)
{
	  CTRL_Obj *obj = (CTRL_Obj *)handle;

	  obj->T = period;
}

//! \brief      Gets the period of controller
//! \param[in]  handle		The controller (CTRL) handle
//! \return		float32_t   Period of controller (float32)
inline float32_t CTRL_getPeriod(CTRL_Handle handle)
{
	  CTRL_Obj *obj = (CTRL_Obj *)handle;

	  return(obj->T);
}


//! \brief      Sets the speed PID prescalar max value
//! \param[in]  handle  		The controller (CTRL) handle
//! \param[in] 	prescale_max    prescalar maximum value
inline void CTRL_setSpdPrescalarMax(CTRL_Handle handle, uint16_t prescale_max)
{
	  CTRL_Obj *obj = (CTRL_Obj *)handle;

	  obj->spdPrescaler.max = prescale_max;
}

//! \brief     Gets the speed PID prescalar max value
//! \param[in]  handle  		The controller (CTRL) handle
//! \returns 	prescale_max    prescalar maximum value
inline uint16_t CTRL_getSpdPrescalarMax(CTRL_Handle handle)
{
	  CTRL_Obj *obj = (CTRL_Obj *)handle;

	  return(obj->spdPrescaler.max);
}

//! \brief     Initializes the Control (CTRL) object
//! \param[in] pMemory     A pointer to the memory for the ctrl object
//! \param[in] numBytes    The number of bytes allocated for the ctrl object, bytes
//! \param[in] period	   FOC, period
//! \return The Control (CTRL) object handle
CTRL_Handle CTRL_init( void *pMemory, const size_t numBytes, const float32_t period);

//! \brief     Setup the Control module to default values
//! \param[in] handle  The controller (CTRL) handle
//! \param[in] period	   FOC, period
void CTRL_setup( CTRL_Handle handle, const float32_t period  );

//! \brief     Runs the FOC Algorthm
//! \param[in] focHandle	The FOC controller handle
//! \param[in] adcData_in   Current ADC measurements
//! \param[in] elecPos_in   Rotor position measurment
//! \param[in] currentSpd  	Current speed feedback measurementW
//! \param[out] pwmData_out  - PWM values (Q15) passed out
inline void CTRL_run(CTRL_Handle ctrlHandle,
					MATH_vec2 *adcData_in,
					ElecPos_Data_t *elecPos_in,
					float32_t currentSpd,
		            MATH_vec3 *pwmData_out )
{
	CTRL_Obj *ctrl = (CTRL_Obj *)ctrlHandle;

	// run the Clarke object
	CLARKE_run_twoInput( ctrl->clarkeHandle, adcData_in, &ctrl->iAlpha_Beta );

	// setup Park object
	PARK_setup(ctrl->parkHandle,elecPos_in->ElecTheta );

	// run the Park object
	PARK_run( ctrl->parkHandle, &ctrl->iAlpha_Beta, &ctrl->iDs_Qs );

    switch(ctrl->ctrlType){
    case SPEED_CTRL:
    	if( ctrl->spdPrescaler.count >= ctrl->spdPrescaler.max )
    	{
    		//ramp to desired speed command
    		RMPCNTL_Set_TargetValue(ctrl->rmpCntlHandle, ctrl->spdRef);
    		RMPCNTL_Calc(ctrl->rmpCntlHandle);
    		PID_run( ctrl->pidHandle_spd, ctrl->rmpCntl.setpointValue, currentSpd, &(ctrl->IqRef) );
    		ctrl->spdPrescaler.count = 0;
    	}else
    	{
    		ctrl->spdPrescaler.count++;
    	}
    	// fall through and run lower loops too.
    case TORQUE_CTRL:

        // run the Id PID controller
        PID_run(ctrl->pidHandle_Id, ctrl->IdRef, ctrl->iDs_Qs.value[0], &(ctrl->vDs_Qs.value[0]) );

        // run the Iq PID controller
        PID_run(ctrl->pidHandle_Iq, ctrl->IqRef, ctrl->iDs_Qs.value[1], &(ctrl->vDs_Qs.value[1]) );
    	break;

    case OPEN_DUTY_CYCLE:
    	ctrl->vDs_Qs.value[0] = ctrl->VqRef;
    	ctrl->vDs_Qs.value[1] = ctrl->VdRef;
    	break;

    case DISABLED:
        pwmData_out->value[0] = 0.5;
        pwmData_out->value[1] = 0.5;
        pwmData_out->value[2] = 0.5;
        return;

    default:
    	break;

    }

    // Setup the iPark module with theta
    IPARK_setup(ctrl->iparkHandle, elecPos_in->ElecTheta );

    // Run the iPark Transform
    IPARK_run( ctrl->iparkHandle, &ctrl->vDs_Qs, &ctrl->vAlpha_Beta );

    // Run the Space-vector generator
    SVGEN_run( ctrl->svgenHandle, &( ctrl->vAlpha_Beta), &(ctrl->Tabc) );

    // Convert floating values to Q15 (16-bit signed integer)
    pwmData_out->value[0] = ctrl->Tabc.value[0];
    pwmData_out->value[1] = ctrl->Tabc.value[1];
    pwmData_out->value[2] = ctrl->Tabc.value[2];

}


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif // #define _FOR_H_ 
