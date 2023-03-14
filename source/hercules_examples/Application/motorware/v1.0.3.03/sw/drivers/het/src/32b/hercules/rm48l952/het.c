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
/** @file het.c 
*   @brief HET Driver Implementation File
*   @date 15.Feb.2012
*   @version 03.00.01
*
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#include "het.h"
//#include "std_nhet.h"
#include "8301.h"

/* USER CODE BEGIN (0) */

//! \file   ~/drivers/het/src/32b/hercules/rm48l952/het.c
//! \brief  Contains the various functions related to the
//!         high efficiency timer (HET) peripheral
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Global variables                                                           */

static const uint32_t s_het1pwmPolarity[] =
{
    3U,
    3U,
    3U,
    3U,
    3U,
    3U,
    3U,
    3U,
};




/** @fn void hetInit(void)
*   @brief Initializes the het Driver
*
*   This function initializes the het 1 module.
*/
void hetInit(void)
{
    /** @b intalise @b HET */

    /** - Set HET pins default output value */
    hetREG1->DOUT = (0U << 31U)
                 | (1U << 30U)
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
                 | (1U << 19U)
                 | (0U << 18U) 
                 | (1U << 17U)
                 | (0U << 16U) 
                 | (0U << 15U) 
                 | (0U << 14U) 
                 | (0U << 13U) 
                 | (0U << 12U) 
                 | (0U << 11U) 
                 | (0U << 10U) 
                 | (0U << 9U)
                 | (0U << 8U)
                 | (0U << 7U)
                 | (0U << 6U)
                 | (0U << 5U)
                 | (0U << 4U)
                 | (0U << 3U)
                 | (0U << 2U)
                 | (0U << 1U)
                 | (0U);

    /** - Set HET pins direction */
    hetREG1->DIR = 0x00000000U
                | 0x40000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00100000U
                | 0x00080000U
                | 0x00000000U
                | 0x00020000U
                | 0x00010000U
                | 0x00008000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000400U
                | 0x00000000U
                | 0x00000100U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000010U
                | 0x00000000U
                | 0x00000004U
                | 0x00000000U
                | 0x00000001U;

    /** - Set HET pins open drain enable */
    hetREG1->PDR = 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U;

    /** - Set HET pins pullup/down enable */
    hetREG1->PULDIS = 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U 
                   | 0x00000000U
                   | 0x00000000U
                   | 0x00000000U
                   | 0x00000000U
                   | 0x00000000U
                   | 0x00000000U
                   | 0x00000000U
                   | 0x00000000U
                   | 0x00000000U
                   | 0x00000000U;

     /** - Set HET pins pullup/down select */
    hetREG1->PSL = 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U 
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U;

    /** - Set HET pins high resolution share */
    hetREG1->HRSH = 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U
                 | 0x00000000U
                 | 0x00000000U
                 | 0x00000000U
                 | 0x00000000U;

    /** - Set HET pins AND share */
    hetREG1->AND = 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U
                 | 0x00000000U
                 | 0x00000000U
                 | 0x00000000U
                 | 0x00000000U;				 

    /** - Set HET pins XOR share */
    hetREG1->XOR = 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U 
                 | 0x00000000U
                 | 0x00000000U
                 | 0x00000000U
                 | 0x00000000U
                 | 0x00000000U;
				 
/* USER CODE BEGIN (1) */
/* USER CODE END */

    /** - Setup prescaler values
	*     - Loop resolution prescaler
	*     - High resolution prescaler
	*/
    hetREG1->PFR = (5U << 8U)
                | (0U);
 	
	/** - Fill HET RAM with opcodes and Data */
	/** - "x" in "HET_INITx_PST" denote the HET module Instance   
    *      Valid range of x - 0 to 9
    *      For HET1 module x = 0	
    *      Refer HET assembler User guide for more Info
	*/
	memcpy((void*)hetRAM1, (void*)HET_INIT0_PST, sizeof(HET_INIT0_PST));

    /** - Setup interrupt priority level */
    hetREG1->PRY = 0xFFFFFFFF;
	
    /** - Enable interrupts */
    hetREG1->INTENAC = 0xFFFFFFFFU;
    hetREG1->INTENAS = 0x00000000U 
                     | 0x00000000U 
				     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U  
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U 
                     | 0x00000000U
                     | 0x00000000U
                     | 0x00000000U
                     | 0x00000000U
                     | 0x00000000U
                     | 0x00000000U
                     | 0x00000000U
                     | 0x00000000U
                     | 0x00000000U
                     | 0x00000000U;

   
   /** - Setup control register 
    *     - Enable output buffers
    *     - Ignore software breakpoints
    *     - Master mode
    *     - Enable HET
    */
    hetREG1->GCR = 0x01030000U;
    /**   @note This function has to be called before the driver can be used.\n
    *           This function has to be executed in priviledged mode.\n
    */



}

