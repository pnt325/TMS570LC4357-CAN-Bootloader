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
/** @file esm.c 
*   @brief Esm Driver Source File
*   @date 15.December.2011
*   @version 03.00.00
*
*   This file contains:
*   - API Funcions
*   .
*   which are relevant for the Esm driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */

//! \file   ~/drivers/esm/src/32b/hercules/champion/esm.c
//! \brief  Contains the various functions related to the
//!         ESM peripheral
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

/* USER CODE END */

/* Include Files */

#include "esm.h"

/* USER CODE BEGIN (1) */

// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

/* USER CODE END */


/** @fn void esmInit(void)
*   @brief Initializes Esm Driver
*
*   This function initializes the Esm driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void esmInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** - Disable error pin channels */
    esmREG->EPENACLR1 = 0xFFFFFFFFU;
    esmREG->EPENACLR4 = 0xFFFFFFFFU;

    /** - Disable interrupts */
    esmREG->INTENACLR1 = 0xFFFFFFFFU;
    esmREG->INTENACLR4 = 0xFFFFFFFFU;

    /** - Clear error status flags */
    esmREG->ESTATUS1[0U] = 0xFFFFFFFFU;
    esmREG->ESTATUS1[1U] = 0xFFFFFFFFU;
    esmREG->ESTATUS2EMU  = 0xFFFFFFFFU;
    esmREG->ESTATUS1[2U] = 0xFFFFFFFFU;
    esmREG->ESTATUS4[0U] = 0xFFFFFFFFU;
    esmREG->ESTATUS4[1U] = 0xFFFFFFFFU;
    esmREG->ESTATUS5EMU  = 0xFFFFFFFFU;
    esmREG->ESTATUS4[2U] = 0xFFFFFFFFU;

    /** - Setup LPC preload */
    esmREG->LTCPRELOAD = 16384U - 1U;

    /** - Reset error pin */
    if (esmREG->EPSTATUS == 0U)
    {
        esmREG->KEY = 0x00000005U;
    }
    else
    {
        esmREG->KEY = 0x00000000U;
    }

    /** - Clear interrupt level */
    esmREG->INTLVLCLR1 = 0xFFFFFFFFU;
    esmREG->INTLVLCLR4 = 0xFFFFFFFFU;

    /** - Set interrupt level */
    esmREG->INTLVLSET1 = (0U << 31U)
                       | (0U << 30U)
                       | (0U << 29U)
                       | (0U << 28U)
                       | (0U << 27U)
                       | (0U << 26U)
                       | (0U << 25U)
                       | (0U << 24U)
                       | (0U << 23U)
                       | (0U << 22U)
                       | (0U << 21U)
                       | (0U << 20U)
                       | (0U << 19U)
                       | (0U << 18U)
                       | (0U << 17U)
                       | (0U << 16U)
                       | (0U << 15U)
                       | (0U << 14U)
                       | (0U << 13U)
                       | (0U << 12U)
                       | (0U << 11U)
                       | (0U << 10U)
                       | (0U <<  9U)
                       | (0U <<  8U)
                       | (0U <<  7U)
                       | (0U <<  6U)
                       | (0U <<  5U)
                       | (0U <<  4U)
                       | (0U <<  3U)
                       | (0U <<  2U)
                       | (0U <<  1U)
                       | (0U);

    esmREG->INTLVLSET4 = (0U << 31U)
                       | (0U << 30U)
                       | (0U << 29U)
                       | (0U << 28U)
                       | (0U << 27U)
                       | (0U << 26U)
                       | (0U << 25U)
                       | (0U << 24U)
                       | (0U << 23U)
                       | (0U << 22U)
                       | (0U << 21U)
                       | (0U << 20U)
                       | (0U << 19U)
                       | (0U << 18U)
                       | (0U << 17U)
                       | (0U << 16U)
                       | (0U << 15U)
                       | (0U << 14U)
                       | (0U << 13U)
                       | (0U << 12U)
                       | (0U << 11U)
                       | (0U << 10U)
                       | (0U <<  9U)
                       | (0U <<  8U)
                       | (0U <<  7U)
                       | (0U <<  6U)
                       | (0U <<  5U)
                       | (0U <<  4U)
                       | (0U <<  3U)
                       | (0U <<  2U)
                       | (0U <<  1U)
                       | (0U);

    /** - Enable error pin channels */
    esmREG->EPENASET1 = (0U << 31U)
                      | (0U << 30U)
                      | (0U << 29U)
                      | (0U << 28U)
                      | (0U << 27U)
                      | (0U << 26U)
                      | (0U << 25U)
                      | (0U << 24U)
                      | (0U << 23U)
                      | (0U << 22U)
                      | (0U << 21U)
                      | (0U << 20U)
                      | (0U << 19U)
                      | (0U << 18U)
                      | (0U << 17U)
                      | (0U << 16U)
                      | (0U << 15U)
                      | (0U << 14U)
                      | (0U << 13U)
                      | (0U << 12U)
                      | (0U << 11U)
                      | (0U << 10U)
                      | (0U <<  9U)
                      | (0U <<  8U)
                      | (0U <<  7U)
                      | (0U <<  6U)
                      | (0U <<  5U)
                      | (0U <<  4U)
                      | (0U <<  3U)
                      | (0U <<  2U)
                      | (0U <<  1U)
                      | (0U);

    esmREG->EPENASET4 = (0U << 31U)
                      | (0U << 30U)
                      | (0U << 29U)
                      | (0U << 28U)
                      | (0U << 27U)
                      | (0U << 26U)
                      | (0U << 25U)
                      | (0U << 24U)
                      | (0U << 23U)
                      | (0U << 22U)
                      | (0U << 21U)
                      | (0U << 20U)
                      | (0U << 19U)
                      | (0U << 18U)
                      | (0U << 17U)
                      | (0U << 16U)
                      | (0U << 15U)
                      | (0U << 14U)
                      | (0U << 13U)
                      | (0U << 12U)
                      | (0U << 11U)
                      | (0U << 10U)
                      | (0U <<  9U)
                      | (0U <<  8U)
                      | (0U <<  7U)
                      | (0U <<  6U)
                      | (0U <<  5U)
                      | (0U <<  4U)
                      | (0U <<  3U)
                      | (0U <<  2U)
                      | (0U <<  1U)
                      | (0U);

    /** - Enable interrpts */
    esmREG->INTENASET1 = (0U << 31U)
                       | (0U << 30U)
                       | (0U << 29U)
                       | (0U << 28U)
                       | (0U << 27U)
                       | (0U << 26U)
                       | (0U << 25U)
                       | (0U << 24U)
                       | (0U << 23U)
                       | (0U << 22U)
                       | (0U << 21U)
                       | (0U << 20U)
                       | (0U << 19U)
                       | (0U << 18U)
                       | (0U << 17U)
                       | (0U << 16U)
                       | (0U << 15U)
                       | (0U << 14U)
                       | (0U << 13U)
                       | (0U << 12U)
                       | (0U << 11U)
                       | (0U << 10U)
                       | (0U <<  9U)
                       | (0U <<  8U)
                       | (0U <<  7U)
                       | (0U <<  6U)
                       | (0U <<  5U)
                       | (0U <<  4U)
                       | (0U <<  3U)
                       | (0U <<  2U)
                       | (0U <<  1U)
                       | (0U);

    esmREG->INTENASET4 = (0U << 31U)
                       | (0U << 30U)
                       | (0U << 29U)
                       | (0U << 28U)
                       | (0U << 27U)
                       | (0U << 26U)
                       | (0U << 25U)
                       | (0U << 24U)
                       | (0U << 23U)
                       | (0U << 22U)
                       | (0U << 21U)
                       | (0U << 20U)
                       | (0U << 19U)
                       | (0U << 18U)
                       | (0U << 17U)
                       | (0U << 16U)
                       | (0U << 15U)
                       | (0U << 14U)
                       | (0U << 13U)
                       | (0U << 12U)
                       | (0U << 11U)
                       | (0U << 10U)
                       | (0U <<  9U)
                       | (0U <<  8U)
                       | (0U <<  7U)
                       | (0U <<  6U)
                       | (0U <<  5U)
                       | (0U <<  4U)
                       | (0U <<  3U)
                       | (0U <<  2U)
                       | (0U <<  1U)
                       | (0U);

