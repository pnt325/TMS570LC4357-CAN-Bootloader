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
#ifndef _GUI_H_
#define _GUI_H_

//! \file   ~/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/tms570ls1227/src
//! \brief  Contains the public interface to the 
//!         GUI module routines
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes
#include "modules/types/src/32b/types.h"
#include "stddef.h"
#include "solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/tms570ls1227/src/drv.h"
#include "modules/speed_pr/src/float32/hercules/speed_pr.h"
#include "modules/pid/src/float32/hercules/pid.h"
#include "modules/dlog/src/float32/hercules/DLOG.h"
//!
//! \defgroup GUI

//!
//! \ingroup GUI
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines
#define RW_CURRENT_GAIN		10.3125
#define RW_DCBUS_GAIN		66.32
#define TORQUE_NM_PER_A		0.0388


// **************************************************************************
// the typedefs

//! \brief Defines the GUI object
//!
typedef struct _GUI_obj_
{
    float32_t   Kp_current;
    float32_t   Ki_current;
    float32_t   Kd_current;
    float32_t   Sat_current;

    float32_t   Kp_spd;
    float32_t   Ki_spd;
    float32_t   Kd_spd;
    float32_t   Sat_spd;

    float32_t   CommThreshold;

    float32_t   IMotor;
    float32_t   VBus;
    float32_t   IPhaseA;
    float32_t   IPhaseB;
    float32_t   BemfA;
    float32_t   BemfB;
    float32_t   BemfC;
    float32_t   SpdMotor;
    float32_t   PosMotor;
    uint16_t    FaultMotor;
    uint16_t    OTFlg;
    uint16_t    OVFlg;
    uint32_t    nERROR;

    float32_t   SpdCmd;
    float32_t   TorqueCmd;
    float32_t	DutyCmd;
    float32_t   CtrlType;
    float32_t   EnableFlg;
    uint16_t    RstFault;
    uint16_t    LogScalar;

    float32_t   Rs;
    float32_t   Rr;
    float32_t   Ls_d;
    float32_t   Ls_q;
    float32_t   BaseFreq;
    float32_t   K_sl;
    float32_t   K_lsf;

    uint16_t    numPolePairs;
    int16_t     Motor_Enc_Dir;
    uint32_t    LineCount;
    float32_t   GearRatio;

    int32_t		SpeedRPM;
    float32_t	CurrentDisplay;
    float32_t	DFuncStartup;
    uint16_t	RampUpTime;
    int32_t		BeginStartRPM;
    int32_t		EndStartRPM;
    uint16_t	AdvancedStartup;
    float32_t	CommErrorMax;
    uint16_t	TripCnt;
    float32_t	CurrentStartup;
    float32_t	IMax;
    uint16_t	Poles;
    int16_t		MinVDC;
    int16_t		MaxVDC;

    float32_t   LP_freq;
    
    float32_t	*DlogChannel1;
    float32_t	*DlogChannel2;
    float32_t	*DlogChannel3;
    float32_t	*DlogChannel4;
    uint16_t	DlogArraySize;

    uint16_t	TPSFlag;
} GUI_Obj;

//! \brief Defines the GUI handle
typedef struct GUI_Obj     *GUI_Handle;

// **************************************************************************
// the globals
extern GUI_Obj gGUIObj;

// **************************************************************************
// the function prototypes

//! \brief     Initializes the GUI module
//! \param[in] pMemory            A pointer to the memory for the GUI object
//! \param[in] numBytes           The number of bytes allocated for the GUI object, bytes
//! \return The GUI object handle
GUI_Handle GUI_init(void *pMemory,const size_t numBytes);


//! \brief     Runs the GUI module
//! \param[in] guiHandle  The GUI handle
void GUI_setup(GUI_Handle guiHandle, DRV_Handle drvHandle, GRAPH_Handle graphHandle);


//! \brief     Runs the GUI data transfer module
//! \param[in] guiHandle  GUI handle
inline void GUI_run(GUI_Handle guiHandle, DRV_Handle drvHandle, GRAPH_Handle graphHandle)
{   
    GUI_Obj *gui = (GUI_Obj *)guiHandle;
    DRV_Obj *drv = (DRV_Obj *)drvHandle;

    // Data Transfers happen here
    // Change parameters
    PID_setGains(drv->pidSpdHandle, gui->Kp_spd, gui->Ki_spd * T , gui->Kd_spd / T);
    PID_setMinMax(drv->pidSpdHandle, -gui->Sat_spd, gui->Sat_spd);

    PID_setGains(drv->pidIDCHandle, gui->Kp_current, gui->Ki_current * T , gui->Kd_current / T );
    PID_setMinMax(drv->pidIDCHandle, -gui->Sat_current, gui->Sat_current);

    drv->threshold = gui->CommThreshold;

    drv->controlMode = gui->CtrlType;
    drv->enableFlag = gui->EnableFlg;
    Graph_set_prescalar(graphHandle, gui->LogScalar);

    switch( drv->controlMode )
    {
    case(CURRENT):
		drv->ref = gui->TorqueCmd;
    	drv->currentMode = 1;
    	drv->velocityMode = 0;
		break;
    case(VELOCITY):
		drv->ref = gui->SpdCmd;
    	drv->currentMode = 0;
    	drv->velocityMode = 2;
		break;
    case(CASCADE):
		drv->ref = gui->SpdCmd;
    	drv->currentMode = 1;
    	drv->velocityMode = 2;
    	break;
    default:
    	drv->ref = gui->DutyCmd;
    	drv->currentMode = 0;
    	drv->velocityMode = 0;
    	break;
    }

    drv->dFuncStartup = gui->DFuncStartup;
    drv->rampUpTime = gui->RampUpTime;
    drv->beginStartRPM = gui->BeginStartRPM;
    drv->endStartRPM = gui->EndStartRPM;
    drv->advancedStartup = gui->AdvancedStartup;
    drv->commErrorMax = gui->CommErrorMax;
    drv->tripCnt = gui->TripCnt;
    drv->currentStartup = gui->CurrentStartup;
    drv->iMax = gui->IMax;
    drv->minVDC = gui->MinVDC;
    drv->maxVDC = gui->MaxVDC;

    // Update monitor values
    gui->SpeedRPM = drv->speedRPM;
    gui->CurrentDisplay = drv->iDCFdbk*drv->mod6Handle->cntDirection;
    gui->Poles = drv->poles;

    gui->IMotor = drv->iDCFdbk*RW_CURRENT_GAIN*drv->mod6Handle->cntDirection;
    gui->VBus = drv->vDCBus*RW_DCBUS_GAIN;
    gui->BemfA = drv->iqVaIn;
    gui->BemfB = drv->iqVbIn;
    gui->BemfC = drv->iqVcIn;

    gui->SpdMotor = SPEED_MEAS_CAP_Get_Speed_Output(drv->speedHandle);

	gui->OTFlg = DRV_get_overTempFlg(drvHandle);
	gui->OVFlg = DRV_get_overVoltageFlg(drvHandle);
	gui->FaultMotor = DRV_get_bridgeFaultFlg(drvHandle);

	drv->tpsFlag = gui->TPSFlag;

    return;
} // end of GUI_run() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif // end of _GUI_H_ definition
