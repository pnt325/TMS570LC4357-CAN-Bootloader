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
#ifndef __SPEED_FR_H__
#define __SPEED_FR_H__

//! \file   ~/modules/speed_fr/src/float32/speed_fr.h
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

#define   SPEED_FR_SAT(A, Pos, Neg)  (fmax(((fminf((A),(Pos)))),(Neg)))


// **************************************************************************
// the typedefs

//! \brief Defines the SPEED_FR controller object
//!
typedef struct _SPEED_FR_Obj_{
       float32_t OldElecTheta;   //!< History: Electrical angle at previous step (pu)
       float32_t Speed;       	 //!< Output: Speed in per-unit  (pu)
       float32_t BaseRpm;        //!< Parameter: Base speed in rpm
       float32_t K1;         	 //!< Parameter: Constant for differentiator
       float32_t K2;         	 //!< Parameter: Constant for low-pass filter (pu)
       float32_t K3;         	 //!< Parameter: Constant for low-pass filter (pu)
       float32_t SpeedRpm;       //!< Output : Speed in rpm
       float32_t Tmp_fr;		 //!< Temp Variable
       float32_t filterCutoff;	 //!< Low Pass Filter Cutoff Frequency
       float32_t baseFreq;		 //!< Base Frequency of the motor
       float32_t T;				 //!< Estimator Sampling period
       uint16_t polePairs;		 //!< Motor number of pole pairs
       } SPEED_FR_Obj;

//! \brief Defines the SPEED_FR handle
//!
typedef SPEED_FR_Obj *SPEED_FR_Handle;

// **************************************************************************
// the function prototypes

//! \brief     Initializes the Speed_FR module
//! \param[in] pMemory            A pointer to the memory for the Speed_FR object
//! \param[in] numBytes           The number of bytes allocated for the Speed_FR object, bytes
//! \return The Speed_FR object handle
SPEED_FR_Handle SPEED_FR_init(void *pMemory,const size_t numBytes);

//! \brief     Calculates Speed_FR module parameters
//! \param[in] Speed_frHandle  The Speed_FR handle
inline void SPEED_FR_calc_params(SPEED_FR_Handle Speed_frHandle)
{
	SPEED_FR_Obj *speed_fr = (SPEED_FR_Obj *)Speed_frHandle;

	speed_fr->K1 =  1.0f / (speed_fr->baseFreq * speed_fr->T);

	speed_fr->K2 =  1.0f / (1.0f + (speed_fr->T * speed_fr->filterCutoff) ) ;

	speed_fr->K3 =  1.0f - speed_fr->K2 ;


	speed_fr->BaseRpm = 120.0 * (speed_fr->baseFreq / (2*speed_fr->polePairs));
} // end of SPEED_FR_calc_params() function


//! \brief     Sets the low pass filter cutoff frequency
//! \param[in] Speed_frHandle  The Speed_FR handle
//! \param[in] cutoff 		   The cutoff frequency in rad/s
inline void SPEED_FR_set_cutoff(SPEED_FR_Handle Speed_frHandle, const float32_t cutoff)
{
	SPEED_FR_Obj *speed_fr = (SPEED_FR_Obj *)Speed_frHandle;

	speed_fr->filterCutoff = cutoff;

	SPEED_FR_calc_params(Speed_frHandle);
} // end of SPEED_FR_set_cutoff() function


//! \brief     Sets the base frequency
//! \param[in] Speed_estHandle  The SPEED_FR handle
//! \param[in] baseFreq			The base frequency in Hz
inline void SPEED_FR_set_base_freq(SPEED_FR_Handle Speed_frHandle, const float32_t baseFreq)
{
	SPEED_FR_Obj *speed_fr = (SPEED_FR_Obj *)Speed_frHandle;

	speed_fr->baseFreq = baseFreq;

	// This functions assumes that all of the params are added to SPEED_FR_Obj,
	//will not set params correctly until all accessor functions are called with correct values
	SPEED_FR_calc_params(Speed_frHandle);
} // end of SPEED_FR_set_base_freq() function