/* USER CODE BEGIN (4) */
/* USER CODE END */
}


/** @fn uint32_t esmError(void)
*   @brief Return Error status
*
*   @return The error status
*
*   Returns the error status.
*/
uint32_t esmError(void)
{
    uint32_t status;

/* USER CODE BEGIN (5) */
/* USER CODE END */

    status = esmREG->EPSTATUS;

/* USER CODE BEGIN (6) */
/* USER CODE END */

    return status;
}


/** @fn void esmEnableError(uint64_t channels)
*   @brief Enable Group 1 Channels Error Signals propagation
*
*   @param[in] channels - Channel mask
*
*   Enable Group 1 Channels Error Signals propagation to the error pin.
*/
void esmEnableError(uint64_t channels)
{
/* USER CODE BEGIN (7) */
/* USER CODE END */

    esmREG->EPENASET4 = (uint32_t)((channels >> 32) & 0xFFFFFFFF);
    esmREG->EPENASET1 = (uint32_t)(channels & 0xFFFFFFFF);

/* USER CODE BEGIN (8) */
/* USER CODE END */
}


/** @fn void esmDisableError(uint64_t channels)
*   @brief Disable Group 1 Channels Error Signals propagation
*
*   @param[in] channels - Channel mask
*
*   Disable Group 1 Channels Error Signals propagation to the error pin.
*/
void esmDisableError(uint64_t channels)
{
/* USER CODE BEGIN (9) */
/* USER CODE END */

    esmREG->EPENACLR4 = (uint32_t)((channels >> 32) & 0xFFFFFFFF);
    esmREG->EPENACLR1 = (uint32_t)(channels & 0xFFFFFFFF);

/* USER CODE BEGIN (10) */
/* USER CODE END */
}


