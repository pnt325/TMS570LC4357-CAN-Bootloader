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
#ifndef __SPEED_EST_H__
#define __SPEED_EST_H__

//! \file   ~/modules/speed_est/src/float32/speed_est.h
//! \brief  Contains the public interface to the rotor angle based speed
//!         measurement modules.
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include <math.h>
#include "modules/math/src/float32/math_fpu32.h"

//!
//! \defgroup SPEED_EST

//!
//! \ingroup SPEED_EST
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

#define   SPEED_EST_SAT(A, Pos, Neg)  (fmax(((fmin((A),(Pos)))),(Neg)))


// **************************************************************************
// the typedefs

//! \brief Defines the SPEED_EST controller object
//!
typedef struct _SPEED_EST_Obj_{
       float32_t OldEstimatedTheta;   	//!< History: Electrical angle at previous step (pu)
       float32_t EstimatedSpeed;       	//!< Output: EstimatedSpeed in per-unit  (pu)
       float32_t ThetaDiff_MaxLimit;	//!< The Differentiator maximum position limit
       float32_t ThetaDiff_MinLimit;	//!< The Differentiator minimum position limit
       float32_t BaseRpm;      			//!< Parameter: Base speed in rpm
       float32_t K1;         			//!< Parameter: Constant for differentiator
       float32_t K2;         			//!< Parameter: Constant for low-pass filter (pu)
       float32_t K3;         			//!< Parameter: Constant for low-pass filter (pu)
       float32_t EstimatedSpeedRpm;     //!< Output : Speed in rpm
       float32_t Tmp_est;				//!< Temp Variable
       float32_t filterCutoff;			//!< Low Pass Filter Cutoff Frequency
       float32_t baseFreq;				//!< Base Frequency of the motor
       float32_t T;						//!< Estimator Sampling period
       uint16_t polePairs;				//!< Motor number of pole pairs
       } SPEED_EST_Obj;

//! \brief Defines the SPEED_EST handle
//!
typedef SPEED_EST_Obj *SPEED_EST_Handle;

// **************************************************************************
// the function prototypes

//! \brief     Initializes the SPEED_EST module
//! \param[in] pMemory            A pointer to the memory for the SPEED_EST object
//! \param[in] numBytes           The number of bytes allocated for the SPEED_EST object, bytes
//! \return The SPEED_EST object handle
SPEED_EST_Handle SPEED_EST_init(void *pMemory,const size_t numBytes);

//! \brief     Calculates the SPEED_EST module parameters
//! \param[in] Speed_estHandle  The SPEED_EST handle
inline void SPEED_EST_calc_params(SPEED_EST_Handle Speed_estHandle)
{
	SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;

	speed_est->K1 =  1.0 / (speed_est->baseFreq * speed_est->T);

	speed_est->K2 =  1.0 / (1.0 + (speed_est->T * speed_est->filterCutoff) ) ;

	speed_est->K3 =  1.0 - speed_est->K2 ;


	speed_est->BaseRpm = 120.0 * (speed_est->baseFreq / (2*speed_est->polePairs));
} // end of SPEED_EST_calc_params() function


//! \brief     Sets the low pass filter cutoff frequency
//! \param[in] Speed_estHandle  The SPEED_EST handle
//! \param[in] cutoff 		   The cutoff frequency in rad/s
inline void SPEED_EST_set_cutoff(SPEED_EST_Handle Speed_estHandle, const float32_t cutoff)
{
	SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;

	speed_est->filterCutoff = cutoff;

	SPEED_EST_calc_params(Speed_estHandle);
} // end of SPEED_EST_set_cutoff() function


//! \brief     Sets the base frequency
//! \param[in] Speed_estHandle  The SPEED_EST handle
//! \param[in] baseFreq			The base frequency in Hz
inline void SPEED_EST_set_base_freq(SPEED_EST_Handle Speed_estHandle, const float32_t baseFreq)
{
	SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;

	speed_est->baseFreq = baseFreq;

	// This functions assumes that all of the params are added to SPEED_EST_Obj,
	// will not set params correctly until all accessor functions are called with correct values
	SPEED_EST_calc_params(Speed_estHandle);
} // end of SPEED_EST_set_base_freq() function


//! \brief     Sets the filter period parameter
//! \param[in] Speed_estHandle  The SPEED_EST handle
//! \param[in] cuttoff 		   The cuttoff frequency in Hz
inline void SPEED_EST_set_period(SPEED_EST_Handle Speed_estHandle, const float32_t period)
{
	SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;

	speed_est->T = period;

	SPEED_EST_calc_params(Speed_estHandle);
} // end of SPEED_EST_set_period() function


