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
/** @file adc.c 
*   @brief ADC Driver Source File
*   @date 04.January.2012
*   @version 03.00.00
*
*   This file contains:
*   - API Funcions
*   - Interrupt Handlers
*   .
*   which are relevant for the ADC driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */

//! \file   ~/drivers/adc/adc_bldc/src/32b/hercules/tms570ls3137/adc.c
//! \brief  Contains the various functions related to the
//!         analog-to-digital converter (ADC) object
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

/* USER CODE END */

/* Include Files */

#include "adc.h"

/* USER CODE BEGIN (1) */

// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

/* USER CODE END */


/** @fn void adcInit(void)
*   @brief Initializes ADC Driver
*
*   This function initializes the ADC driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void adcInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */



    /** @b Initialize @b ADC1: */

    /** - Reset ADC module */
    adcREG1->RSTCR = 1U;
    adcREG1->RSTCR = 0U;

    /** - Enable 12-BIT ADC  */
    adcREG1->OPMODECR |= 0x80000000U;

    /** - Setup prescaler */
    adcREG1->CLOCKCR = 2U;
 
    /** - Setup memory boundaries */
    adcREG1->BNDCR  =(8U << 16U)|(8U + 8U);
    adcREG1->BNDEND = 2U;
 
    /** - Setup event group conversion mode
    *     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
    */
    adcREG1->GxMODECR[0U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup event group hardware trigger
     *     - Setup hardware trigger edge
     *     - Setup hardware trigger source
     */
    adcREG1->G0SRC = 0x00000000U
                   | ADC1_EVENT;

    /** - Setup event group sample window */
    adcREG1->G0SAMP = 4U;

    /** - Setup event group sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G0SAMPDISEN = 0U << 8U
                         | 0x00000000U;

    /** - Setup group 1 conversion mode
    *     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
    */
    adcREG1->GxMODECR[1U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000008U
                          | 0x00000000U;

    /** - Setup group 1 hardware trigger
     *     - Setup hardware trigger edge
     *     - Setup hardware trigger source
     */
    adcREG1->G1SRC = 0x00000000U
                   | ADC1_HET1_17; /* Alternate Trigger Source */

    /** - Setup group 1 sample window */
    adcREG1->G1SAMP = 4U;

    /** - Setup group 1 sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G1SAMPDISEN = 0U << 8U
                         | 0x00000000U;

    /** - Setup group 2 conversion mode
     *     - Setup data format
     *     - Enable/Disable channel id in conversion result
     *     - Enable/Disable continuous conversion
     */
    adcREG1->GxMODECR[2U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000008U
                          | 0x00000000U;

    /** - Setup group 2 hardware trigger
	*     - Setup hardware trigger edge
    *     - Setup hardware trigger source
	*/
    adcREG1->G2SRC = 0x00000000U
                   | ADC1_HET1_19; /* Alternate Trigger Source */

    /** - Setup group 2 sample window */
    adcREG1->G2SAMP = 4U;

    /** - Setup group 2 sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G2SAMPDISEN = 0U << 8U
                         | 0x00000000U;

    /** - Enable ADC module */
    adcREG1->OPMODECR |= 0x80140001U;

    /** - Wait for buffer inialisation complete */
    while ((adcREG1->BUFINIT) != 0) { /* Wait */ } 
    
    /** - Setup parity */
    adcREG1->PARCR = 0x00000005U;


/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/** @fn void adcStartConversion(adcBASE_t *adc, uint32_t group)
*   @brief Starts an ADC conversion
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function starts a convesion of the ADC hardware group.
*
*/

/** - s_adcSelect is used as constant table for channel selection */
static const uint32_t s_adcSelect[2U][3U] =
{
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000200U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00008000U |
    0x00000000U |
    0x00000000U |
    0x00040000U |
    0x00000000U |
    0x00100000U |
    0x00200000U |
    0x00000000U |
    0x00800000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U ,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
};

/** - s_adcSelect is used as constant table for channel selection */
static const uint32_t s_adcFiFoSize[2U][3U] =
{
    16U,
    16U,
    16U,
    16U,
    16U,
    16U,
};

/* USER CODE BEGIN (6) */
/* USER CODE END */

void adcStartConversion(adcBASE_t *adc, uint32_t group)
{
    uint32_t index = adc == adcREG1 ? 0U : 1U;

/* USER CODE BEGIN (7) */
/* USER CODE END */

    /** - Setup FiFo size */
    adc->GxINTCR[group] = s_adcFiFoSize[index][group];

    /** - Start Conversion */
    adc->GxSEL[group] = s_adcSelect[index][group];

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (8) */
/* USER CODE END */
}

/* USER CODE BEGIN (9) */
/* USER CODE END */


/** @fn void adcStopConversion(adcBASE_t *adc, uint32_t group)
*   @brief Stops an ADC conversion
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function stops a convesion of the ADC hardware group.
*
*/

/* USER CODE BEGIN (10) */
/* USER CODE END */

void adcStopConversion(adcBASE_t *adc, uint32_t group)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    /** - Stop Conversion */
    adc->GxSEL[group] = 0U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (12) */
/* USER CODE END */
}

/* USER CODE BEGIN (13) */
/* USER CODE END */


/** @fn void adcResetFiFo(adcBASE_t *adc, uint32_t group)
*   @brief Resets FiFo read and write pointer.
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function resets the FiFo read and write pointrs.
*
*/

/* USER CODE BEGIN (14) */
/* USER CODE END */

void adcResetFiFo(adcBASE_t *adc, uint32_t group)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */

    /** - Reset FiFo */
    adc->GxFIFORESETCR[group] = 1U;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           the conversion should be stopped before calling this function. 
    */

/* USER CODE BEGIN (16) */
/* USER CODE END */
}

/* USER CODE BEGIN (17) */
/* USER CODE END */


/** @fn uint32_t adcGetData(adcBASE_t *adc, uint32_t group, adcData_t *data)
*   @brief Gets converted a ADC values
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @param[out] data Pointer to store ADC converted data
*   @return The function will return the number of converted values copied into data buffer:
*
*   This function writes a ADC message into a ADC message box.
*
*/


/* USER CODE BEGIN (18) */
/* USER CODE END */

uint32_t adcGetData(adcBASE_t *adc, uint32_t group, adcData_t *data)
{
    uint32_t  i;
    uint32_t  buf;
    uint32_t  mode;    
    uint32_t  count = 16;
    adcData_t *ptr = data; 

/* USER CODE BEGIN (19) */
/* USER CODE END */

    mode = ((adc->GxMODECR[group]) & 0x00000300U);

    if(mode == ADC_12_BIT)
      {
        /** -  Get conversion data and channel/pin id */
        for (i = 0; i < count-1; i++)		// edited this loop so that it doesn't overrun a 16 value array, until bug is fixed *data must always be a 16 value or bigger array.
        {
          buf        = adc->GxBUF[group].BUF0;
          ptr->value = (uint16_t)(buf & 0xFFFU);
          ptr->id    = (uint32_t)((buf >> 16U) & 0x1FU);
          ptr++;
        }
      }
      else
      {
        /** -  Get conversion data and channel/pin id */
        for (i = 0; i < count-1; i++)		// edited this loop so that it doesn't overrun a 16 value array, until bug is fixed *data must always be a 16 value or bigger array.
        {
          buf        = adc->GxBUF[group].BUF0;
          ptr->value = (uint16_t)(buf & 0x3FFU);
          ptr->id    = (uint32_t)((buf >> 10U) & 0x1FU);
          ptr++;
        }
      }


    adc->GxINTFLG[group] = 9U;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           The user is responsible to initialize the message box.
    */

/* USER CODE BEGIN (20) */
/* USER CODE END */

    return count;
}

/* USER CODE BEGIN (21) */
/* USER CODE END */


/** @fn uint32_t adcIsFifoFull(adcBASE_t *adc, uint32_t group)
*   @brief Checks if FiFo buffer is full
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @return The function will return:
*           - 0: When FiFo buffer is not full   
*           - 1: When FiFo buffer is full   
*           - 3: When FiFo buffer overflow occured    
*
*   This function checks FiFo buffer status.
*
*/


/* USER CODE BEGIN (22) */
/* USER CODE END */

uint32_t adcIsFifoFull(adcBASE_t *adc, uint32_t group)
{
    uint32_t flags;

/* USER CODE BEGIN (23) */
/* USER CODE END */

    /** - Read FiFo flags */
    flags = adc->GxINTFLG[group] & 3U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (24) */
/* USER CODE END */

    return flags;
}

/* USER CODE BEGIN (25) */
/* USER CODE END */


/** @fn uint32_t adcIsConversionComplete(adcBASE_t *adc, uint32_t group)
*   @brief Checks if Conversion is complete
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @return The function will return:
*           - 0: When is not finished   
*           - 8: When conversion is complete   
*
*   This function checks if conversion is complete.
*
*/


/* USER CODE BEGIN (26) */
/* USER CODE END */

uint32_t adcIsConversionComplete(adcBASE_t *adc, uint32_t group)
{
    uint32_t flags;

/* USER CODE BEGIN (27) */
/* USER CODE END */

    /** - Read conversion flags */
    flags = adc->GxINTFLG[group] & 8U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (28) */
/* USER CODE END */

    return flags;
}

/* USER CODE BEGIN (29) */
/* USER CODE END */

/** @fn void adcCalibration(adcBASE_t *adc)
*   @brief Computes offset error using Calibration mode
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   This function computes offset error using Calibration mode
*
*/
void adcCalibration(adcBASE_t *adc)
{
/* USER CODE BEGIN (30) */
/* USER CODE END */
    
	uint32_t conv_val[5]={0,0,0,0,0},loop_index=0;
	uint32_t offset_error=0;
	uint32_t backup_mode;
	
	/** - Backup Mode before Calibration  */
	backup_mode = adc->OPMODECR;
	
	/** - Enable 12-BIT ADC  */
	adcREG1->OPMODECR |= 0x80000000U;

	/* Disable all channels for conversion */
	adc->GxSEL[0]=0x00;
	adc->GxSEL[1]=0x00;
	adc->GxSEL[2]=0x00;

	for(loop_index=0;loop_index<4;loop_index++)
	{
		/* Disable Self Test and Calibration mode */
		adc->CALCR=0x0;
	
		switch(loop_index)
		{
			case 0 : 	/* Test 1 : Bride En = 0 , HiLo =0 */
						adc->CALCR=0x0;
						break;

			case 1 :	/* Test 1 : Bride En = 0 , HiLo =1 */
						adc->CALCR=0x0100;
						break;

			case 2 : 	/* Test 1 : Bride En = 1 , HiLo =0 */
						adc->CALCR=0x0200;
						break;
		
			case 3 : 	/* Test 1 : Bride En = 1 , HiLo =1 */
						adc->CALCR=0x0300;
						break;
		}
	
		/* Enable Calibration mode */
		adc->CALCR|=0x1;
	
		/* Start calibration conversion */
		adc->CALCR|=0x00010000;

		/* Wait for calibration conversion to complete */
		while((adc->CALCR & 0x00010000)==0x00010000);

		/* Read converted value */
		conv_val[loop_index]= adc->CALR;
	}

	/* Disable Self Test and Calibration mode */
	adc->CALCR=0x0;

	/* Compute the Offset error correction value */
	conv_val[4]=conv_val[0]+ conv_val[1] + conv_val[2] + conv_val[3];

	conv_val[4]=(conv_val[4]/4);

	offset_error=conv_val[4]-0x7FF;

	/*Write the offset error to the Calibration register */
	/* Load 2;s complement of the computed value to ADCALR register */
	offset_error=~offset_error;
	offset_error=offset_error & 0xFFF;
	offset_error=offset_error+1;

	adc->CALR = offset_error;

  /** - Restore Mode after Calibration  */
	adc->OPMODECR = backup_mode;
	
 /**   @note The function adcInit has to be called before using this function. */

/* USER CODE BEGIN (31) */
/* USER CODE END */
}


/** @fn void adcMidPointCalibration(adcBASE_t *adc)
*   @brief Computes offset error using Mid Point Calibration mode
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   This function computes offset error using Mid Point Calibration mode
*
*/

/* USER CODE BEGIN (32) */
/* USER CODE END */

uint32_t adcMidPointCalibration(adcBASE_t *adc)
{
/* USER CODE BEGIN (33) */
/* USER CODE END */
    
	uint32_t conv_val[3]={0,0,0},loop_index=0;
	uint32_t offset_error=0;
	uint32_t backup_mode;
	
	/** - Backup Mode before Calibration  */
	backup_mode = adc->OPMODECR;
	
	/** - Enable 12-BIT ADC  */
	adcREG1->OPMODECR |= 0x80000000U;

	/* Disable all channels for conversion */
	adc->GxSEL[0]=0x00;
	adc->GxSEL[1]=0x00;
	adc->GxSEL[2]=0x00;

	for(loop_index=0;loop_index<2;loop_index++)
	{
		/* Disable Self Test and Calibration mode */
		adc->CALCR=0x0;
	
		switch(loop_index)
		{
			case 0 : 	/* Test 1 : Bride En = 0 , HiLo =0 */
						adc->CALCR=0x0;
						break;

			case 1 :	/* Test 1 : Bride En = 0 , HiLo =1 */
						adc->CALCR=0x0100;
						break;

		}
	
		/* Enable Calibration mode */
		adc->CALCR|=0x1;
	
		/* Start calibration conversion */
		adc->CALCR|=0x00010000;

		/* Wait for calibration conversion to complete */
		while((adc->CALCR & 0x00010000)==0x00010000);

		/* Read converted value */
		conv_val[loop_index]= adc->CALR;
	}

	/* Disable Self Test and Calibration mode */
	adc->CALCR=0x0;

	/* Compute the Offset error correction value */
	conv_val[2]=(conv_val[0])+ (conv_val[1]);

	conv_val[2]=(conv_val[2]/2);

	offset_error=conv_val[2]-0x7FF;

	/* Write the offset error to the Calibration register           */
	/* Load 2's complement of the computed value to ADCALR register */
	offset_error=~offset_error;
	offset_error=offset_error & 0xFFF;
	offset_error=offset_error+1;

	adc->CALR = offset_error;

  /** - Restore Mode after Calibration  */
	adc->OPMODECR = backup_mode;
	
	return(offset_error);

 /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (34) */
/* USER CODE END */
}

/* USER CODE BEGIN (35) */
/* USER CODE END */

/** @fn void adcEnableNotification(adcBASE_t *adc, uint32_t group)
*   @brief Enable notification
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function will enable the notification of a conversion.
*   In single conversion mode for conversion complete and
*   in continuous conversion mode when the FiFo buffer is full.
*
*/

/* USER CODE BEGIN (36) */
/* USER CODE END */

void adcEnableNotification(adcBASE_t *adc, uint32_t group)
{
    uint32_t notif = adc->GxMODECR[group] & 2U ? 1U : 8U;

/* USER CODE BEGIN (37) */
/* USER CODE END */

    adc->GxINTENA[group] = notif;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           This function should be called before the conversion is started
    */

/* USER CODE BEGIN (38) */
/* USER CODE END */
}

/* USER CODE BEGIN (39) */
/* USER CODE END */


/** @fn void adcDisableNotification(adcBASE_t *adc, uint32_t group)
*   @brief Disable notification
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function will disable the notification of a conversion.
*/

/* USER CODE BEGIN (40) */
/* USER CODE END */

void adcDisableNotification(adcBASE_t *adc, uint32_t group)
{
/* USER CODE BEGIN (41) */
/* USER CODE END */

    adc->GxINTENA[group] = 0U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (42) */
/* USER CODE END */
}

/* USER CODE BEGIN (43) */
/* USER CODE END */


/** @fn void adc1Group0Interrupt(void)
*   @brief ADC1 Event Group Interrupt Handler
*/

/* USER CODE BEGIN (44) */
/* USER CODE END */

#pragma INTERRUPT(adc1Group0Interrupt, IRQ)

void adc1Group0Interrupt(void)
{
/* USER CODE BEGIN (45) */
/* USER CODE END */
    
    adcREG1->GxINTFLG[0U] = 9U;

    adcNotification(adcREG1, adcGROUP0);

/* USER CODE BEGIN (46) */
/* USER CODE END */
}

/* USER CODE BEGIN (47) */
/* USER CODE END */


/** @fn void adc1Group1Interrupt(void)
*   @brief ADC1 Group 1 Interrupt Handler
*/

/* USER CODE BEGIN (48) */
/* USER CODE END */

#pragma INTERRUPT(adc1Group1Interrupt, IRQ)

void adc1Group1Interrupt(void)
{
/* USER CODE BEGIN (49) */
/* USER CODE END */
    
    adcREG1->GxINTFLG[1U] = 9U;

    adcNotification(adcREG1, adcGROUP1);

/* USER CODE BEGIN (50) */

/* USER CODE END */
}

/* USER CODE BEGIN (51) */
/* USER CODE END */


/** @fn void adc1Group2Interrupt(void)
*   @brief ADC1 Group 2 Interrupt Handler
*/

/* USER CODE BEGIN (52) */
/* USER CODE END */

#pragma INTERRUPT(adc1Group2Interrupt, IRQ)

void adc1Group2Interrupt(void)
{
/* USER CODE BEGIN (53) */
/* USER CODE END */
    
    adcREG1->GxINTFLG[2U] = 9U;

    adcNotification(adcREG1, adcGROUP2);
		
/* USER CODE BEGIN (54) */

/* USER CODE END */
}

/* USER CODE BEGIN (55) */
/* USER CODE END */


/** @fn void adc2Group0Interrupt(void)
*   @brief ADC2 Event Group Interrupt Handler
*/

/* USER CODE BEGIN (56) */
/* USER CODE END */

#pragma INTERRUPT(adc2Group0Interrupt, IRQ)

void adc2Group0Interrupt(void)
{
/* USER CODE BEGIN (57) */
/* USER CODE END */
    
    adcREG2->GxINTFLG[0U] = 9U;

    adcNotification(adcREG2, adcGROUP0);

/* USER CODE BEGIN (58) */
/* USER CODE END */
}

/* USER CODE BEGIN (59) */
/* USER CODE END */


/** @fn void adc2Group1Interrupt(void)
*   @brief ADC2 Group 1 Interrupt Handler
*/

/* USER CODE BEGIN (60) */
/* USER CODE END */

#pragma INTERRUPT(adc2Group1Interrupt, IRQ)

void adc2Group1Interrupt(void)
{
/* USER CODE BEGIN (61) */
/* USER CODE END */
    
    adcREG2->GxINTFLG[1U] = 9U;

    adcNotification(adcREG2, adcGROUP1);

/* USER CODE BEGIN (62) */
/* USER CODE END */
}

/* USER CODE BEGIN (63) */
/* USER CODE END */


/** @fn void adc2Group2Interrupt(void)
*   @brief ADC2 Group 2 Interrupt Handler
*/

/* USER CODE BEGIN (64) */
/* USER CODE END */

#pragma INTERRUPT(adc2Group2Interrupt, IRQ)

void adc2Group2Interrupt(void)
{
/* USER CODE BEGIN (65) */
/* USER CODE END */
    
    adcREG2->GxINTFLG[2U] = 9U;

    adcNotification(adcREG2, adcGROUP2);

/* USER CODE BEGIN (66) */
/* USER CODE END */
}

/* USER CODE BEGIN (67) */

// end of file

/* USER CODE END */


