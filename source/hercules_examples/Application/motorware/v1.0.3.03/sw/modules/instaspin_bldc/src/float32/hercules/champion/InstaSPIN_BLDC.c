/*!
 * @file    InstaSPIN_BLDC_Lib.c
 * @author  Texas Instruments (C) Copyright 2012 (Assisted by D3 Engineering Tech Team)
 * @date    5-7-2012
 * @version 1.0
 * @brief   This file contains all InstaSPIN Functions: Setup, Sets, and Gets.
 */

#include "InstaSPIN_BLDC.h"

/*!
 * @ingroup         INSTASPIN_Setup
 * @fn              void INSTASPIN_Setup(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to setup the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 */
void INSTASPIN_Setup(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;

    INSTASPIN_Set_Vag(instaHandle, INSTASPIN_VAG_DEFAULT);
    INSTASPIN_Set_Vbg(instaHandle, INSTASPIN_VBG_DEFAULT);
    INSTASPIN_Set_Vcg(instaHandle, INSTASPIN_VCG_DEFAULT);
    INSTASPIN_Set_Van(instaHandle, INSTASPIN_VAN_DEFAULT);
    INSTASPIN_Set_Vbn(instaHandle, INSTASPIN_VBN_DEFAULT);
    INSTASPIN_Set_Vcn(instaHandle, INSTASPIN_VCN_DEFAULT);
    INSTASPIN_Set_VaOffset(instaHandle, INSTASPIN_VA_OFFSET_DEFAULT);
    INSTASPIN_Set_VbOffset(instaHandle, INSTASPIN_VB_OFFSET_DEFAULT);
    INSTASPIN_Set_VcOffset(instaHandle, INSTASPIN_VC_OFFSET_DEFAULT);
    INSTASPIN_Set_Int_Threshold(instaHandle, INSTASPIN_INT_THRESH_DEFAULT);
    INSTASPIN_Set_Vint_lockout(instaHandle, INSTASPIN_VINT_LOCKOUT_DEFAULT);
    INSTASPIN_Set_Vphase(instaHandle, INSTASPIN_VPHASE_DEFAULT);
    INSTASPIN_Set_V_int(instaHandle, INSTASPIN_VINT_DEFAULT);
    INSTASPIN_Set_Comm_Trig(instaHandle, INSTASPIN_COMM_TRIG_DEFAULT);
    INSTASPIN_Set_State(instaHandle, INSTASPIN_STATE_DEFAULT);

    STATEFILTER_Setup(instaObj->stateFilter);
}

/*!
 * @ingroup         INSTASPIN_Set_Vag
 * @fn              void INSTASPIN_Set_Vag(H_INSTASPIN_BLDC instaHandle, _iq vag)
 * @brief           Function to Set vag for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vag				The new vag value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vag(H_INSTASPIN_BLDC instaHandle, _iq vag)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vag = vag;
}

/*!
 * @ingroup         INSTASPIN_Get_Vag
 * @fn              _iq INSTASPIN_Get_Vag(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vag for the InstaSPIN Module
 * @param [in]		instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The vag value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_Vag(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vag;
}

/*!
 * @ingroup         INSTASPIN_Set_Vbg
 * @fn              void INSTASPIN_Set_Vbg(H_INSTASPIN_BLDC instaHandle, _iq Vbg)
 * @brief           Function to Set Vbg for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		Vbg				The new Vbg value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vbg(H_INSTASPIN_BLDC instaHandle, _iq vbg)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vbg = vbg;
}

/*!
 * @ingroup         INSTASPIN_Get_Vbg
 * @fn              _iq INSTASPIN_Get_Vbg(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vbg for the InstaSPIN Module
 * @param [in]	  	instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The vbg value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_Vbg(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vbg;
}

/*!
 * @ingroup         INSTASPIN_Set_Vcg
 * @fn              void INSTASPIN_Set_Vcg(H_INSTASPIN_BLDC instaHandle, _iq vcg)
 * @brief           Function to Set vcg for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vcg				The new vcg value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vcg(H_INSTASPIN_BLDC instaHandle, _iq vcg)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vcg = vcg;
}

/*!
 * @ingroup         INSTASPIN_Get_Vcg
 * @fn              _iq INSTASPIN_Get_Vcg(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vcg for the InstaSPIN Module
 * @param [in]		instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The vcg value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_Vcg(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vcg;
}

/*!
 * @ingroup         INSTASPIN_Set_Van
 * @fn              void INSTASPIN_Set_Van(H_INSTASPIN_BLDC instaHandle, _iq van)
 * @brief           Function to Set van for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		van				The new van value for the InstaSPIN Module
 */