//! \brief     Sets the number of motor pole pairs
//! \param[in] Speed_estHandle  The SPEED_EST handle
//! \param[in] cuttoff 		   The cuttoff frequency in Hz
inline void SPEED_EST_set_num_pole_pairs(SPEED_EST_Handle Speed_estHandle, const uint16_t polePairs)
{
	SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;

	speed_est->polePairs = polePairs;

	SPEED_EST_calc_params(Speed_estHandle);
} // end of SPEED_EST_set_num_pole_pairs() function


//! \brief     Sets up the SPEED_EST module
//! \param[in] Speed_estHandle  	The SPEED_EST handle
//! \param[in] period  				Estimator Sampling period
//! \param[in] baseFreq  			Base Frequency of the motor
//! \param[in] polePairs  			Motor number of pole pairs
//! \param[in] cutoff  				Low Pass Filter Cutoff Frequency
//! \param[in] ThetaDiff_MaxLimit  	The Differentiator maximum position limit
//! \param[in] ThetaDiff_MinLimit  	The Differentiator minimum position limit
inline void SPEED_EST_setup(SPEED_EST_Handle Speed_estHandle, const float32_t period, const float32_t baseFreq, const uint16_t polePairs,
						    const float32_t cutoff, const float32_t ThetaDiff_MaxLimit, const float32_t ThetaDiff_MinLimit  )
{
	SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;

	speed_est->T = period;

	speed_est->baseFreq = baseFreq;

	speed_est->polePairs = polePairs;

	speed_est->filterCutoff = cutoff;

	//set max and min bounds on theta used for speed estimation
	speed_est->ThetaDiff_MaxLimit = ThetaDiff_MaxLimit;
	speed_est->ThetaDiff_MinLimit = ThetaDiff_MinLimit;

	SPEED_EST_calc_params(Speed_estHandle);
} // end of SPEED_EST_setup() function


//! \brief     Gets the estimated speed
//! \param[in] Speed_estHandle  The SPEED_EST handle
//! \return	   Estimated speed
inline float32_t SPEED_EST_get_speed(SPEED_EST_Handle Speed_estHandle)
{
    SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;
    return(speed_est->EstimatedSpeed);
} // end of SPEED_EST_get_speed() function


//! \brief     Gets the speed in RPMs
//! \param[in] Speed_estHandle  The SPEED_EST handle
//! \return	   Estimated Speed in RPM
inline float32_t SPEED_EST_get_speed_rpm(SPEED_EST_Handle Speed_estHandle)
{
    SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;
    return(speed_est->EstimatedSpeedRpm);
}// end of SPEED_EST_get_speed() function


//! \brief     Gets the low pass filter cutoff frequency
//! \param[in] Speed_estHandle  The SPEED_EST handle
//! \return	   filterCutoff 	The cutoff frequency in rad/s
inline float32_t SPEED_EST_get_cutoff(SPEED_EST_Handle Speed_estHandle)
{
    SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;
    return(speed_est->filterCutoff);
} // end of SPEED_EST_get_cutoff() function


//! \brief     Gets the base frequency
//! \param[in] Speed_estHandle  The SPEED_EST handle
//! \return	   baseFreq			The base frequency in Hz
inline float32_t SPEED_EST_get_base_freq(SPEED_EST_Handle Speed_estHandle)
{
    SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;
    return(speed_est->baseFreq);
}// end of SPEED_EST_get_base_freq() function


//! \brief     Runs the SPEED_EST module
//! \param[in] Speed_estHandle  The SPEED_EST handle
//! \param[in] ElecTheta	The position of the motor
//! \param[out] speed_out	The estimated speed of the motor
inline void SPEED_EST_run(SPEED_EST_Handle Speed_estHandle, const float32_t ElecTheta, float32_t* speed_out )
{
    
    SPEED_EST_Obj *speed_est = (SPEED_EST_Obj *)Speed_estHandle;

    if( (ElecTheta < speed_est->ThetaDiff_MaxLimit) & (ElecTheta > speed_est->ThetaDiff_MinLimit) )
    {
        speed_est->Tmp_est = speed_est->K1 * ( ElecTheta - speed_est->OldEstimatedTheta);
    }else
    {
        speed_est->Tmp_est = speed_est->EstimatedSpeed;
    }
    
    // Low-pass filter
    speed_est->Tmp_est = (speed_est->K2 * speed_est->EstimatedSpeed) + (speed_est->K3 * speed_est->Tmp_est);
    
    speed_est->Tmp_est = SPEED_EST_SAT(speed_est->Tmp_est, 1.0, -1.0);
    
    speed_est->EstimatedSpeed = speed_est->Tmp_est;
    
    speed_est->OldEstimatedTheta = ElecTheta;
    
    speed_est->EstimatedSpeedRpm = ( speed_est->BaseRpm * speed_est->EstimatedSpeed);
    *speed_out = speed_est->EstimatedSpeed;
}// end of SPEED_EST_run() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // __SPEED_EST_H__

