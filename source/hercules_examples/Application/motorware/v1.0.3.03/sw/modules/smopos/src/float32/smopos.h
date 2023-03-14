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
#ifndef __SMOPOS_H__
#define __SMOPOS_H__

//! \file   ~/modules/smopos/src/float32/smopos.h
//! \brief  Contains the public interface to the sliding mode observer
//!         position feedback module.
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "modules/math/src/float32/math_fpu32.h"
#include "modules/types/src/32b/controller_data_types.h"

//!
//! \defgroup SMOPOS

//!
//! \ingroup SMOPOS
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines


// **************************************************************************
// the typedefs

//! \brief Defines the SMO_POS controller object
//!
typedef struct _SMO_POS_Obj_{
		float32_t  Rs; 			// Input: Stator resistance (ohm) 
		float32_t  Ls;			// Input: Stator inductance (H) 	  			      
		float32_t  Ib; 			// Input: Base phase current (amp) 
		float32_t  Vb;			// Input: Base phase voltage (volt) 
		float32_t  Ts;			// Input: Sampling period in sec 
		float32_t  Fsmopos;		// Output: constant using in observed current calculation 
		float32_t  Gsmopos;		// Output: constant using in observed current calculation
		float32_t  Ealpha;   	// Variable: Stationary alfa-axis back EMF 
		float32_t  Zalpha;      // Parameter: Stationary alfa-axis sliding control
		float32_t  EstIalpha;   // Variable: Estimated stationary alfa-axis stator current 
		float32_t  Ebeta;  		// Variable: Stationary beta-axis back EMF 
		float32_t  Zbeta;      	// Parameter: Stationary beta-axis sliding control
		float32_t  EstIbeta;    // Variable: Estimated stationary beta-axis stator current 
		float32_t  IalphaError; // Variable: Stationary alfa-axis current error                 
		float32_t  Kslide;     	// Parameter: Sliding control gain 
		float32_t  IbetaError;  // Variable: Stationary beta-axis current error                 
		float32_t  Kslf;       	// Parameter: Sliding control filter gain 
		float32_t  E0;			// Parameter: 0.5
		float32_t  Theta;     	// Parameter: Compensated rotor angle
		} SMO_POS_Obj;
		
		
//! \brief Defines the SMO POS handle
//!
typedef SMO_POS_Obj *SMO_POS_Handle;


// **************************************************************************
// the function prototypes


//! \brief     Initializes the SMO_POS module
//! \param[in] pMemory		A pointer to the memory for the SMO_POS object
//! \param[in] numBytes		The number of bytes allocated for the SMO_POS object, bytes
//! \param[in] Rs           Stator resistance (ohm)
//! \param[in] Ls           Stator inductance (H)
//! \param[in] Vb           Base phase voltage (volt)
//! \param[in] Ib           Base phase current (amp)
//! \param[in] period       Sampling period in sec
//! \return The SMO_POS object handle
SMO_POS_Handle SMO_POS_init(void *pMemory,const size_t numBytes, const float32_t Rs, const float32_t Ls,const float32_t Vb, const float32_t Ib, const float32_t period);


//! \brief     Setup the SMO_POS module
//! \param[in] SMO_POS_Handle  The SMO_POS handle
inline void SMO_POS_calc_params(SMO_POS_Handle smo_posHandle)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;
	
	smo_pos->Fsmopos = expf((-smo_pos->Rs/smo_pos->Ls)*(smo_pos->Ts));
	smo_pos->Gsmopos = (smo_pos->Vb/smo_pos->Ib)*(1.0f/smo_pos->Rs)*(1.0f-smo_pos->Fsmopos);
} // end of SMO_POS_calc_params() function


//! \brief     Setup the SMO_POS module
//! \param[in] SMO_POS_Handle  The SMO_POS handle
//! \param[in] Rs			   The Motor Stator Resistance in Ohms
inline void SMO_POS_set_Rs(SMO_POS_Handle smo_posHandle, const float32_t Rs)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

	smo_pos->Rs = Rs;

	SMO_POS_calc_params(smo_posHandle);
} // end of SMO_POS_set_Rs() function


