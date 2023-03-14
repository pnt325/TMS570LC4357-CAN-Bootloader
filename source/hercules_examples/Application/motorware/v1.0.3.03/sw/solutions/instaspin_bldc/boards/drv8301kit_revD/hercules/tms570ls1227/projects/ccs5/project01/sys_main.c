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
/** @file sys_main.c 
*   @brief Application main file
*   @date 15.December.2011
*   @version 03.00.00
*
*   This file contains the main function, for FOC motor control
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */

//! \file   ~/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src/sys_main.c
//!
//! \brief  Main system file for the three phase sensored speed SMO project
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

#include "sys_main.h"
/* USER CODE END */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */


// **************************************************************************
// the globals

DRV_Handle drvHandle;				// Handle to the Inverter driver object

GUI_Handle guiHandle;				// Handle to the GUI object

GRAPH_DATA	graph;
GRAPH_Handle graphHandle = &graph;
float32_t DlogCh1 = 0;
float32_t DlogCh2 = 0;
float32_t DlogCh3 = 0;
float32_t DlogCh4 = 0;
int32_t GraphInput = 0;

/* USER CODE END */


/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

// **************************************************************************
// the functions

/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	_mpuInit_();
	(*(volatile unsigned int *)(0xFFFFEA38))=0x83E70B13;
    (*(volatile unsigned int *)(0xFFFFEA3C))=0x95A4F1E0;
    (*(volatile unsigned int *)(0xFFFFEB88))=0x00000002;//ADC Alternate Trigger

    //enable all ePWM s + TZ + ECAP1,2,3,4 + EQEP1+EQEP2
    *(volatile unsigned int *) 0xFFFFEBA4 = 0x01010102; // Enable TBCLK 37[1]
    *(volatile unsigned int *) 0xFFFFEB10 = 0x08010801; // nTZ1 0[19], nTZ2 0[27],
    *(volatile unsigned int *) 0xFFFFEB18 = 0x04010110; // ETPWM1A 2[26], EQEP2I 2[4]
    *(volatile unsigned int *) 0xFFFFEB1C = 0x01040101; // ETPWM1B 3[18]
    *(volatile unsigned int *) 0xFFFFEB20 = 0x20200104; // ETPWM2A 4[2], EQEP2A 4[21], EQEP2B 4[29]
    *(volatile unsigned int *) 0xFFFFEB24 = 0x01080404; // ETPWM2B 5[2], ETPWM3A 5[10], ETPWM3B 5[19]
    *(volatile unsigned int *) 0xFFFFEB2C = 0x01040101; // ETPWM5A 7[18]
    *(volatile unsigned int *) 0xFFFFEB30 = 0x01040104; // ETPWM5B 8[2], ECAP1 8[18]
    *(volatile unsigned int *) 0xFFFFEB34 = 0x01010801; //EQEP1B 9[11], SPI3CS0/EQEP1I 9[16/19]
    *(volatile unsigned int *) 0xFFFFEB40 = 0x20100101; // ECAP4 12[20],ECAP5 12[29]
    *(volatile unsigned int *) 0xFFFFEB40 = 0x04010101; // ECAP6 13[26]
    *(volatile unsigned int *) 0xFFFFEB54 = 0x01010110; // nTZ3 17[4]
    *(volatile unsigned int *) 0xFFFFEB5C = 0x01010801; // EQEP2S 19[11]
    *(volatile unsigned int *) 0xFFFFEB60 = 0x01100101; // EQEP1S 20[20]
    *(volatile unsigned int *) 0xFFFFEB7C = 0x01010104; // ETPWM4A 27[2]
    *(volatile unsigned int *) 0xFFFFEB94 = 0x01010102; // ETPWM4B 33[1], SPI3SOMI/ECAP2 33[8/10], SPI3SIMO/ECAP3 33[16/18],SPI3CLK/EQEP1A 33[24/26]
    *(volatile unsigned int *) 0xFFFFEB98 = 0x01020201; // ETPWM6A 34[9], ETPWM6B 34[17]
    *(volatile unsigned int *) 0xFFFFEB8C =0x01010102;//SRC=110, A2 31[1]
    (*(volatile unsigned int *)(0xFFFFEA38))=0x0;
    (*(volatile unsigned int *)(0xFFFFEA3C))=0x0;

    guiHandle = GUI_init(&gGUIObj,sizeof(gGUIObj));

	// initialize the driver
	drvHandle = DRV_init(&drv,sizeof(drv), T);

	// initialize the graph module (data logger)
	graph.ch1Ptr = &DlogCh1;
	graph.ch2Ptr = &DlogCh2;
	graph.ch3Ptr = &DlogCh3;
	graph.ch4Ptr = &DlogCh4;
	graph.trigValue = 0.0;
	graph.size = 0x00FF;
	graph.holdoff = 3;
	graph.prescalar = 5;
	Graph_Data_Init(graphHandle);

	// initialize the gui

	GUI_setup(guiHandle, drvHandle, graphHandle);

	// Send SPI commands to DRV8301 to set it up
	spiREG3->DAT1 = 0x13D0;
    while((spiREG3->FLG & 0x100)!=0x100);
    drv.SPI3_RXDATA[0] = (spiREG3->BUF) & 0xFF;

    spiREG3->DAT1 = 0x8000;
    while((spiREG3->FLG & 0x100)!=0x100);
    drv.SPI3_RXDATA[1] = (spiREG3->BUF) & 0xFF;

    spiREG3->DAT1 = 0x180D;
    while((spiREG3->FLG & 0x100)!=0x100);
    drv.SPI3_RXDATA[2] = (spiREG3->BUF) & 0xFF;

    spiREG3->DAT1 = 0x8000;
    while((spiREG3->FLG & 0x100)!=0x100);
    drv.SPI3_RXDATA[3] = (spiREG3->BUF) & 0xFF;

    while((GetChar(drv.ecmpHandle) != '2') && (!gGUIObj.TPSFlag));

    if(!gGUIObj.TPSFlag)
    {
    	gGUIObj.DutyCmd = 0;
    	gGUIObj.TorqueCmd = 0;
    	gGUIObj.SpdCmd = 0;
    	gGUIObj.EnableFlg = 1;
    	PutText(drv.ecmpHandle, "Motor Enabled\r\n");
    }

	// Endless loop to wait for start command from either GUI or button
	while(DRV_get_Enable(drvHandle) != 1){

	    GUI_run((GUI_Handle)&gGUIObj, drvHandle, graphHandle);
	}

	// Start the PWMs and Interrupt
	DRV_Motor_start(drvHandle);

	// Enable the peripheral interrupt notifications
	gioEnableNotification(0);
	gioEnableNotification(1);
	adcEnableNotification(adcREG1, adcGROUP1);	
	adcEnableNotification(adcREG1, adcGROUP2);

	// Drop into main while loop
	drv.ADC_INT_ENA=1;
	while(1)
	{
		drv.SCI_Command = GetChar(drv.ecmpHandle);
		switch (drv.SCI_Command)
		{
			case '3':
				gGUIObj.CtrlType = 0;
				gGUIObj.DutyCmd = 0.3;
				PutText(drv.ecmpHandle, "Duty Cycle Mode Enabled\r\n");
				break;
			case '4':
				gGUIObj.CtrlType = 1;
				gGUIObj.TorqueCmd = 0.3;
				PutText(drv.ecmpHandle, "Current Mode Enabled\r\n");
				break;
			case '5':
				gGUIObj.CtrlType = 2;
				gGUIObj.SpdCmd = 0.3;
				PutText(drv.ecmpHandle, "Velocity Mode Enabled\r\n");
				break;
			case '6':
				gGUIObj.CtrlType = 3;
				gGUIObj.SpdCmd = 0.3;
				PutText(drv.ecmpHandle, "Cascade (Current + Velocity) Mode Enabled\r\n");
				break;
			case '7':
				gGUIObj.DutyCmd = 0;
				gGUIObj.CtrlType = 0;
				gGUIObj.SpdCmd = 0;
				gGUIObj.TorqueCmd = 0;
				PutText(drv.ecmpHandle, "Motor Stopped\r\n");
				break;
			case '8':
				drv.ecmpHandle->DiagFlag = !drv.ecmpHandle->DiagFlag;
				PutText(drv.ecmpHandle, "Watchdog Diagnostics Flag Toggled\r\n");
				break;
		}
		if(drv.Process_WDA==1)
		{
			ecmpWdQaSendAnswer(drv.ecmpHandle, 0, 0, 0);
	    	drv.Process_WDA = 0;
		}
		// Run the GUI interface
	    GUI_run((GUI_Handle)&gGUIObj, drvHandle, graphHandle);
	} 
