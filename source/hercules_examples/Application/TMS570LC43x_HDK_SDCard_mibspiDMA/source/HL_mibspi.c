/** @file HL_mibspi.c 
*   @brief MIBSPI Driver Implementation File
*   @date 11-Dec-2018
*   @version 04.07.01
*
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "HL_mibspi.h"
#include "HL_sys_vim.h"
/* USER CODE BEGIN (1) */
/* USER CODE END */

/* SourceId : MIBSPI_SourceId_001 */
/* DesignId : MIBSPI_DesignId_001 */
/* Requirements : HL_CONQ_MIBSPI_SR9 */
/** @fn void mibspiInit(void)
*   @brief Initializes the MIBSPI Driver
*
*   This function initializes the MIBSPI module.
*/
void mibspiInit(void)
{
uint32 i ;

/* USER CODE BEGIN (2) */
/* USER CODE END */


    /** @b initialize @b MIBSPI2 */

    /** bring MIBSPI out of reset */
    mibspiREG2->GCR0 = 0U;
    mibspiREG2->GCR0 = 1U;

    /** enable MIBSPI2 multibuffered mode and enable buffer RAM */
    mibspiREG2->MIBSPIE = (mibspiREG2->MIBSPIE & 0xFFFFFFFEU) | 1U;

    /** MIBSPI2 master mode and clock configuration */
    mibspiREG2->GCR1 = (mibspiREG2->GCR1 & 0xFFFFFFFCU) | ((uint32)((uint32)1U << 1U)  /* CLOKMOD */
                  | 1U);  /* MASTER */

    /** MIBSPI2 enable pin configuration */
    mibspiREG2->INT0 = (mibspiREG2->INT0 & 0xFEFFFFFFU) | (uint32)((uint32)0U << 24U);  /* ENABLE HIGHZ */

    /** - Delays */
    mibspiREG2->DELAY = (uint32)((uint32)50U << 24U)  /* C2TDELAY */
                      | (uint32)((uint32)50U << 16U)  /* T2CDELAY */
                      | (uint32)((uint32)0U << 8U)   /* T2EDELAY */
                      | (uint32)((uint32)0U << 0U);  /* C2EDELAY */

    /** - Data Format 0 */
    mibspiREG2->FMT0 = (uint32)((uint32)0U << 24U)  /* wdelay */
                     | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                     | (uint32)((uint32)0U << 22U)  /* parity enable */
                     | (uint32)((uint32)0U << 21U)  /* wait on enable */
                     | (uint32)((uint32)0U << 20U)  /* shift direction */
                     | (uint32)((uint32)0U << 17U)  /* clock polarity */
                     | (uint32)((uint32)0U << 16U)  /* clock phase */
                     | (uint32)((uint32)249U << 8U)  /* baudrate prescale */
                     | (uint32)((uint32)8U << 0U); /* data word length */

    /** - Data Format 1 */
    mibspiREG2->FMT1 = (uint32)((uint32)0U << 24U)  /* wdelay */
                     | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                     | (uint32)((uint32)0U << 22U)  /* parity enable */
                     | (uint32)((uint32)0U << 21U)  /* wait on enable */
                     | (uint32)((uint32)0U << 20U)  /* shift direction */
                     | (uint32)((uint32)0U << 17U)  /* clock polarity */
                     | (uint32)((uint32)0U << 16U)  /* clock phase */
                     | (uint32)((uint32)249U << 8U)  /* baudrate prescale */
                     | (uint32)((uint32)8U << 0U); /* data word length */

    /** - Data Format 2 */
    mibspiREG2->FMT2 = (uint32)((uint32)0U << 24U)  /* wdelay */
                     | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                     | (uint32)((uint32)0U << 22U)  /* parity enable */
                     | (uint32)((uint32)0U << 21U)  /* wait on enable */
                     | (uint32)((uint32)0U << 20U)  /* shift direction */
                     | (uint32)((uint32)0U << 17U)  /* clock polarity */
                     | (uint32)((uint32)0U << 16U)  /* clock phase */
                     | (uint32)((uint32)14U << 8U)  /* baudrate prescale */
                     | (uint32)((uint32)8U << 0U); /* data word length */

    /** - Data Format 3 */
    mibspiREG2->FMT3 = (uint32)((uint32)0U << 24U)  /* wdelay */
                     | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                     | (uint32)((uint32)0U << 22U)  /* parity enable */
                     | (uint32)((uint32)0U << 21U)  /* wait on enable */
                     | (uint32)((uint32)0U << 20U)  /* shift direction */
                     | (uint32)((uint32)0U << 17U)  /* clock polarity */
                     | (uint32)((uint32)0U << 16U)  /* clock phase */
                     | (uint32)((uint32)74U << 8U)  /* baudrate prescale */
                     | (uint32)((uint32)16U << 0U); /* data word length */

    /** - Default Chip Select */
    mibspiREG2->DEF = (uint32)(0xFFU);

    /** - wait for buffer initialization complete before accessing MibSPI registers */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while ((mibspiREG2->FLG & 0x01000000U) != 0U)
    {
    } /* Wait */

    /** enable MIBSPI RAM Parity */
    mibspiREG2->PAR_ECC_CTRL = (mibspiREG2->PAR_ECC_CTRL & 0xFFFFFFF0U) | (0x00000005U);

    /** - initialize transfer groups */
    mibspiREG2->TGCTRL[0U] = (uint32)((uint32)1U << 30U)  /* oneshot */
                           | (uint32)((uint32)0U << 29U)  /* pcurrent reset */
                           | (uint32)((uint32)TRG_ALWAYS << 20U)  /* trigger event */
                           | (uint32)((uint32)TRG_DISABLED << 16U)  /* trigger source */
                           | (uint32)((uint32)0U << 8U);  /* start buffer */

    mibspiREG2->TGCTRL[1U] = (uint32)((uint32)1U << 30U)  /* oneshot */
                           | (uint32)((uint32)0U << 29U)  /* pcurrent reset */
                           | (uint32)((uint32)TRG_ALWAYS << 20U)  /* trigger event */
                           | (uint32)((uint32)TRG_DISABLED << 16U)  /* trigger source */
                           | (uint32)((uint32)1U << 8U);  /* start buffer */

    mibspiREG2->TGCTRL[2U] = (uint32)((uint32)1U << 30U)  /* oneshot */
                           | (uint32)((uint32)0U << 29U)  /* pcurrent reset */
                           | (uint32)((uint32)TRG_ALWAYS << 20U)  /* trigger event */
                           | (uint32)((uint32)TRG_DISABLED << 16U)  /* trigger source */
                           | (uint32)((uint32)(1U+127U) << 8U);  /* start buffer */

    mibspiREG2->TGCTRL[3U] = (uint32)((uint32)1U << 30U)  /* oneshot */
                           | (uint32)((uint32)0U << 29U)  /* pcurrent reset */
                           | (uint32)((uint32)TRG_ALWAYS << 20U)  /* trigger event */
                           | (uint32)((uint32)TRG_DISABLED << 16U)  /* trigger source */
                           | (uint32)((uint32)(1U+127U+1U) << 8U);  /* start buffer */

    mibspiREG2->TGCTRL[4U] = (uint32)((uint32)1U << 30U)  /* oneshot */
                           | (uint32)((uint32)0U << 29U)  /* pcurrent reset */
                           | (uint32)((uint32)TRG_ALWAYS << 20U)  /* trigger event */
                           | (uint32)((uint32)TRG_DISABLED << 16U)  /* trigger source */
                           | (uint32)((uint32)(1U+127U+1U+0U) << 8U);  /* start buffer */

    mibspiREG2->TGCTRL[5U] = (uint32)((uint32)1U << 30U)  /* oneshot */
                           | (uint32)((uint32)0U << 29U)  /* pcurrent reset */
                           | (uint32)((uint32)TRG_ALWAYS << 20U)  /* trigger event */
                           | (uint32)((uint32)TRG_DISABLED << 16U)  /* trigger source */
                           | (uint32)((uint32)(1U+127U+1U+0U+0U) << 8U);  /* start buffer */

    mibspiREG2->TGCTRL[6U] = (uint32)((uint32)1U << 30U)  /* oneshot */
                           | (uint32)((uint32)0U << 29U)  /* pcurrent reset */
                           | (uint32)((uint32)TRG_ALWAYS << 20U)  /* trigger event */
                           | (uint32)((uint32)TRG_DISABLED << 16U)  /* trigger source */
                           | (uint32)((uint32)(1U+127U+1U+0U+0U+0U) << 8U);  /* start buffer */

    mibspiREG2->TGCTRL[7U] = (uint32)((uint32)1U << 30U)  /* oneshot */
                           | (uint32)((uint32)0U << 29U)  /* pcurrent reset */
                           | (uint32)((uint32)TRG_ALWAYS << 20U)  /* trigger event */
                           | (uint32)((uint32)TRG_DISABLED << 16U)  /* trigger source */
                           | (uint32)((uint32)(1U+127U+1U+0U+0U+0U+0U) << 8U);  /* start buffer */


    mibspiREG2->TGCTRL[8U] = (uint32)(1U+127U+1U+0U+0U+0U+0U+0U) << 8U;

    mibspiREG2->LTGPEND = (mibspiREG2->LTGPEND & 0xFFFF00FFU) | (uint32)(((uint32)(1U+127U+1U+0U+0U+0U+0U+0U)-1U) << 8U);

    /** - initialize buffer ram */
    {
        i = 0U;

#if (1U > 0U)
        {

#if (1U > 1U)

            while (i < (1U-1U))
            {
                mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                          | (uint16)((uint16)0U << 12U)  /* chip select hold */
                                          | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                          | (uint16)((uint16)0U << 11U)  /* lock transmission */
                                          | (uint16)((uint16)0U << 8U)  /* data format */
                                          | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_0)) & (uint16)0x00FFU);  /* chip select */
                i++;
            }
