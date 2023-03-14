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
//! \file   ~/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137/src/ctrl.c
//! \brief  Contains the various functions related to the CTRL object
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

#include "solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137/src/ctrl.h"

// **************************************************************************
// the globals


//! \brief     Initializes the Control (CTRL) object
//! \param[in] pMemory     A pointer to the memory for the ctrl object
//! \param[in] numBytes    The number of bytes allocated for the ctrl object, bytes
//! \param[in] period	   FOC, period
//! \return The Control (CTRL) object handle
CTRL_Handle CTRL_init( void *pMemory, const size_t numBytes, const float32_t period)
{
	CTRL_Handle ctrlHandle;

	if(numBytes < sizeof(CTRL_Obj))
	return((CTRL_Handle)NULL);

	// assign the handle
	ctrlHandle = (CTRL_Handle)pMemory;

	CTRL_Obj *ctrl = (CTRL_Obj *) ctrlHandle;

	// init the CLARKE module
	ctrl->clarkeHandle = CLARKE_init( (void*) &(ctrl->clarke), sizeof(ctrl->clarke) );

	// init the park module
	ctrl->parkHandle = PARK_init( (void*) &ctrl->park, sizeof(ctrl->park) );

	// init the Id PID module
	ctrl->pidHandle_Id = PID_init( (void*) &ctrl->pid_Id, sizeof(ctrl->pid_Id) );

	// init the Iq PID module
	ctrl->pidHandle_Iq = PID_init( (void*) &ctrl->pid_Iq, sizeof(ctrl->pid_Iq) );

	// init the speed ramp controller module
	ctrl->rmpCntlHandle = RMPCNTL_init((void*) &ctrl->rmpCntl, sizeof(ctrl->rmpCntl) );

	// init the speed PID module
	ctrl->pidHandle_spd = PID_init( (void*) &ctrl->pid_spd, sizeof(ctrl->pid_spd) );

	// init the iPark module
	ctrl->iparkHandle = IPARK_init( (void*) &ctrl->ipark, sizeof(ctrl->ipark) );

	// init the SVGEN module
	ctrl->svgenHandle = SVGEN_init( (void*) &ctrl->svgen, sizeof(ctrl->svgen) );

	// Setup control module
	CTRL_setup(ctrlHandle, period);

	return(ctrlHandle);
}


//! \brief     Setup the Control module to default values
//! \param[in] handle  The controller (CTRL) handle
//! \param[in] period	   FOC, period
void CTRL_setup( CTRL_Handle handle, const float32_t period)
{
	CTRL_Obj *ctrl = (CTRL_Obj *) handle;

	// TODO file better value to default set the period to, 0.0 won't work because then we'll divide by 0.0
	CTRL_setPeriod(handle, period );

	// setup the CLARKE module
	CLARKE_setNumSensors(ctrl->clarkeHandle, 2 );
	CLARKE_setScaleFactors(ctrl->clarkeHandle, (1.0), (1.0) );

	// setup the PARK module
	PARK_setup(ctrl->parkHandle, (0.0) );

	// setup the Id PID module
	CTRL_setPID_Id_param(handle, (0.08982), (1800), (0.0) );
	PID_setMinMax( ctrl->pidHandle_Id, -0.30, 0.30);

	// setup the Iq PID module
	CTRL_setPID_Iq_param(handle, (0.08982), (1800), (0.0) );
	PID_setMinMax(ctrl->pidHandle_Iq, -0.95, 0.95);

	// setup the speed ramp controller module
	RMPCNTL_Setup(ctrl->rmpCntlHandle);

	// setup the speed PID module
	CTRL_setSpdPrescalarMax( handle, 10);
	CTRL_setPID_spd_param(handle, (2.23), (0.1), (0.0) );
	//Rated continuous current of motor
	PID_setMinMax( ctrl->pidHandle_spd, -0.71, 0.71);

	// setup the IPARK module
	IPARK_setup( ctrl->iparkHandle, (0.0) );
}


