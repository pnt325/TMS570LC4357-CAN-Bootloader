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
//! \file   ~/drivers/qep/src/32b/hercules/champion/enc.c
//! \brief  ENC driver for TMS570
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "drivers/qep/src/32b/hercules/champion/enc.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

//! \brief     Initializes the ENC module
//! \param[in] pMemory            A pointer to the memory for the ENC object
//! \param[in] numBytes           The number of bytes allocated for the ENC object, bytes
//! \param[in] lineCounts         Counts per rotation of encoder
//! \param[in] polePairs          Number of pole pairs of the motor
//! \param[in] calibratedAngle    Raw angular offset between encoder index and phase a
//! \param[in] dir          	  Direction of positive rotation of the motor
//! \return The  ENC object handle
ENC_Handle ENC_init(void *pMemory,const size_t numBytes, const uint32_t lineCounts, const uint32_t polePairs, const int32_t calibratedAngle, const int32_t dir)
{
  ENC_Handle encHandle;

  if(numBytes < sizeof(ENC_Obj))
    return((ENC_Handle)NULL);

  // assign the handle
  encHandle = (ENC_Handle)pMemory;

  //Setup the ENC module
  ENC_setup(encHandle, lineCounts, polePairs, calibratedAngle, dir);

  return(encHandle);
} // end of ENC_init() function


//! \brief     Setup the ENC module
//! \param[in] encHandle          The enc handle
//! \param[in] lineCounts         Counts per rotation of encoder
//! \param[in] polePairs          Number of pole pairs of the motor
//! \param[in] calibratedAngle    Raw angular offset between encoder index and phase a
//! \param[in] dir          	  Direction of positive rotation of the motor
void ENC_setup( ENC_Handle encHandle, const uint32_t lineCounts, const uint32_t polePairs, const int32_t calibratedAngle, const int32_t dir)
{
	ENC_Obj *obj = (ENC_Obj *)encHandle;

	//TODO figure out how to configure line counts in the encoder hardware
	obj->lineCounts = lineCounts;

	if(dir >= 0)
	{obj->direction = 1;}
	else
	{obj->direction = -1;}

	obj->MechScaler = 1.0 / (4* obj->lineCounts);

	obj->calibratedAngle = calibratedAngle;

	obj->polePairs = polePairs;

	obj->rawTheta = 0x0;
	obj->ElecTheta = 0.0;
	obj->MechTheta = 0.0;
} // end of ENC_setup() function