#endif
            mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                      | (uint16)((uint16)0U << 12U) /* chip select hold */
                                      | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                      | (uint16)((uint16)0U << 8U)  /* data format */
                                      | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_0)) & (uint16)0x00FFU);  /* chip select */


            i++;
        }
#endif

#if (127U > 0U)
        {

#if (127U > 1U)

            while (i < ((1U+127U)-1U))
            {
                mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                          | (uint16)((uint16)0U << 12U)  /* chip select hold */
                                          | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                          | (uint16)((uint16)0U << 11U)  /* lock transmission */
                                          | (uint16)((uint16)1U << 8U)  /* data format */
                                          | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_0)) & (uint16)0x00FFU);  /* chip select */

                i++;
            }
#endif
            mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                      | (uint16)((uint16)0U << 12U) /* chip select hold */
                                      | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                      | (uint16)((uint16)1U << 8U)  /* data format */
                                      | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_0)) & (uint16)0x00FFU);  /* chip select */

            i++;
        }
#endif

#if (1U > 0U)
        {

#if (1U > 1U)

            while (i < ((1U+127U+1U)-1U))
            {
                mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                          | (uint16)((uint16)0U << 12U)  /* chip select hold */
                                          | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                          | (uint16)((uint16)0U << 11U)  /* lock transmission */
                                          | (uint16)((uint16)1U << 8U)  /* data format */
                                          | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_0)) & (uint16)0x00FFU);  /* chip select */

                i++;
            }
