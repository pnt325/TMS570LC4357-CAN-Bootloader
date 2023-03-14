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
#ifndef __ENC_H__
#define __ENC_H__

//! \file   ~/drivers/qep/src/32b/hercules/champion/enc.h
//! \brief  ENC driver for TMS570
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

#include <math.h>
#include "modules/math/src/float32/math_fpu32.h"
#include "modules/types/src/32b/controller_data_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// **************************************************************************
// the defines


// **************************************************************************
// the typedefs

//! \brief Defines the ENC object
//!
typedef struct _ENC_Obj_{
	float32_t	ElecTheta;      	//!< The electrical position of the motor
	float32_t	MechTheta;      	//!< The mechanical position of the motor
	uint32_t	lineCounts;     	//!< The line count of the encoder
	uint32_t	polePairs;      	//!< The number of motor pole pairs
	int32_t		rawTheta;        	//!< A parameter based on the encoder count
	int32_t		calibratedAngle; 	//!< Encoder offset to zero electrical degrees
	float32_t	MechScaler;	   		//!< Scale from electrical position to mechanical position
	int32_t		direction;	   		//!< Positive direction of the motor
}  ENC_Obj;


//! \brief Defines the ENC handle
//!
typedef ENC_Obj *ENC_Handle;


// **************************************************************************
// the function prototypes

//! \brief     Initializes the ENC module
//! \param[in] pMemory	A pointer to the memory for the ENC object
//! \param[in] numBytes	The number of bytes allocated for the ENC object, bytes
//! \return    The ENC object handle
ENC_Handle ENC_init(void *pMemory,const size_t numBytes, const uint32_t lineCounts, const uint32_t polePairs, const int32_t calibratedAngle, const int32_t dir);


//! \brief     Setup the ENC module
//! \param[in] encHandle          The enc handle
//! \param[in] lineCounts         Counts per rotation of encoder
//! \param[in] polePairs          Number of pole pairs of the motor
//! \param[in] calibratedAngle
//! \param[in] dir
void ENC_setup( ENC_Handle encHandle, const uint32_t lineCounts, const uint32_t polePairs, const int32_t calibratedAngle, const int32_t dir);


//! \brief     Set Electric Theta
//! \param[in] encHandle          The enc handle
//! \param[in] elecTheta          Value of electric theta to be set (pu)
inline void ENC_set_calibratedAngle( ENC_Handle encHandle, const int32_t calibratedAngle)
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;

    obj->calibratedAngle = calibratedAngle;
} // end of ENC_set_calibratedAngle() function


//! \brief     Get Electric Theta
//! \param[in] encHandle	The enc handle
//! \return    calibratedAngle (pu)
inline int32_t ENC_get_calibratedAngle( ENC_Handle encHandle )
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;

    return( obj->calibratedAngle);
} // end of ENC_get_calibratedAngle() function


//! \brief     Set Electric Theta
//! \param[in] encHandle          The enc handle
//! \param[in] elecTheta          Value of electric theta to be set (pu)
inline void ENC_set_ElecTheta( ENC_Handle encHandle, const float32_t elecTheta)
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;

    obj->ElecTheta = elecTheta;
} // end of ENC_set_ElecTheta() function


//! \brief     Get Mechanical Theta
//! \param[in] encHandle	The enc handle
//! \return    Mechanical	Theta (pu)
inline float32_t ENC_get_MechTheta( ENC_Handle encHandle )
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;
    
    return(obj->MechTheta);
} // end of ENC_get_MechTheta() function


//! \brief     Set number of pole pairs
//! \param[in] encHandle	The enc handle
//! \param[in] polePairs	The number of motor pole pairs
inline void ENC_set_polePairs( ENC_Handle encHandle, const uint32_t   polePairs)
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;

    obj->polePairs = polePairs;
} // end of ENC_set_polePairs() function


//! \brief     	Get number of pole pairs
//! \param[in]  encHandle	The enc handle
//! \return     polePairs
inline uint32_t  ENC_get_polePairs( ENC_Handle encHandle )
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;

    return( obj->polePairs);
} // end of ENC_get_polePairs() function


//! \brief     Set direction
//! \param[in] encHandle          The enc handle
//! \param[in] direction          Set motor-encoder direction
inline void ENC_set_direction( ENC_Handle encHandle, const int32_t   direction)
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;

    obj->direction = direction;
} // end of ENC_set_direction() function


//! \brief     Get direction
//! \param[in] encHandle          The enc handle
//! \return    direction (motor-encoder)
inline int32_t ENC_get_direction( ENC_Handle encHandle )
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;

    return(obj->direction);
} // end of ENC_get_direction() function


//! \brief     Set lineCounts
//! \param[in] encHandle          The enc handle
//! \param[in] lineCounts         Set encoder line counts
inline void ENC_set_lineCounts( ENC_Handle encHandle, const uint32_t   lineCounts)
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;

    obj->lineCounts = lineCounts;
} // end of ENC_set_lineCounts() function


//! \brief     Get lineCounts
//! \param[in] encHandle          The enc handle
//! \return    lineCounts (encoder)
inline uint32_t ENC_get_lineCounts( ENC_Handle encHandle )
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;

    return(obj->lineCounts);
} // end of ENC_get_lineCounts() function


//! \brief     Setup the ENC module
//! \param[in]  encHandle		The enc handle
//! \param[in]  POSCNT_Value	The count value from the HET
//! \param[out] elecPos			the (electrical) position of the rotor
inline void ENC_run( ENC_Handle encHandle, ElecPos_Data_t* elecPos, uint32_t *POSCNT_Value)
{
    ENC_Obj *obj = (ENC_Obj *)encHandle;
    
    if(obj->direction == -1)
    	obj->rawTheta = (int32_t)( (4*obj->lineCounts) - (*POSCNT_Value));
    else
    	obj->rawTheta = (int32_t)(*POSCNT_Value);
    
    obj->rawTheta += obj->calibratedAngle;

    // Bound rawTheta
    if (obj->rawTheta < 0)
    	obj->rawTheta = obj->rawTheta+ 4*obj->lineCounts;
    else if (obj->rawTheta > 4*obj->lineCounts)
    	obj->rawTheta = obj->rawTheta- 4*obj->lineCounts;

    
    obj->MechTheta = obj->MechScaler * (float32_t) obj->rawTheta;
    
    // Scale ElecTheta, then keep bounded between [0.0, 1.0)
    obj->ElecTheta = fmodf( (obj->MechTheta * (float32_t)obj->polePairs), 1.0);
    
    elecPos->ElecTheta = obj->ElecTheta;
    
    return;
} // end of ENC_run() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif // __ENC_H__