/** @fn void esmTriggerErrorPinReset(void)
*   @brief Trigger error pin reset and switch back to normal operation
*
*   Trigger error pin reset and switch back to normal operation.
*/
void esmTriggerErrorPinReset(void)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    esmREG->KEY = 5U;

/* USER CODE BEGIN (12) */
/* USER CODE END */
}


/** @fn void esmActivateNormalOperation(void)
*   @brief Activate normal operation
*
*   Activates normal operation mode.
*/
void esmActivateNormalOperation(void)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    esmREG->KEY = 0U;

/* USER CODE BEGIN (14) */
/* USER CODE END */
}


/** @fn void esmEnableInterrupt(uint64_t channels)
*   @brief Enable Group 1 Channels Interrupts
*
*   @param[in] channels - Channel mask
*
*   Enable Group 1 Channels Interrupts.
*/
void esmEnableInterrupt(uint64_t channels)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */

    esmREG->INTENASET4 = (uint32_t)((channels >> 32) & 0xFFFFFFFF);
    esmREG->INTENASET1 = (uint32_t)(channels & 0xFFFFFFFF);

/* USER CODE BEGIN (16) */
/* USER CODE END */
}


/** @fn void esmDisableInterrupt(uint64_t channels)
*   @brief Disable Group 1 Channels Interrupts
*
*   @param[in] channels - Channel mask
*
*   Disable Group 1 Channels Interrupts.
*/
void esmDisableInterrupt(uint64_t channels)
{
/* USER CODE BEGIN (17) */
/* USER CODE END */

    esmREG->INTENACLR4 = (uint32_t)((channels >> 32) & 0xFFFFFFFF);
    esmREG->INTENACLR1 = (uint32_t)(channels & 0xFFFFFFFF);

/* USER CODE BEGIN (18) */
/* USER CODE END */
}


/** @fn void esmSetInterruptLevel(uint64_t channels, uint64_t flags)
*   @brief Set Group 1 Channels Interrupt Levels
*
*   @param[in] channels - Channel mask
*   @param[in] flags - Level mask: - 0: Low priority interrupt
*                                  - 1: High priority interrupt
*
*   Set Group 1 Channels Interrupts levels.
*/
void esmSetInterruptLevel(uint64_t channels, uint64_t flags)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */

    esmREG->INTLVLCLR4 = (uint32_t)(((channels & ~flags) >> 32) & 0xFFFFFFF);
    esmREG->INTLVLSET4 = (uint32_t)(((channels & flags) >> 32) & 0xFFFFFFFF);
    esmREG->INTLVLCLR1 = (uint32_t)(channels & ~flags & 0xFFFFFFF);
    esmREG->INTLVLSET1 = (uint32_t)(channels & flags & 0xFFFFFFFF);

/* USER CODE BEGIN (20) */
/* USER CODE END */
}


/** @fn void esmClearStatus(uint32_t group, uint64_t channels)
*   @brief Clear Group error status
*
*   @param[in] group    - Error group
*   @param[in] channels - Channel mask
*
*   Clear Group error status.
*/
void esmClearStatus(uint32_t group, uint64_t channels)
{
/* USER CODE BEGIN (21) */
/* USER CODE END */

    esmREG->ESTATUS4[group] = (uint32_t)((channels >> 32) & 0xFFFFFFFF);
    esmREG->ESTATUS1[group] = (uint32_t)(channels & 0xFFFFFFFF);

/* USER CODE BEGIN (22) */
/* USER CODE END */
}


/** @fn void esmClearStatusBuffer(uint64_t channels)
*   @brief Clear Group 2 error status buffer
*
*   @param[in] channels - Channel mask
*
*   Clear Group 2 error status buffer.
*/
void esmClearStatusBuffer(uint64_t channels)
{
/* USER CODE BEGIN (23) */
/* USER CODE END */

    esmREG->ESTATUS5EMU = (uint32_t)((channels >> 32) & 0xFFFFFFFF);
    esmREG->ESTATUS2EMU = (uint32_t)(channels & 0xFFFFFFFF);

/* USER CODE BEGIN (24) */
/* USER CODE END */
}


