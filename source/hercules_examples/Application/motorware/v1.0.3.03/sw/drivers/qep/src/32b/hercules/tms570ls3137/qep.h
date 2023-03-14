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
#ifndef __QEP_H__
#define __QEP_H__

//! \file   ~/drivers/qep/src/32b/hercules/tms570ls3137/qep.h
//! \brief  QEP driver for TMS570
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

#include <math.h>
#include "modules/math/src/float32/math_fpu32.h"
#include "drivers/het/src/32b/hercules/tms570ls3137/het.h"
#include "modules/types/src/32b/controller_data_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// **************************************************************************
// the defines

#define QEP_COUNT_HET_OFFSET	52U

#define QEP_INDEX_HET_OFFSET	42U


// **************************************************************************
// the typedefs

//! \brief Defines the QEP object
//!
typedef struct _QEP_Obj_{
	float32_t	ElecTheta;      	//!< The electrical position of the motor
	float32_t	MechTheta;      	//!< The mechanical position of the motor
	uint32_t	lineCounts;     	//!< The line count of the encoder
	uint32_t	polePairs;      	//!< The number of motor pole pairs
	int32_t		rawTheta;        	//!< A parameter based on the encoder count
	int32_t		calibratedAngle; 	//!< Encoder offset to zero electrical degrees
	float32_t	MechScaler;	   		//!< Scale from electrical position to mechanical position
	int32_t		direction;	   		//!< Positive direction of the motor
}  QEP_Obj;


//! \brief Defines the QEP handle
//!
typedef QEP_Obj *QEP_Handle;

//! \brief Defines the QEP HET object
//!
typedef struct _QEP_HET_Obj_{
	uint32_t   POSCNT_Prog;       //!< program field
	uint32_t   POSCNT_Ctrl;       //!< ctrl field
	uint32_t   POSCNT_Data;       //!< data field
	uint32_t   POSCNT_Rsvd;       //!< reserved field
}  QEP_HET_Obj;

//! \brief Defines the QEP HET Object handle
//!
typedef QEP_HET_Obj *QEP_HET_Handle;


// **************************************************************************
// the function prototypes

//! \brief     Initializes the QEP module
//! \param[in] pMemory	A pointer to the memory for the QEP object
//! \param[in] numBytes	The number of bytes allocated for the QEP object, bytes
//! \return    The QEP object handle
QEP_Handle QEP_init(void *pMemory,const size_t numBytes, const uint32_t lineCounts, const uint32_t polePairs, const int32_t calibratedAngle, const int32_t dir);


//! \brief     Setup the QEP module
//! \param[in] qepHandle          The qep handle
//! \param[in] lineCounts         Counts per rotation of encoder
//! \param[in] polePairs          Number of pole pairs of the motor
//! \param[in] calibratedAngle
//! \param[in] dir
void QEP_setup( QEP_Handle qepHandle, const uint32_t lineCounts, const uint32_t polePairs, const int32_t calibratedAngle, const int32_t dir);


//! \brief     Set Electric Theta
//! \param[in] qepHandle          The qep handle
//! \param[in] elecTheta          Value of electric theta to be set (pu)
inline void QEP_set_calibratedAngle( QEP_Handle qepHandle, const int32_t calibratedAngle)
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;

    obj->calibratedAngle = calibratedAngle;
} // end of QEP_set_calibratedAngle() function


//! \brief     Get Electric Theta
//! \param[in] qepHandle	The qep handle
//! \return    calibratedAngle (pu)
inline int32_t QEP_get_calibratedAngle( QEP_Handle qepHandle )
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;

    return( obj->calibratedAngle);
} // end of QEP_get_calibratedAngle() function


//! \brief     Set Electric Theta
//! \param[in] qepHandle          The qep handle
//! \param[in] elecTheta          Value of electric theta to be set (pu)
inline void QEP_set_ElecTheta( QEP_Handle qepHandle, const float32_t elecTheta)
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;

    obj->ElecTheta = elecTheta;
} // end of QEP_set_ElecTheta() function


