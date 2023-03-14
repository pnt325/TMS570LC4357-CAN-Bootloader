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
//! \file   ~/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/rm48l952/src/gui.c
//! \brief  Contains the various functions related to the GUI object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "gui.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals

GUI_Obj gGUIObj;


// **************************************************************************
// the functions


//! \brief     Initializes the GUI module
//! \param[in] pMemory		A pointer to the memory for the GUI object
//! \param[in] numBytes     The number of bytes allocated for the GUI object, bytes
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


//! \brief     Sets up the GUI module
//! \param[in] guiHandle  	The GUI handle
//! \param[in] drvHandle  	The DRV handle
//! \param[in] graphHandle  The GRAPH handle
void GUI_setup(GUI_Handle guiHandle, DRV_Handle drvHandle, GRAPH_Handle graphHandle)
{
    GUI_Obj *gui = (GUI_Obj *)guiHandle;
    DRV_Obj *drv = (DRV_Obj *)drvHandle;
    ADC_Data_t adcData;

    // Setup gui variables
    gui->Kp_spd = PID_getProportionalGain(drv->ctrl.pidHandle_spd);
    gui->Ki_spd = PID_getIntegralGain(drv->ctrl.pidHandle_spd)/(CTRL_getPeriod(drv->ctrlHandle)*CTRL_getSpdPrescalarMax(drv->ctrlHandle));
    gui->Kd_spd = PID_getDerivativeGain(drv->ctrl.pidHandle_spd)*(CTRL_getPeriod(drv->ctrlHandle)*CTRL_getSpdPrescalarMax(drv->ctrlHandle));
    gui->Sat_spd = PID_getSaturation(drv->ctrl.pidHandle_spd);

    gui->Kp_Iq = PID_getProportionalGain(drv->ctrl.pidHandle_Iq);
    gui->Ki_Iq = PID_getIntegralGain(drv->ctrl.pidHandle_Iq)/(CTRL_getPeriod(drv->ctrlHandle));
    gui->Kd_Iq = PID_getDerivativeGain(drv->ctrl.pidHandle_Iq)*(CTRL_getPeriod(drv->ctrlHandle));
    gui->Sat_Iq = PID_getSaturation(drv->ctrl.pidHandle_Iq);

    gui->Kp_Id = PID_getProportionalGain(drv->ctrl.pidHandle_Id);
    gui->Ki_Id = PID_getIntegralGain(drv->ctrl.pidHandle_Id)/(CTRL_getPeriod(drv->ctrlHandle));
    gui->Kd_Id = PID_getDerivativeGain(drv->ctrl.pidHandle_Id)*(CTRL_getPeriod(drv->ctrlHandle));
    gui->Sat_Id = PID_getSaturation(drv->ctrl.pidHandle_Id);

    gui->CommAngleOffset = QEP_get_calibratedAngle(drv->qepHandle);
    gui->Cal_offset_A = DRV_get_cal_offset_A(drvHandle);
    gui->Cal_offset_B = DRV_get_cal_offset_B(drvHandle);
    gui->Adc_current_gain_A = DRV_get_adc_current_gain_A(drvHandle);
    gui->Adc_current_gain_B = DRV_get_adc_current_gain_B(drvHandle);

	adcData = DRV_get_adcData(drvHandle);
    gui->IMotor = 0;
    gui->VBus = adcData.dcBusV;
    gui->IPhaseA  = adcData.I.value[0];
    gui->IPhaseB = adcData.I.value[1];
    gui->SpeedEncoder = SPEED_FR_get_speed_rpm(drv->speed_frHandle);
    gui->SpeedSMO = SPEED_EST_get_speed_rpm(drv->speed_estHandle);
    gui->SpeedRPM = 0;
    gui->FaultMotor = 0;
    gui->FaultEncoder = DRV_get_encoderFaultReg(drvHandle);
    gui->OTFlg = DRV_get_overTempFlg(drvHandle);
    gui->OVFlg = DRV_get_overVoltageFlg(drvHandle);
    gui->BFFlg = DRV_get_bridgeFaultFlg(drvHandle);

    gui->SpdCmd = PID_getRefValue(drv->ctrl.pidHandle_spd);
    gui->IqCmd = PID_getRefValue(drv->ctrl.pidHandle_Iq);
    gui->IdCmd = PID_getRefValue(drv->ctrl.pidHandle_Id);
    gui->CtrlType = CTRL_get_Control_Mode(drv->ctrlHandle);
    gui->EnableFlg = DRV_get_Enable(drvHandle);
    gui->RstFault = 0;
    gui->LogScalar = Graph_get_prescalar(graphHandle);

    gui->Rs = SMO_POS_get_Rs(drv->smoPosHandle);
    gui->Ls_q = SMO_POS_get_Ls(drv->smoPosHandle);
    gui->K_sl = SMO_POS_getKslideGain(drv->smoPosHandle);
    gui->K_lsf = SMO_POS_getKslfGain(drv->smoPosHandle);
    gui->SwitchOverSpdFwd = DRV_get_SwitchOverSpdFwd(drvHandle);
    gui->SwitchOverSpdRev = DRV_get_SwitchOverSpdRev(drvHandle);

    gui->numPolePairs = QEP_get_polePairs(drv->qepHandle);
    gui->Motor_Enc_Dir = QEP_get_direction(drv->qepHandle);
    gui->LineCount = QEP_get_lineCounts(drv->qepHandle);
    gui->GearRatio = 1;

    gui->BaseFreq = SPEED_EST_get_base_freq(drv->speed_estHandle);
    gui->LP_freq = SPEED_EST_get_cutoff(drv->speed_estHandle);

    gui->DlogChannel1 = &(gDLog4CHBuff1[0]);
    gui->DlogChannel2 = &(gDLog4CHBuff2[0]);
    gui->DlogChannel3 = &(gDLog4CHBuff3[0]);
    gui->DlogChannel4 = &(gDLog4CHBuff4[0]);
    gui->DlogArraySize = DLOG_ARRAY_SIZE;

    gui->calibrateEnable = 0;
    gui->rtiBenchmarkTime = DRV_get_rtiBenchmarkTime(drvHandle);
    gui->GraphInput = GraphInput;
    gui->reserved = 0;

}