#endif
            mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                      | (uint16)((uint16)0U << 12U) /* chip select hold */
                                      | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                      | (uint16)((uint16)1U << 8U)  /* data format */
                                      | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_0)) & (uint16)0x00FFU);  /* chip select */

            i++;
        }
#endif

#if (0U > 0U)
        {

#if (0U > 1U)

            while (i < ((1U+127U+1U+0U)-1U))
            {
                mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                          | (uint16)((uint16)0U << 12U)  /* chip select hold */
                                          | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                          | (uint16)((uint16)0U << 11U)  /* lock transmission */
                                          | (uint16)((uint16)0U << 8U)  /* data format */
                                          | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_3)) & (uint16)0x00FFU);  /* chip select */

                i++;
            }
#endif
            mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                      | (uint16)((uint16)0U << 12U) /* chip select hold */
                                      | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                      | (uint16)((uint16)0U << 8U)  /* data format */
                                      | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_3)) & (uint16)0x00FFU);  /* chip select */

            i++;
        }
#endif

#if (0U > 0U)
        {

#if (0U > 1U)

            while (i < ((1U+127U+1U+0U+0U)-1U))
            {
                mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                          | (uint16)((uint16)0U << 12U)  /* chip select hold */
                                          | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                          | (uint16)((uint16)0U << 11U)  /* lock transmission */
                                          | (uint16)((uint16)0U << 8U)  /* data format */
                                          | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_4)) & (uint16)0x00FFU);  /* chip select */

                i++;
            }
#endif
            mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                      | (uint16)((uint16)0U << 12U) /* chip select hold */
                                      | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                      | (uint16)((uint16)0U << 8U)  /* data format */
                                      | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_4)) & (uint16)0x00FFU);  /* chip select */

            i++;
        }
#endif

#if (0U > 0U)
        {

#if (0U > 1U)

            while (i < ((1U+127U+1U+0U+0U+0U)-1U))
            {
                mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                          | (uint16)((uint16)0U << 12U)  /* chip select hold */
                                          | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                          | (uint16)((uint16)0U << 11U)  /* lock transmission */
                                          | (uint16)((uint16)0U << 8U)  /* data format */
                                          | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_5)) & (uint16)0x00FFU);  /* chip select */

                i++;
            }
#endif
            mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                      | (uint16)((uint16)0U << 12U) /* chip select hold */
                                      | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                      | (uint16)((uint16)0U << 8U)  /* data format */
                                      | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_5)) & (uint16)0x00FFU);  /* chip select */

            i++;
        }
#endif

#if (0U > 0U)
        {

#if (0U > 1U)

            while (i < ((1U+127U+1U+0U+0U+0U+0U)-1U))
            {
                mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                          | (uint16)((uint16)0U << 12U)  /* chip select hold */
                                          | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                          | (uint16)((uint16)0U << 11U)  /* lock transmission */
                                          | (uint16)((uint16)0U << 8U)  /* data format */
                                          | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_6)) & (uint16)0x00FFU);  /* chip select */

                i++;
            }
#endif
            mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                      | (uint16)((uint16)0U << 12U) /* chip select hold */
                                      | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                      | (uint16)((uint16)0U << 8U)  /* data format */
                                      | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_6)) & (uint16)0x00FFU);  /* chip select */

            i++;
        }
#endif

