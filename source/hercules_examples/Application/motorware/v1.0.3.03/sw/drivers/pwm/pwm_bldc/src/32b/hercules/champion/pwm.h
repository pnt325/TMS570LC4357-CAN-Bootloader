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
#ifndef _PWM_H_
#define _PWM_H_

//! \file   ~/drivers/pwm/pwm_bldc/src/32b/hercules/champion/pwm.h
//! \brief  Contains public interface to various functions related
//!         to the pulse width modulation (PWM) object
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "modules/types/src/32b/types.h"


//!
//! \defgroup PWM

//!
//! \ingroup PWM
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

#define	vCNT_MAX 						122				 		// NHET Loop value-1 --> 20kHz PWM base period

#define APWMH_HET_OFFSET				29U

#define BPWMH_HET_OFFSET				31U

#define CPWMH_HET_OFFSET				33U

#define APWML_HET_OFFSET				35U

#define BPWML_HET_OFFSET				37U

#define CPWML_HET_OFFSET				39U

#define PWM_SYNC_HET_OFFSET				28U

#define PWM_SYNC_CURRENT				41U

// **************************************************************************
// the typedefs

//! \brief Defines the pulse width modulation (PWM) object
//!
typedef struct _PWM_Obj_
{
  int32_t   CMPR_Prog;       //!< compare rising edge program field
  int32_t   CMPR_Ctrl;       //!< compare rising edge ctrl field
  int32_t   CMPR_Data;       //!< compare rising edge data field
  int32_t   CMPR_Rsvd;       //!< compare rising edge reserved field
  int32_t   CMPF_Prog;       //!< compare falling edge program field
  int32_t   CMPF_Ctrl;       //!< compare falling edge ctrl field
  int32_t   CMPF_Data;       //!< compare falling edge data field
  int32_t   CMPF_Rsvd;       //!< compare falling edge reserved field

} PWM_Obj;


//! \brief Defines the pulse width modulation (PWM) handle
//!
typedef struct PWM_Obj *PWM_Handle;


//! \brief Defines the pulse width modulation (PWM) object
//!
typedef struct _PWM_SYNC_Obj_
{
  int32_t   SYNC_Prog;       //!< program field
  int32_t   SYNC_Ctrl;       //!< ctrl field
  int32_t   SYNC_Data;       //!< data field
  int32_t   SYNC_Rsvd;       //!< reserved field

} PWM_SYNC_Obj;


//! \brief Defines the pulse width modulation (PWM) handle
//!
typedef struct PWM_SYNC_Obj *PWM_SYNC_Handle;


// **************************************************************************
// the function prototypes


//! \brief     Initializes the pulse width modulation (PWM) object handle
//! \param[in] pMemory   A pointer to the base address of the PWM registers
//! \param[in] numBytes  The number of bytes allocated for the PWM object
//! \return    The pulse width modulation (PWM) object handle
PWM_Handle PWM_init(void *pMemory,const size_t numBytes);

//! \brief     Initializes the ADC PWM sync handle
//! \param[in] pMemory   A pointer to the base address of the registers
//! \param[in] numBytes  The number of bytes allocated for the object
//! \return    The pulse width modulation sync (PWM) object handle
PWM_SYNC_Handle PWM_SYNC_init(void *pMemory,const size_t numBytes);


//! \brief     Writes the pulse width modulation (PWM) data value to the HET counter hardware
//! \param[in] pwmHandle  The pulse width modulation (PWM) object handle
//! \param[in] pwmData    The PWM data value
inline void PWM_write_Cmp(PWM_Handle pwmHandle,const int16_t pwmData)
{
  PWM_Obj *pwm = (PWM_Obj *)pwmHandle;

  int16_t value;
  uint16_t period = (128*(vCNT_MAX + 1));
  uint16_t Mperiod = period>>1;
  int32_t tmp;


  // Compute the compare from the related duty cycle ratio
  tmp = (int32_t)Mperiod * (int32_t)(pwmData);
  value = (int16_t)(tmp>>16) + (int16_t)(Mperiod>>1);

  // Compute the opposite PWM compare's (falling edge)
       if(value<0) value=0;
       if(value>Mperiod) value=Mperiod;

       pwm->CMPR_Data = value;
       pwm->CMPF_Data = period - value;

  return;
} // end of PWM_write_Cmp() function


//! \brief     Writes the pulse width modulation (PWM) ADC sync value to the HET hardware
//! \param[in] pwmHandle  The pulse width modulation sync (PWM) object handle
inline void PWM_Sync(PWM_SYNC_Handle pwmSyncHandle)
{
	PWM_SYNC_Obj *sync = (PWM_SYNC_Obj *)pwmSyncHandle;

	sync->SYNC_Data = 1<<7;

	return;
}//end of PWM_Sync() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif  // end of _PWM_H_ definition
