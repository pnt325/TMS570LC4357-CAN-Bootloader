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
/** @file adc.h
*   @brief ADC Driver Header File
*   @date 04.January.2012
*   @version 03.00.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the ADC driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#include "sys_common.h"

#ifndef __ADC_H__
#define __ADC_H__

/* USER CODE BEGIN (0) */

//! \file   ~/drivers/adc/src/32b/hercules/tms570ls3137/adc.h
//! \brief  Contains public interface to various functions related
//!         to the analog-to-digital converter (ADC) object
//!
//! (C) Copyright 2012, Texas Instruments, Inc.

// **************************************************************************
// the includes

// drivers


// modules


//!
//! \defgroup ADC

//!
//! \ingroup ADC
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

/* USER CODE END */


/* ADC General Definitions */

/** @def adcGROUP0
*   @brief Alias name for ADC event group
*
*   @note This value should be used for API argument @a group
*/
#define adcGROUP0 0U

/** @def adcGROUP1
*   @brief Alias name for ADC group 1
*
*   @note This value should be used for API argument @a group
*/
#define adcGROUP1 1U

/** @def adcGROUP2
*   @brief Alias name for ADC group 2
*
*   @note This value should be used for API argument @a group
*/
#define adcGROUP2 2U

/** @enum adcResolution
*   @brief Alias names for data resolution
*   This enumeration is used to provide alias names for the data resolution:
*     - 12 bit resolution
*     - 10 bit resolution
*     - 8  bit resolution
*/

enum adcResolution
{
    ADC_12_BIT = 0x00000000, /**< Alias for 12 bit data resolution */
    ADC_10_BIT = 0x00000100, /**< Alias for 10 bit data resolution */
    ADC_8_BIT  = 0x00000200  /**< Alias for 8 bit data resolution  */
};

/** @enum adcFiFoStatus
*   @brief Alias names for FiFo status
*   This enumeration is used to provide alias names for the current FiFo states:
*     - FiFo is not full
*     - FiFo is full
*     - FiFo overflow occured
*/

enum adcFiFoStatus
{
    ADC_FIFO_IS_NOT_FULL = 0, /**< Alias for FiFo is not full       */
    ADC_FIFO_IS_FULL     = 1, /**< Alias for FiFo is full           */
    ADC_FIFO_OVERFLOW    = 3  /**< Alias for FiFo overflow occured  */
};

/** @enum adcConversionStatus
*   @brief Alias names for conversion status
*   This enumeration is used to provide alias names for the current conversion states:
*     - Conversion is not finished
*     - Conversion is finished
*/

enum adcConversionStatus
{
    ADC_CONVERSION_IS_NOT_FINISHED = 0, /**< Alias for current conversion is not finished */
    ADC_CONVERSION_IS_FINISHED     = 8  /**< Alias for current conversion is  finished    */
};

/** @enum adc1HwTriggerSource
*   @brief Alias names for hardware trigger source
*   This enumeration is used to provide alias names for the hardware trigger sources:
*/

enum adc1HwTriggerSource
{
	ADC1_EVENT = 0,       /**< Alias for event pin             */
	ADC1_HET1_8 = 1,      /**< Alias for HET1 pin 8            */
	ADC1_HET1_10 = 2,     /**< Alias for HET1 pin 10           */
	ADC1_RTI_COMP0 = 3,   /**< Alias for RTI compare 0 match   */
	ADC1_HET1_12 = 4,     /**< Alias for HET1 pin 12           */
	ADC1_HET1_14 = 5,     /**< Alias for HET1 pin 14           */
	ADC1_GIOB0 = 6,       /**< Alias for GIO port b pin 0      */
	ADC1_GIOB1 = 7,       /**< Alias for GIO port b pin 1      */
	ADC1_HET2_= 1,        /**< Alias for HET2 pin 5            */
	ADC1_HET1_27 = 2,     /**< Alias for HET1 pin 27           */
	ADC1_HET1_17 = 4,     /**< Alias for HET1 pin 17           */
	ADC1_HET1_19 = 5,     /**< Alias for HET1 pin 19           */
	ADC1_HET1_11 = 6,     /**< Alias for HET1 pin 11           */
	ADC1_HET1_13 = 7      /**< Alias for HET2 pin 13           */
};

