/** @file het.c 
*   @brief HET Driver Implementation File
*   @date 15.December.2011
*   @version 03.00.00
*
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#include "het.h"
//#include "std_nhet.h"
#include "8301.h"


/* USER CODE BEGIN (0) */

//! \file   ~/drivers/het/src/32b/hercules/champion/het.c
//! \brief  Contains the various functions related to the
//!         high efficiency timer (HET) peripheral
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Global variables                                                           */



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
                | 0x00080000U
                | 0x00000000U
                | 0x00020000U
                | 0x00010000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000100U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000000U
                | 0x00000004U
                | 0x00000000U
                | 0x00000000U;

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
                | 0x00000400U //HET10 pull up
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

/* USER CODE BEGIN (5) */

// end of file

/* USER CODE END */




