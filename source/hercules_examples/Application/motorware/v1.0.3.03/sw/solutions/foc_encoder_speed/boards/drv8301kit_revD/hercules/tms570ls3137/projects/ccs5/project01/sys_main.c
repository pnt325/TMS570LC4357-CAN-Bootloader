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

//! \file   ~/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137
//!			/projects/ccs5/project01/src/sys_main.c
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
GRAPH_Handle graphHandle = &graph;	// Handle for graphing object
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
    (*(volatile unsigned int *)(0xFFFFEB84))=0x01000101;//GIOB2 Errata
    (*(volatile unsigned int *)(0xFFFFEB88))=0x00000002;//ADC Alternate Trigger
    (*(volatile unsigned int *)(0xFFFFEA38))=0x0;
    (*(volatile unsigned int *)(0xFFFFEA3C))=0x0;

	// initialize the driver
	drvHandle = DRV_init(&drv,sizeof(drv), T, vCNT_SCALE, ENCODER_COMMUTATION_MODE);

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
	guiHandle = GUI_init(&gGUIObj,sizeof(gGUIObj));
	GUI_setup(guiHandle, drvHandle, graphHandle);

	// Send SPI commands to DRV8301 from HET
	hetRAM1->Instruction[2U].Data = 0x200;
	if((hetREG1->GCR & 1)==0) hetREG1->GCR    = 0x00030001U;	// Start HET

	// Endless loop to wait for start command from either GUI or button
	while(DRV_get_Enable(drvHandle) != 1){
		GUI_run((GUI_Handle)&gGUIObj, drvHandle, graphHandle);
	}

	// Switch HET to PWM mode
	hetRAM1->Instruction[0U].Data = 1;
	// Initialize the PWM base period
 	hetRAM1->Instruction[26U].Control = T*vCNT_SCALE;
 	// Initialize the ADC trigger point
	hetRAM1->Instruction[35U].Data = ((T*vCNT_SCALE+1)/2)*128;

	// Start the PWMs and Interrupt
	DRV_FOC_start(drvHandle);

	// Enable the peripheral interrupt notifications
	gioEnableNotification(0);
	gioEnableNotification(1);
	adcEnableNotification(adcREG1, adcGROUP1);	
	adcEnableNotification(adcREG1, adcGROUP2);

	// Drop into main while loop
	while(1)
	{
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
	DRV_run(drvHandle);

	//Log data
	switch (GraphInput) {
	case 1:
		DlogCh1 = drv.currentSpd;	 		// Encoder based speed feedback
		DlogCh2 = drv.currentAB.value[0];	// Motor Phase A current
		DlogCh3 = drv.elecPos2.ElecTheta;	// SMO electrical angle
		DlogCh4 = drv.elecPos1.ElecTheta;	// Encoder electrical angle
		break;

	case 2:
		DlogCh1 = drv.adcData.iTotal*RW_CURRENT_GAIN*TORQUE_NM_PER_A;	// Motor Torque output
		DlogCh2 = drv.adcData.iTotal*RW_CURRENT_GAIN;					// Total motor current
		DlogCh3 = drv.adcData.dcBusV*RW_DCBUS_GAIN;			// DC bus measurement
		DlogCh4 = drv.gPwmData.Tabc.value[0];				// PWM1 signal
		break;
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
void rtiNotification(uint32_t notification){return;}
/********************************************************************************
	ESM Notification	(a dummy-function for the compiler, no affects)
********************************************************************************/
void esmGroup1Notification(uint32_t channel){return;}
void esmGroup2Notification(uint32_t channel){return;}
void hetNotification(hetBASE_t *het, uint32_t offset){return;}
/* USER CODE END */