#if (0U > 0U)
        {

#if (0U > 1U)

            while (i < ((1U+127U+1U+0U+0U+0U+0U+0U)-1U))
            {
                mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                          | (uint16)((uint16)0U << 12U)  /* chip select hold */
                                          | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                          | (uint16)((uint16)0U << 11U)  /* lock transmission */
                                          | (uint16)((uint16)0U << 8U)  /* data format */
                                          | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_7)) & (uint16)0x00FFU);  /* chip select */

                i++;
            }
#endif
            mibspiRAM2->tx[i].control = (uint16)((uint16)4U << 13U)  /* buffer mode */
                                      | (uint16)((uint16)0U << 12U) /* chip select hold */
                                      | (uint16)((uint16)0U << 10U)  /* enable WDELAY */
                                      | (uint16)((uint16)0U << 8U)  /* data format */
                                      | ((uint16)(~((uint16)0xFFU ^ (uint16)CS_7)) & (uint16)0x00FFU);  /* chip select */
            i++;
        }
#endif
    }

    /** - set interrupt levels */
    mibspiREG2->LVL = (uint32)((uint32)0U << 9U)  /* TXINT */
                    | (uint32)((uint32)0U << 8U)  /* RXINT */
                    | (uint32)((uint32)0U << 6U)  /* OVRNINT */
                    | (uint32)((uint32)0U << 4U)  /* BITERR */
                    | (uint32)((uint32)0U << 3U)  /* DESYNC */
                    | (uint32)((uint32)0U << 2U)  /* PARERR */
                    | (uint32)((uint32)0U << 1U)  /* TIMEOUT */
                    | (uint32)((uint32)0U << 0U); /* DLENERR */

    /** - clear any pending interrupts */
    mibspiREG2->FLG |= 0xFFFFU;

    /** - enable interrupts */
    mibspiREG2->INT0 = (mibspiREG2->INT0 & 0xFFFF0000U)
                     | (uint32)((uint32)0U << 9U)  /* TXINT */
                     | (uint32)((uint32)0U << 8U)  /* RXINT */
                     | (uint32)((uint32)0U << 6U)  /* OVRNINT */
                     | (uint32)((uint32)0U << 4U)  /* BITERR */
                     | (uint32)((uint32)0U << 3U)  /* DESYNC */
                     | (uint32)((uint32)0U << 2U)  /* PARERR */
                     | (uint32)((uint32)0U << 1U)  /* TIMEOUT */
                     | (uint32)((uint32)0U << 0U); /* DLENERR */

    /** @b initialize @b MIBSPI2 @b Port */

    /** - MIBSPI2 Port output values */
    mibspiREG2->PC3 = (uint32)((uint32)1U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)0U << 9U)  /* CLK */
                    | (uint32)((uint32)0U << 10U)  /* SIMO */
                    | (uint32)((uint32)0U << 11U); /* SOMI */

    /** - MIBSPI2 Port direction */
    mibspiREG2->PC1 = (uint32)((uint32)1U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)1U << 9U)  /* CLK */
                    | (uint32)((uint32)1U << 10U)  /* SIMO */
                    | (uint32)((uint32)0U << 11U); /* SOMI */

    /** - MIBSPI2 Port open drain enable */
    mibspiREG2->PC6 = (uint32)((uint32)0U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)0U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)0U << 9U)  /* CLK */
                    | (uint32)((uint32)0U << 10U)  /* SIMO */
                    | (uint32)((uint32)0U << 11U); /* SOMI */


    /** - MIBSPI2 Port pullup / pulldown selection */
    mibspiREG2->PC8 = (uint32)((uint32)1U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)1U << 8U)  /* ENA */
                    | (uint32)((uint32)1U << 9U)  /* CLK */
                    | (uint32)((uint32)1U << 10U)  /* SIMO */
                    | (uint32)((uint32)1U << 11U); /* SOMI */


    /** - MIBSPI2 Port pullup / pulldown enable*/
    mibspiREG2->PC7 = (uint32)((uint32)0U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)0U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)0U << 9U)  /* CLK */
                    | (uint32)((uint32)0U << 10U)  /* SIMO */
                    | (uint32)((uint32)0U << 11U); /* SOMI */


    /* MIBSPI2 set all pins to functional */
    mibspiREG2->PC0 = (uint32)((uint32)0U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)0U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)1U << 9U)  /* CLK */
                    | (uint32)((uint32)1U << 10U)  /* SIMO */
                    | (uint32)((uint32)1U << 11U); /* SOMI */

    /** - Finally start MIBSPI2 */
    mibspiREG2->GCR1 = (mibspiREG2->GCR1 & 0xFEFFFFFFU) | 0x01000000U;





/* USER CODE BEGIN (3) */
/* USER CODE END */

}