/** @fn void pwmStart( hetRAMBASE_t * hetRAM, uint32_t pwm)
*   @brief Start pwm signal
*   @param[in] hetRAM Pointer to HET RAM:
*              - hetRAM1: HET1 RAM pointer
*              - hetRAM2: HET2 RAM pointer
*   @param[in] pwm Pwm signal:
*              - pwm0: Pwm 0
*              - pwm1: Pwm 1
*              - pwm2: Pwm 2
*              - pwm3: Pwm 3
*              - pwm4: Pwm 4
*              - pwm5: Pwm 5
*              - pwm6: Pwm 6
*              - pwm7: Pwm 7
*
*   Start the given pwm signal
*/

void pwmStart( hetRAMBASE_t * hetRAM, uint32_t pwm)
{
 
   hetRAM->Instruction[(pwm << 1U) + 41U].Control  |= 0x00400000U;
}


/** @fn void pwmStop( hetRAMBASE_t * hetRAM, uint32_t pwm)
*   @brief Stop pwm signal
*   @param[in] hetRAM Pointer to HET RAM:
*              - hetRAM1: HET1 RAM pointer
*              - hetRAM2: HET2 RAM pointer
*   @param[in] pwm Pwm signal:
*              - pwm0: Pwm 0
*              - pwm1: Pwm 1
*              - pwm2: Pwm 2
*              - pwm3: Pwm 3
*              - pwm4: Pwm 4
*              - pwm5: Pwm 5
*              - pwm6: Pwm 6
*              - pwm7: Pwm 7
*
*   Stop the given pwm signal
*/

void pwmStop( hetRAMBASE_t * hetRAM, uint32_t pwm)
{
    hetRAM->Instruction[(pwm << 1U) + 41U].Control  &= ~0x00400000U;
}


/** @fn void pwmSetDuty(hetRAMBASE_t * hetRAM, uint32_t pwm, uint32_t duty)
*   @brief Set duty cycle
*   @param[in] hetRAM Pointer to HET RAM:
*              - hetRAM1: HET1 RAM pointer
*              - hetRAM2: HET2 RAM pointer
*   @param[in] pwm Pwm signal:
*              - pwm0: Pwm 0
*              - pwm1: Pwm 1
*              - pwm2: Pwm 2
*              - pwm3: Pwm 3
*              - pwm4: Pwm 4
*              - pwm5: Pwm 5
*              - pwm6: Pwm 6
*              - pwm7: Pwm 7
*   @param[in] duty duty cycle in %.
*
*   Sets a new duty cycle on the given pwm signal
*/

void pwmSetDuty(hetRAMBASE_t * hetRAM, uint32_t pwm, uint32_t duty)
{
    uint32_t action;
    uint32_t pwmPolarity;
    double   period = hetRAM->Instruction[(pwm << 1U) + 42U].Data + 128U;
    if(hetRAM == hetRAM1)
    {
        pwmPolarity = s_het1pwmPolarity[pwm];
    }
    else
    {
    }
    if (duty == 0U)
    {
        action = (pwmPolarity == 3U) ? 0U : 2U;
    }
    else if (duty >= 100U)
    {
        action = (pwmPolarity == 3U) ? 2U : 0U;
    }
    else
    {
        action = pwmPolarity;
    }
        
    hetRAM->Instruction[(pwm << 1U) + 41U].Control = (hetRAM->Instruction[(pwm << 1U) + 41U].Control & ~0x18U) | (action << 3U);
    hetRAM->Instruction[(pwm << 1U) + 41U].Data = (uint32_t)(period * duty / 100.0) + 128U;
}


