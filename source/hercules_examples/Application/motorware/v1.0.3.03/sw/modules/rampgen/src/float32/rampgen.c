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
//! \file   ~/modules/rampgen/src/float32/rampgen.c
//! \brief  Portable C fixed point code.  These functions define the 
//!         Ramp Generation module routines
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "modules/rampgen/src/float32/rampgen.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

RAMPGEN_Handle RAMPGEN_init(void *pMemory, const size_t numBytes)
{
  RAMPGEN_Handle rampgenHandle;

  if(numBytes < sizeof(RAMPGEN_Obj))
    return((RAMPGEN_Handle)NULL);

  // assign the handle
  rampgenHandle = (RAMPGEN_Handle)pMemory;

  return(rampgenHandle);     
} // end of RAMPGEN_init() function


//! \brief     Setup the RAMPGEN module
//! \param[in] rampgenHandle	The rampgen handle
//! \param[in] Freq         	Ramp Frequency (pu)
//! \param[in] StepAngleMax     Maximum step angle (pu)
//! \param[in] Angle         	Step angle (pu)
//! \param[in] Gain          	Ramp gain (pu)
//! \param[in] Offset    		Ramp offset (pu)
void RAMPGEN_setup(RAMPGEN_Handle rampgenHandle,const float32_t Freq,const float32_t StepAngleMax,const float32_t Angle,const float32_t Gain,const float32_t Offset)
{
  RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;

  rampgen->Freq = Freq;
  rampgen->StepAngleMax = StepAngleMax;
  rampgen->Angle = Angle;
  rampgen->Gain = Gain;
  rampgen->Offset = Offset;

  return;
} // end of RAMPGEN_setup() function

// end of file
