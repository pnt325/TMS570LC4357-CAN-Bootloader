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
/** @file system.c 
*   @brief System Driver Source File
*   @date 15.December.2011
*   @version 03.00.00
*
*   This file contains:
*   - API Funcions
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */

//! \file   ~/boards/drv8301kit_revD/hercules/tms570ls3137/
//!         sensored_speed_smo/projects/ccs5/project01/src/system.c
//! \brief  Contains the public interface to the
//!         types definitions
//!
//! (C) Copyright 2012, Texas Instruments, Inc.


// **************************************************************************
// the function prototypes

/* USER CODE END */


/* Include Files */

#include "system.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


extern void _coreDisableFlashEcc_();
extern void _coreEnableFlashEcc_();


/** @fn void systemInit(void)
*   @brief Initializes System Driver
*
*   This function initializes the System driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void systemInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** @b Initialize @b Flash @b Wrapper: */

    /** - Setup flash read mode, address wait states and data wait states */
    flashWREG->FRDCNTL =  0x00000000U 
                       | (3U << 8U) 
                       | (1U << 4U) 
                       |  1U;

    /** - Setup flash bank power modes */
    flashWREG->FBFALLBACK = 0x00000000
                          | (SYS_ACTIVE << 14U) 
                          | (SYS_SLEEP << 12U) 
                          | (SYS_SLEEP << 10U) 
                          | (SYS_SLEEP << 8U) 
                          | (SYS_SLEEP << 6U) 
                          | (SYS_SLEEP << 4U) 
                          | (SYS_ACTIVE << 2U) 
                          |  SYS_ACTIVE;

    /** @b Initialize @b Lpo: */
    /** Load TRIM values from OTP if present else load user defined values */
    if(LPO_TRIM_VALUE != 0xFFFF)
    {
    
        systemREG1->LPOMONCTL  = (1U << 24U)
                                | LPO_TRIM_VALUE;
    }
    else
    {

    	systemREG1->LPOMONCTL 	= (1U << 24U)
                                 | (16U << 8U)
                                 | 8U;
    }

    /** @b Initialize @b Pll2: */

    /**   - Setup pll2 control register :
    *     - Setup Pll output clock divider
    *     - Setup reference clock divider 
    *     - Setup internal Pll output divider
    *     - Setup Pll multiplier          
    */

    systemREG2->PLLCTL3 = ((2U - 1U) << 29U)
                        | ((1U - 1U)<< 24U) 
                        | ((6U - 1U)<< 16U) 
                        | ((120U - 1U) << 8U);


    /** @b Initialize @b Pll1: */

    /**   - Setup pll control register 1:
    *     - Setup reset on oscillator slip 
    *     - Setup bypass on pll slip
    *     - Setup Pll output clock divider
    *     - Setup reset on oscillator fail
    *     - Setup reference clock divider 
    *     - Setup Pll multiplier          
    */
    systemREG1->PLLCTL1 =  0x00000000U 
                        |  0x20000000U 
                        | ((1U - 1U)<< 24U) 
                        |  0x00000000U 
                        | ((6U - 1U)<< 16U) 
                        | ((120U - 1U)<< 8U);

    /**   - Setup pll control register 2
    *     - Enable/Disable frequency modulation
    *     - Setup spreading rate
    *     - Setup bandwidth adjustment
    *     - Setup internal Pll output divider
    *     - Setup spreading amount
    */
    systemREG1->PLLCTL2 =  0x00000000U
                        | (255U << 22U)
                        | (7U << 12U)
                        | ((2U - 1U)<< 9U)
                        |  61U;


    /** @b Initialize @b Clock @b Tree: */

    /** - Start clock source lock */
    systemREG1->CSDIS = 0x00000000U	
                      | 0x00000000U 
                      | 0x00000008U 
                      | 0x00000080U 
                      | 0x00000000U 
                      | 0x00000000U 
                      | 0x00000000U;

    /** - Wait for until clocks are locked */
    while ((systemREG1->CSVSTAT & ((systemREG1->CSDIS ^ 0xFF) & 0xFF)) != ((systemREG1->CSDIS ^ 0xFF) & 0xFF))
{
}
    /** - Setup GCLK, HCLK and VCLK clock source for normal operation, power down mode and after wakeup */
    systemREG1->GHVSRC = (SYS_PLL1 << 24U) 
                       | (SYS_PLL1 << 16U) 
                       |  SYS_PLL1;

    /** - Power-up all peripharals */
    pcrREG->PSPWRDWNCLR0 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR1 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR2 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR3 = 0xFFFFFFFFU;

    /** - Setup synchronous peripheral clock dividers for VCLK1, VCLK2, VCLK3, VCLK4 */
    systemREG1->VCLKR   = 1U;
    systemREG1->VCLK2R  = 1U;
    systemREG2->VCLK3R  = 1U;

    /** - Setup RTICLK1 and RTICLK2 clocks */
    systemREG1->RCLKSRC = (1U << 24U)
                        | (SYS_VCLK << 16U) 
                        | (1U << 8U)  
                        |  SYS_VCLK;

    /** - Setup asynchronous peripheral clock sources for AVCLK1 and AVCLK2 */
    systemREG1->VCLKASRC = (SYS_VCLK << 8U)
                          |  SYS_VCLK;

    systemREG2->VCLKACON1 = (1U << 24) 
                           | 1 << 20U 
                           | (SYS_VCLK << 16)
                           | (1U << 8)
                           | 1 << 4U 
                           | SYS_VCLK;

    /** - Enable Peripherals */
    systemREG1->PENA = 1U;

    /** - set ECLK pins functional mode */
    systemREG1->SYSPC1 = 0U;

    /** - set ECLK pins default output value */
    systemREG1->SYSPC4 = 0U;

    /** - set ECLK pins output direction */
    systemREG1->SYSPC2 = 1U;

    /** - set ECLK pins open drain enable */
    systemREG1->SYSPC7 = 0U;

    /** - set ECLK pins pullup/pulldown enable */
    systemREG1->SYSPC8 = 0U;

    /** - set ECLK pins pullup/pulldown select */
    systemREG1->SYSPC9 = 1U;

    /** - Setup ECLK */
    systemREG1->ECPCNTL = (0U << 24U)
                        | (0U << 23U)
                        | ((8U - 1U) & 0xFFFFU);

    /** @note: HCLK >= VCLK2 >= VCLK_sys */


/* USER CODE BEGIN (4) */
/* USER CODE END */
}

void systemPowerDown(uint32_t mode)
{
    /* Disable clock sources */
    systemREG1->CSDISSET = mode & 0x000000FFU;

    /* Disable clock domains */
    systemREG1->CDDIS = (mode >> 8U) & 0x00000FFFU;

    /* Idle CPU */
    asm(" wfi");
}


/* USER CODE BEGIN (5) */

// end of file

/* USER CODE END */
