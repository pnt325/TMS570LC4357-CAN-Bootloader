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
#ifndef _PID_H_
#define _PID_H_

//! \file   ~/modules/pid/src/float32/pid.h
//! \brief  Contains the public interface to the 
//!         Proportional-Integral-Derivative controller (PID) module routines
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes
#ifdef CIMSIS
#include "modules/math/src/float32/core_r4_simd.h"
#include "modules/math/src/float32/arm_common_tables.h"
#endif

#include "modules/math/src/float32/math_fpu32.h"

//!
//! \defgroup PID

//!
//! \ingroup PID
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines



// **************************************************************************
// the typedefs

//! \brief Defines the PID controller object
//!
typedef struct _PID_Obj_
{
  float32_t Kp;                     //!< the proportional gain for the PID controller
  float32_t Ki;                     //!< the integral gain for the PID controller
  float32_t Kd;                     //!< the derivative gain for the PID controller

  float32_t Ui;                     //!< the integrator start value for the PID controller

  float32_t refValue;               //!< the reference input value
  float32_t fbackValue;             //!< the feedback input value
		
  float32_t outMin;                 //!< the minimum output value allowwed for the PID controller
  float32_t outMax;                 //!< the maximum output value allowwed for the PID controller

} PID_Obj; 


//! \brief Defines the PID handle
//!
typedef PID_Obj *PID_Handle;


// **************************************************************************
// the function prototypes

//! \brief     Gets the derivative gain in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \return    The derivative gain in the PID controller
inline float32_t PID_getDerivativeGain(PID_Handle pidHandle)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  return(pid->Kd);
} // end of PID_getDerivativeGain() function


//! \brief     Gets the feedback value in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \return    The feedback value in the PID controller
inline float32_t PID_getFbackValue(PID_Handle pidHandle)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  return(pid->fbackValue);
} // end of PID_getFbackValue() function


//! \brief     Gets the integral gain in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \return    The integral gain in the PID controller
inline float32_t PID_getIntegralGain(PID_Handle pidHandle)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  return(pid->Ki);
} // end of PID_getIntegralGain() function


//! \brief     Gets the proportional gain in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \return    The proportional gain in the PID controller
inline float32_t PID_getProportionalGain(PID_Handle pidHandle)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  return(pid->Kp);
} // end of PID_getProportionalGain() function


//! \brief     Gets the reference value in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \return    The reference value in the PID controller
inline float32_t PID_getRefValue(PID_Handle pidHandle)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  return(pid->refValue);
} // end of PID_getRefValue() function

//! \brief     Gets the integrator value in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \return    The integral start value for the PID controller
inline float32_t PID_getIntegrator(PID_Handle pidHandle)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  return(pid->Ui);
} // end of PID_getIntegrator() function

//! \brief     Gets the Saturation value in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \return    The Saturation value for the PID controller
inline float32_t PID_getSaturation(PID_Handle pidHandle)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  return(pid->outMax);
} // end of PID_getIntegrator() function

//! \brief     Initializes the PID controller
//! \param[in] pMemory   A pointer to the memory for the PID controller object
//! \param[in] numBytes  The number of bytes allocated for the PID controller object, bytes
//! \return The PID controller (PID) object handle
PID_Handle PID_init(void *pMemory,const size_t numBytes);