/** @enum adc2HwTriggerSource
*   @brief Alias names for hardware trigger source
*   This enumeration is used to provide alias names for the hardware trigger sources:
*/

enum adc2HwTriggerSource
{
	ADC2_EVENT = 0,       /**< Alias for event pin             */
	ADC2_HET1_8 = 1,      /**< Alias for HET1 pin 8            */
	ADC2_HET1_10 = 2,     /**< Alias for HET1 pin 10           */
	ADC2_RTI_COMP0 = 3,   /**< Alias for RTI compare 0 match   */
	ADC2_HET1_12 = 4,     /**< Alias for HET1 pin 12           */
	ADC2_HET1_14 = 5,     /**< Alias for HET1 pin 14           */
	ADC2_GIOB0 = 6,       /**< Alias for GIO port b pin 0      */
	ADC2_GIOB1 = 7,       /**< Alias for GIO port b pin 1      */
	ADC2_HET2_= 1,        /**< Alias for HET2 pin 5            */
	ADC2_HET1_27 = 2,     /**< Alias for HET1 pin 27           */
	ADC2_HET1_17 = 4,     /**< Alias for HET1 pin 17           */
	ADC2_HET1_19 = 5,     /**< Alias for HET1 pin 19           */
	ADC2_HET1_11 = 6,     /**< Alias for HET1 pin 11           */
	ADC2_HET1_13 = 7      /**< Alias for HET2 pin 13           */
};

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @struct adcData
*   @brief ADC Conversion data structure
*
*   This type is used to pass adc conversion data.
*/
/** @typedef adcData_t
*   @brief ADC Data Type Definition
*/
typedef struct adcData
{
    uint32_t            id;     /**< Channel/Pin Id        */
    uint16_t value;  /**< Conversion data value */
} adcData_t;

/** @struct adcBase
*   @brief ADC Register Frame Definition
*
*   This type is used to access the ADC Registers.
*/
/** @typedef adcBASE_t
*   @brief ADC Register Frame Type Definition
*
*   This type is used to access the ADC Registers.
*/
typedef volatile struct adcBase
{
    uint32_t RSTCR;              /**< 0x0000: Reset control register                            */
    uint32_t OPMODECR;           /**< 0x0004: Operating mode control register                   */
    uint32_t CLOCKCR;            /**< 0x0008: Clock control register                            */
    uint32_t CALCR;              /**< 0x000C: Calibration control register                      */
    uint32_t GxMODECR[3U];       /**< 0x0010,0x0014,0x0018: Group 0-2 mode control register     */
    uint32_t G0SRC;              /**< 0x001C: Group 0 trigger source control register           */
    uint32_t G1SRC;              /**< 0x0020: Group 1 trigger source control register           */
    uint32_t G2SRC;              /**< 0x0024: Group 2 trigger source control register           */
    uint32_t GxINTENA[3U];       /**< 0x0028,0x002C,0x0030: Group 0-2 interrupt enable register */
    uint32_t GxINTFLG[3U];       /**< 0x0034,0x0038,0x003C: Group 0-2 interrupt flag register   */
    uint32_t GxINTCR[3U];        /**< 0x0040-0x0048: Group 0-2 interrupt threshold register     */
    uint32_t G0DMACR;            /**< 0x004C: Group 0 DMA control register                      */
    uint32_t G1DMACR;            /**< 0x0050: Group 1 DMA control register                      */
    uint32_t G2DMACR;            /**< 0x0054: Group 2 DMA control register                      */
    uint32_t BNDCR;              /**< 0x0058: Buffer boundary control register                  */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1)) 
    uint32_t BNDEND  : 16U;      /**< 0x005C: Buffer boundary end register                      */
    uint32_t BUFINIT : 16U;      /**< 0x005C: Buffer initialization register                    */