//! \brief     Setup the SMO_POS module
//! \param[in] SMO_POS_Handle  The SMO_POS handle
//! \param[in] Ls			   The Motor Stator Inductance in Henrys
inline void SMO_POS_set_Ls(SMO_POS_Handle smo_posHandle, const float32_t Ls)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

	smo_pos->Ls = Ls;

	SMO_POS_calc_params(smo_posHandle);
} // end of SMO_POS_set_Ls() function


//! \brief     Setup the SMO_POS module
//! \param[in] SMO_POS_Handle  The SMO_POS handle
//! \param[in] BaseVoltage	   The Motor Base Voltage in Volts
inline void SMO_POS_set_BaseVoltage(SMO_POS_Handle smo_posHandle, const float32_t BaseVoltage)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

	smo_pos->Vb = BaseVoltage;

	SMO_POS_calc_params(smo_posHandle);
} // end of SMO_POS_set_BaseVoltage() function


//! \brief     Setup the SMO_POS module
//! \param[in] SMO_POS_Handle  The SMO_POS handle
//! \param[in] BaseCurrent	   The Motor Base Current in Amps
inline void SMO_POS_set_BaseCurrent(SMO_POS_Handle smo_posHandle, const float32_t BaseCurrent)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

	smo_pos->Ib = BaseCurrent;

	SMO_POS_calc_params(smo_posHandle);
} // end of SMO_POS_set_BaseCurrent() function


//! \brief     Setup the SMO_POS module
//! \param[in] SMO_POS_Handle  The SMO_POS handle
//! \param[in] Period	   The Module execution period in Seconds
inline void SMO_POS_set_period(SMO_POS_Handle smo_posHandle, const float32_t period)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

	smo_pos->Ts = period;

	SMO_POS_calc_params(smo_posHandle);
} // end of SMO_POS_set_period() function


//! \brief     Setup the SMO_POS module
//! \param[in] SMO_POS_Handle  The SMO_POS handle
//! \param[in] Kslide	The Module Slider Gain
inline void SMO_POS_set_Kslide(SMO_POS_Handle smo_posHandle, const float32_t Kslide)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

	smo_pos->Kslide = Kslide;
} // end of SMO_POS_set_Kslide() function


//! \brief     Setup the SMO_POS module
//! \param[in] SMO_POS_Handle  The SMO_POS handle
//! \param[in] Kslf	   The Module slf Gain
inline void SMO_POS_set_Kslf(SMO_POS_Handle smo_posHandle, const float32_t Kslf)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

	smo_pos->Kslf = Kslf;
} // end of SMO_POS_set_Kslf() function


//! \brief     Sets up the SMO_POS module
//! \param[in] smo_posHandle  The smo_pos handle
//! \param[in] Rs           Stator resistance (ohm)
//! \param[in] Ls           Stator inductance (H)
//! \param[in] Vb           Base phase voltage (volt)
//! \param[in] Ib           Base phase current (amp)
//! \param[in] period       Sampling period in sec
void SMO_POS_setup(SMO_POS_Handle smo_posHandle, const float32_t Rs, const float32_t Ls,const float32_t Vb, const float32_t Ib, const float32_t period );


