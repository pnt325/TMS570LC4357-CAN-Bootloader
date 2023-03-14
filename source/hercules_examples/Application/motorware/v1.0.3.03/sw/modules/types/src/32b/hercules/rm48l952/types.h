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
/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef __TYPES_H__
#define __TYPES_H__

//! \file   ~/sw/modules/types/src/32b/hercules/rm48l952/types.h
//! \brief  Contains the public interface to the
//!         types definitions
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


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

// **************************************************************************
// the typedefs

//! \brief Defines the portable data type for a Boolean value
//!
typedef char            bool_t;

//! \brief Defines the portable data type for a status result
//!
typedef unsigned short  status;

//! \brief Defines the portable data type for 8 bit, signed fixed-point data
//!
typedef char            int8_t;

//! \brief Defines the portable data type for 16 bit, signed fixed-point data
//!
typedef short           int16_t;

//! \brief Defines the portable data type for 32 bit, signed fixed-point data
//!
typedef int             int32_t;

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
typedef short           int_least16_t;

//! \brief Defines the portable data type for at least 16 bit, unsigned fixed-point data
//!
typedef unsigned short  uint_least16_t;

//! \brief Defines the portable data type for at least 32 bit, signed fixed-point data
//!
typedef int             int_least32_t;

//! \brief Defines the portable data type for at least 32 bit, unsigned fixed-point data
//!
typedef unsigned int    uint_least32_t;

/** @def NULL
*   @brief NULL definition
*/
#ifndef NULL
    #define NULL ((void *) 0U)
#endif

/** @def TRUE
*   @brief definition for TRUE
*/
#ifndef TRUE
    #define TRUE 1U
#endif

/** @def FALSE
*   @brief BOOLEAN definition for FALSE
*/
#ifndef FALSE
    #define FALSE 0U
#endif

#ifndef _UINT64_T_DECLARED
typedef unsigned long long uint64_t;
#define	_UINT64_T_DECLARED
#endif

#ifndef _UINT32_T_DECLARED
typedef unsigned int uint32_t;
#define	_UINT32_T_DECLARED
#endif

#ifndef _UINT16_T_DECLARED
typedef unsigned short uint16_t;
#define	_UINT16_T_DECLARED
#endif

#ifndef _UINT8_T_DECLARED
typedef unsigned char uint8_t;
#define	_UINT8_T_DECLARED
#endif

#if defined (CCS )
typedef long long __int64;
#define __packed
#endif

 #if defined (__GNUC__)
 typedef long long __int64;
 #define __packed	__attribute__ ((packed))
 #endif


 //! \brief 64-bit signed integer data type
 //!
 typedef __int64 		int64_t ;

//! \brief 8-bit fractional data type in 1.7 format.
//!
 typedef int8_t 		q7_t;

//! \brief 16-bit fractional data type in 1.15 format.
//!
 typedef int16_t 		q15_t;

//! \brief 32-bit fractional data type in 1.31 format.
//!
 typedef int32_t 		q31_t;

//! \brief 64-bit fractional data type in 1.63 format.
//!
 typedef int64_t 		q63_t;

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

	float32_t  value[2];

} MATH_vec2;


//! \brief Defines a three element vector
//!
typedef struct _MATH_vec3_
{

	float32_t  value[3];

} MATH_vec3;


#ifdef __cplusplus
}
#endif /* extern "C" */

//@}  // ingroup

#endif
