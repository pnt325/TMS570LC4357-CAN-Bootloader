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
#ifndef _TRAJ_H_
#define _TRAJ_H_

//! \file   ~/sw/modules/traj/src/32b/traj.h
//! \brief  Contains public interface to various functions related
//!         to the trajectory (TRAJ) object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "sw/modules/types/src/float32/types_fpu32.h"
#include "sw/modules/iqmath/src/float32/IQmathLib_fpu32.h"

//!
//! \defgroup TRAJ

//!
//! \ingroup TRAJ
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

//! \brief Defines the trajectory (TRAJ) object
//!
typedef struct _TRAJ_Obj_
{
  _iq   targetValue;   //!< the target value for the trajectory
  _iq   intValue;      //!< the intermediate value along the trajectory
  _iq   minValue;      //!< the minimum value for the trajectory generator
  _iq   maxValue;      //!< the maximum value for the trajectory generator
  _iq   maxSlope;      //!< the maximum slope for the trajectory generator
} TRAJ_Obj;


//! \brief Defines the TRAJ handle
//!
typedef struct TRAJ_Obj   *TRAJ_Handle;


// **************************************************************************
// the globals


// **************************************************************************
// the function prototypes

//! \brief     Gets the intermediate value for the trajectory
//! \param[in] trajHandle  The TRAJ handle
//! \return    The intermediate value
inline _iq TRAJ_getIntValue(TRAJ_Handle trajHandle)
{
  TRAJ_Obj *traj = (TRAJ_Obj *)trajHandle;

  return(traj->intValue);
} // end of TRAJ_getIntValue() function


//! \brief     Gets the minimum value for the trajectory
//! \param[in] trajHandle  The TRAJ handle
//! \return    The minimum value
inline _iq TRAJ_getMinValue(TRAJ_Handle trajHandle)
{
  TRAJ_Obj *traj = (TRAJ_Obj *)trajHandle;

  return(traj->minValue);
} // end of TRAJ_getMinValue() function


//! \brief     Gets the maximum slope for the trajectory
//! \param[in] trajHandle  The TRAJ handle
//! \return    The maximum slope
inline _iq TRAJ_getMaxSlope(TRAJ_Handle trajHandle)
{
  TRAJ_Obj *traj = (TRAJ_Obj *)trajHandle;

  return(traj->maxSlope);
} // end of TRAJ_getMaxSlope() function


//! \brief     Gets the maximum value for the trajectory
//! \param[in] trajHandle  The TRAJ handle
//! \return    The maximum value
inline _iq TRAJ_getMaxValue(TRAJ_Handle trajHandle)
{
  TRAJ_Obj *traj = (TRAJ_Obj *)trajHandle;

  return(traj->maxValue);
} // end of TRAJ_getMaxValue() function


//! \brief     Gets the target value for the trajectory
//! \param[in] trajHandle  The TRAJ handle
//! \return    The target value
inline _iq TRAJ_getTargetValue(TRAJ_Handle trajHandle)
{
  TRAJ_Obj *traj = (TRAJ_Obj *)trajHandle;

  return(traj->targetValue);
} // end of TRAJ_getTargetValue() function


//! \brief     Initializes the trajectory (TRAJ) object
//! \param[in] pMemory   A pointer to the memory for the trajectory (TRAJ) object
//! \param[in] numBytes  The number of bytes allocated for the trajectory object, bytes
//! \return The trajectory (TRAJ) object handle
TRAJ_Handle TRAJ_init(void *pMemory,const size_t numBytes);


//! \brief     Runs the trajectory (TRAJ) object
//! \param[in] trajHandle  The TRAJ handle
void TRAJ_run(TRAJ_Handle trajHandle);


//! \brief     Sets the intermediate value for the trajectory
//! \param[in] trajHandle  The TRAJ handle
//! \param[in] intValue    The intermediate value
inline void TRAJ_setIntValue(TRAJ_Handle trajHandle,const _iq intValue)
{
  TRAJ_Obj *traj = (TRAJ_Obj *)trajHandle;

  traj->intValue = intValue;

  return;
} // end of TRAJ_setIntValue() function


//! \brief     Sets the minimum value for the trajectory
//! \param[in] trajHandle  The TRAJ handle
//! \param[in] minValue    The minimum value
inline void TRAJ_setMinValue(TRAJ_Handle trajHandle,const _iq minValue)
{
  TRAJ_Obj *traj = (TRAJ_Obj *)trajHandle;

  traj->minValue = minValue;

  return;
} // end of TRAJ_setMinValue() function


//! \brief     Sets the maximum value for the trajectory
//! \param[in] trajHandle  The TRAJ handle
//! \param[in] maxSlope    The maximum value
inline void TRAJ_setMaxSlope(TRAJ_Handle trajHandle,const _iq maxSlope)
{
  TRAJ_Obj *traj = (TRAJ_Obj *)trajHandle;

  traj->maxSlope = maxSlope;

  return;
} // end of TRAJ_setMaxSlope() function


//! \brief     Sets the maximum value for the trajectory
//! \param[in] trajHandle  The TRAJ handle
//! \param[in] maxValue    The maximum value
inline void TRAJ_setMaxValue(TRAJ_Handle trajHandle,const _iq maxValue)
{
  TRAJ_Obj *traj = (TRAJ_Obj *)trajHandle;

  traj->maxValue = maxValue;

  return;
} // end of TRAJ_setMaxValue() function


//! \brief     Sets the target value for the trajectory
//! \param[in] trajHandle   The TRAJ handle
//! \param[in] targetValue  The target value
inline void TRAJ_setTargetValue(TRAJ_Handle trajHandle,const _iq targetValue)
{
  TRAJ_Obj *traj = (TRAJ_Obj *)trajHandle;

  traj->targetValue = targetValue;

  return;
} // end of TRAJ_setTargetValue() function


//! \brief     Sets up the trajectory (TRAJ) object
//! \param[in] trajHandle  The TRAJ handle
void TRAJ_setup(TRAJ_Handle trajHandle);


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // end of _TRAJ_H_ definition