/* SourceId : MIBSPI_SourceId_002 */
/* DesignId :  */
/* Requirements :  */
/** @fn boolean mibspiIsBuffInitialized(mibspiBASE_t *mibspi)
*   @brief Checks if Mibspi buffer is initialized.
*   @param[in] mibspi   - Mibspi module base address
*
*   This function brings Mibspi module out of reset.
*/
boolean mibspiIsBuffInitialized(mibspiBASE_t *mibspi)
{
    volatile boolean status;
/* USER CODE BEGIN (4) */
/* USER CODE END */

	if((mibspi->FLG & 0x01000000U) != 0x01000000U)
	{
		status = TRUE;
	}
	else
	{
		status = FALSE;
	}

/* USER CODE BEGIN (5) */
/* USER CODE END */
    return (status);
}

/* SourceId : MIBSPI_SourceId_003 */
/* DesignId :  */
/* Requirements :  */
/** @fn void mibspiOutofReset(mibspiBASE_t *mibspi)
*   @brief Bring Mibspi Module Out of Reset
*   @param[in] mibspi   - Mibspi module base address
*
*   This function brings Mibspi module out of reset.
*/
void mibspiOutofReset(mibspiBASE_t *mibspi)
{
/* USER CODE BEGIN (6) */
/* USER CODE END */

    mibspi->GCR0 |= 0x1U;

/* USER CODE BEGIN (7) */
/* USER CODE END */
}

/* SourceId : MIBSPI_SourceId_004 */
/* DesignId :  */
/* Requirements :  */
/** @fn void mibspiReset(mibspiBASE_t *mibspi)
*   @brief Take Mibspi Module to Reset
*   @param[in] mibspi   - Mibspi module base address
*
*   This function takes Mibspi module to reset.
*/
void mibspiReset(mibspiBASE_t *mibspi)
{
/* USER CODE BEGIN (8) */
/* USER CODE END */

    mibspi->GCR0 = 0x0U;

/* USER CODE BEGIN (9) */
/* USER CODE END */
}

/* SourceId : MIBSPI_SourceId_005 */
/* DesignId : MIBSPI_DesignId_002 */
/* Requirements : HL_CONQ_MIBSPI_SR10 */
/** @fn void mibspiSetFunctional(mibspiBASE_t *mibspi, uint32 port)
*   @brief Change functional behavior of pins at runtime.
*   @param[in] mibspi   - mibspi module base address
*   @param[in] port  - Value to write to PC0 register
*
*   Change the value of the PC0 register at runtime, this allows to
*   dynamically change the functionality of the MIBSPI pins between functional
*   and GIO mode.
*/
void mibspiSetFunctional(mibspiBASE_t *mibspi, uint32 port)
{
/* USER CODE BEGIN (10) */
/* USER CODE END */

    mibspi->PC0 = port;

/* USER CODE BEGIN (11) */
/* USER CODE END */
}

/* SourceId : MIBSPI_SourceId_006 */
/* DesignId : MIBSPI_DesignId_003 */
/* Requirements : HL_CONQ_MIBSPI_SR11 */
/** @fn void mibspiSetData(mibspiBASE_t *mibspi, uint32 group, uint16 * data)
*   @brief Set Buffer Data
*   @param[in] mibspi   - Spi module base address
*   @param[in] group - Transfer group (0..7)
*   @param[in] data  - new data for transfer group
*
*   This function updates the data for the specified transfer group,
*   the length of the data must match the length of the transfer group.
*/
void mibspiSetData(mibspiBASE_t *mibspi, uint32 group, uint16 * data)
{
/* USER CODE BEGIN (12) */
/* USER CODE END */

    mibspiRAM_t *ram    = mibspi == mibspiREG1 ? mibspiRAM1 : 
	                     (mibspi == mibspiREG2 ? mibspiRAM2 : 
						 (mibspi == mibspiREG3 ? mibspiRAM3 : 
						 (mibspi == mibspiREG4 ? mibspiRAM4 : mibspiRAM5)));
    uint32 start  = (mibspi->TGCTRL[group] >> 8U) & 0xFFU;
    uint32 end    = (group == 7U) ? (((mibspi->LTGPEND & 0x00007F00U) >> 8U) + 1U) : ((mibspi->TGCTRL[group+1U] >> 8U) & 0xFFU);

    if (end == 0U) {end = 128U;}

    while (start < end)
    {
    /*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Valid non NULL input parameters are only allowed in this driver" */
        ram->tx[start].data = *data;
        data++;
        start++;
    }
/* USER CODE BEGIN (13) */
/* USER CODE END */
}