#ifdef CIMSIS
//! \brief     Runs the PID controller
//! \param[in] pidHandle   The PID controller handle
//! \param[in] refValue    The reference value to the controller
//! \param[in] fbackValue  The feedback value to the controller
//! \param[in] pOutValue   The pointer to the controller output value
inline void PID_run(PID_Handle pidHandle,const float32_t refValue,const float32_t fbackValue,float32_t *pOutValue)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  float32_t Error;			// PID internal variables
  float32_t Up;
  float32_t Ui;

  uint32_t  index;			// Index value returned by arm min/max f32 functions
  uint32_t  blocksize = 2;	// Block size for min/max value calculation
  float32_t minArg[2];		// Arguments for min function
  float32_t maxArg[2];		// Arguments for max function
  float32_t maxValue;		// Output of min function
  float32_t minValue;		// output of max function

  // Update proportional output
  Error = refValue - fbackValue;
  Ui = pid->Ui;                     // load the previous integral output
  Up = (pid->Kp * Error);           // Compute the proportional output

  // Compute the integral output with saturation
  // Handle saturation minimum bound condition
  minArg[0] = (Ui + (pid->Ki * Up));
  minArg[1] = pid->outMax;
  arm_min_f32(minArg,blocksize,&minValue,&index);

  // Handle saturation maximum bound condition
  maxArg[0] = minValue;
  maxArg[1] = pid->outMin;
  arm_max_f32 (maxArg,blocksize,&maxValue,&index);
  Ui = maxValue;

  pid->Ui = Ui;    // store the intetral output
  pid->refValue = refValue;
  pid->fbackValue = fbackValue;

  // Saturate the output
  // Handle saturation minimum bound condition
  minArg[0] = Up + Ui;
  minArg[1] = pid->outMax;
  arm_min_f32(minArg,blocksize,&minValue,&index);

  // Handle saturation maximum bound condition
  maxArg[0] = minValue;
  maxArg[1] = pid->outMin;
  arm_max_f32 (maxArg,blocksize,&maxValue,&index);
  *pOutValue = maxValue;

  return;
} // end of PID_run() function
#else
//! \brief     Runs the PID controller
//! \param[in] pidHandle   The PID controller handle
//! \param[in] refValue    The reference value to the controller
//! \param[in] fbackValue  The feedback value to the controller
//! \param[in] pOutValue   The pointer to the controller output value
inline void PID_run(PID_Handle pidHandle,const float32_t refValue,const float32_t fbackValue,float32_t *pOutValue)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  float32_t Error;
  float32_t Up,Ui;


  Error = refValue - fbackValue;

  Ui = pid->Ui;                                                  			// load the previous integral output
  Up = (pid->Kp * Error);                                    				// Compute the proportional output

  Ui = fmaxf(((fminf((Ui + (pid->Ki * Up)),(pid->outMax)))),(pid->outMin)); 	// Compute the integral output with saturation

  pid->Ui = Ui;                                                  			// store the intetral output
  pid->refValue = refValue;
  pid->fbackValue = fbackValue;

  *pOutValue = fmaxf(((fminf((Up + Ui),(pid->outMax)))),(pid->outMin)); 		// Saturate the output

  return;
} // end of PID_run() function
#endif

//! \brief     Sets the derivative gain in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \param[in] Kd         The derivative gain for the PID controller
inline void PID_setDerivativeGain(PID_Handle pidHandle,const float32_t Kd)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  pid->Kd = Kd;

  return;
} // end of PID_setDerivativeGain() function


//! \brief     Sets the gains in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \param[in] Kp         The proportional gain for the PID controller
//! \param[in] Ki         The integrator gain for the PID controller
//! \param[in] Kd         The derivative gain for the PID controller
inline void PID_setGains(PID_Handle pidHandle,const float32_t Kp,const float32_t Ki, const float32_t Kd)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  pid->Kp = Kp;
  pid->Ki = Ki;
  pid->Kd = Kd;

  return;
} // end of PID_setGains() function


//! \brief     Sets the integrator start value in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \param[in] Ui         The integral start value for the PID controller
inline void PID_setIntegrator(PID_Handle pidHandle,const float32_t Ui)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  pid->Ui = Ui;

  return;
} // end of PID_setIntegrator() function


//! \brief     Sets the integral gain in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \param[in] Ki         The integral gain for the PID controller
inline void PID_setIntegralGain(PID_Handle pidHandle,const float32_t Ki)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  pid->Ki = Ki;

  return;
} // end of PID_setIntegralGain() function


//! \brief     Sets the minimum and maximum output value allowed in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \param[in] outMin     The minimum output value allowed
//! \param[in] outMax     The maximum output value allowed
inline void PID_setMinMax(PID_Handle pidHandle,const float32_t outMin,const float32_t outMax)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  pid->outMin = outMin;
  pid->outMax = outMax;

  return;
} // end of PID_setMinMax() function


//! \brief     Sets the proportional gain in the PID controller
//! \param[in] pidHandle  The PID controller handle
//! \param[in] Kp         The proportional gain for the PID controller
inline void PID_setProportionalGain(PID_Handle pidHandle,const float32_t Kp)
{
  PID_Obj *pid = (PID_Obj *)pidHandle;

  pid->Kp = Kp;

  return;
} // end of PID_setProportionalGain() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif //end of _PID_H_ definition