/** @fn void pwmSetSignal(hetRAMBASE_t * hetRAM, uint32_t pwm, hetSIGNAL_t signal)
*   @brief Set period
*   @param[in] hetRAM Pointer to HET RAM:
*              - hetRAM1: HET1 RAM pointer
*              - hetRAM2: HET2 RAM pointer
*   @param[in] pwm Pwm signal:
*              - pwm0: Pwm 0
*              - pwm1: Pwm 1
*              - pwm2: Pwm 2
*              - pwm3: Pwm 3
*              - pwm4: Pwm 4
*              - pwm5: Pwm 5
*              - pwm6: Pwm 6
*              - pwm7: Pwm 7
*   @param[in] signal signal 
               - duty cycle in %.
*              - period period in us.
*
*   Sets a new pwm signal
*/

void pwmSetSignal(hetRAMBASE_t * hetRAM, uint32_t pwm, hetSIGNAL_t signal)
{
    uint32_t action;
    uint32_t period;
    uint32_t pwmPolarity;
    
    if(hetRAM == hetRAM1)
    {
	    period = (uint32_t)(signal.period * 1000.0 / 1600.000) << 7U;
        pwmPolarity = s_het1pwmPolarity[pwm];
    }
    else
    {
    }
    if (signal.duty == 0U)
    {
        action = (pwmPolarity == 3U) ? 0U : 2U;
    }
    else if (signal.duty >= 100U)
    {
        action = (pwmPolarity == 3U) ? 2U : 0U;
    }
    else
    {
        action = pwmPolarity;
    }
        
    hetRAM->Instruction[(pwm << 1U) + 41U].Control = (hetRAM->Instruction[(pwm << 1U) + 41U].Control & ~0x18U) | (action << 3U);
    hetRAM->Instruction[(pwm << 1U) + 41U].Data = (uint32_t)(period * signal.duty / 100.0) + 128U;
    hetRAM->Instruction[(pwm << 1U) + 42U].Data = period - 128U;
}


/** @fn hetSIGNAL_t pwmGetSignal(hetRAMBASE_t * hetRAM, uint32_t pwm)
*   @brief Get duty cycle
*   @param[in] hetRAM Pointer to HET RAM:
*              - hetRAM1: HET1 RAM pointer
*              - hetRAM2: HET2 RAM pointer
*   @param[in] pwm Pwm signal:
*              - pwm0: Pwm 0
*              - pwm1: Pwm 1
*              - pwm2: Pwm 2
*              - pwm3: Pwm 3
*              - pwm4: Pwm 4
*              - pwm5: Pwm 5
*              - pwm6: Pwm 6
*              - pwm7: Pwm 7
*
*   Gets current signal of the given pwm signal.
*/

hetSIGNAL_t pwmGetSignal(hetRAMBASE_t * hetRAM, uint32_t pwm)
{
    hetSIGNAL_t signal;   
    uint32_t    duty   = hetRAM->Instruction[(pwm << 1U) + 41U].Data - 128;
    uint32_t    period = hetRAM->Instruction[(pwm << 1U) + 42U].Data + 128;
    
    signal.duty   = (uint32_t)(100.0 * duty / period);

    if(hetRAM == hetRAM1)
    {
        signal.period = (period >> 7U) * 1600.000 / 1000.0;
    }
    else
    {
        signal.period = (period >> 7U) * 800.000 / 1000.0;
    }
    return signal;
}


