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
#ifndef _RAMPGEN_H_
#define _RAMPGEN_H_

//! \file   ~/sw/modules/rampgen/src/32b/rampgen.h
//! \brief  Contains the public interface to the 
//!         Ramp Generation module routines 
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "sw/modules/iqmath/src/32b/IQmathLib.h"
#include "sw/modules/math/src/32b/math.h"


//!
//! \defgroup RAMPGEN

//!
//! \ingroup RAMPGEN
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

// **************************************************************************
// the typedefs

//! \brief Defines the Ramp Generation object
//!
typedef struct _RAMPGEN_Obj_
{

  _iq  Freq;              //!< Input: Ramp Frequency (pu)
  _iq  StepAngleMax;      //!< Parameter: Maximum step angle (pu)
  _iq  Angle;             //!< Variable: Step angle (pu)
  _iq  Gain;              //!< Input: Ramp gain (pu)
  _iq  Offset;            //!< Input: Ramp offset (pu)

} RAMPGEN_Obj;

//! \brief Defines the Park handle
//!
typedef struct RAMPGEN_Obj   *RAMPGEN_Handle;

// **************************************************************************
// the function prototypes

//! \brief     Initializes the Ramp Generator
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \param[in] Freq           The Ramp Frequency
//! \param[in] StepAngleMax   The Maximum step angle
//! \param[in] Angle          The Step angle
//! \param[in] Gain           The Ramp gain
//! \param[in] Offset         The Ramp offset
extern void RAMPGEN_init(RAMPGEN_Handle rampgenHandle,const _iq Freq,const _iq StepAngleMax,
                         const _iq Angle,const _iq Gain,const _iq Offset);


//! \brief     Runs the Ramp Generator
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \param[in] Freq           The Ramp Frequency
//! \param[in] Gain           The Ramp gain
//! \param[in] Offset         The Ramp offset
//! \param[in] pOutValue      The pointer to the output data
static inline void RAMPGEN_run(RAMPGEN_Handle rampgenHandle,const _iq Freq,const _iq Gain,
                               const _iq Offset,_iq *pOutValue)
{
  RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;
  _iq Output;

  rampgen->Freq = Freq;
  rampgen->Gain = Gain;
  rampgen->Offset = Offset;

  rampgen->Angle += _IQmpy(rampgen->StepAngleMax,rampgen->Freq); //Compute the angle rate

  if (rampgen->Angle>_IQ(1.0))                                   //Saturate the angle rate within (-1,1)
    {
      rampgen->Angle -= _IQ(1.0);
    }
  else if (rampgen->Angle<_IQ(-1.0))
    {
      rampgen->Angle += _IQ(1.0);
    }

  Output = _IQmpy(rampgen->Angle,rampgen->Gain) + rampgen->Offset; // Compute the ramp output

  if (Output > _IQ(1.0))         // Saturate the ramp output within (-1,1)
    {
      Output -= _IQ(1.0);
    }
  else if (Output < _IQ(-1.0))
    {
      Output += _IQ(1.0);
    }

  *pOutValue = Output;

  return;
  
} // end of RAMPGEN_run() function


//! \brief     Sets the Maximum step angle in the Ramp Generator
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \param[in] StepAngleMax   The Maximum step angle
extern void RAMPGEN_setStepAngleMax(RAMPGEN_Handle rampgenHandle,const _iq StepAngleMax);


//! \brief     Sets the Angle in the Ramp Generator
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \param[in] Angle          The Step angle
extern void RAMPGEN_setAngle(RAMPGEN_Handle rampgenHandle,const _iq Angle);

#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif //end of _RAMPGEN_H_ definition