/* SourceId : MIBSPI_SourceId_007 */
/* DesignId : MIBSPI_DesignId_004 */
/* Requirements : HL_CONQ_MIBSPI_SR12 */
/** @fn void mibspiGetData(mibspiBASE_t *mibspi, uint32 group, uint16 * data)
*   @brief Retrieves Buffer Data from receive buffer
*   @param[in]  mibspi   - Spi module base address
*   @param[in]  group - Transfer group (0..7)
*   @param[out] data  - pointer to data array
*
*   @return error flags from data buffer, if there was a receive error on
*           one of the buffers this will be reflected in the return value.
*
*   This function transfers the data from the specified transfer group receive
*   buffers to the data array,  the length of the data must match the length 
*   of the transfer group.
*/
uint32 mibspiGetData(mibspiBASE_t *mibspi, uint32 group, uint16 * data)
{
/* USER CODE BEGIN (14) */
/* USER CODE END */

    mibspiRAM_t *ram    = mibspi == mibspiREG1 ? mibspiRAM1 : 
	                     (mibspi == mibspiREG2 ? mibspiRAM2 : 
						 (mibspi == mibspiREG3 ? mibspiRAM3 : 
						 (mibspi == mibspiREG4 ? mibspiRAM4 : mibspiRAM5)));
    uint32 start  = (mibspi->TGCTRL[group] >> 8U) & 0xFFU;
    uint32 end    = (group == 7U) ? (((mibspi->LTGPEND & 0x00007F00U) >> 8U) + 1U) : ((mibspi->TGCTRL[group+1U] >> 8U) & 0xFFU);
    uint16 mibspiFlags  = 0U;
	uint32 ret;
    if (end == 0U) {end = 128U;}

    while (start < end)
    {
        mibspiFlags  |= ram->rx[start].flags;
        /*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Valid non NULL input parameters are only allowed in this driver" */
        *data = ram->rx[start].data;
        data++;
        start++;
    }

	ret = ((uint32)mibspiFlags >> 8U) & 0x5FU;
/* USER CODE BEGIN (15) */
/* USER CODE END */

    return ret;
}


/* SourceId : MIBSPI_SourceId_008 */
/* DesignId : MIBSPI_DesignId_005 */
/* Requirements : HL_CONQ_MIBSPI_SR13 */
/** @fn void mibspiTransfer(mibspiBASE_t *mibspi, uint32 group)
*   @brief Transmit Transfer Group
*   @param[in] mibspi   - Spi module base address
*   @param[in] group - Transfer group (0..7)
*
*   Initiates a transfer for the specified transfer group.
*/
void mibspiTransfer(mibspiBASE_t *mibspi, uint32 group)
{
/* USER CODE BEGIN (16) */
/* USER CODE END */

    mibspi->TGCTRL[group] |= 0x80000000U;

/* USER CODE BEGIN (17) */
/* USER CODE END */
}


/* SourceId : MIBSPI_SourceId_009 */
/* DesignId : MIBSPI_DesignId_006 */
/* Requirements : HL_CONQ_MIBSPI_SR14 */
/** @fn boolean mibspiIsTransferComplete(mibspiBASE_t *mibspi, uint32 group)
*   @brief Check for Transfer Group Ready
*   @param[in] mibspi   - Spi module base address
*   @param[in] group - Transfer group (0..7)
*
*   @return TRUE is transfer complete, otherwise FALSE.
*
*   Checks to see if the transfer for the specified transfer group
*   has finished.
*/
boolean mibspiIsTransferComplete(mibspiBASE_t *mibspi, uint32 group)
{
    boolean status;

/* USER CODE BEGIN (18) */
/* USER CODE END */

    if(((((mibspi->TGINTFLG & 0xFFFF0000U) >> 16U)>> group) & 1U) == 1U)
    {
       mibspi->TGINTFLG = (mibspi->TGINTFLG & 0x0000FFFFU) | ((uint32)((uint32)1U << group) << 16U);
       status = TRUE;
    }
    else
    {
       status = FALSE;
    }
    
/* USER CODE BEGIN (19) */
/* USER CODE END */
    
    return (status);
}


/* SourceId : MIBSPI_SourceId_010 */
/* DesignId : MIBSPI_DesignId_009 */
/* Requirements : HL_CONQ_MIBSPI_SR17 */
/** @fn void mibspiEnableLoopback(mibspiBASE_t *mibspi, loopBackType_t Loopbacktype)
*   @brief Enable Loopback mode for self test
*   @param[in] mibspi        - Mibspi module base address
*   @param[in] Loopbacktype  - Digital or Analog
*
*   This function enables the Loopback mode for self test.
*/
void mibspiEnableLoopback(mibspiBASE_t *mibspi, loopBackType_t Loopbacktype)
{
/* USER CODE BEGIN (20) */
/* USER CODE END */
    
    /* Clear Loopback incase enabled already */
    mibspi->IOLPKTSTCR = 0U;
    
    /* Enable Loopback either in Analog or Digital Mode */
    mibspi->IOLPKTSTCR = (uint32)0x00000A00U
                       | (uint32)((uint32)Loopbacktype << 1U);
    
/* USER CODE BEGIN (21) */
/* USER CODE END */
}

