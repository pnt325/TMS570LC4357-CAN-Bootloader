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

//! \file   ~/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137/src/gui.h
//! \brief  Contains the public interface to the 
//!         GUI module routines
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "sys_common.h"


// **************************************************************************
// the modules

#include "solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/ctrl.h"
#include "solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/drv.h"
#include "modules/dlog/src/float32/hercules/DLOG.h"
#include "modules/types/src/32b/controller_data_types.h"


// **************************************************************************
// the drivers

#include "drivers/qep/src/32b/hercules/champion/enc.h"

// **************************************************************************
// the defines
#define RW_CURRENT_GAIN		10.3125
#define RW_DCBUS_GAIN		66.32
#define TORQUE_NM_PER_A		0.0388


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


// **************************************************************************
// the typedefs

//! \brief Defines the GUI object
//!
typedef struct _GUI_obj_
{
    // (FOC Systems)
    float32_t   Kp_Iq;
    float32_t   Ki_Iq;
    float32_t   Kd_Iq;
    float32_t   Sat_Iq;

    float32_t   Kp_Id;
    float32_t   Ki_Id;
    float32_t   Kd_Id;
    float32_t   Sat_Id;
    
    float32_t   Kp_spd;
    float32_t   Ki_spd;
    float32_t   Kd_spd;
    float32_t   Sat_spd;

    int32_t   	CommAngleOffset;
    int32_t		Cal_offset_A;
    int32_t		Cal_offset_B;
    float32_t	Adc_current_gain_A;
    float32_t	Adc_current_gain_B;


    float32_t   IMotor;
    float32_t   VBus;
    float32_t   IPhaseA;
    float32_t   IPhaseB;
    float32_t   SpeedEncoder;
    float32_t   SpeedSMO;
    float32_t   SpeedRPM;
    uint32_t    FaultMotor;
    uint32_t    FaultEncoder;
    uint32_t    OTFlg;
    uint32_t    OVFlg;
    uint32_t    BFFlg;
    uint32_t    nERROR;

    float32_t   SpdCmd;
    float32_t   IqCmd;
    float32_t   IdCmd;
    uint32_t	CtrlType;
    uint32_t   	EnableFlg;
    uint32_t    RstFault;
    uint32_t    LogScalar;

    float32_t   Rs;
    float32_t   Ls_q;
    float32_t   BaseFreq;
    float32_t   K_sl;
    float32_t   K_lsf;
    float32_t 	SwitchOverSpdFwd;
    float32_t 	SwitchOverSpdRev;

    uint32_t    numPolePairs;
    int32_t     Motor_Enc_Dir;
    uint32_t    LineCount;
    float32_t   GearRatio;

    float32_t   LP_freq;

    float32_t	*DlogChannel1;
    float32_t	*DlogChannel2;
    float32_t	*DlogChannel3;
    float32_t	*DlogChannel4;
    uint32_t	DlogArraySize;
    
    int32_t		calibrateEnable;
    float32_t	rtiBenchmarkTime;
    int32_t 	GraphInput;
    uint32_t	reserved;

    uint16_t	TPSFlag;
} GUI_Obj;


//! \brief Defines the GUI handle
typedef struct GUI_Obj	*GUI_Handle;


// **************************************************************************
// the globals

//! \brief Defines the DRV object
//!
extern GUI_Obj gGUIObj;
extern int32_t GraphInput;


// **************************************************************************
// the function prototypes

//! \brief     Initializes the GUI module
//! \param[in] pMemory		A pointer to the memory for the GUI object
//! \param[in] numBytes     The number of bytes allocated for the GUI object, bytes
//! \return The GUI object handle
GUI_Handle GUI_init(void *pMemory,const size_t numBytes);


//! \brief     Sets up the GUI module
//! \param[in] guiHandle  	The GUI handle
//! \param[in] drvHandle  	The DRV handle
//! \param[in] graphHandle  The GRAPH handle
void GUI_setup(GUI_Handle guiHandle, DRV_Handle drvHandle, GRAPH_Handle graphHandle);