#else
    uint32_t BUFINIT : 16U;      /**< 0x005C: Buffer initialization register                    */
    uint32_t BNDEND  : 16U;      /**< 0x005C: Buffer boundary end register                      */
#endif
    uint32_t G0SAMP;             /**< 0x0060: Group 0 sample window register                    */
    uint32_t G1SAMP;             /**< 0x0064: Group 1 sample window register                    */
    uint32_t G2SAMP;             /**< 0x0068: Group 2 sample window register                    */
    uint32_t G0SR;               /**< 0x006C: Group 0 status register                           */
    uint32_t G1SR;               /**< 0x0070: Group 1 status register                           */
    uint32_t G2SR;               /**< 0x0074: Group 2 status register                           */
    uint32_t GxSEL[3U];          /**< 0x0078-0x007C: Group 0-2 channel select register          */
    uint32_t CALR;               /**< 0x0084: Calibration register                              */
    uint32_t SMSTATE;            /**< 0x0088: State machine state register                      */
    uint32_t LASTCONV;           /**< 0x008C: Last conversion register                          */
    struct
    {
        uint32_t BUF0;           /**< 0x0090,0x00B0,0x00D0: Group 0-2 result buffer 1 register  */
        uint32_t BUF1;           /**< 0x0094,0x00B4,0x00D4: Group 0-2 result buffer 1 register  */
        uint32_t BUF2;           /**< 0x0098,0x00B8,0x00D8: Group 0-2 result buffer 2 register  */
        uint32_t BUF3;           /**< 0x009C,0x00BC,0x00DC: Group 0-2 result buffer 3 register  */
        uint32_t BUF4;           /**< 0x00A0,0x00C0,0x00E0: Group 0-2 result buffer 4 register  */
        uint32_t BUF5;           /**< 0x00A4,0x00C4,0x00E4: Group 0-2 result buffer 5 register  */
        uint32_t BUF6;           /**< 0x00A8,0x00C8,0x00E8: Group 0-2 result buffer 6 register  */
        uint32_t BUF7;           /**< 0x00AC,0x00CC,0x00EC: Group 0-2 result buffer 7 register  */
    } GxBUF[3U];
    uint32_t G0EMUBUFFER;        /**< 0x00F0: Group 0 emulation result buffer                   */
    uint32_t G1EMUBUFFER;        /**< 0x00F4: Group 1 emulation result buffer                   */
    uint32_t G2EMUBUFFER;        /**< 0x00F8: Group 2 emulation result buffer                   */
    uint32_t EVTDIR;             /**< 0x00FC: Event pin direction register                      */
    uint32_t EVTOUT;             /**< 0x0100: Event pin digital output register                 */
    uint32_t EVTIN;              /**< 0x0104: Event pin digital input register                  */
    uint32_t EVTSET;             /**< 0x0108: Event pin set register                            */
    uint32_t EVTCLR;             /**< 0x010C: Event pin clear register                          */
    uint32_t EVTPDR;             /**< 0x0110: Event pin open drain register                     */
    uint32_t EVTDIS;             /**< 0x0114: Event pin pull disable register                   */
    uint32_t EVTPSEL;            /**< 0x0118: Event pin pull select register                    */
    uint32_t G0SAMPDISEN;        /**< 0x011C: Group 0 sample discharge register                 */
    uint32_t G1SAMPDISEN;        /**< 0x0120: Group 1 sample discharge register                 */
    uint32_t G2SAMPDISEN;        /**< 0x0124: Group 2 sample discharge register                 */
    uint32_t MAGINTCR1;          /**< 0x0128: Magnitude interrupt control register 1            */
    uint32_t MAGINT1MASK;        /**< 0x012C: Magnitude interrupt mask register 1               */
    uint32_t MAGINTCR2;          /**< 0x0130: Magnitude interrupt control register 2            */
    uint32_t MAGINT2MASK;        /**< 0x0134: Magnitude interrupt mask register 2               */
    uint32_t MAGINTCR3;          /**< 0x0138: Magnitude interrupt control register 3            */
    uint32_t MAGINT3MASK;        /**< 0x013C: Magnitude interrupt mask register 3               */
    uint32_t MAGINTCR4;          /**< 0x0140: Magnitude interrupt control register 4            */
    uint32_t MAGINT4MASK;        /**< 0x0144: Magnitude interrupt mask register 4               */
    uint32_t MAGINTCR5;          /**< 0x0148: Magnitude interrupt control register 5            */
    uint32_t MAGINT5MASK;        /**< 0x014C: Magnitude interrupt mask register 5               */
    uint32_t MAGINTCR6;          /**< 0x0150: Magnitude interrupt control register 6            */
    uint32_t MAGINT6MASK;        /**< 0x0154: Magnitude interrupt mask register 6               */
    uint32_t MAGTHRINTENASET;    /**< 0x0158: Magnitude interrupt set register                  */
    uint32_t MAGTHRINTENACLR;    /**< 0x015C: Magnitude interrupt clear register                */
    uint32_t MAGTHRINTFLG;       /**< 0x0160: Magnitude interrupt flag register                 */
    uint32_t MAGTHRINTOFFSET;    /**< 0x0164: Magnitude interrupt offset register               */
    uint32_t GxFIFORESETCR[3U];  /**< 0x0168,0x016C,0x0170: Group 0-2 fifo reset register       */
    uint32_t G0RAMADDR;          /**< 0x0174: Group 0 RAM pointer register                      */
    uint32_t G1RAMADDR;          /**< 0x0178: Group 1 RAM pointer register                      */
    uint32_t G2RAMADDR;          /**< 0x017C: Group 2 RAM pointer register                      */
    uint32_t PARCR;              /**< 0x0180: Parity control register                           */
    uint32_t PARADDR;            /**< 0x0184: Parity error address register                     */
} adcBASE_t;


