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
#ifndef _SVGEN_H_
#define _SVGEN_H_

//! \file   ~/modules/svgen/src/float32/svgen.h
//! \brief  Contains the public interface to the 
//!         Space Vector Generator (SVGEN) module routines 
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "modules/math/src/float32/math_fpu32.h"

//!
//! \defgroup SVGEN

//!
//! \ingroup SVGEN
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines



// **************************************************************************
// the typedefs

//! \brief Defines the Space Vector Generator object
//!
typedef struct _SVGEN_Obj_
{
	float32_t   Va;			//!< reference phase-a voltage function
	float32_t   Vb;			//!< reference phase-b voltage function
	float32_t   Vc;			//!< reference phase-c voltage function
	float32_t   t1;			//!< switching function
	float32_t   t2;			//!< switching function
	float32_t   temp_sv1;	//!< temp variable
	float32_t   temp_sv2;	//!< temp variable

} SVGEN_Obj;


//! \brief Defines the SVGEN handle
//!
typedef struct SVGEN_Obj   *SVGEN_Handle;



// **************************************************************************
// the function prototypes

//! \brief     Initializes the space vector generator module
//! \param[in] pMemory   A pointer to the space vector generator object memory
//! \param[in] numBytes  The number of bytes allocated for the space vector generator object, bytes
//! \return The state vector generator (SVGEN) object handle
SVGEN_Handle SVGEN_init(void *pMemory,const size_t numBytes);


//! \brief     Runs the space vector generator 
//! \param[in] svgenHandle  The SVGEN handle
//! \param[in] pVref        The pointer to the d-q reference voltages
//! \param[in] pT           The pointer to the PWM time durations
inline void SVGEN_run(SVGEN_Handle svgenHandle,const MATH_vec2 *pVref,MATH_vec3 *pT)
{
  SVGEN_Obj *svgen = (SVGEN_Obj *)svgenHandle;

  uint16_t   Sector = 0;  // Sector

  svgen->temp_sv1 = (pVref->value[1] * 0.5f); 			// divide by 2
  svgen->temp_sv2 = (0.8660254f * pVref->value[0]);		// 0.8660254 = sqrt(3)/2


  // Inverse clarke transformation
  svgen->Va = pVref->value[1];
  svgen->Vb = -svgen->temp_sv1 + svgen->temp_sv2;
  svgen->Vc = -svgen->temp_sv1 - svgen->temp_sv2;

  // 60 degree Sector determination
  if (svgen->Va > 0) Sector = 1;
  if (svgen->Vb > 0) Sector = Sector+2;
  if (svgen->Vc > 0) Sector = Sector+4;

  // X,Y,Z (Va,Vb,Vc) calculations X = Va, Y = Vb, Z = Vc
  svgen->Va = pVref->value[1];
  svgen->Vb = svgen->temp_sv1 + svgen->temp_sv2;
  svgen->Vc = svgen->temp_sv1 - svgen->temp_sv2;

  // Sector 0: this is special case for (Ualpha,Ubeta) = (0,0)

  switch(Sector)
    {
    case 0:
      pT->value[0] = 0.5;
      pT->value[1] = 0.5;
      pT->value[2] = 0.5;
      break;
    case 1:  // Sector 1: t1=Z and t2=Y (abc ---> Tb,Ta,Tc)
      svgen->t1 = svgen->Vc;
      svgen->t2 = svgen->Vb;
      pT->value[1] = ((1-svgen->t1-svgen->t2) * 0.5f);		// tbon = (1-t1-t2)/2
      pT->value[0] = pT->value[1]+svgen->t1;			 	// taon = tbon+t1
      pT->value[2] = pT->value[0]+svgen->t2;			  	// tcon = taon+t2
      break;
    case 2:  // Sector 2: t1=Y and t2=-X (abc ---> Ta,Tc,Tb)
      svgen->t1 = svgen->Vb;
      svgen->t2 = -svgen->Va;
      pT->value[0] = ((1-svgen->t1-svgen->t2) * 0.5f);		//	taon = (1-t1-t2)/2
      pT->value[2] = pT->value[0]+svgen->t1;				//  tcon = taon+t1
      pT->value[1] = pT->value[2]+svgen->t2;				//  tbon = tcon+t2
      break;
    case 3:  // Sector 3: t1=-Z and t2=X (abc ---> Ta,Tb,Tc)
      svgen->t1 = -svgen->Vc;
      svgen->t2 = svgen->Va;
      pT->value[0]= ((1-svgen->t1-svgen->t2) * 0.5f);		//	taon = (1-t1-t2)/2
      pT->value[1] = pT->value[0]+svgen->t1;				//	tbon = taon+t1
      pT->value[2] = pT->value[1]+svgen->t2;				//	tcon = tbon+t2
      break;
    case 4:  // Sector 4: t1=-X and t2=Z (abc ---> Tc,Tb,Ta)
      svgen->t1 = -svgen->Va;
      svgen->t2 = svgen->Vc;
      pT->value[2]= ((1-svgen->t1-svgen->t2) * 0.5f);		//	tcon = (1-t1-t2)/2
      pT->value[1] = pT->value[2]+svgen->t1;				//	tbon = tcon+t1
      pT->value[0] = pT->value[1]+svgen->t2;				//	taon = tbon+t2
      break;
    case 5:  // Sector 5: t1=X and t2=-Y (abc ---> Tb,Tc,Ta)
      svgen->t1 = svgen->Va;
      svgen->t2 = -svgen->Vb;
      pT->value[1]= ((1-svgen->t1-svgen->t2) * 0.5f);		//	tbon = (1-t1-t2)/2
      pT->value[2] = pT->value[1]+svgen->t1;				//	tcon = tbon+t2
      pT->value[0] = pT->value[2]+svgen->t2;				//	taon = tcon+t2
      break;
    case 6:  // Sector 6: t1=-Y and t2=-Z (abc ---> Tc,Ta,Tb)
      svgen->t1 = -svgen->Vb;
      svgen->t2 = -svgen->Vc;
      pT->value[2]= ((1-svgen->t1-svgen->t2) * 0.5f);		//	tcon = (1-t1-t2)/2
      pT->value[0] = pT->value[2]+svgen->t1;				//	taon = tcon+t1
      pT->value[1] = pT->value[0]+svgen->t2;				//	tbon = taon+t2
      break;
    } // end of switch block


  //  Convert the unsigned (ranged (0,1)) -> signed format (ranged (-1,1))
  pT->value[0] = ((pT->value[0] - 0.5f) * 2.0f);
  pT->value[1] = ((pT->value[1] - 0.5f) * 2.0f);
  pT->value[2] = ((pT->value[2] - 0.5f) * 2.0f);

  return;
} // end of SVGEN_run() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // end of _SVGEN_H_ definition