//! \brief     Get Mechanical Theta
//! \param[in] qepHandle	The qep handle
//! \return    Mechanical	Theta (pu)
inline float32_t QEP_get_MechTheta( QEP_Handle qepHandle )
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;
    
    return(obj->MechTheta);
} // end of QEP_get_MechTheta() function


//! \brief     Set number of pole pairs
//! \param[in] qepHandle	The qep handle
//! \param[in] polePairs	The number of motor pole pairs
inline void QEP_set_polePairs( QEP_Handle qepHandle, const uint32_t   polePairs)
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;

    obj->polePairs = polePairs;
} // end of QEP_set_polePairs() function


//! \brief     	Get number of pole pairs
//! \param[in]  qepHandle	The qep handle
//! \return     polePairs
inline uint32_t  QEP_get_polePairs( QEP_Handle qepHandle )
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;

    return( obj->polePairs);
} // end of QEP_get_polePairs() function


//! \brief     Set direction
//! \param[in] qepHandle          The qep handle
//! \param[in] direction          Set motor-encoder direction
inline void QEP_set_direction( QEP_Handle qepHandle, const int32_t   direction)
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;

    obj->direction = direction;
} // end of QEP_set_direction() function


//! \brief     Get direction
//! \param[in] qepHandle          The qep handle
//! \return    direction (motor-encoder)
inline int32_t QEP_get_direction( QEP_Handle qepHandle )
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;

    return(obj->direction);
} // end of QEP_get_direction() function


//! \brief     Set lineCounts
//! \param[in] qepHandle          The qep handle
//! \param[in] lineCounts         Set encoder line counts
inline void QEP_set_lineCounts( QEP_Handle qepHandle, const uint32_t   lineCounts)
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;

    obj->lineCounts = lineCounts;
} // end of QEP_set_lineCounts() function


//! \brief     Get lineCounts
//! \param[in] qepHandle          The qep handle
//! \return    lineCounts (encoder)
inline uint32_t QEP_get_lineCounts( QEP_Handle qepHandle )
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;

    return(obj->lineCounts);
} // end of QEP_get_lineCounts() function


//! \brief     Setup the QEP module
//! \param[in]  qepHandle		The qep handle
//! \param[in]  POSCNT_Value	The count value from the HET
//! \param[out] elecPos			the (electrical) position of the rotor
inline void QEP_run( QEP_Handle qepHandle, ElecPos_Data_t* elecPos, uint32_t *POSCNT_Value)
{
    QEP_Obj *obj = (QEP_Obj *)qepHandle;
    
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
} // end of QEP_run() function


//! \brief     Initializes the QEP HET module
//! \param[in] pMemory            A pointer to the memory for the QEP HET object
//! \param[in] numBytes           The number of bytes allocated for the QEP HET object, bytes
//! \return The  QEP HET object handle
QEP_HET_Handle QEP_HET_init(void *pMemory,const size_t numBytes);


//! \brief     Setup the QEP module
//! \param[in]  qepHETHandle	The qep HET handle
//! \param[out] POSCNT_Value	The count value from the HET
inline void QEP_read_POSCNT( QEP_HET_Handle qepHETHandle, uint32_t *POSCNT_Value)
{
    QEP_HET_Obj *obj = (QEP_HET_Obj *)qepHETHandle;
    *POSCNT_Value = (obj->POSCNT_Data) >> 7;

    return;
} // end of QEP_read_POSCNT() function


//! \brief     Clear the QEP index pulse register
//! \param[in]  qepIndexHandle		The qep HET handle
inline void QEP_Clear_Index(QEP_HET_Handle qepIndexHandle)
{
	QEP_HET_Obj *obj = (QEP_HET_Obj *)qepIndexHandle;

	obj->POSCNT_Data = 0U;

	return;
} // end of QEP_Clear_Index() function


//! \brief     Clear the QEP index pulse register
//! \param[in] qepIndexHandle		The qep HET handle
//! \return    Index Pulse Register Data
inline uint32_t QEP_Read_Index(QEP_HET_Handle qepIndexHandle)
{
	QEP_HET_Obj *obj = (QEP_HET_Obj *)qepIndexHandle;

	return(obj->POSCNT_Data);
} // end of QEP_Read_Index() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif // __QEP_H__ 