//! \brief     Sets the filter period parameter
//! \param[in] Speed_frHandle  The Speed_FR handle
//! \param[in] cuttoff 		   The cuttoff frequency in Hz
inline void SPEED_FR_set_period(SPEED_FR_Handle Speed_frHandle, const float32_t period)
{
	SPEED_FR_Obj *speed_fr = (SPEED_FR_Obj *)Speed_frHandle;

	speed_fr->T = period;

	SPEED_FR_calc_params(Speed_frHandle);
} // end of SPEED_FR_set_period() function


//! \brief     Sets the number of motor pole pairs
//! \param[in] Speed_frHandle  The Speed_FR handle
//! \param[in] cuttoff 		   The cuttoff frequency in Hz
inline void SPEED_FR_set_num_pole_pairs(SPEED_FR_Handle Speed_frHandle, const uint16_t polePairs)
{
	SPEED_FR_Obj *speed_fr = (SPEED_FR_Obj *)Speed_frHandle;

	speed_fr->polePairs = polePairs;

	SPEED_FR_calc_params(Speed_frHandle);
} // end of SPEED_FR_set_num_pole_pairs() function


//! \brief     Sets up the Speed_FR module
//! \param[in] Speed_frHandle  The Speed_FR handle
//! \param[in] period  				Sampling period
//! \param[in] baseFreq  			Base Frequency of the motor
//! \param[in] polePairs  			Motor number of pole pairs
//! \param[in] cutoff  				Low Pass Filter Cutoff Frequency
inline void SPEED_FR_setup(SPEED_FR_Handle Speed_frHandle, const float32_t period, const float32_t baseFreq,const uint16_t polePairs, const float32_t cutoff )
{
	SPEED_FR_Obj *speed_fr = (SPEED_FR_Obj *)Speed_frHandle;

	speed_fr->T = period;

	speed_fr->baseFreq = baseFreq;

	speed_fr->polePairs = polePairs;

	speed_fr->filterCutoff = cutoff;

	SPEED_FR_calc_params(Speed_frHandle);
} // end of SPEED_EST_setup() function


//! \brief     Gets the speed
//! \param[in] Speed_frHandle  The Speed_FR handle
//! \return	   Motor Speed
inline float32_t SPEED_FR_get_speed(SPEED_FR_Handle Speed_frHandle)
{
    SPEED_FR_Obj *speed_fr = (SPEED_FR_Obj *)Speed_frHandle;
    return(speed_fr->Speed);
} // end of SPEED_FR_get_speed() function


//! \brief     Gets the speed in RPMs
//! \param[in] Speed_frHandle  The Speed_FR handle
//! \return	   Motor Speed in RPM
inline float32_t SPEED_FR_get_speed_rpm(SPEED_FR_Handle Speed_frHandle)
{
    SPEED_FR_Obj *speed_fr = (SPEED_FR_Obj *)Speed_frHandle;
    return(speed_fr->SpeedRpm);
}// end of SPEED_FR_get_speed_rpm() function


//! \brief     Runs the Speed_FR module
//! \param[in] Speed_frHandle  The Speed_FR handle
//! \param[in] ElecTheta	The position of the motor
//! \param[out] speed_out	The speed of the motor
inline void SPEED_FR_run(SPEED_FR_Handle Speed_frHandle, const float32_t ElecTheta, float32_t* speed_out )
{

    SPEED_FR_Obj *speed_fr = (SPEED_FR_Obj *)Speed_frHandle;

    if( (ElecTheta < (0.9f)) & (ElecTheta > 0.1f ) )
    {
        speed_fr->Tmp_fr = speed_fr->K1 * ( ElecTheta - speed_fr->OldElecTheta);
    }else
    {
        speed_fr->Tmp_fr = speed_fr->Speed;
    }
    
    // Low-pass filter
    speed_fr->Tmp_fr = (speed_fr->K2 * speed_fr->Speed) + (speed_fr->K3 * speed_fr->Tmp_fr);
    
    speed_fr->Tmp_fr = SPEED_FR_SAT(speed_fr->Tmp_fr, 1.0f, -1.0f);
    
    speed_fr->Speed = speed_fr->Tmp_fr;
    
    speed_fr->OldElecTheta = ElecTheta;
    
    speed_fr->SpeedRpm = ( speed_fr->BaseRpm * speed_fr->Speed);
    *speed_out = speed_fr->Speed;
}// end of SPEED_FR_run() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // __SPEED_FR_H__

