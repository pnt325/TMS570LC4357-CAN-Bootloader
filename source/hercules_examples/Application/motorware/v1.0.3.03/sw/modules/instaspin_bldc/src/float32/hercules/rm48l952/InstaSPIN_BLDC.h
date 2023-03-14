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
/*!
 * @file    InstaSPIN_BLDC_Lib.h
 * @author  Texas Instruments (C) Copyright 2012 (Assisted by D3 Engineering Tech Team)
 * @date    5-7-2012
 * @version 1.0
 * @brief   This is the header file for the InstaSPIN BLDC Module
 */

#ifndef LM_INSTASPIN_BLDC_LIB_H//C28X_INSTASPIN_BLDC_LIB_H
#define LM_INSTASPIN_BLDC_LIB_H//C28X_INSTASPIN_BLDC_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

// Includes
#include "modules/types/src/32b/types.h"

// Defines
#define NULL	0
#define STATEFILTER_STATE_DEFAULT		0
#define STATEFILTER_SENSE_DEFAULT		A
#define STATEFILTER_INTEGRATE_DEFAULT	NEG
#define	INSTASPIN_VAG_DEFAULT			0
#define INSTASPIN_VBG_DEFAULT			0
#define INSTASPIN_VCG_DEFAULT			0
#define INSTASPIN_VAN_DEFAULT			0
#define INSTASPIN_VBN_DEFAULT			0
#define INSTASPIN_VCN_DEFAULT			0
#define INSTASPIN_VA_OFFSET_DEFAULT		0
#define INSTASPIN_VB_OFFSET_DEFAULT		0
#define INSTASPIN_VC_OFFSET_DEFAULT		0
#define INSTASPIN_INT_THRESH_DEFAULT	0x2FFF
#define INSTASPIN_VINT_LOCKOUT_DEFAULT	NO
#define INSTASPIN_VPHASE_DEFAULT		0
#define INSTASPIN_VINT_DEFAULT			0
#define INSTASPIN_COMM_TRIG_DEFAULT		NO
#define INSTASPIN_STATE_DEFAULT			0

// Typedefs
typedef enum
{
	A=0,
	B=1,
	C=2
} Esense;

typedef enum
{
	NEG=0,
	POS=1
} Eintdir;

//-----------------------------------------------------------------------------
// Structure and object definitions
//-----------------------------------------------------------------------------
typedef struct
{
	uint16_t state;   				// Input: Values 0 to 5
	Esense	sense;					// Output: What phase to sense (A/B/C)
	Eintdir integrate;	    		// Output: BEMF integrator count direction (POS/NEG)
} STATEFILTER;

typedef STATEFILTER *H_STATEFILTER;	//  Handle to object STATEFILTER

// enumerations
typedef enum
{
	NO=0,
	YES=1
} Eintbool;

// Structure and object definitions
typedef struct
{
	float32_t	vag;				// Internal: Vag input -- contains real Va + VaOffset --> referenced to ground (float32_t)
	float32_t	vbg;				// Internal: Vbg input -- contains real Vb + VbOffset --> referenced to ground (float32_t)
	float32_t	vcg;				// Internal: Vcg input -- contains real Vc + VcOffset --> referenced to ground (float32_t)
	float32_t	van;				// Internal: Va to neutral (float32_t)
	float32_t	vbn;				// Internal: Vb to neutral (float32_t)
	float32_t	vcn;				// Internal: Vc to neutral (float32_t)
	float32_t	vaOffset;			// VaOffset (float32_t)
	float32_t	vbOffset;			// VbOffset (float32_t)
	float32_t	vcOffset;			// VcOffset (float32_t)
	float32_t	intThreshold;		// Input: Integration threshold where a commutate happens (float32_t)
	Eintbool vIntLockout;	// Internal: Flyback voltage lockout flag
	float32_t	*vPhase;			// Internal: Pointer to the Phase voltage to count	(float32_t)
	float32_t	vInt;				// Output: Integrator	(float32_t)
	Eintbool commTrig;		// Output:  Commutation trigger impulse
	uint16_t state; 		// Input: Values 0 to 5
	H_STATEFILTER stateFilter;
} INSTASPIN_BLDC;

typedef INSTASPIN_BLDC *H_INSTASPIN_BLDC;			//  Handle to object INSTASPIN_BLDC

