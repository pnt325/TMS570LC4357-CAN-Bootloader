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
//! \file   ~/sw/modules/rampgen/src/32b/rampgen.c
//! \brief  Portable C fixed point code.  These functions define the 
//!         Ramp Generation module routines
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "sw/modules/rampgen/src/32b/rampgen.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

void RAMPGEN_init(RAMPGEN_Handle rampgenHandle,const _iq Freq,const _iq StepAngleMax,
                  const _iq Angle,const _iq Gain,const _iq Offset)
{
  RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;

  rampgen->Freq = Freq;
  rampgen->StepAngleMax = StepAngleMax;
  rampgen->Angle = Angle;
  rampgen->Gain = Gain;
  rampgen->Offset = Offset;

  return;
} // end of RAMPGEN_init() function


void RAMPGEN_setStepAngleMax(RAMPGEN_Handle rampgenHandle,const _iq StepAngleMax)
{
  RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;

  rampgen->StepAngleMax = StepAngleMax;

  return;
} // end of RAMPGEN_setStepAngleMax() function


void RAMPGEN_setAngle(RAMPGEN_Handle rampgenHandle,const _iq Angle)
{
  RAMPGEN_Obj *rampgen = (RAMPGEN_Obj *)rampgenHandle;

  rampgen->Angle = Angle;

  return;
} // end of RAMPGEN_setAngle() function

// end of file