/* SourceId : MIBSPI_SourceId_011 */
/* DesignId : MIBSPI_DesignId_010 */
/* Requirements : HL_CONQ_MIBSPI_SR18 */
/** @fn void mibspiDisableLoopback(mibspiBASE_t *mibspi)
*   @brief Enable Loopback mode for self test
*   @param[in] mibspi        - Mibspi module base address
*
*   This function disable the Loopback mode.
*/
void mibspiDisableLoopback(mibspiBASE_t *mibspi)
{
/* USER CODE BEGIN (22) */
/* USER CODE END */
    
    /* Disable Loopback Mode */
    mibspi->IOLPKTSTCR = 0x00000500U;
    
/* USER CODE BEGIN (23) */
/* USER CODE END */
}

/* SourceId : MIBSPI_SourceId_012 */
/* DesignId : MIBSPI_DesignId_011 */
/* Requirements : HL_CONQ_MIBSPI_SR21 */
/** @fn void mibspiPmodeSet(mibspiBASE_t *mibspi, mibspiPmode_t Pmode, mibspiDFMT_t DFMT)
*   @brief Set the Pmode for the selected Data Format register
*   @param[in] mibspi   - Mibspi module base address
*   @param[in] Pmode    - Mibspi Parellel mode
*                            PMODE_NORMAL    
*                            PMODE_2_DATALINE
*                            PMODE_4_DATALINE
*                            PMODE_8_DATALINE
*   @param[in] DFMT     - Mibspi Data Format register
*                            DATA_FORMAT0
*                            DATA_FORMAT1
*                            DATA_FORMAT2
*                            DATA_FORMAT3
*
*   This function sets the Pmode for the selected Data Format register.
*/
void mibspiPmodeSet(mibspiBASE_t *mibspi, mibspiPmode_t Pmode, mibspiDFMT_t DFMT)
{
    uint32 pmctrl_reg;
    /* Set the Pmode for the selected Data Format register */
    pmctrl_reg     = (mibspi->PMCTRL & (~(uint32)((uint32)0xFFU << (8U * DFMT))));
    mibspi->PMCTRL = (pmctrl_reg | (uint32)((uint32)Pmode <<  ((8U * DFMT))));
    
}

/* SourceId : MIBSPI_SourceId_013 */
/* DesignId : MIBSPI_DesignId_007 */
/* Requirements : HL_CONQ_MIBSPI_SR15 */
/** @fn void mibspiEnableGroupNotification(mibspiBASE_t *mibspi, uint32 group, uint32 level)
*   @brief Enable Transfer Group interrupt
*   @param[in] mibspi   - Spi module base address
*   @param[in] group - Transfer group (0..7)
*   @param[in] level - Interrupt level
*
*   This function enables the transfer group finished interrupt.
*/
void mibspiEnableGroupNotification(mibspiBASE_t *mibspi, uint32 group, uint32 level)
{
/* USER CODE BEGIN (24) */
/* USER CODE END */

    if (level != 0U)
    {
        mibspi->TGITLVST = (mibspi->TGITLVST & 0x0000FFFFU) | (uint32)((uint32)((uint32)1U << group) << 16U);
    }
    else
    {
        mibspi->TGITLVCR = (mibspi->TGITLVCR & 0x0000FFFFU) | (uint32)((uint32)((uint32)1U << group) << 16U);
    }
    mibspi->TGITENST = (mibspi->TGITENST & 0x0000FFFFU) | (uint32)((uint32)((uint32)1U << group) << 16U);

/* USER CODE BEGIN (25) */
/* USER CODE END */
}

/* SourceId : MIBSPI_SourceId_014 */
/* DesignId : MIBSPI_DesignId_008 */
/* Requirements : HL_CONQ_MIBSPI_SR16 */
/** @fn void mibspiDisableGroupNotification(mibspiBASE_t *mibspi, uint32 group)
*   @brief Disable Transfer Group interrupt
*   @param[in] mibspi   - Spi module base address
*   @param[in] group - Transfer group (0..7)
*
*   This function disables the transfer group finished interrupt.
*/
void mibspiDisableGroupNotification(mibspiBASE_t *mibspi, uint32 group)
{
/* USER CODE BEGIN (26) */
/* USER CODE END */

    mibspi->TGITENCR = (mibspi->TGITENCR & 0x0000FFFFU) | (uint32)((uint32)((uint32)1U << group) << 16U);

/* USER CODE BEGIN (27) */
/* USER CODE END */
}


