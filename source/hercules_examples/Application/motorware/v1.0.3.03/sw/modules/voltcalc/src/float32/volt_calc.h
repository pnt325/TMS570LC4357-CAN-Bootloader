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
#ifndef __VOLT_CALC_H__
#define __VOLT_CALC_H__

//! \file   ~/modules/voltcalc/src/float32/volt_calc.h
//! \brief  Contains the public interface to the 3 phase
//!         switching voltage calculation module.
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "modules/math/src/float32/math_fpu32.h"
#include "modules/types/src/32b/controller_data_types.h"

//!
//! \defgroup VOLT

//!
//! \ingroup VOLT
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

#define ONE_THIRD  0.33333333333333f
#define TWO_THIRD  0.66666666666667f
#define INV_SQRT3  0.57735026918963f


// **************************************************************************
// the typedefs

//! \brief Defines the VOLT_CALC controller object
//!
typedef struct _VOLT_CALC_Obj_{
    	uint32_t	OutOfPhase; 	//!< Parameter: Out of Phase adjustment (0 or 1)
    	float32_t	MfuncV1;  		//!< Parameter: Modulation voltage phase A (pu)
    	float32_t	MfuncV2;		//!< Parameter: Modulation voltage phase B (pu)
    	float32_t	MfuncV3;		//!< Parameter: Modulation voltage phase C (pu)
	  	float32_t	VphaseA;		//!< Parameter: Phase voltage phase A (pu)
	  	float32_t	VphaseB;		//!< Parameter: Phase voltage phase B (pu)
	  	float32_t	VphaseC;		//!< Parameter: Phase voltage phase C (pu)
		} VOLT_CALC_Obj;
		
		
//! \brief Defines the VOLT CALC handle
//!
typedef VOLT_CALC_Obj *VOLT_CALC_Handle;

// **************************************************************************
// the function prototypes

//! \brief     Initializes the VOLT_CALC module
//! \param[in] pMemory            A pointer to the memory for the VOLT_CALC object
//! \param[in] numBytes           The number of bytes allocated for the VOLT_CALC object, bytes
//! \return The VOLT_CALC object handle
VOLT_CALC_Handle VOLT_CALC_init(void *pMemory,const size_t numBytes);


//! \brief     Runs the VOLT_CALC module
//! \param[in] volt_calcHandle  The volt_calc handle
//! \param[in] ADC_Data_t 		The DC Bus Voltage
//! \param[in] pMfuncV 			The switching functions
//! \param[out] pVout 			The transformed voltages
inline void VOLT_CALC_run(VOLT_CALC_Handle volt_calcHandle, const ADC_Data_t* DcBusV, const MATH_vec3 *pMfuncV, MATH_vec2* pVout )
{
	VOLT_CALC_Obj *volt = (VOLT_CALC_Obj *)volt_calcHandle;

	volt->MfuncV1 = pMfuncV->value[0];
	volt->MfuncV2 = pMfuncV->value[1];
	volt->MfuncV3 = pMfuncV->value[2];

    if (volt->OutOfPhase > 0)
    {
       volt->MfuncV1 = -volt->MfuncV1;
       volt->MfuncV2 = -volt->MfuncV2;
       volt->MfuncV3 = -volt->MfuncV3;
    }

    // scale the incomming Modulation functions with the DC bus voltage value
    volt->MfuncV1 = (DcBusV->dcBusV * volt->MfuncV1);
    volt->MfuncV2 = (DcBusV->dcBusV * volt->MfuncV2);
    volt->MfuncV3 = (DcBusV->dcBusV * volt->MfuncV3);

    // calculate the 3 Phase voltages
    // Phase A
    volt->VphaseA = (TWO_THIRD * volt->MfuncV1);
    volt->VphaseA -= (ONE_THIRD * volt->MfuncV2);
    volt->VphaseA -= (ONE_THIRD * volt->MfuncV3);

    // Phase B
    volt->VphaseB = (TWO_THIRD * volt->MfuncV2);
    volt->VphaseB -= (ONE_THIRD * volt->MfuncV1);
    volt->VphaseB -= (ONE_THIRD * volt->MfuncV3);

    // Phase C
    volt->VphaseC = (TWO_THIRD * volt->MfuncV3);
    volt->VphaseC -= (ONE_THIRD * volt->MfuncV1);
    volt->VphaseC -= (ONE_THIRD * volt->MfuncV2);

    // Voltage transformation (a,b,c)  ->  (Alpha,Beta)
    // Alpha-axis
    pVout->value[0] = volt->VphaseA;

    // Beta-axis
    pVout->value[1] = ((volt->VphaseA + (2 * volt->VphaseB)) * INV_SQRT3);
}


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // __VOLT_CALC_H__