/** @fn void pwmEnableNotification(hetBASE_t * hetREG, uint32_t pwm, uint32_t notification)
*   @brief Enable pwm notification
*   @param[in] hetREG Pointer to HET Module:
*              - hetREG1: HET1 Module pointer
*              - hetREG2: HET2 Module pointer
*   @param[in] pwm Pwm signal:
*              - pwm0: Pwm 0
*              - pwm1: Pwm 1
*              - pwm2: Pwm 2
*              - pwm3: Pwm 3
*              - pwm4: Pwm 4
*              - pwm5: Pwm 5
*              - pwm6: Pwm 6
*              - pwm7: Pwm 7
*   @param[in] notification Pwm notification:
*              - pwmEND_OF_DUTY:   Notification on end of duty
*              - pwmEND_OF_PERIOD: Notification on end of end period
*              - pwmEND_OF_BOTH:   Notification on end of both duty and period
*/

void pwmEnableNotification(hetBASE_t * hetREG, uint32_t pwm, uint32_t notification)
{
    hetREG->FLG     = notification << (pwm << 1U);
    hetREG->INTENAS = notification << (pwm << 1U);
}


/** @fn void pwmDisableNotification(hetBASE_t * hetREG, uint32_t pwm, uint32_t notification)
*   @brief Enable pwm notification
*   @param[in] hetREG Pointer to HET Module:
*              - hetREG1: HET1 Module pointer
*              - hetREG2: HET2 Module pointer
*   @param[in] pwm Pwm signal:
*              - pwm0: Pwm 0
*              - pwm1: Pwm 1
*              - pwm2: Pwm 2
*              - pwm3: Pwm 3
*              - pwm4: Pwm 4
*              - pwm5: Pwm 5
*              - pwm6: Pwm 6
*              - pwm7: Pwm 7
*   @param[in] notification Pwm notification:
*              - pwmEND_OF_DUTY:   Notification on end of duty
*              - pwmEND_OF_PERIOD: Notification on end of end period
*              - pwmEND_OF_BOTH:   Notification on end of both duty and period
*/

void pwmDisableNotification(hetBASE_t * hetREG, uint32_t pwm, uint32_t notification)
{
    hetREG->INTENAC = notification << (pwm << 1U);
}


/** @fn void edgeResetCounter(hetRAMBASE_t * hetRAM, uint32_t edge)
*   @brief Resets edge counter to 0
*   @param[in] hetRAM Pointer to HET RAM:
*              - hetRAM1: HET1 RAM pointer
*              - hetRAM2: HET2 RAM pointer
*   @param[in] edge Edge signal:
*              - edge0: Edge 0
*              - edge1: Edge 1
*              - edge2: Edge 2
*              - edge3: Edge 3
*              - edge4: Edge 4
*              - edge5: Edge 5
*              - edge6: Edge 6
*              - edge7: Edge 7
*
*   Reset edge counter to 0.
*/

void edgeResetCounter(hetRAMBASE_t * hetRAM, uint32_t edge)
{
    hetRAM->Instruction[edge + 17U].Data = 0U;
}


/** @fn uint32_t edgeGetCounter(hetRAMBASE_t * hetRAM, uint32_t edge)
*   @brief Get current edge counter value
*   @param[in] hetRAM Pointer to HET RAM:
*              - hetRAM1: HET1 RAM pointer
*              - hetRAM2: HET2 RAM pointer
*   @param[in] edge Edge signal:
*              - edge0: Edge 0
*              - edge1: Edge 1
*              - edge2: Edge 2
*              - edge3: Edge 3
*              - edge4: Edge 4
*              - edge5: Edge 5
*              - edge6: Edge 6
*              - edge7: Edge 7
*
*   Gets current edge counter value.
*/

uint32_t edgeGetCounter(hetRAMBASE_t * hetRAM, uint32_t edge)
{
    return hetRAM->Instruction[edge + 17U].Data >> 7U;
}


/** @fn void edgeEnableNotification(hetBASE_t * hetREG, uint32_t edge)
*   @brief Enable edge notification
*   @param[in] hetREG Pointer to HET Module:
*              - hetREG1: HET1 Module pointer
*              - hetREG2: HET2 Module pointer
*   @param[in] edge Edge signal:
*              - edge0: Edge 0
*              - edge1: Edge 1
*              - edge2: Edge 2
*              - edge3: Edge 3
*              - edge4: Edge 4
*              - edge5: Edge 5
*              - edge6: Edge 6
*              - edge7: Edge 7
*/

