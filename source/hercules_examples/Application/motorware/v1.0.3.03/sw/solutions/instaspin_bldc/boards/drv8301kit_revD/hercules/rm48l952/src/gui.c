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
//! \file   ~/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/rm48l952/src
//! \brief  Contains the various functions related to the GUI object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

// drivers

// modules
#include "gui.h"

// platforms

// **************************************************************************
// the defines


// **************************************************************************
// the globals

GUI_Obj gGUIObj;


// **************************************************************************
// the functions


//! \brief     Initializes the GUI module
//! \param[in] pMemory            A pointer to the memory for the GUI object
//! \param[in] numBytes           The number of bytes allocated for the GUI object, bytes
//! \return The GUI object handle
GUI_Handle GUI_init(void *pMemory,const size_t numBytes)
{
    GUI_Handle guiHandle;
    
    if(numBytes < sizeof(GUI_Obj))
        return((GUI_Handle)NULL);
        
    // assign the handle
    guiHandle = (GUI_Handle)pMemory;
    
    
    return(guiHandle);
    
}


//! \brief     Runs the GUI module
//! \param[in] guiHandle  The GUI handle
void GUI_setup(GUI_Handle guiHandle, DRV_Handle drvHandle, GRAPH_Handle graphHandle)
{
    GUI_Obj *gui = (GUI_Obj *) guiHandle;
    DRV_Obj *drv = (DRV_Obj *) drvHandle;

    //accessor functions to set up initial parameters go here
    gui->Kp_spd = PID_getProportionalGain(drv->pidSpdHandle);
    gui->Ki_spd = PID_getIntegralGain(drv->pidSpdHandle) * fs;
    gui->Kd_spd = PID_getDerivativeGain(drv->pidSpdHandle) * T;
    gui->Sat_spd = PID_getSaturation(drv->pidSpdHandle);

    gui->Kp_current = PID_getProportionalGain(drv->pidIDCHandle);
    gui->Ki_current = PID_getIntegralGain(drv->pidIDCHandle) * fs;
    gui->Kd_current = PID_getDerivativeGain(drv->pidIDCHandle)  * T;
    gui->Sat_current = PID_getSaturation(drv->pidIDCHandle);

    gui->CommThreshold = drv->threshold;

    gui->IMotor = drv->iDCFdbk*RW_CURRENT_GAIN;
    gui->VBus = drv->vDCBus*RW_DCBUS_GAIN;
    gui->BemfA = drv->iqVaIn;
    gui->BemfB = drv->iqVbIn;
    gui->BemfC = drv->iqVcIn;

    gui->SpdMotor = SPEED_MEAS_CAP_Get_Speed_Output(drv->speedHandle);
    gui->SpdCmd = PID_getRefValue(drv->pidSpdHandle);
    gui->TorqueCmd = PID_getRefValue(drv->pidIDCHandle);
    gui->DutyCmd = drv->ref;

    gui->CtrlType = drv->controlMode;
    gui->EnableFlg = drv->enableFlag;
    gui->LogScalar = Graph_get_prescalar(graphHandle);

    gui->SpeedRPM = drv->speedRPM;
    gui->CurrentDisplay = drv->currentDisplay;
    gui->DFuncStartup = drv->dFuncStartup;
    gui->RampUpTime = drv->rampUpTime;
    gui->BeginStartRPM = drv->beginStartRPM;
    gui->EndStartRPM = drv->endStartRPM;
    gui->AdvancedStartup = drv->advancedStartup;
    gui->CommErrorMax = drv->commErrorMax;
    gui->TripCnt = drv->tripCnt;
    gui->CurrentStartup = drv->currentStartup;
    gui->IMax = drv->iMax;
    gui->Poles = drv->poles;
    gui->MinVDC = drv->minVDC;
    gui->MaxVDC = drv->maxVDC;

	gui->OTFlg = DRV_get_overTempFlg(drvHandle);
	gui->OVFlg = DRV_get_overVoltageFlg(drvHandle);
	gui->FaultMotor = DRV_get_bridgeFaultFlg(drvHandle);
	gui->nERROR = 0;

    gui->DlogChannel1 = &(gDLog4CHBuff1[0]);
    gui->DlogChannel2 = &(gDLog4CHBuff2[0]);
    gui->DlogChannel3 = &(gDLog4CHBuff3[0]);
    gui->DlogChannel4 = &(gDLog4CHBuff4[0]);
    gui->DlogArraySize = DLOG_ARRAY_SIZE;
}