//! \brief     Runs the SMO_POS module
//! \param[in] smo_posHandle  The smo_pos handle
//! \param[in] 
inline void SMO_POS_run(SMO_POS_Handle smo_posHandle, const MATH_vec2 *vInVec,const MATH_vec2 *iInVec, ElecPos_Data_t* smoPosOut )
{   
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

    //	Sliding mode current observer
    smo_pos->EstIalpha = (smo_pos->Fsmopos * smo_pos->EstIalpha) + (smo_pos->Gsmopos * (vInVec->value[0] - smo_pos->Ealpha - smo_pos->Zalpha));
    smo_pos->EstIbeta  = (smo_pos->Fsmopos * smo_pos->EstIbeta)  + (smo_pos->Gsmopos * (vInVec->value[1] - smo_pos->Ebeta - smo_pos->Zbeta));

	//	Current errors
//    smo_pos->IalphaError = smo_pos->EstIalpha - iInVec->value[0];
//    smo_pos->IbetaError  = smo_pos->EstIbeta  - iInVec->value[1];
    // Invert clarke waveforms to SMO unit.
    smo_pos->IalphaError = smo_pos->EstIalpha + iInVec->value[0];
    smo_pos->IbetaError  = smo_pos->EstIbeta  + iInVec->value[1];

    //  Sliding control calculator
	//  smo_pos->Zalpha=smo_pos->IalphaError*smo_pos->Kslide/smo_pos->E0) where E0=0.5 here
    // 	Original c2000 styple implementation
	if (fabsf(smo_pos->IalphaError) < smo_pos->E0)
	   smo_pos->Zalpha = (smo_pos->Kslide * (smo_pos->IalphaError / smo_pos->E0));
	else if (smo_pos->IalphaError >= smo_pos->E0)
	   smo_pos->Zalpha = smo_pos->Kslide;
	else if (smo_pos->IalphaError <= -smo_pos->E0)
	   smo_pos->Zalpha = -smo_pos->Kslide;

	if (fabsf(smo_pos->IbetaError) < smo_pos->E0)
	   smo_pos->Zbeta = (smo_pos->Kslide * (smo_pos->IbetaError / smo_pos->E0));
	else if (smo_pos->IbetaError >= smo_pos->E0)
	   smo_pos->Zbeta = smo_pos->Kslide;
	else if (smo_pos->IbetaError <= -smo_pos->E0)
	   smo_pos->Zbeta = -smo_pos->Kslide;

	//	Sliding control filter -> back EMF calculator
    smo_pos->Ealpha = smo_pos->Ealpha + (smo_pos->Kslf * (smo_pos->Zalpha-smo_pos->Ealpha));
    smo_pos->Ebeta  = smo_pos->Ebeta  + (smo_pos->Kslf * (smo_pos->Zbeta -smo_pos->Ebeta));

	//  Rotor angle calculator -> Theta = atan(-Ealpha,Ebeta)
    smo_pos->Theta = 0.1591549430918953f * atan2f(-smo_pos->Ealpha,smo_pos->Ebeta);
    if (smo_pos->Theta  < 0.0f)
    	smo_pos->Theta += 1.0f;

    smoPosOut->ElecTheta = smo_pos->Theta;
} // end of SMO_POS_run() function


//! \brief     Gets the Kslide gain in the SMO Module
//! \param[in] smo_posHandle  The smo_pos handle
//! \return    The KSlide gain in the SMO Module
inline float32_t SMO_POS_getKslideGain(SMO_POS_Handle smo_posHandle)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

  return(smo_pos->Kslide);
} // end of SMO_POS_getKslideGain() function


//! \brief     Gets the Kslf gain in the SMO Module
//! \param[in] smo_posHandle  The smo_pos handle
//! \return    The KSlf gain in the SMO Module
inline float32_t SMO_POS_getKslfGain(SMO_POS_Handle smo_posHandle)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

  return(smo_pos->Kslf);
} // end of SMO_POS_getKsfGain() function


//! \brief     Gets the Theta output of the SMO Module
//! \param[in] smo_posHandle  The smo_pos handle
//! \return    The Theta Angle in the SMO Module
inline float32_t SMO_POS_getTheta(SMO_POS_Handle smo_posHandle)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

  return(smo_pos->Theta);
} // end of SMO_POS_getTheta() function


//! \brief     Setup the SMO_POS module
//! \param[in] SMO_POS_Handle  The SMO_POS handle
//! \return    Rs			   The Motor Stator Resistance in Ohms
inline float32_t SMO_POS_get_Rs(SMO_POS_Handle smo_posHandle)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

	return(smo_pos->Rs);

} // end of SMO_POS_get_Rs() function


//! \brief     Setup the SMO_POS module
//! \param[in] SMO_POS_Handle  The SMO_POS handle
//! \return    Ls			   The Motor Stator Inductance in Henrys
inline float32_t SMO_POS_get_Ls(SMO_POS_Handle smo_posHandle)
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

	return(smo_pos->Ls);

} // end of SMO_POS_get_Ls() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // __SMOPOS_H__

