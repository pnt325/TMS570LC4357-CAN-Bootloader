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
#ifndef _CONTROLLER_DATA_TYPES_H_
#define _CONTROLLER_DATA_TYPES_H_

//! \file   ~/modules/types/src/32b/hercules/rm48l952/controller_data_types.h
//! \brief  Contains the public interface to the controller data types 
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "modules/types/src/32b/types.h"

// **************************************************************************
// the typedefs

//!
//! \defgroup CLARKE

//!
//! \ingroup CLARKE
//@{


#ifdef __cplusplus
extern "C" {
#endif

//! \brief Defines the ADC data
//!
typedef struct _ADC_Data_t_
{
  MATH_vec3 I;          //!< the current values
  MATH_vec3 V;          //!< the voltage values
  float32_t  dcBusV;    //!< the dcBus voltage value
  float32_t  iTotal;    //!< the total current

} ADC_Data_t;

//! \brief Defines the PWM data
//!
typedef struct _PWM_Data_t_
{
  int16_t  value[3];      //!< the PWM time-durations for each motor phase

} PWM_Data_t;

//! \brief Defines the ElecPos Input type
//!
typedef struct _ElecPos_Data_t_
{
	float32_t ElecTheta;   //!< input electrical position, scaled pu [0.0,1.0)
	uint32_t Dir;	   //!< direction of rotation of the motor shaft (Boolean)

} ElecPos_Data_t;


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif // end of _CONTROLLER_DATA_TYPES_H_ definition