// Globals

// Function Prototypes
/*!
 * @ingroup         INSTASPIN_Setup
 * @fn              void INSTASPIN_Setup(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to setup the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 */
void INSTASPIN_Setup(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_Vag
 * @fn              void INSTASPIN_Set_Vag(H_INSTASPIN_BLDC instaHandle, float32_t vag)
 * @brief           Function to Set vag for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vag				The new vag value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vag(H_INSTASPIN_BLDC instaHandle, float32_t vag);

/*!
 * @ingroup         INSTASPIN_Get_Vag
 * @fn              float32_t INSTASPIN_Get_Vag(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vag for the InstaSPIN Module
 * @param [in]		instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The vag value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_Vag(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_Vbg
 * @fn              void INSTASPIN_Set_Vbg(H_INSTASPIN_BLDC instaHandle, float32_t Vbg)
 * @brief           Function to Set Vbg for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		Vbg				The new Vbg value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vbg(H_INSTASPIN_BLDC instaHandle, float32_t vbg);

/*!
 * @ingroup         INSTASPIN_Get_Vbg
 * @fn              float32_t INSTASPIN_Get_Vbg(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vbg for the InstaSPIN Module
 * @param [in]	  	instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The vbg value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_Vbg(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_Vcg
 * @fn              void INSTASPIN_Set_Vcg(H_INSTASPIN_BLDC instaHandle, float32_t vcg)
 * @brief           Function to Set vcg for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vcg				The new vcg value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vcg(H_INSTASPIN_BLDC instaHandle, float32_t vcg);

/*!
 * @ingroup         INSTASPIN_Get_Vcg
 * @fn              float32_t INSTASPIN_Get_Vcg(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vcg for the InstaSPIN Module
 * @param [in]		instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The vcg value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_Vcg(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_Van
 * @fn              void INSTASPIN_Set_Van(H_INSTASPIN_BLDC instaHandle, float32_t van)
 * @brief           Function to Set van for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		van				The new van value for the InstaSPIN Module
 */
void INSTASPIN_Set_Van(H_INSTASPIN_BLDC instaHandle, float32_t van);

/*!
 * @ingroup         INSTASPIN_Get_Van
 * @fn              float32_t INSTASPIN_Get_Van(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get van for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The van value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_Van(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_Vbn
 * @fn              void INSTASPIN_Set_Vbn(H_INSTASPIN_BLDC instaHandle, float32_t vbn)
 * @brief           Function to Set vbn for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vbn				The new vbn value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vbn(H_INSTASPIN_BLDC instaHandle, float32_t vbn);

/*!
 * @ingroup         INSTASPIN_Get_Vbn
 * @fn              float32_t INSTASPIN_Get_Vbn(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vbn for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The vbn value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_Vbn(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_Vcn
 * @fn              void INSTASPIN_Set_Vcn(H_INSTASPIN_BLDC instaHandle, float32_t vcn)
 * @brief           Function to Set vcn for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vcn				The new vcn value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vcn(H_INSTASPIN_BLDC instaHandle, float32_t vcn);

/*!
 * @ingroup         INSTASPIN_Get_Vcn
 * @fn              float32_t INSTASPIN_Get_Vcn(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vcn for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The vcn value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_Vcn(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_VaOffset
 * @fn              void INSTASPIN_Set_VaOffset(H_INSTASPIN_BLDC instaHandle, float32_t vaOffset)
 * @brief           Function to Set vaOffset for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vaOffset		The new vaOffset value for the InstaSPIN Module
 */
void INSTASPIN_Set_VaOffset(H_INSTASPIN_BLDC instaHandle, float32_t vaOffset);

/*!
 * @ingroup         INSTASPIN_Get_VaOffset
 * @fn              float32_t INSTASPIN_Get_VaOffset(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vaOffset for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The vaOffset value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_VaOffset(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_VbOffset
 * @fn              void INSTASPIN_Set_VbOffset(H_INSTASPIN_BLDC instaHandle, float32_t vbOffset)
 * @brief           Function to Set vbOffset for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vbOffset		The new vbOffset value for the InstaSPIN Module
 */
void INSTASPIN_Set_VbOffset(H_INSTASPIN_BLDC instaHandle, float32_t vbOffset);

/*!
 * @ingroup         INSTASPIN_Get_VbOffset
 * @fn              float32_t INSTASPIN_Get_VbOffset(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vbOffset for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The vbOffset value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_VbOffset(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_VcOffset
 * @fn              void INSTASPIN_Set_VcOffset(H_INSTASPIN_BLDC instaHandle, float32_t vcOffset)
 * @brief           Function to Set vcOffset for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vcOffset		The new vcOffset value for the InstaSPIN Module
 */
void INSTASPIN_Set_VcOffset(H_INSTASPIN_BLDC instaHandle, float32_t vcOffset);

/*!
 * @ingroup         INSTASPIN_Get_VcOffset
 * @fn              float32_t INSTASPIN_Get_VcOffset(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vcOffset for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The vcOffset value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_VcOffset(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_Int_Threshold
 * @fn              void INSTASPIN_Set_Int_Threshold(H_INSTASPIN_BLDC instaHandle, float32_t intThreshold)
 * @brief           Function to Set the Threshold for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		intThreshold	The new Threshold value for the InstaSPIN Module
 */
void INSTASPIN_Set_Int_Threshold(H_INSTASPIN_BLDC instaHandle, float32_t intThreshold);

/*!
 * @ingroup         INSTASPIN_Get_Int_Threshold
 * @fn              float32_t INSTASPIN_Get_Int_Threshold(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get the Threshold for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The Threshold value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_Int_Threshold(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_Vint_lockout
 * @fn              void INSTASPIN_Set_Vint_lockout(H_INSTASPIN_BLDC instaHandle, float32_t vIntLockout)
 * @brief           Function to Set vIntLockout for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vIntLockout		The new Lockout value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vint_lockout(H_INSTASPIN_BLDC instaHandle, Eintbool vIntLockout);

/*!
 * @ingroup         INSTASPIN_Get_Vint_lockout
 * @fn              Eintbool INSTASPIN_Get_Vint_lockout(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vIntLockout for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			Eintbool		The Lockout value for the InstaSPIN Module
 */
Eintbool INSTASPIN_Get_Vint_lockout(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_Vphase
 * @fn              void INSTASPIN_Set_Vphase(H_INSTASPIN_BLDC instaHandle, float32_t vPhase)
 * @brief           Function to Set Vphase for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vPhase			The new vPhase value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vphase(H_INSTASPIN_BLDC instaHandle, float32_t *vPhase);

/*!
 * @ingroup         INSTASPIN_Get_Vphase
 * @fn              float32_t INSTASPIN_Get_Vphase(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vPhase for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The vPhase value for the InstaSPIN Module
 */
float32_t *INSTASPIN_Get_Vphase(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_V_int
 * @fn              void INSTASPIN_Set_V_Int(H_INSTASPIN_BLDC instaHandle, float32_t vInt)
 * @brief           Function to Set vInt for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vInt			The new vInt value for the InstaSPIN Module
 */
void INSTASPIN_Set_V_int(H_INSTASPIN_BLDC instaHandle, float32_t vInt);

/*!
 * @ingroup         INSTASPIN_Get_V_Int
 * @fn              float32_t INSTASPIN_Get_V_Int(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vInt for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			float32_t				The vInt value for the InstaSPIN Module
 */
float32_t INSTASPIN_Get_V_int(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_Comm_Trig
 * @fn              void INSTASPIN_Set_Comm_Trig(H_INSTASPIN_BLDC instaHandle, float32_t commTrig)
 * @brief           Function to Set commTrig for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		commTrig		The new commTrig value for the InstaSPIN Module
 */
void INSTASPIN_Set_Comm_Trig(H_INSTASPIN_BLDC instaHandle, Eintbool commTrig);

/*!
 * @ingroup         INSTASPIN_Get_Comm_Trig
 * @fn              Eintbool INSTASPIN_Get_Comm_Trig(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get commTrig for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			Eintbool		The commTrig value for the InstaSPIN Module
 */
Eintbool INSTASPIN_Get_Comm_Trig(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         INSTASPIN_Set_State
 * @fn              void INSTASPIN_Set_State(H_INSTASPIN_BLDC instaHandle, float32_t State)
 * @brief           Function to Set State for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		State			The new State value for the InstaSPIN Module
 */
void INSTASPIN_Set_State(H_INSTASPIN_BLDC instaHandle, uint16_t state);

/*!
 * @ingroup         INSTASPIN_Get_State
 * @fn              uint16_t INSTASPIN_Get_State(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get State for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			uint16_t			The State value for the InstaSPIN Module
 */
uint16_t INSTASPIN_Get_State(H_INSTASPIN_BLDC instaHandle);

/*!
 * @ingroup         STATEFILTER_Setup
 * @fn              void STATEFILTER_Setup(H_STATEFILTER stateFilterHandle)
 * @brief           Function to Setup a Statefilter Handler
 * @param [in]      stateFilterHandle	The Handle for the StateFilter Module
 */
void STATEFILTER_Setup(H_STATEFILTER stateFilterHandle);

/*!
 * @ingroup         STATEFILTER_Set_State
 * @fn              void STATEFILTER_Set_State(H_STATEFILTER stateFilterHandle, uint16_t State)
 * @brief           Function to Set the State of the StateFilter
 * @param [in/out]  stateFilterHandle	The Handle for the StateFilter Module
 * @param [in]		State				The new State value for the StateFilter Module
 */
void STATEFILTER_Set_State(H_STATEFILTER stateFilterHandle, uint16_t state);

/*!
 * @ingroup         STATEFILTER_Get_State
 * @fn              uint16_t STATEFILTER_Get_State(H_STATEFILTER stateFilterHandle)
 * @brief           Function to Get State for the StateFilter Module
 * @param [in]      stateFilterHandle	The Handle for the StateFilter Module
 * @return			uint16_t				The State value for the StateFilter Module
 */
uint16_t STATEFILTER_Get_State(H_STATEFILTER stateFilterHandle);

/*!
 * @ingroup         STATEFILTER_Set_Sense
 * @fn              void STATEFILTER_Set_Sense(H_STATEFILTER stateFilterHandle, uint16_t Sense)
 * @brief           Function to Set the Sense of the StateFilter
 * @param [in/out]  stateFilterHandle	The Handle for the StateFilter Module
 * @param [in]		Sense				The new Sense value for the StateFilter Module
 */
void STATEFILTER_Set_Sense(H_STATEFILTER stateFilterHandle, Esense sense);

/*!
 * @ingroup         STATEFILTER_Get_Sense
 * @fn              Esense STATEFILTER_Get_Sense(H_STATEFILTER stateFilterHandle)
 * @brief           Function to Get Sense for the StateFilter Module
 * @param [in]      stateFilterHandle	The Handle for the StateFilter Module
 * @return			Esense				The Sense value for the StateFilter Module
 */
Esense STATEFILTER_Get_Sense(H_STATEFILTER stateFilterHandle);

/*!
 * @ingroup         STATEFILTER_Set_Integrate
 * @fn              void STATEFILTER_Set_Integrate(H_STATEFILTER stateFilterHandle, uint16_t Integrate)
 * @brief           Function to Set the Integrate of the StateFilter
 * @param [in/out]  stateFilterHandle	The Handle for the StateFilter Module
 * @param [in]		Integrate			The new Integrate value for the StateFilter Module
 */
void STATEFILTER_Set_Integrate(H_STATEFILTER stateFilterHandle, Eintdir integrate);

/*!
 * @ingroup         STATEFILTER_Get_Integrate
 * @fn              Eintdir STATEFILTER_Get_Integrate(H_STATEFILTER stateFilterHandle)
 * @brief           Function to Get Integrate for the StateFilter Module
 * @param [in]      stateFilterHandle	The Handle for the StateFilter Module
 * @return			Eintdir				The Integrate value for the StateFilter Module
 */
Eintdir STATEFILTER_Get_Integrate(H_STATEFILTER stateFilterHandle);

/*!
 * @ingroup         bemfposint_calc
 * @fn              void bemfposint_calc(H_INSTASPIN_BLDC v)
 * @brief           Function to run InstaSPIN for Positive Integrated BEMF Values
 * @param [in/out]  v		Handler for the InstaSPIN Module
 */
inline void bemfposint_calc(H_INSTASPIN_BLDC v)
{
	v->commTrig = NO;

	if(v->vIntLockout == YES)
	{
		if(*(v->vPhase) < 0)
		{
			v->vIntLockout = NO;
		}
	}
	else
	{
		v->vInt += *(v->vPhase);			// Integrate the phase voltage

		if(v->vInt > 0)					// Only integrate positively
		{
			if(v->vInt > v->intThreshold)	// Check to see if there is enough volt-seconds to commutate
			{
				v->vIntLockout = YES;
				v->commTrig = YES;
				v->vInt = 0;
			}
		}
		else
		{
			v->vInt = 0;
		}
	}
}

/*!
 * @ingroup         bemfnegint_calc
 * @fn              void bemfnegint_calc(H_INSTASPIN_BLDC v)
 * @brief           Function to run InstaSPIN for Negative Integrated BEMF Values
 * @param [in/out]  v		Handler for the InstaSPIN Module
 */
inline void bemfnegint_calc(H_INSTASPIN_BLDC v)
{
	v->commTrig = NO;

	if(v->vIntLockout == YES)
	{
		if(*(v->vPhase) > 0)
		{
			v->vIntLockout = NO;
		}
	}
	else
	{
		v->vInt += *(v->vPhase);			// Integrate the phase voltage

		if(v->vInt < 0)					// Only integrate negatively
		{
			if(v->vInt < -(v->intThreshold))	// Check to see if there is enough volt-seconds to commutate
			{
				v->vIntLockout = YES;
				v->commTrig = YES;
				v->vInt = 0;
			}
		}
		else
		{
			v->vInt = 0;
		}
	}
}

/*!
 * @ingroup         bemfint_calc
 * @fn              bemfint_calc(H_INSTASPIN_BLDC v, H_STATEFILTER s)
 * @brief           Function to run InstaSPIN Integration
 * @param [in/out]  v		Handler for the InstaSPIN Module
 * @param [in/out]	s		Handler for the StateFilter Module
 */
inline void bemfint_calc(H_INSTASPIN_BLDC v, H_STATEFILTER s)
{
	switch (s->sense)
	{
	case A:
		v->vPhase = &(v->van);			// Point to phase voltage A to neutral
		break;

	case B:
		v->vPhase = &(v->vbn);			// Point to phase voltage B to neutral
		break;

	case C:
		v->vPhase = &(v->vcn);			// Point to phase voltage C to neutral
	}
	if (s->integrate == POS)
	{
		bemfposint_calc(v);						// Integrate positive
	}
	else
	{
		bemfnegint_calc(v);						// Integrate negative
	}
}

/*!
 * @ingroup         statefilter_calc
 * @fn              void statefilter_calc(H_STATEFILTER v)
 * @brief           Function to calculate the state and integration values of the StateFilter
 * @param [in/out]  v		Handler for the StateFilter Module
 */
inline void statefilter_calc(H_STATEFILTER v)
{
	switch (v->state)
	{
	case 0:
		v->sense = C;
		v->integrate = NEG;
		break;

	case 1:
		v->sense = B;
		v->integrate = POS;
		break;

	case 2:
		v->sense = A;
		v->integrate = NEG;
		break;

	case 3:
		v->sense = C;
		v->integrate = POS;
		break;

	case 4:
		v->sense = B;
		v->integrate = NEG;
		break;

	case 5:
		v->sense = A;
		v->integrate = POS;
	}
}

/*!
 * @ingroup         InstaSPIN_BLDC_Calc
 * @fn              InstaSPIN_BLDC_Calc(H_INSTASPIN_BLDC i)
 * @brief           Function to run InstaSPIN Calculations
 * @param [in/out]  v		Handler for the InstaSPIN Module
 */
inline void InstaSPIN_BLDC_Calc(H_INSTASPIN_BLDC i)
{
// ------------------------------------------------------------------------------
//    Connect inputs of the STATE_FILTER module and call the State Filter macro.
// ------------------------------------------------------------------------------
	i->stateFilter->state = i->state;		// Update the state
	statefilter_calc((i->stateFilter));

// ------------------------------------------------------------------------------
//    Connect inputs of the BEMFINT module and call the BEMF Integration macro.
// ------------------------------------------------------------------------------
	i->van = i->vag - ((i->vbg + i->vcg) * 0.5);		// Calculate phase voltages
	i->vbn = i->vbg - ((i->vag + i->vcg) * 0.5);		// Calculate phase voltages
	i->vcn = i->vcg - ((i->vbg + i->vag) * 0.5);		// Calculate phase voltages
	bemfint_calc(i, (i->stateFilter));

}


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================

