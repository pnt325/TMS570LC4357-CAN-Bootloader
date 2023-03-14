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
//! \file   ~/drivers/pwm/src/32b/hercules/tms570ls3137/pwm.c
//! \brief  Contains the various functions related to the
//!         pulse width modulation (PWM) object
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "drivers/pwm/src/32b/hercules/tms570ls3137/pwm.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions


PWM_Handle PWM_init(void *pMemory,const size_t numBytes)
{
  PWM_Handle pwmHandle;


  if(numBytes < sizeof(PWM_Obj))
    return((PWM_Handle)NULL);


  // assign the handle
  pwmHandle = (PWM_Handle)pMemory;

  return(pwmHandle);
} // end of PWM_init() function


PWM_SYNC_Handle PWM_SYNC_init(void *pMemory,const size_t numBytes)
{
  PWM_SYNC_Handle pwmSyncHandle;


  if(numBytes < sizeof(PWM_SYNC_Obj))
    return((PWM_SYNC_Handle)NULL);


  // assign the handle
  pwmSyncHandle = (PWM_SYNC_Handle)pMemory;

  return(pwmSyncHandle);
} // end of PWM_SYNC_init() function

// end of file
