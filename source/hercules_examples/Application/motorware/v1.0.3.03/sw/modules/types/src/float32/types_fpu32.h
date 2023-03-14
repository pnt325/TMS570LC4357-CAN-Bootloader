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
// Copyright (c) 2005-2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
#ifndef _TYPES_H_
#define _TYPES_H_

//! \file   ~sw/modules/types/src/types.h
//! \brief  Contains the public interface to the 
//!         types definitions
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "string.h"  // needed for size_t typedef

//!
//! \defgroup TYPES

//!
//! \ingroup TYPES
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines


//! \brief Defines true
//!
#define   TRUE          1


//! \brief Defines false
//!
#define   FALSE         0


//! \brief Defines off
//!
#define   OFF           0


//! \brief Defines ok
//!
#define   OK            0


//! \brief Defines on
//!
#define   ON            1


//! \brief Defines generic error
//!
#define   ERROR         1


//! \brief Defines null
//!
#define NULL    0


// **************************************************************************
// the typedefs

//! \brief Defines the portable data type for a Boolean value
//!
typedef char            bool_t;

//! \brief Defines the portable data type for a status result
//!
typedef unsigned int    status;

//! \brief Defines the portable data type for 8 bit, signed fixed-point data
//!
typedef char            int8_t;

//! \brief Defines the portable data type for 8 bit, unsigned fixed-point data
//!
typedef char            uint8_t;

//! \brief Defines the portable data type for 16 bit, signed fixed-point data
//!
typedef int             int16_t;

//! \brief Defines the portable data type for 16 bit, unsigned fixed-point data
//!
typedef unsigned int    uint16_t;

//! \brief Defines the portable data type for 32 bit, signed fixed-point data
//!
typedef long            int32_t;

//! \brief Defines the portable data type for 32 bit, unsigned fixed-point data
//!
typedef unsigned long   uint32_t;

//! \brief Defines the portable data type for 32 bit, signed floating-point data
//!
typedef float           float32_t;

//! \brief Defines the portable data type for 64 bit, signed floating-point data
//!
typedef long double     float64_t;

//! \brief Defines the portable data type for at least 8 bit, signed fixed-point data
//!
typedef char            int_least8_t;

//! \brief Defines the portable data type for at least 8 bit, unsigned fixed-point data
//!
typedef char            uint_least8_t;

//! \brief Defines the portable data type for at least 16 bit, signed fixed-point data
//!
typedef int             int_least16_t;

//! \brief Defines the portable data type for at least 16 bit, unsigned fixed-point data
//!
typedef unsigned int    uint_least16_t;

//! \brief Defines the portable data type for at least 32 bit, signed fixed-point data
//!
typedef long            int_least32_t;

//! \brief Defines the portable data type for at least 32 bit, unsigned fixed-point data
//!
typedef unsigned long   uint_least32_t;


//! \brief Define the complex data type for at least 16 bit real and at least 16 bit imaginary components
//!
typedef struct _cplx_least16_t
{
  int_least16_t  imag;
  int_least16_t  real;
} cplx_least16_t;


//! \brief Define the complex data type for 16 bit real and 16 bit imaginary components
//!
typedef struct _cplx16_t_
{
  int16_t  imag;
  int16_t  real;
} cplx16_t;


//! \brief Define the complex data type for at least 32 bit real and at least 32 bit imaginary components
//!
typedef struct _cplx_least32_t_
{
  int32_t  imag;
  int32_t  real;
} cplx_least32_t;


//! \brief Define the complex data type for 32 bit real and 32 bit imaginary components
//!
typedef struct _cplx32_t
{
  int32_t  imag;
  int32_t  real;
} cplx32_t;


//! \brief Defines a two element vector
//!
typedef struct _MATH_vec2_
{

  int32_t  value[2];

} MATH_vec2;


//! \brief Defines a three element vector
//!
typedef struct _MATH_vec3_
{

  int32_t  value[3];

} MATH_vec3;


//! \brief Defines the ADC data
//!
typedef struct _ADC_Data_t_
{
  MATH_vec3 I;          //!< the current values

  MATH_vec3 V;          //!< the voltage values

  int16_t  dcBus;       //!< the dcBus value

} ADC_Data_t;


//! \brief Defines the PWM data
//!
typedef struct _PWM_Data_t_
{
  int16_t  value[3];      //!< the PWM time-durations for each motor phase

} PWM_Data_t;


//! \brief Enumeration for the motor types
//!
typedef enum 
{
  MOTOR_Type_Induction=0,     //!< induction
  MOTOR_Type_Pm               //!< permanent magnet
} MOTOR_Type_e;

//! \brief Enumeration for the hardware
//!
typedef enum 
{
  PLATFORM_HV_KIT_REV5=0,
  PLATFORM_DRV8312_KIT_REVD,
  PLATFORM_DRV8301_KIT_REVB,
  PLATFORM_HV_KIT_REV8
} PLATFORM_e;


#ifdef __cplusplus
}
#endif /* extern "C" */

//@}  // ingroup

#endif  // end of _TYPES_H_ definition