/* SourceId : MIBSPI_SourceId_016 */
/* DesignId : MIBSPI_DesignId_012 */
/* Requirements : HL_CONQ_MIBSPI_SR23 */
/** @fn void mibspi2GetConfigValue(mibspi_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*    @param[in] *config_reg: pointer to the struct to which the initial or current 
*                           value of the configuration registers need to be stored
*    @param[in] type:     whether initial or current value of the configuration registers need to be stored
*                        - InitialValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*                        - CurrentValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') 
*   of the configuration registers to the struct pointed by config_reg
*
*/
void mibspi2GetConfigValue(mibspi_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {
        config_reg->CONFIG_GCR1       = MIBSPI2_GCR1_CONFIGVALUE; 
        config_reg->CONFIG_INT0       = MIBSPI2_INT0_CONFIGVALUE; 
        config_reg->CONFIG_LVL        = MIBSPI2_LVL_CONFIGVALUE; 
        config_reg->CONFIG_PCFUN      = MIBSPI2_PCFUN_CONFIGVALUE; 
        config_reg->CONFIG_PCDIR      = MIBSPI2_PCDIR_CONFIGVALUE; 
        config_reg->CONFIG_PCPDR      = MIBSPI2_PCPDR_CONFIGVALUE; 
        config_reg->CONFIG_PCDIS      = MIBSPI2_PCDIS_CONFIGVALUE; 
        config_reg->CONFIG_PCPSL      = MIBSPI2_PCPSL_CONFIGVALUE; 
        config_reg->CONFIG_DELAY      = MIBSPI2_DELAY_CONFIGVALUE; 
        config_reg->CONFIG_FMT0       = MIBSPI2_FMT0_CONFIGVALUE; 
        config_reg->CONFIG_FMT1       = MIBSPI2_FMT1_CONFIGVALUE; 
        config_reg->CONFIG_FMT2       = MIBSPI2_FMT2_CONFIGVALUE; 
        config_reg->CONFIG_FMT3       = MIBSPI2_FMT3_CONFIGVALUE; 
        config_reg->CONFIG_MIBSPIE    = MIBSPI2_MIBSPIE_CONFIGVALUE; 
        config_reg->CONFIG_LTGPEND    = MIBSPI2_LTGPEND_CONFIGVALUE; 
        config_reg->CONFIG_TGCTRL[0U] = MIBSPI2_TGCTRL0_CONFIGVALUE;
        config_reg->CONFIG_TGCTRL[1U] = MIBSPI2_TGCTRL1_CONFIGVALUE;
        config_reg->CONFIG_TGCTRL[2U] = MIBSPI2_TGCTRL2_CONFIGVALUE;
        config_reg->CONFIG_TGCTRL[3U] = MIBSPI2_TGCTRL3_CONFIGVALUE;
        config_reg->CONFIG_TGCTRL[4U] = MIBSPI2_TGCTRL4_CONFIGVALUE;
        config_reg->CONFIG_TGCTRL[5U] = MIBSPI2_TGCTRL5_CONFIGVALUE;
        config_reg->CONFIG_TGCTRL[6U] = MIBSPI2_TGCTRL6_CONFIGVALUE;
        config_reg->CONFIG_TGCTRL[7U] = MIBSPI2_TGCTRL7_CONFIGVALUE;
        config_reg->CONFIG_PAR_ECC_CTRL   = MIBSPI2_PAR_ECC_CTRL_CONFIGVALUE; 
    }
    else
    {
    /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Register read back support" */
        config_reg->CONFIG_GCR1       = mibspiREG2->GCR1;
        config_reg->CONFIG_INT0       = mibspiREG2->INT0;
        config_reg->CONFIG_LVL        = mibspiREG2->LVL;
        config_reg->CONFIG_PCFUN      = mibspiREG2->PC0;
        config_reg->CONFIG_PCDIR      = mibspiREG2->PC1;
        config_reg->CONFIG_PCPDR      = mibspiREG2->PC6;
        config_reg->CONFIG_PCDIS      = mibspiREG2->PC7;
        config_reg->CONFIG_PCPSL      = mibspiREG2->PC8;
        config_reg->CONFIG_DELAY      = mibspiREG2->DELAY;
        config_reg->CONFIG_FMT0       = mibspiREG2->FMT0;
        config_reg->CONFIG_FMT1       = mibspiREG2->FMT1;
        config_reg->CONFIG_FMT2       = mibspiREG2->FMT2;
        config_reg->CONFIG_FMT3       = mibspiREG2->FMT3;
        config_reg->CONFIG_MIBSPIE    = mibspiREG2->MIBSPIE;
        config_reg->CONFIG_LTGPEND    = mibspiREG2->LTGPEND;
        config_reg->CONFIG_TGCTRL[0U] = mibspiREG2->TGCTRL[0U];
        config_reg->CONFIG_TGCTRL[1U] = mibspiREG2->TGCTRL[1U];
        config_reg->CONFIG_TGCTRL[2U] = mibspiREG2->TGCTRL[2U];
        config_reg->CONFIG_TGCTRL[3U] = mibspiREG2->TGCTRL[3U];
        config_reg->CONFIG_TGCTRL[4U] = mibspiREG2->TGCTRL[4U];
        config_reg->CONFIG_TGCTRL[5U] = mibspiREG2->TGCTRL[5U];
        config_reg->CONFIG_TGCTRL[6U] = mibspiREG2->TGCTRL[6U];
        config_reg->CONFIG_TGCTRL[7U] = mibspiREG2->TGCTRL[7U];
        config_reg->CONFIG_PAR_ECC_CTRL   = mibspiREG2->PAR_ECC_CTRL;
    }
}










