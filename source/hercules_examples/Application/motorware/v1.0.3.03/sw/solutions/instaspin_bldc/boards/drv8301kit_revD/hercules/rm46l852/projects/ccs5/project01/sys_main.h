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

//! \file   ~/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src/sys_main.h
//!
//! \brief  Main system header file for the three phase sensored speed SMO project
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes


// **************************************************************************
// the drivers

#include "drivers/gio/src/32b/hercules/champion/gio.h"
#include "drivers/adc/adc_bldc/src/32b/hercules/champion/adc.h"
#include "drivers/rti/src/32b/hercules/champion/rti.h"
#include "drivers/het/pwm_bldc/src/32b/hercules/champion/het.h"
#include "drivers/pwm/pwm_bldc/src/32b/hercules/champion/epwm.h"
#include "drivers/pinmux/src/32b/hercules/champion/pinmux.h"
#include "sys_mpu.h"


// **************************************************************************
// the modules

#include "solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/src/drv.h"
#include "solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/src/gui.h"
#include "modules/ecmp/src/float32/champion/ecmp.h"
#include "modules/dlog/src/float32/hercules/DLOG.h"


// **************************************************************************
// the defines


// **************************************************************************
// the typedefs


// **************************************************************************
// the function prototypes


#endif // SYS_MAIN_H_ definition