/** @fn void esmSetCounterPreloadValue(uint32_t value)
*   @brief Set couter preload value
*
*   @param[in] value - Counter preload value
*
*   Set counter preload value.
*/
void esmSetCounterPreloadValue(uint32_t value)
{
/* USER CODE BEGIN (25) */
/* USER CODE END */

    esmREG->LTCPRELOAD = value & 0xC000U;

/* USER CODE BEGIN (26) */
/* USER CODE END */
}


/** @fn uint64_t esmGetStatus(uint32_t group, uint64_t channel)
*   @brief Return Error status
*
*   @param[in] group   - Error group
*   @param[in] channel - Error Channel
*
*   @return The channel status of selected group
*
*   Returns the channel status of selected group.
*/
uint64_t esmGetStatus(uint32_t group, uint64_t channel)
{
    uint64_t status;

/* USER CODE BEGIN (27) */
/* USER CODE END */

    status = (((uint64_t)esmREG->ESTATUS4[group] << 32) | esmREG->ESTATUS1[group]) & channel;

/* USER CODE BEGIN (28) */
/* USER CODE END */

    return status;
}


/** @fn uint64_t esmGetStatusBuffer(uint64_t channel)
*   @brief Return Group 2 channel x Error status buffer
*
*   @param[in] channel - Error Channel
*
*   @return The channel status
*
*   Returns the group 2 bufferd status of selected channel.
*/
uint64_t esmGetStatusBuffer(uint64_t channel)
{
    uint32_t status;

/* USER CODE BEGIN (29) */
/* USER CODE END */

    status = (((uint64_t)esmREG->ESTATUS5EMU << 32) | esmREG->ESTATUS2EMU) & channel;

/* USER CODE BEGIN (30) */
/* USER CODE END */

    return status;
}

/** @fn void esmHighInterrupt(void)
*   @brief High Level Interrupt for ESM
*/
#pragma INTERRUPT(esmHighInterrupt, FIQ)


void esmHighInterrupt(void)
{
    int vec = esmREG->INTOFFH - 1;

/* USER CODE BEGIN (31) */
/* USER CODE END */

    if (vec >= 96)
    {
        esmREG->ESTATUS4[1U] = 1U << (vec-96);
        esmGroup2Notification(vec-64);
    }
    else if (vec >= 64)
    {
        esmREG->ESTATUS4[0U] = 1U << (vec-64);
        esmGroup1Notification(vec-32);
    }
    else if (vec >= 32)
    {
        esmREG->ESTATUS1[1U] = 1U << (vec-32);
        esmGroup2Notification(vec-32);
    }
    else if (vec >= 0)
    {
        esmREG->ESTATUS1[0U] = 1 << vec;
        esmGroup1Notification(vec);
    }
    else
    {
        esmREG->ESTATUS4[0U] = 0xFFFFFFFFU;
        esmREG->ESTATUS4[1U] = 0xFFFFFFFFU;
        esmREG->ESTATUS1[0U] = 0xFFFFFFFFU;
        esmREG->ESTATUS1[1U] = 0xFFFFFFFFU;
    }

/* USER CODE BEGIN (32) */
/* USER CODE END */
}


/** @fn void esmLowInterrupt(void)
*   @brief Low Level Interrupt for ESM
*/
#pragma INTERRUPT(esmLowInterrupt, IRQ)

void esmLowInterrupt(void)
{

    /* Note : Group 1 Error         */
    /* 1  to 32 -> channel 0  to 31 */
    /* 65 to 96 -> channel 32 to 63 */

    int vec = esmREG->INTOFFL - 1;

/* USER CODE BEGIN (33) */
/* USER CODE END */


    if (vec >= 64)     /* channel 32 to 63 */
    {
        esmREG->ESTATUS4[0U] = 1U << (vec-64);
        esmGroup1Notification(vec-32);
    }
    else if (vec >= 0) /* channel 0 to 31  */
    {
        esmREG->ESTATUS1[0U] = 1U << vec;
        esmGroup1Notification(vec);
    }
    else
    {
        esmREG->ESTATUS4[0U] = 0xFFFFFFFFU;
        esmREG->ESTATUS1[0U] = 0xFFFFFFFFU;
    }

/* USER CODE BEGIN (34) */
/* USER CODE END */
}

/* USER CODE BEGIN (35) */

// end of file

/* USER CODE END */