void INSTASPIN_Set_Van(H_INSTASPIN_BLDC instaHandle, _iq van)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->van = van;
}

/*!
 * @ingroup         INSTASPIN_Get_Van
 * @fn              _iq INSTASPIN_Get_Van(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get van for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The van value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_Van(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->van;
}

/*!
 * @ingroup         INSTASPIN_Set_Vbn
 * @fn              void INSTASPIN_Set_Vbn(H_INSTASPIN_BLDC instaHandle, _iq vbn)
 * @brief           Function to Set vbn for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vbn				The new vbn value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vbn(H_INSTASPIN_BLDC instaHandle, _iq vbn)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vbn = vbn;
}

/*!
 * @ingroup         INSTASPIN_Get_Vbn
 * @fn              _iq INSTASPIN_Get_Vbn(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vbn for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The vbn value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_Vbn(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vbn;
}

/*!
 * @ingroup         INSTASPIN_Set_Vcn
 * @fn              void INSTASPIN_Set_Vcn(H_INSTASPIN_BLDC instaHandle, _iq vcn)
 * @brief           Function to Set vcn for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vcn				The new vcn value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vcn(H_INSTASPIN_BLDC instaHandle, _iq vcn)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vcn = vcn;
}

/*!
 * @ingroup         INSTASPIN_Get_Vcn
 * @fn              _iq INSTASPIN_Get_Vcn(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vcn for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The vcn value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_Vcn(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vcn;
}

/*!
 * @ingroup         INSTASPIN_Set_VaOffset
 * @fn              void INSTASPIN_Set_VaOffset(H_INSTASPIN_BLDC instaHandle, _iq vaOffset)
 * @brief           Function to Set vaOffset for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vaOffset		The new vaOffset value for the InstaSPIN Module
 */
void INSTASPIN_Set_VaOffset(H_INSTASPIN_BLDC instaHandle, _iq vaOffset)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vaOffset = vaOffset;
}

/*!
 * @ingroup         INSTASPIN_Get_VaOffset
 * @fn              _iq INSTASPIN_Get_VaOffset(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vaOffset for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The vaOffset value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_VaOffset(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vaOffset;
}

/*!
 * @ingroup         INSTASPIN_Set_VbOffset
 * @fn              void INSTASPIN_Set_VbOffset(H_INSTASPIN_BLDC instaHandle, _iq vbOffset)
 * @brief           Function to Set vbOffset for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vbOffset		The new vbOffset value for the InstaSPIN Module
 */
void INSTASPIN_Set_VbOffset(H_INSTASPIN_BLDC instaHandle, _iq vbOffset)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vbOffset = vbOffset;
}

/*!
 * @ingroup         INSTASPIN_Get_VbOffset
 * @fn              _iq INSTASPIN_Get_VbOffset(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vbOffset for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The vbOffset value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_VbOffset(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vbOffset;
}

/*!
 * @ingroup         INSTASPIN_Set_VcOffset
 * @fn              void INSTASPIN_Set_VcOffset(H_INSTASPIN_BLDC instaHandle, _iq vcOffset)
 * @brief           Function to Set vcOffset for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vcOffset		The new vcOffset value for the InstaSPIN Module
 */
void INSTASPIN_Set_VcOffset(H_INSTASPIN_BLDC instaHandle, _iq vcOffset)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vcOffset = vcOffset;
}

/*!
 * @ingroup         INSTASPIN_Get_VcOffset
 * @fn              _iq INSTASPIN_Get_VcOffset(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vcOffset for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The vcOffset value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_VcOffset(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vcOffset;
}

/*!
 * @ingroup         INSTASPIN_Set_Int_Threshold
 * @fn              void INSTASPIN_Set_Int_Threshold(H_INSTASPIN_BLDC instaHandle, _iq intThreshold)
 * @brief           Function to Set the Threshold for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		intThreshold	The new Threshold value for the InstaSPIN Module
 */
void INSTASPIN_Set_Int_Threshold(H_INSTASPIN_BLDC instaHandle, _iq intThreshold)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->intThreshold = intThreshold;
}