/** @def adcREG1
*   @brief ADC1 Register Frame Pointer
*
*   This pointer is used by the ADC driver to access the ADC1 registers.
*/
#define adcREG1 ((adcBASE_t *)0xFFF7C000U)

/** @def adcREG2
*   @brief ADC2 Register Frame Pointer
*
*   This pointer is used by the ADC driver to access the ADC2 registers.
*/
#define adcREG2 ((adcBASE_t *)0xFFF7C200U)

/* USER CODE BEGIN (2) */
/* USER CODE END */


/* ADC Interface Functions */

void adcInit(void);
void adcStartConversion(adcBASE_t *adc, uint32_t group);
void adcStopConversion(adcBASE_t *adc, uint32_t group);
void adcResetFiFo(adcBASE_t *adc, uint32_t group);
uint32_t  adcGetData(adcBASE_t *adc, uint32_t group, adcData_t *data);
uint32_t  adcIsFifoFull(adcBASE_t *adc, uint32_t group);
uint32_t  adcIsConversionComplete(adcBASE_t *adc, uint32_t group);
void adcEnableNotification(adcBASE_t *adc, uint32_t group);
void adcDisableNotification(adcBASE_t *adc, uint32_t group);
void adcCalibration(adcBASE_t *adc);
uint32_t adcMidPointCalibration(adcBASE_t *adc);

/** @fn void adcNotification(adcBASE_t *adc, uint32_t group)
*   @brief Group notification
*   @param[in] adc Pointer to ADC node:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] group number of ADC node:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   @note This function has to be provide by the user.
*/
void adcNotification(adcBASE_t *adc, uint32_t group);

/* USER CODE BEGIN (3) */

#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

/* USER CODE END */


#endif
