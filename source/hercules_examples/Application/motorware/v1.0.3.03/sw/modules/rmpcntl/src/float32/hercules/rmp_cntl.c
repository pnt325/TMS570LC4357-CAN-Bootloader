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
//! \file   ~modules/rmpcntl/src/float32/hercules/rmp_cntl.c
//! \brief  Portable C fixed point code.  These functions define the
//!         Ramp Control module routines
//!
//! (C) Copyright 2012, Texas Instruments, Inc.



// **************************************************************************
// the includes

#include "modules/rmpcntl/src/float32/hercules/rmp_cntl.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

//! \brief           Function to initialize the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
RMPCNTL_handle RMPCNTL_init(void *pMemory, const size_t numBytes)
{
	RMPCNTL_handle rmpCntlHandle;

	if(numBytes < sizeof(RMPCNTL_Obj))
		return((RMPCNTL_handle)NULL);

	// assign the handle
	rmpCntlHandle = (RMPCNTL_handle)pMemory;

	return(rmpCntlHandle);
} // end of RMPCNTL_init() function


//! \brief           Function to setup the Ramp Control Module
//! \param [in/out]  rmpCntlHandle		The Handle for the Ramp Control Module
void RMPCNTL_Setup(RMPCNTL_handle rmpCntlHandle)
{
	RMPCNTL_Obj *rmpCntl = (RMPCNTL_Obj *)rmpCntlHandle;

	rmpCntl->targetValue = 0;
	rmpCntl->rampDelayMax  = 5;
	rmpCntl->rampLowLimit = -1.0;
	rmpCntl->rampHighLimit = 1.0;
	rmpCntl->rampDelayCount = 0;
	rmpCntl->setpointValue = 0;
	rmpCntl->stepSize = 0.01;
	rmpCntl->equalFlag = 0;

}
