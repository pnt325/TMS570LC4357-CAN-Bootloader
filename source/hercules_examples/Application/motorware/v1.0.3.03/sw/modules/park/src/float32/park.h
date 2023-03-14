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
#ifndef _PARK_H_
#define _PARK_H_

//! \file   ~/modules/park/src/float32/park.h
//! \brief  Contains the public interface to the 
//!         Park transform module routines 
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
//! \defgroup PARK

//!
//! \ingroup PARK
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines



// **************************************************************************
// the typedefs

//! \brief Defines the PARK object
//!
typedef struct _PARK_Obj_
{

  float32_t  sinTh;      //!< the sine of the angle between the d,q and the alpha,beta coordinate systems
  float32_t  cosTh;      //!< the cosine of the angle between the d,q and the alpha,beta coordinate systems

} PARK_Obj;


//! \brief Defines the PARK handle
//!
typedef struct PARK_Obj   *PARK_Handle;


// **************************************************************************
// the function prototypes

//! \brief     Gets the cosine of the angle between the d,q and the alpha,beta coordinate systems
//! \param[in] parkHandle  The Park transform handle
//! \return    The cosine of the angle
inline float32_t PARK_getCosTh(PARK_Handle parkHandle)
{
  PARK_Obj *park = (PARK_Obj *)parkHandle;

  return(park->cosTh);
} // end of PARK_getCosTh() function


//! \brief     Gets the sine of the angle between the d,q and the alpha,beta coordinate systems
//! \param[in] parkHandle  The Park transform handle
//! \return    The sine of the angle
inline float32_t PARK_getSinTh(PARK_Handle parkHandle)
{
  PARK_Obj *park = (PARK_Obj *)parkHandle;

  return(park->sinTh);
} // end of PARK_getSinTh() function


//! \brief     Initializes the Park transform module
//! \param[in] pMemory      A pointer to the memory for the Park object
//! \param[in] numBytes     The number of bytes allocated for the Park object, bytes
//! \return The Park (PARK) object handle
PARK_Handle PARK_init(void *pMemory,const size_t numBytes);


//! \brief     Runs the Park transform module
//! \param[in] parkHandle  The Park transform handle
//! \param[in] pInVec      The pointer to the input vector
//! \param[in] pOutVec     The pointer to the output vector
inline void PARK_run(PARK_Handle parkHandle,const MATH_vec2 *pInVec,MATH_vec2 *pOutVec)
{
  PARK_Obj *park = (PARK_Obj *)parkHandle;

  float32_t sinTh = park->sinTh;
  float32_t cosTh = park->cosTh;

  float32_t value_0 = pInVec->value[0];
  float32_t value_1 = pInVec->value[1];

  pOutVec->value[0] = (value_0 * cosTh) + (value_1 * sinTh);
  pOutVec->value[1] = (value_1 * cosTh) - (value_0 * sinTh);

  return;
} // end of PARK_run() function

#ifdef CIMSIS
//! \brief     Sets up the Park transform module
//! \param[in] parkHandle  The Park transform handle
//! \param[in] Th          The angle between the d,q and the alpha,beta coordinate systems
inline void PARK_setup(PARK_Handle parkHandle,const float32_t Th)
{
  PARK_Obj *park = (PARK_Obj *)parkHandle;

  float32_t temp_theta    = (-1.0f)*(Th-0.5f) * 360.0f;	// Conversion for per unit [0,1] to [-0.5,0.5]
  	  	  	  										// Scaling of angle to degrees [-180,180]
  	  	  	  	  									// Inversion of phase due to CMSIS Cortex R DSP Library_2_0_0.lib sine/cosine table access
  // call CMSIS function
  arm_sin_cos_f32 (temp_theta,
	           &park->sinTh,
		       &park->cosTh);
  park->cosTh = -1 * park->cosTh;	// Due to CMSIS Cortex R DSP Library_2_0_0.lib cosine table access method

  return;
} // end of PARK_setup() function
#else
//! \brief     Sets up the Park transform module
//! \param[in] parkHandle  The Park transform handle
//! \param[in] Th          The angle between the d,q and the alpha,beta coordinate systems
inline void PARK_setup(PARK_Handle parkHandle,const float32_t Th)
{
  PARK_Obj *park = (PARK_Obj *)parkHandle;

  float32_t angle_temp = Th * 6.2831853f;

  park->sinTh = sinf(angle_temp);
  park->cosTh = cosf(angle_temp);

  return;
} // end of PARK_setup() function
#endif


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // end of _PARK_H_ definition

