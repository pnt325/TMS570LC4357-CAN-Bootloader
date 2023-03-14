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
#ifndef _CLARKE_H_
#define _CLARKE_H_

//! \file   ~sw/modules/clarke/src/32b/clarke.h
//! \brief  Contains the public interface to the 
//!         Clarke transform (CLARKE) module routines
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "sw/modules/iqmath/src/32b/IQmathLib.h"
#include "sw/modules/math/src/32b/math.h"
#include "sw/modules/types/src/32b/types.h"

//!
//! \defgroup CLARKE

//!
//! \ingroup CLARKE
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines



// **************************************************************************
// the typedefs

//! \brief Defines the CLARKE object
//!
typedef struct _CLARKE_Obj_
{
  _iq      alpha_sf;           //!< the scale factor for the alpha component
  _iq      beta_sf;            //!< the scale factor for the beta component

  uint_least8_t  numSensors;   //!< the number of sensors

} CLARKE_Obj;


//! \brief Defines the CLARKE handle
//!
typedef struct CLARKE_Obj   *CLARKE_Handle;


// **************************************************************************
// the globals


// **************************************************************************
// the function prototypes


//! \brief     Gets the number of sensors
//! \param[in] clarkeHandle  The Clarke transform handle
//! \return    The number of sensors
static inline uint_least8_t CLARKE_getNumSensors(CLARKE_Handle clarkeHandle)
{
  CLARKE_Obj *clarke = (CLARKE_Obj *)clarkeHandle;

  return(clarke->numSensors);
} // end of CLARKE_getNumSensors() function


//! \brief     Initializes the Clarke transform module
//! \param[in] pMemory            A pointer to the memory for the Clarke object
//! \param[in] numBytes           The number of bytes allocated for the Clarke object, bytes
//! \return The Clarke (CLARKE) object handle
extern CLARKE_Handle CLARKE_init(void *pMemory,const size_t numBytes);


//! \brief     Runs the Clarke transform module for three inputs
//! \param[in] clarkeHandle  The Clarke transform handle
//! \param[in] pInVec        The pointer to the input vector
//! \param[in] pOutVec       The pointer to the output vector
static inline void CLARKE_run(CLARKE_Handle clarkeHandle,const MATH_vec3 *pInVec,MATH_vec2 *pOutVec)
{
  CLARKE_Obj *clarke = (CLARKE_Obj *)clarkeHandle;

  uint_least8_t numSensors = clarke->numSensors;

  _iq alpha_sf = clarke->alpha_sf;
  _iq beta_sf = clarke->beta_sf;


  if(numSensors == 3)
    {
      pOutVec->value[0] = _IQmpy(lshft_1(pInVec->value[0]) - (pInVec->value[1] + pInVec->value[2]),alpha_sf);
      pOutVec->value[1] = _IQmpy(pInVec->value[1] - pInVec->value[2],beta_sf);
    }
  else if(numSensors == 2)
    {
      pOutVec->value[0] = _IQmpy(pInVec->value[0],alpha_sf);
      pOutVec->value[1] = _IQmpy(pInVec->value[0] + lshft_1(pInVec->value[1]),beta_sf);
    }

  return;
} // end of CLARKE_run() function


//! \brief     Runs the Clarke transform module for two inputs
//! \param[in] clarkeHandle  The Clarke transform handle
//! \param[in] pInVec        The pointer to the input vector
//! \param[in] pOutVec       The pointer to the output vector
static inline void CLARKE_run_twoInput(CLARKE_Handle clarkeHandle,const MATH_vec2 *pInVec,MATH_vec2 *pOutVec)
{
  CLARKE_Obj *clarke = (CLARKE_Obj *)clarkeHandle;

  _iq beta_sf = clarke->beta_sf;


  pOutVec->value[0] = pInVec->value[0];

  pOutVec->value[1] = _IQmpy(pInVec->value[0] + _IQmpy2(pInVec->value[1]),beta_sf);

  return;
} // end of CLARKE_run_twoInput() function


//! \brief     Sets the number of sensors
//! \param[in] clarkeHandle  The Clarke transform handle
//! \param[in] numSensors    The number of sensors
static inline void CLARKE_setNumSensors(CLARKE_Handle clarkeHandle,const uint_least8_t numSensors)
{
  CLARKE_Obj *clarke = (CLARKE_Obj *)clarkeHandle;

  clarke->numSensors = numSensors;

  return;
} // end of CLARKE_setNumSensors() function


//! \brief     Sets the scale factors
//! \param[in] clarkeHandle  The Clarke transform handle
//! \param[in] alpha_sf      The scale factor for the alpha voltage
//! \param[in] beta_sf       The scale factor for the beta voltage
static inline void CLARKE_setScaleFactors(CLARKE_Handle clarkeHandle,const _iq alpha_sf,const _iq beta_sf)
{
  CLARKE_Obj *clarke = (CLARKE_Obj *)clarkeHandle;


  clarke->alpha_sf = alpha_sf;
  clarke->beta_sf = beta_sf;

  return;
} // end of CLARKE_setScaleFactors() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // end of _CLARKE_H_ definition

