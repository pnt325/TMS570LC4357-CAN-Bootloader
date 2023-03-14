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
// Copyright (c) 2005-2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
#ifndef SYS_MAIN_H_
#define SYS_MAIN_H_

//! \file   ~/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137
//!			/projects/ccs5/project01/src/sys_main.h
//!
//! \brief  Main system header file for the three phase sensored speed SMO project
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes


// **************************************************************************
// the drivers

#include "drivers/gio/src/32b/hercules/tms570ls3137/gio.h"
#include "drivers/adc/src/32b/hercules/tms570ls3137/adc.h"
#include "drivers/rti/src/32b/hercules/tms570ls3137/rti.h"
#include "drivers/het/src/32b/hercules/tms570ls3137/het.h"
#include "drivers/pwm/src/32b/hercules/tms570ls3137/pwm.h"
#include "drivers/qep/src/32b/hercules/tms570ls3137/qep.h"
#include "drivers/pinmux/src/32b/hercules/tms570ls3137/pinmux.h"
#include "sys_mpu.h"


// **************************************************************************
// the modules

#include "solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137/src/ctrl.h"
#include "solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137/src/drv.h"
#include "solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls3137/src/gui.h"
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

// Timing Constants For interrupt and FOC
//#define T			0.0000992				// FOC frequency
//#define T			0.0001
//#define vCNT_SCALE 	2490000

#define T			0.00005
#define vCNT_SCALE 	2490000


// **************************************************************************
// the typedefs


// **************************************************************************
// the function prototypes


#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif // SYS_MAIN_H_ definition
