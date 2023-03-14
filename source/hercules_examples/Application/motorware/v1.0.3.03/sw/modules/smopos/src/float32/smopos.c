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
//! \file   ~/modules/smopos/src/float32/smopos.c
//! \brief  Contains the public interface to the sliding mode observer
//!         position feedback module.
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "modules/types/src/32b/types.h"
#include "modules/smopos/src/float32/smopos.h"


// **************************************************************************
// the globals


// **************************************************************************
// the functions


//! \brief     Initializes the SMO_POS module
//! \param[in] pMemory      A pointer to the memory for the SMO_POS object
//! \param[in] numBytes     The number of bytes allocated for the SMO_POS object, bytes
//! \param[in] Rs           Stator resistance (ohm)
//! \param[in] Ls           Stator inductance (H)
//! \param[in] Vb           Base phase voltage (volt)
//! \param[in] Ib           Base phase current (amp)
//! \param[in] period       Sampling period in sec
//! \return The SMO_POS object handle
SMO_POS_Handle SMO_POS_init(void *pMemory,const size_t numBytes, const float32_t Rs, const float32_t Ls,const float32_t Vb, const float32_t Ib, const float32_t period)
{
	SMO_POS_Handle smo_posHandle;
	SMO_POS_Obj *smo_pos;

    if(numBytes < sizeof(SMO_POS_Obj))
        { return( (SMO_POS_Handle) NULL);}

    // assign the handle
    smo_posHandle = (SMO_POS_Handle)pMemory;

    // assign the object
    smo_pos = (SMO_POS_Obj *)smo_posHandle;

    // Setup sliding mode observer
    SMO_POS_setup(smo_posHandle, Rs,  Ls, Vb, Ib, period);

    //Initialize the Filter
    smo_pos->Kslide = (float32_t) 0.15;
    smo_pos->Kslf = (float32_t) 0.1;
    smo_pos->E0 = 0.5;

    return(smo_posHandle);
}// end of SMO_POS_init() function


//! \brief     Sets up the SMO_POS module
//! \param[in] smo_posHandle  The smo_pos handle
//! \param[in] Rs           Stator resistance (ohm)
//! \param[in] Ls           Stator inductance (H)
//! \param[in] Vb           Base phase voltage (volt)
//! \param[in] Ib           Base phase current (amp)
//! \param[in] period       Sampling period in sec
void SMO_POS_setup(SMO_POS_Handle smo_posHandle, const float32_t Rs, const float32_t Ls,const float32_t Vb, const float32_t Ib, const float32_t period )
{
	SMO_POS_Obj *smo_pos = (SMO_POS_Obj *)smo_posHandle;

	smo_pos->Rs = Rs;

	smo_pos->Ls = Ls;

	smo_pos->Vb = Vb;

	smo_pos->Ib = Ib;

	smo_pos->Ts = period;

	SMO_POS_calc_params(smo_posHandle);
}// end of SMO_POS_setup() function

// end of file