/*!
 * @ingroup         INSTASPIN_Get_Int_Threshold
 * @fn              _iq INSTASPIN_Get_Int_Threshold(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get the Threshold for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The Threshold value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_Int_Threshold(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->intThreshold;
}

/*!
 * @ingroup         INSTASPIN_Set_Vint_lockout
 * @fn              void INSTASPIN_Set_Vint_lockout(H_INSTASPIN_BLDC instaHandle, _iq vIntLockout)
 * @brief           Function to Set vIntLockout for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vIntLockout		The new Lockout value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vint_lockout(H_INSTASPIN_BLDC instaHandle, Eintbool vIntLockout)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vIntLockout = vIntLockout;
}

/*!
 * @ingroup         INSTASPIN_Get_Vint_lockout
 * @fn              Eintbool INSTASPIN_Get_Vint_lockout(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vIntLockout for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			Eintbool		The Lockout value for the InstaSPIN Module
 */
Eintbool INSTASPIN_Get_Vint_lockout(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vIntLockout;
}

/*!
 * @ingroup         INSTASPIN_Set_Vphase
 * @fn              void INSTASPIN_Set_Vphase(H_INSTASPIN_BLDC instaHandle, _iq vPhase)
 * @brief           Function to Set Vphase for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vPhase			The new vPhase value for the InstaSPIN Module
 */
void INSTASPIN_Set_Vphase(H_INSTASPIN_BLDC instaHandle, _iq *vPhase)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vPhase = vPhase;
}

/*!
 * @ingroup         INSTASPIN_Get_Vphase
 * @fn              _iq INSTASPIN_Get_Vphase(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vPhase for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The vPhase value for the InstaSPIN Module
 */
_iq *INSTASPIN_Get_Vphase(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vPhase;
}

/*!
 * @ingroup         INSTASPIN_Set_V_int
 * @fn              void INSTASPIN_Set_V_Int(H_INSTASPIN_BLDC instaHandle, _iq vInt)
 * @brief           Function to Set vInt for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		vInt			The new vInt value for the InstaSPIN Module
 */
void INSTASPIN_Set_V_int(H_INSTASPIN_BLDC instaHandle, _iq vInt)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->vInt = vInt;
}

/*!
 * @ingroup         INSTASPIN_Get_V_Int
 * @fn              _iq INSTASPIN_Get_V_Int(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get vInt for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			_iq				The vInt value for the InstaSPIN Module
 */
_iq INSTASPIN_Get_V_int(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->vInt;
}

/*!
 * @ingroup         INSTASPIN_Set_Comm_Trig
 * @fn              void INSTASPIN_Set_Comm_Trig(H_INSTASPIN_BLDC instaHandle, _iq commTrig)
 * @brief           Function to Set commTrig for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		commTrig		The new commTrig value for the InstaSPIN Module
 */
void INSTASPIN_Set_Comm_Trig(H_INSTASPIN_BLDC instaHandle, Eintbool commTrig)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->commTrig = commTrig;
}

/*!
 * @ingroup         INSTASPIN_Get_Comm_Trig
 * @fn              Eintbool INSTASPIN_Get_Comm_Trig(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get commTrig for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			Eintbool		The commTrig value for the InstaSPIN Module
 */
Eintbool INSTASPIN_Get_Comm_Trig(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->commTrig;
}

/*!
 * @ingroup         INSTASPIN_Set_State
 * @fn              void INSTASPIN_Set_State(H_INSTASPIN_BLDC instaHandle, _iq State)
 * @brief           Function to Set State for the InstaSPIN Module
 * @param [in/out]  instaHandle		The Handle for the InstaSPIN Module
 * @param [in]		State			The new State value for the InstaSPIN Module
 */
void INSTASPIN_Set_State(H_INSTASPIN_BLDC instaHandle, uint16_t state)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    instaObj->state = state;
}

/*!
 * @ingroup         INSTASPIN_Get_State
 * @fn              uint16_t INSTASPIN_Get_State(H_INSTASPIN_BLDC instaHandle)
 * @brief           Function to Get State for the InstaSPIN Module
 * @param [in]      instaHandle		The Handle for the InstaSPIN Module
 * @return			uint16_t			The State value for the InstaSPIN Module
 */
uint16_t INSTASPIN_Get_State(H_INSTASPIN_BLDC instaHandle)
{
    INSTASPIN_BLDC *instaObj = (INSTASPIN_BLDC *)instaHandle;
    return instaObj->state;
}

