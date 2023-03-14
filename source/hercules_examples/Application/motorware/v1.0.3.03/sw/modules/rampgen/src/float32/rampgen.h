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

//! \file   ~/modules/rampgen/src/float32/rampgen.h
//! \brief  Contains the public interface to the 
//!         Ramp Generation module routines 
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "modules/math/src/float32/math_fpu32.h"


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

  float32_t  Freq;              //!< Input: Ramp Frequency (pu)
  float32_t  StepAngleMax;      //!< Parameter: Maximum step angle (pu)
  float32_t  Angle;             //!< Variable: Step angle (pu)
  float32_t  Gain;              //!< Input: Ramp gain (pu)
  float32_t  Offset;            //!< Input: Ramp offset (pu)
  int32_t  rampExecutionCount;	//!< Variable: Ramp cycle count

} RAMPGEN_Obj;

//! \brief Defines the Ramp Generation object handle
//!
typedef struct RAMPGEN_Obj   *RAMPGEN_Handle;

// **************************************************************************
// the function prototypes

//! \brief     Setup the Ramp Generator
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \param[in] Freq           The Ramp Frequency
//! \param[in] StepAngleMax   The Maximum step angle
//! \param[in] Angle          The Step angle
//! \param[in] Gain           The Ramp gain
//! \param[in] Offset         The Ramp offset
void RAMPGEN_setup(RAMPGEN_Handle rampgenHandle,const float32_t Freq,const float32_t StepAngleMax,const float32_t Angle,const float32_t Gain,const float32_t Offset);

//! \brief     Initializes the RAMPGEN module
//! \param[in] pMemory            A pointer to the memory for the Rampgen object
//! \param[in] numBytes           The number of bytes allocated for the Rampgen object, bytes
//! \return The Rampgen (RAMPGEN) object handle
RAMPGEN_Handle RAMPGEN_init(void *pMemory, const size_t numBytes);


//! \brief     Setup the Ramp Generator
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \param[in] Freq           The Ramp Frequency
inline void RAMPGEN_setFreq(RAMPGEN_Handle rampgenHandle,const float32_t Freq)
{
	RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;

	rampgen->Freq = Freq;
}

//! \brief     Runs the Ramp Generator
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \param[in] Freq           The Ramp Frequency
//! \param[in] Gain           The Ramp gain
//! \param[in] Offset         The Ramp offset
//! \param[in] pOutValue      The pointer to the output data
inline void RAMPGEN_run(RAMPGEN_Handle rampgenHandle,float32_t *pOutValue)
{
  RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;
  float32_t Output;

  //rampgen->Freq = Freq;
  //rampgen->Gain = Gain;
  //rampgen->Offset = Offset;

  rampgen->Angle += (rampgen->StepAngleMax * rampgen->Freq); //Compute the angle rate

  if (rampgen->Angle>(1.0) )                                   //Saturate the angle rate within (-1,1)
    {
      rampgen->Angle -= (1.0);
    }
  else if (rampgen->Angle< (-1.0))
    {
      rampgen->Angle += (1.0);
    }

  Output = (rampgen->Angle * rampgen->Gain) + rampgen->Offset; // Compute the ramp output

  if (Output > (1.0))         // Saturate the ramp output within (-1,1)
    {
      Output -= (1.0);
      rampgen->rampExecutionCount++;
    }
  else if (Output < (-1.0))
    {
      Output += (1.0);
      rampgen->rampExecutionCount++;
    }


  *pOutValue = Output;

  return;
  
} // end of RAMPGEN_run() function


//! \brief     Sets the Maximum step angle in the Ramp Generator
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \param[in] StepAngleMax   The Maximum step angle
inline void RAMPGEN_setStepAngleMax(RAMPGEN_Handle rampgenHandle,const float32_t StepAngleMax)
{
  RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;

  rampgen->StepAngleMax = StepAngleMax;

  return;
} // end of RAMPGEN_setStepAngleMax() function


//! \brief     Sets the Angle in the Ramp Generator
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \param[in] Angle          The Step angle
inline void RAMPGEN_setAngle(RAMPGEN_Handle rampgenHandle,const float32_t Angle)
{
  RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;

  rampgen->Angle = Angle;

  return;
} // end of RAMPGEN_setAngle() function

//! \brief     Sets the cycle count of the Ramp Generator
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \param[in] countVal   	  The count value to reset the ramp cycle counter
inline void RAMPGEN_setExecutionCount(RAMPGEN_Handle rampgenHandle,const int32_t countVal)
{
  RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;

  rampgen->rampExecutionCount = countVal;

  return;
} // end of RAMPGEN_setExecutionCount() function


//! \brief     Get the Ramp Generator cycle count
//! \param[in] rampgenHandle  The RAMPGEN handle
//! \return    rampExecutionCount (number of ramp cycles encountered)
inline int32_t RAMPGEN_getExecutionCount(RAMPGEN_Handle rampgenHandle)
{
  RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;

  return(rampgen->rampExecutionCount);

} // end of RAMPGEN_setStepAngleMax() function



#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif //end of _RAMPGEN_H_ definition