void edgeEnableNotification(hetBASE_t * hetREG, uint32_t edge)
{
    hetREG->FLG     = 0x20000U << edge;
    hetREG->INTENAS = 0x20000U << edge;
}


/** @fn void edgeDisableNotification(hetBASE_t * hetREG, uint32_t edge)
*   @brief Enable edge notification
*   @param[in] hetREG Pointer to HET Module:
*              - hetREG1: HET1 Module pointer
*              - hetREG2: HET2 Module pointer
*   @param[in] edge Edge signal:
*              - edge0: Edge 0
*              - edge1: Edge 1
*              - edge2: Edge 2
*              - edge3: Edge 3
*              - edge4: Edge 4
*              - edge5: Edge 5
*              - edge6: Edge 6
*              - edge7: Edge 7
*/

void edgeDisableNotification(hetBASE_t * hetREG, uint32_t edge)
{
    hetREG->INTENAC = 0x20000U << edge;
}


/** @fn hetSIGNAL_t capGetSignal(hetRAMBASE_t * hetRAM, uint32_t cap)
*   @brief Get capture signal
*   @param[in] hetRAM Pointer to HET RAM:
*              - hetRAM1: HET1 RAM pointer
*              - hetRAM2: HET2 RAM pointer
*   @param[in] cap captured signal:
*              - cap0: Captured signal 0
*              - cap1: Captured signal 1
*              - cap2: Captured signal 2
*              - cap3: Captured signal 3
*              - cap4: Captured signal 4
*              - cap5: Captured signal 5
*              - cap6: Captured signal 6
*              - cap7: Captured signal 7
*
*   Gets current signal of the given capture signal.
*/

hetSIGNAL_t capGetSignal(hetRAMBASE_t * hetRAM, uint32_t cap)
{
    uint32_t    duty   = hetRAM->Instruction[(cap << 1U) + 25U].Data;
    uint32_t    period = hetRAM->Instruction[(cap << 1U) + 26U].Data;
	hetSIGNAL_t signal;   
    
    signal.duty   = (uint32_t)(100.0 * duty / period);
    
    if( hetRAM == hetRAM1)
    {
        signal.period = (period >> 7U) * 1600.000 / 1000.0;
    }
    else
    {
        signal.period = (period >> 7U) * 800.000 / 1000.0;
    }
    return signal;
}


/** @fn void hetResetTimestamp(hetRAMBASE_t *hetRAM)
*   @brief Resets timestamp
*   @param[in] hetRAM Pointer to HET RAM:
*              - hetRAM1: HET1 RAM pointer
*              - hetRAM2: HET2 RAM pointer
*
*   Resets loop count based timstamp.
*/

void hetResetTimestamp(hetRAMBASE_t * hetRAM)
{
    hetRAM->Instruction[0U].Data = 0;
}


/** @fn uint32_t hetGetTimestamp(hetRAMBASE_t *hetRAM)
*   @brief Returns timestamp
*
*   Returns loop count based timstamp.
*/

uint32_t hetGetTimestamp(hetRAMBASE_t * hetRAM)
{
    return hetRAM->Instruction[57U].Data;
}

/* USER CODE BEGIN (4) */
/* USER CODE END */

/** @fn void het1HighLevelInterrupt(void)
*   @brief Level 0 Interrupt for HET1
*/
#pragma INTERRUPT(het1HighLevelInterrupt, IRQ)

void het1HighLevelInterrupt(void)
{
    uint32_t vec = hetREG1->OFF1;
	
	hetNotification(hetREG1,vec);
}


/** @fn void het1LowLevelInterrupt(void)
*   @brief Level 1 Interrupt for HET1
*/
#pragma INTERRUPT(het1LowLevelInterrupt, IRQ)

void het1LowLevelInterrupt(void)
{
    uint32_t vec = hetREG1->OFF2;
	
	hetNotification(hetREG1,vec);
}