/* USER CODE END */
}


/* USER CODE BEGIN (4) */
/********************************************************************************
	ADC Notification
********************************************************************************/			                           
void adcNotification(adcBASE_t *adc, uint32_t group)
{
	//Run the Motor
	DRV_EnableMotor(drvHandle);
	DRV_run(drvHandle);

	//Log data
	switch (GraphInput) {
	case 0:
	default:
		DlogCh1 = (float) drv.mod6Handle->counter;
		DlogCh2 = (float) drv.instaHandle->vInt;
		DlogCh3 = (float) drv.iqVaIn;
		DlogCh4 = (float) drv.iDCFdbk;
	}

	// ------------------------------------------------------------------------------
	// Update data logger
	// ------------------------------------------------------------------------------
	Graph_Data_Update(graphHandle);

} 	// end of the interrupt


// Here are dummy functions for the HALCoGen generated drivers
/********************************************************************************
	RTI Notification	(a dummy-function for the compiler, no affects)
********************************************************************************/			                           
void rtiNotification(uint32_t notification)
{
	switch(notification)
    {
        case 4 :
        	if(drv.ADC_INT_ENA==0)
        	{
        		ecmpWdQaSendAnswer(drv.ecmpHandle, 0, 0, 0);
        	}
        	else
        	{
        		drv.Process_WDA = 1;
        	}

        break;
    }
    return;
}
/********************************************************************************
	ESM Notification	(a dummy-function for the compiler, no affects)
********************************************************************************/
void esmGroup1Notification(uint32_t channel){return;}
void esmGroup2Notification(uint32_t channel){return;}
void hetNotification(hetBASE_t *het, uint32_t offset){return;}
/* USER CODE END */