//! \brief     Runs the GUI data transfer update
//! \param[in] guiHandle  	The GUI handle
//! \param[in] drvHandle  	The DRV handle
//! \param[in] graphHandle	The GRAPH handle
inline void GUI_run(GUI_Handle guiHandle, DRV_Handle drvHandle, GRAPH_Handle graphHandle)
{   
    GUI_Obj *gui = (GUI_Obj *)guiHandle;
    DRV_Obj *drv = (DRV_Obj *)drvHandle;

    uint16_t mode;
    ADC_Data_t adcData;

    // Set system enable flag
    if ((DRV_get_Enable(drvHandle) == 0) && (gui->EnableFlg == 1)) {
		gui->CtrlType = 0;
		gui->SpdCmd = 0;
		gui->IqCmd = 0;
		gui->IdCmd = 0;
    	DRV_FOC_start(drvHandle);
    }
    else if  ((DRV_get_Enable(drvHandle) == 1) && (gui->EnableFlg == 0)) {
		gui->CtrlType = 0;
		gui->SpdCmd = 0;
		gui->IqCmd = 0;
		gui->IdCmd = 0;
    	DRV_FOC_stop(drvHandle);
    }
 	DRV_set_Enable(drvHandle, gui->EnableFlg);

    // Reset gate driver fault upon request
    if (gui->RstFault == 1) {
    	DRV_gdFaultReset(drvHandle);
    	gui->RstFault = 0;
    }

    // Update encoder index to motor electrical zero offset
    gui->CommAngleOffset = DRV_run_calibration(drvHandle, gui->calibrateEnable);

    // Update phase current adc measurement scalars
    DRV_set_cal_offset_A(drvHandle, gui->Cal_offset_A);
    DRV_set_cal_offset_B(drvHandle, gui->Cal_offset_B);
    DRV_set_adc_current_gain_A(drvHandle, gui->Adc_current_gain_A);
    DRV_set_adc_current_gain_B(drvHandle, gui->Adc_current_gain_B);

    // Update current and speed PID parameters
    CTRL_setPID_Id_param(drv->ctrlHandle, gui->Kp_Id, gui->Ki_Id, gui->Kd_Id);
    PID_setMinMax(drv->ctrl.pidHandle_Id, -gui->Sat_Id, gui->Sat_Id);

    CTRL_setPID_Iq_param(drv->ctrlHandle, gui->Kp_Iq, gui->Ki_Iq, gui->Kd_Iq);
	PID_setMinMax(drv->ctrl.pidHandle_Iq, -gui->Sat_Iq, gui->Sat_Iq);

    CTRL_setPID_spd_param(drv->ctrlHandle, gui->Kp_spd, gui->Ki_spd, gui->Kd_spd);
	PID_setMinMax(drv->ctrl.pidHandle_spd, -gui->Sat_spd, gui->Sat_spd);


	// Update GUI with instantaneous motor data
	adcData = DRV_get_adcData(drvHandle);
	gui->VBus = (adcData.dcBusV)*RW_DCBUS_GAIN;
	gui->IPhaseA = (adcData.I.value[0])*RW_CURRENT_GAIN;
	gui->IPhaseB = (adcData.I.value[1])*RW_CURRENT_GAIN;
	gui->IMotor = (adcData.iTotal)*RW_CURRENT_GAIN;
    gui->SpeedEncoder = (-1)*SPEED_FR_get_speed_rpm(drv->speed_frHandle);
    gui->SpeedSMO = (-1)*SPEED_EST_get_speed_rpm(drv->speed_estHandle);
	gui->FaultEncoder = DRV_get_encoderFaultReg(drvHandle);
	gui->OTFlg = DRV_get_overTempFlg(drvHandle);
	gui->OVFlg = DRV_get_overVoltageFlg(drvHandle);
	gui->BFFlg = DRV_get_bridgeFaultFlg(drvHandle);

	// Speed reporting selection
    if (gui->FaultEncoder)
    	gui->SpeedRPM = gui->SpeedSMO;
    else
    	gui->SpeedRPM = gui->SpeedEncoder;

	// Protect system in cade of motor fault
	if ((gui->OTFlg) || (gui->OVFlg) || (gui->BFFlg)) {
		gui->FaultMotor = 1;
		if (gui->reserved == 0) {
			CTRL_change_Control_Mode(drv->ctrlHandle, DISABLED);
			gui->CtrlType = 0;
			gui->SpdCmd = 0;
			gui->IqCmd = 0;
			gui->IdCmd = 0;
			gui->reserved = 1;
		}
	}
	else {
		gui->FaultMotor = 0;
		gui->reserved = 0;
	}

	// Protect system in case of encoder fault
	if ((gui->FaultEncoder  == 1) &&
		(drv->commutationMode == ENCODER_COMMUTATION_MODE) &&
		(gui->CtrlType == 2)) //Speed control mode
	{
		gui->SpdCmd = 0;
		gui->CtrlType = 0;
	}


	// Update control mode
	if (gui->calibrateEnable == 0) {

		// Update encoder index to 0.0 degree offset
		ENC_set_calibratedAngle(drv->encHandle, gui->CommAngleOffset);

		// Update control mode
		mode = gui->CtrlType;
		switch(mode)
		{
		   case 1:
			CTRL_change_Control_Mode(drv->ctrlHandle, TORQUE_CTRL);
			CTRL_set_current(drv->ctrlHandle, gui->IdCmd, gui->IqCmd);
			break;

		   case 2:
			CTRL_change_Control_Mode(drv->ctrlHandle, SPEED_CTRL);

			// Bound speed command to +/- 0.99 (pu)
			if (gui->SpdCmd >= 0.99)
				gui->SpdCmd  = 0.99;
			else if (gui->SpdCmd <= -0.99)
				gui->SpdCmd  = -0.99;

			if (DRV_get_encoderFaultReg(drvHandle) && (DRV_get_commutationMode(drvHandle) == ENCODER_COMMUTATION_MODE))
				CTRL_change_Control_Mode(drv->ctrlHandle, DISABLED);
			else
				CTRL_set_spd(drv->ctrlHandle, gui->SpdCmd);
			break;

		   default:
			CTRL_change_Control_Mode(drv->ctrlHandle, DISABLED);
			DRV_set_encoderFaultReg(drvHandle, 0);
			break;
		}
	}


   // Update SMO parameters
   SMO_POS_set_Rs(drv->smoPosHandle, gui->Rs);
   SMO_POS_set_Ls(drv->smoPosHandle, gui->Ls_q);
   SMO_POS_set_Kslide(drv->smoPosHandle, gui->K_sl);
   SMO_POS_set_Kslf(drv->smoPosHandle, gui->K_lsf);
   DRV_set_SwitchOverSpdFwd(drvHandle, gui->SwitchOverSpdFwd);
   DRV_set_SwitchOverSpdRev(drvHandle, gui->SwitchOverSpdRev);

   // Update ENC parameters
   ENC_set_polePairs(drv->encHandle, gui->numPolePairs);
   ENC_set_direction(drv->encHandle, gui->Motor_Enc_Dir);
   ENC_set_lineCounts(drv->encHandle, gui->LineCount);
   QEP_set_max_posn_count(drv->qepHandle, gui->LineCount*4);

   // Update speed feedback parameters
   SPEED_EST_set_base_freq(drv->speed_estHandle, gui->BaseFreq);
   SPEED_EST_set_cutoff(drv->speed_estHandle, gui->LP_freq);
   SPEED_FR_set_base_freq(drv->speed_frHandle, gui->BaseFreq);
   SPEED_FR_set_cutoff(drv->speed_frHandle, gui->LP_freq);

   // Update benchmark ISR service time
   gui->rtiBenchmarkTime = DRV_get_rtiBenchmarkTime(drvHandle);
   Graph_set_prescalar(graphHandle, gui->LogScalar);
   GraphInput = gui->GraphInput;

   drv->tpsFlag = gui->TPSFlag;

    return;
} // end of GUI_run() function


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif // end of _GUI_H_ definition
