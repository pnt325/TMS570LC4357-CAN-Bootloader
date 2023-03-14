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
//! \file   ~/drivers/qep/src/32b/hercules/rm48l952/qep.c
//! \brief  QEP driver for TMS570
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "drivers/qep/src/32b/hercules/rm48l952/qep.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

//! \brief     Initializes the QEP module
//! \param[in] pMemory            A pointer to the memory for the QEP object
//! \param[in] numBytes           The number of bytes allocated for the QEP object, bytes
//! \param[in] lineCounts         Counts per rotation of encoder
//! \param[in] polePairs          Number of pole pairs of the motor
//! \param[in] calibratedAngle    Raw angular offset between encoder index and phase a
//! \param[in] dir          	  Direction of positive rotation of the motor
//! \return The  QEP object handle
QEP_Handle QEP_init(void *pMemory,const size_t numBytes, const uint32_t lineCounts, const uint32_t polePairs, const int32_t calibratedAngle, const int32_t dir)
{
  QEP_Handle qepHandle;

  if(numBytes < sizeof(QEP_Obj))
    return((QEP_Handle)NULL);

  // assign the handle
  qepHandle = (QEP_Handle)pMemory;

  //Setup the QEP module
  QEP_setup(qepHandle, lineCounts, polePairs, calibratedAngle, dir);

  return(qepHandle);
} // end of QEP_init() function


//! \brief     Setup the QEP module
//! \param[in] qepHandle          The qep handle
//! \param[in] lineCounts         Counts per rotation of encoder
//! \param[in] polePairs          Number of pole pairs of the motor
//! \param[in] calibratedAngle    Raw angular offset between encoder index and phase a
//! \param[in] dir          	  Direction of positive rotation of the motor
void QEP_setup( QEP_Handle qepHandle, const uint32_t lineCounts, const uint32_t polePairs, const int32_t calibratedAngle, const int32_t dir)
{
	QEP_Obj *obj = (QEP_Obj *)qepHandle;

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
} // end of QEP_setup() function


//! \brief     Initializes the QEP HET module
//! \param[in] pMemory            A pointer to the memory for the QEP HET object
//! \param[in] numBytes           The number of bytes allocated for the QEP HET object, bytes
//! \return The  QEP HET object handle
QEP_HET_Handle QEP_HET_init(void *pMemory,const size_t numBytes)
{
	QEP_HET_Handle qepHETHandle;

  if(numBytes < sizeof(QEP_HET_Obj))
    return((QEP_HET_Handle)NULL);

  // assign the handle
  qepHETHandle = (QEP_HET_Handle)pMemory;

  return(qepHETHandle);
} // end of QEP_init() function