/*!
 * @ingroup         STATEFILTER_Setup
 * @fn              void STATEFILTER_Setup(H_STATEFILTER stateFilterHandle)
 * @brief           Function to Setup a Statefilter Handler
 * @param [in]      stateFilterHandle	The Handle for the StateFilter Module
 */
void STATEFILTER_Setup(H_STATEFILTER stateFilterHandle)
{
    STATEFILTER_Set_State(stateFilterHandle, STATEFILTER_STATE_DEFAULT);
    STATEFILTER_Set_Sense(stateFilterHandle, STATEFILTER_SENSE_DEFAULT);
    STATEFILTER_Set_Integrate(stateFilterHandle, STATEFILTER_INTEGRATE_DEFAULT);
}

/*!
 * @ingroup         STATEFILTER_Set_State
 * @fn              void STATEFILTER_Set_State(H_STATEFILTER stateFilterHandle, uint16_t State)
 * @brief           Function to Set the State of the StateFilter
 * @param [in/out]  stateFilterHandle	The Handle for the StateFilter Module
 * @param [in]		State				The new State value for the StateFilter Module
 */
void STATEFILTER_Set_State(H_STATEFILTER stateFilterHandle, uint16_t state)
{
    STATEFILTER *stateFilterObj = (STATEFILTER *)stateFilterHandle;
    stateFilterObj->state = state;
}

/*!
 * @ingroup         STATEFILTER_Get_State
 * @fn              uint16_t STATEFILTER_Get_State(H_STATEFILTER stateFilterHandle)
 * @brief           Function to Get State for the StateFilter Module
 * @param [in]      stateFilterHandle	The Handle for the StateFilter Module
 * @return			uint16_t				The State value for the StateFilter Module
 */
uint16_t STATEFILTER_Get_State(H_STATEFILTER stateFilterHandle)
{
    STATEFILTER *stateFilterObj = (STATEFILTER *)stateFilterHandle;
    return stateFilterObj->state;
}

/*!
 * @ingroup         STATEFILTER_Set_Sense
 * @fn              void STATEFILTER_Set_Sense(H_STATEFILTER stateFilterHandle, uint16_t Sense)
 * @brief           Function to Set the Sense of the StateFilter
 * @param [in/out]  stateFilterHandle	The Handle for the StateFilter Module
 * @param [in]		Sense				The new Sense value for the StateFilter Module
 */
void STATEFILTER_Set_Sense(H_STATEFILTER stateFilterHandle, Esense sense)
{
    STATEFILTER *stateFilterObj = (STATEFILTER *)stateFilterHandle;
    stateFilterObj->sense = sense;
}

/*!
 * @ingroup         STATEFILTER_Get_Sense
 * @fn              Esense STATEFILTER_Get_Sense(H_STATEFILTER stateFilterHandle)
 * @brief           Function to Get Sense for the StateFilter Module
 * @param [in]      stateFilterHandle	The Handle for the StateFilter Module
 * @return			Esense				The Sense value for the StateFilter Module
 */
Esense STATEFILTER_Get_Sense(H_STATEFILTER stateFilterHandle)
{
    STATEFILTER *stateFilterObj = (STATEFILTER *)stateFilterHandle;
    return stateFilterObj->sense;
}

/*!
 * @ingroup         STATEFILTER_Set_Integrate
 * @fn              void STATEFILTER_Set_Integrate(H_STATEFILTER stateFilterHandle, uint16_t Integrate)
 * @brief           Function to Set the Integrate of the StateFilter
 * @param [in/out]  stateFilterHandle	The Handle for the StateFilter Module
 * @param [in]		Integrate			The new Integrate value for the StateFilter Module
 */
void STATEFILTER_Set_Integrate(H_STATEFILTER stateFilterHandle, Eintdir integrate)
{
    STATEFILTER *stateFilterObj = (STATEFILTER *)stateFilterHandle;
    stateFilterObj->integrate = integrate;
}

/*!
 * @ingroup         STATEFILTER_Get_Integrate
 * @fn              Eintdir STATEFILTER_Get_Integrate(H_STATEFILTER stateFilterHandle)
 * @brief           Function to Get Integrate for the StateFilter Module
 * @param [in]      stateFilterHandle	The Handle for the StateFilter Module
 * @return			Eintdir				The Integrate value for the StateFilter Module
 */
Eintdir STATEFILTER_Get_Integrate(H_STATEFILTER stateFilterHandle)
{
    STATEFILTER *stateFilterObj = (STATEFILTER *)stateFilterHandle;
    return stateFilterObj->integrate;
}

