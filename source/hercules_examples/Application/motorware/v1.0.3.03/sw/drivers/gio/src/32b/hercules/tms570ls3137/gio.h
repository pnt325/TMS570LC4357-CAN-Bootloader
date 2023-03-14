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
/** @file gio.h
*   @brief GIO Driver Definition File
*   @date 15.December.2011
*   @version 03.00.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#include "sys_common.h"

#ifndef __GIO_H__
#define __GIO_H__

/* USER CODE BEGIN (0) */

//! \file   ~/drivers/gio/src/32b/hercules/tms570ls3137/gio.h
//! \brief  Contains public interface to various functions related
//!         to the general input/output (GIO) object
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

// drivers


// modules


//!
//! \defgroup GIO

//!
//! \ingroup GIO
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

/* USER CODE END */


/** @struct gioBase
*   @brief GIO Base Register Definition
*
*   This structure is used to access the GIO module egisters.
*/
/** @typedef gioBASE_t
*   @brief GIO Register Frame Type Definition
*
*   This type is used to access the GIO Registers.
*/
typedef volatile struct gioBase
{
    uint32_t GCR0;      /**< 0x0000: Global Control Register */
    uint32_t PWDN;      /**< 0x0004: Power Down Register */
    uint32_t INTDET;    /**< 0x0008: Interrupt Detect Regsiter*/
    uint32_t POL;       /**< 0x000C: Interrupt Polarity Register */
    uint32_t INTENASET; /**< 0x0010: Interrupt Enable Set Register */
    uint32_t INTENACLR; /**< 0x0014: Interrupt Enable Clear Register */
    uint32_t LVLSET;    /**< 0x0018: Interrupt Priority Set Register */
    uint32_t LVLCLR;    /**< 0x001C: Interrupt Priority Clear Register */
    uint32_t FLG;       /**< 0x0020: Interrupt Flag Register */
    uint32_t OFFSET0;   /**< 0x0024: Interrupt Offset A Register */
    uint32_t OFFSET1;   /**< 0x0028: Interrupt Offset B Register */
} gioBASE_t;


/** @struct gioPort
*   @brief GIO Port Register Definition
*/
/** @typedef gioPORT_t
*   @brief GIO Port Register Type Definition
*
*   This type is used to access the GIO Port Registers.
*/
typedef volatile struct gioPort
{
    uint32_t DIR;    /**< 0x0000: Data Direction Register */
    uint32_t DIN;    /**< 0x0004: Data Input Register */
    uint32_t DOUT;   /**< 0x0008: Data Output Register */
    uint32_t DSET;   /**< 0x000C: Data Output Set Register */
    uint32_t DCLR;   /**< 0x0010: Data Output Clear Register */
    uint32_t PDR;    /**< 0x0014: Open Drain Regsiter */
    uint32_t PULDIS; /**< 0x0018: Pullup Disable Register */
    uint32_t PSL;    /**< 0x001C: Pull Up/Down Selection Register */
} gioPORT_t;


/** @def gioREG
*   @brief GIO Register Frame Pointer
*
*   This pointer is used by the GIO driver to access the gio module registers.
*/
#define gioREG   ((gioBASE_t *)0xFFF7BC00U)

/** @def gioPORTA
*   @brief GIO Port (A) Register Pointer
*
*   Pointer used by the GIO driver to access PORTA
*/
#define gioPORTA ((gioPORT_t *)0xFFF7BC34U)

/** @def gioPORTB
*   @brief GIO Port (B) Register Pointer
*
*   Pointer used by the GIO driver to access PORTB
*/
#define gioPORTB ((gioPORT_t *)0xFFF7BC54U)


/* GIO Interface Functions */
void gioInit(void);
void gioSetDirection(gioPORT_t *port, uint32_t dir);
void gioSetBit(gioPORT_t *port, uint32_t bit, uint32_t value);
void gioSetPort(gioPORT_t *port, uint32_t value);
uint32_t gioGetBit(gioPORT_t *port, uint32_t bit);
uint32_t gioGetPort(gioPORT_t *port);
void gioToggleBit(gioPORT_t *port, uint32_t bit);
void gioEnableNotification(uint32_t bit);
void gioDisableNotification(uint32_t bit);
void gioNotification(int bit);

/* USER CODE BEGIN (1) */

#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

/* USER CODE END */

#endif
