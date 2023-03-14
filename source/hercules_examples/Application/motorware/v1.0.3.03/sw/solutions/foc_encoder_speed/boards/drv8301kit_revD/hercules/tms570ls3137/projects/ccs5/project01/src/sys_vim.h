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
/** @file sys_vim.h
*   @brief Vectored Interrupt Module Header File
*   @date 15.December.2011
*   @version 03.00.00
*   
*   This file contains:
*   - VIM Type Definitions
*   - VIM General Definitions
*   .
*   which are relevant for Vectored Interrupt Controller.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef __SYS_VIM_H__
#define __SYS_VIM_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */

//! \file   ~/boards/drv8301kit_revD/hercules/tms570ls3137/
//!         sensored_speed_smo/projects/ccs5/project01/src/sys_vim.h
//! \brief  Contains the public interface to the
//!         types definitions
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the includes

//!
//! \defgroup SYS

//!
//! \ingroup SYS
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the function prototypes

/* USER CODE END */


/* VIM Type Definitions */

/** @typedef t_isrFuncPTR
*   @brief ISR Function Pointer Type Definition
*
*   This type is used to access the ISR handler.
*/
typedef void (*t_isrFuncPTR)();

/* USER CODE BEGIN (1) */
/* USER CODE END */


/* VIM General Configuration */

#define VIM_CHANNELS 94U

/* USER CODE BEGIN (2) */
/* USER CODE END */

/* Interrupt Handlers */

extern void phantomInterrupt(void);
extern void esmHighInterrupt(void);
extern void phantomInterrupt(void);
extern void gioHighLevelInterrupt(void);
extern void adc1Group1Interrupt(void);
extern void adc1Group2Interrupt(void);


/* Vim Register Frame Definition */
/** @struct vimBase
*   @brief Vim Register Frame Definition
*
*   This type is used to access the Vim Registers.
*/
/** @typedef vimBASE_t
*   @brief VIM Register Frame Type Definition
*
*   This type is used to access the VIM Registers.
*/
typedef volatile struct vimBase
{
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t      IRQIVEC :  8U;    /* 0x0000        */
    uint32_t              : 24U;    /* 0x0000        */
    uint32_t      FIQIVEC :  8U;    /* 0x0004        */
    uint32_t              : 24U;    /* 0x0004        */
#else
    uint32_t              : 24U;    /* 0x0000        */
    uint32_t      IRQIVEC :  8U;    /* 0x0000        */
    uint32_t              : 24U;    /* 0x0004        */
    uint32_t      FIQIVEC :  8U;    /* 0x0004        */
#endif
    uint32_t      : 32U;            /* 0x0008        */
    uint32_t      : 32U;            /* 0x000C        */
    uint32_t      FIRQPR0;          /* 0x0010        */
    uint32_t      FIRQPR1;          /* 0x0014        */
    uint32_t      FIRQPR2;          /* 0x0018        */
    uint32_t      FIRQPR3;          /* 0x001C        */
    uint32_t      INTREQ0;          /* 0x0020        */
    uint32_t      INTREQ1;          /* 0x0024        */
    uint32_t      INTREQ2;          /* 0x0028        */
    uint32_t      INTREQ3;          /* 0x002C        */
    uint32_t      REQMASKSET0;      /* 0x0030        */
    uint32_t      REQMASKSET1;      /* 0x0034        */
    uint32_t      REQMASKSET2;      /* 0x0038        */
    uint32_t      REQMASKSET3;      /* 0x003C        */
    uint32_t      REQMASKCLR0;      /* 0x0040        */
    uint32_t      REQMASKCLR1;      /* 0x0044        */
    uint32_t      REQMASKCLR2;      /* 0x0048        */
    uint32_t      REQMASKCLR3;      /* 0x004C        */
    uint32_t      WAKEMASKSET0;     /* 0x0050        */
    uint32_t      WAKEMASKSET1;     /* 0x0054        */
    uint32_t      WAKEMASKSET2;     /* 0x0058        */
    uint32_t      WAKEMASKSET3;     /* 0x005C        */
    uint32_t      WAKEMASKCLR0;     /* 0x0060        */
    uint32_t      WAKEMASKCLR1;     /* 0x0064        */
    uint32_t      WAKEMASKCLR2;     /* 0x0068        */
    uint32_t      WAKEMASKCLR3;     /* 0x006C        */
    uint32_t      IRQVECREG;        /* 0x0070        */
    uint32_t      FIQVECREQ;        /* 0x0074        */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t      CAPEVTSRC0 :  7U; /* 0x0078        */
    uint32_t                 :  9U; /* 0x0078        */
    uint32_t      CAPEVTSRC1 :  7U; /* 0x0078        */
    uint32_t                 :  9U; /* 0x0078        */
#else
    uint32_t                 :  9U; /* 0x0078        */
    uint32_t      CAPEVTSRC1 :  7U; /* 0x0078        */
    uint32_t                 :  9U; /* 0x0078        */
    uint32_t      CAPEVTSRC0 :  7U; /* 0x0078        */
#endif
    uint32_t      : 32U;            /* 0x007C        */
    uint8_t CHANMAP[64U];           /* 0x0080-0x017C */
} vimBASE_t;

#define vimREG ((vimBASE_t *)0xFFFFFE00U)

/* USER CODE BEGIN (3) */

#ifdef __cplusplus
}
#endif /* extern "C" */

//@}  // ingroup

/* USER CODE END */


#endif
