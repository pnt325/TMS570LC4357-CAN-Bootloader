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
//! \file   ~modules/ecmp/src/float32/champion/ecmp.h
//! \brief  Header file for the ECMP Module
//!
//! (C) Copyright 2011, Texas Instruments, Inc.

// **************************************************************************
// the includes

//#include "solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/src/drv.h"
#include "sys_common.h"
#include "drivers/spi/src/32b/hercules/champion/spi.h"
#include "drivers/sci/src/32b/hercules/champion/sci.h"
#include "drivers/rti/src/32b/hercules/champion/rti.h"
#include <stdio.h> /* sscanf */


#ifndef ECMP_H_
#define ECMP_H_

// **************************************************************************
// the defines

/** @def RD_DEV_ID
*   @brief Device ID module register ecmp reg alias
*
*   This register is used by the ecmp driver to access the Device ID module register.
*/
#define RD_DEV_ID 0x0600U


/** @def RD_DEV_REV
*   @brief Device Revision module register ecmp reg alias
*
*   This register is used by the ecmp driver to access the Device Revision module register.
*/
#define RD_DEV_REV 0x0C00U


/** @def RD_SAFETY_STAT1
*   @brief SAFETY_STAT1 ecmp reg alias
*
*   This register is used by the ecmp driver to access the SAFETY_STAT1 module register.
*/
#define RD_SAFETY_STAT1 0x2400U

/** @def RD_SAFETY_STAT2
*   @brief SAFETY_STAT2 ecmp reg alias
*
*   This register is used by the ecmp driver to access the SAFETY_STAT2 module register.
*/
#define RD_SAFETY_STAT2 0xC500U

/** @def RD_SAFETY_STAT3
*   @brief SAFETY_STAT3 ecmp reg alias
*
*   This register is used by the ecmp driver to access the SAFETY_STAT3 module register.
*/
#define RD_SAFETY_STAT3 0xA300U

/** @def RD_SAFETY_STAT4
*   @brief SAFETY_STAT4 ecmp reg alias
*
*   This register is used by the ecmp driver to access the SAFETY_STAT4 module register.
*/
#define RD_SAFETY_STAT4 0xA500U

/** @def RD_SAFETY_STAT5
*   @brief SAFETY_STAT5 ecmp reg alias
*
*   This register is used by the ecmp driver to access the SAFETY_STAT5 module register.
*/
#define RD_SAFETY_STAT5 0xC000U

/** @def RD_SAFETY_ERR_CFG
*   @brief SAFETY_ERR_CFG ecmp reg alias
*
*   This register is used by the ecmp driver to access the SAFETY_ERR_CFG module register.
*/
#define RD_SAFETY_ERR_CFG 0x3000U

/** @def RD_SAFETY_ERR_STAT
*   @brief SAFETY_ERR_STAT ecmp reg alias
*
*   This register is used by the ecmp driver to access the SAFETY_ERR_STAT module register.
*/
#define RD_SAFETY_ERR_STAT 0xAA00U

/** @def RD_SAFETY_PWD_THR_CFG
*   @brief SAFETY_PWD_THR_CFG ecmp reg alias
*
*   This register is used by the ecmp driver to access the SAFETY_PWD_THR_CFG module register.
*/
#define RD_SAFETY_PWD_THR_CFG 0x3900U


#define RD_SAFETY_CHECK_CTRL 0x4400U
#define RD_SAFETY_BIST_CTRL 0x3C00U
#define RD_WD_OPEN_WIN_CFG 0x2E00U
#define RD_WD_CLOSE_WIN_CFG 0x0500U
#define RD_WDT_TOKEN 0x3600U
#define RD_WDT_STATUS 0x4E00U
#define RD_DEV_STAT 0x1100U
#define RD_VMON_STAT_1 0x1200U
#define RD_VMON_STAT_2 0xA600U
#define RD_SENS_CTRL 0x5600U
#define RD_SAFETY_FUNC_CFG 0x3A00U
#define RD_SAFE_CFG_CRC 0x5A00U
#define RD_DIAG_CFG_CTRL 0xDD00U
#define RD_DIAG_MUX_SEL 0xAC00U
#define RD_SAFETY_ERR_PWM_H 0xD700U
#define RD_SAFETY_ERR_PWM_L 0x5900U
#define RD_WDT_TOKEN_FDBCK 0x7800U

/**************************************************/
/************* write definitions ******************/
#define SW_UNLOCK 0xBBU //0xBBAAU
#define SW_LOCK 0xBDU //0xBD55U
#define WR_CAN_STBY 0x7DU
#define WR_ERR_CFG 0xDBU
#define WR_ERR_STAT 0xA9U
#define WR_PWD_CFG 0x99U
#define WR_CHK_CTRL 0x93U
#define WR_BIST_CTRL 0x9FU
#define WR_OPEN_WD 0xEDU
#define WR_CLOSE_WD 0x09U
#define WR_ANSWR 0xE1U
#define WR_SENS 0x7BU
#define WR_FUNC_CFG 0x35U
#define WR_CRC 0x63U
#define WR_DIAG_CFG 0xCCU
#define WR_MUX 0xC9U
#define WR_PWM_H 0xD8U
#define WR_PWM_L 0x7EU
#define WR_TOKEN 0x77U

/**************************************************/

#define SCITXREADY (scilinREG->FLR & SCI_TX_INT)
#define SCIRXREADY (scilinREG->FLR & SCI_RX_INT)
#define SCITD (scilinREG->TD)
#define SCIRD (scilinREG->RD)

// **************************************************************************
// the typedefs

/** @enum WDWindow_t
*   @brief WD window status
*/
typedef enum
{
    ECMP_WINDOW_OPEN,
    ECMP_WINDOW_CLOSE
} WDWindow_t;


/** @enum ecmpIsInActiveState_t
*   @brief ecmp state
*/
typedef enum
{
    ECMP_INACTIVE,
    ECMP_ENADRV,
    ECMP_SETWATD,
    ECMP_CLRERR,
    ECMP_ACTIVE
} ecmpIsInActiveState_t;

/** @enum command_t
*   @brief for command line branches
*/
typedef enum
{
    ECMP_CLEAR,
    ECMP_ERRORPIN,
    ECMP_ERRORPININIT,
    ECMP_READ,
    ECMP_WRITE,
    ECMP_WDOPCL,
    ECMP_WDQA,
    ECMP_WDOC,
    ECMP_HELP,
    ECMP_STATE,
    ECMP_WDTFB,
    ECMP_TEST,
    ECMP_WRITEACCESS,
    ECMP_ESM,
    ECMP_GOTOACTIVESTATE,
    ECMP_UNKNOWN
} command_t;

/** @enum command_t
*   @brief used to store variables - to be modified
*/
typedef struct
{
	command_t command;
	command_t secondcommand;
	command_t thirdcommand;
	command_t storage;
} commandline_t;

typedef struct
{
	uint16_t ecmpReadRegAlias[27];
	int8_t **ecmpReg;
	uint16_t ecmpModifyRegAlias1[15];
	uint16_t ecmpModifyRegAlias2[15];
	uint16_t EcmpRegisterValues[27 / sizeof(uint16_t)];
	uint32_t ecmRegisterArrayLength;
	uint32_t ecmpRegisterLength;
	WDWindow_t wdWindow;
	uint32_t trgPulseOpen;
	uint32_t trgPulseClose;
	ecmpIsInActiveState_t ecmpIsInActiveState;
	uint32_t conversion;
	uint16_t SPI2_RXDATA;
	int32_t SP2_Complete;
	int32_t Err_Count;
	int32_t Curr_Sta;
	uint32_t k;
	uint32_t index;
	uint8_t value;
	uint8_t cnt;
	uint16_t answer[8];
	uint32_t token;
	uint32_t tOpen;
	uint32_t tClose;
	uint8_t dataStr[80];
	commandline_t commandlinememory;
	int8_t str[128];
	int16_t length;
	va_list argList;
	uint8_t c_get;
	uint8_t DiagFlag;
} ECMP_Obj;

typedef ECMP_Obj *ECMP_handle;

// **************************************************************************
// the function prototypes

ECMP_handle ECMPInit(void *pMemory, const size_t numBytes);
void ECMPSetup(ECMP_handle ecmpHandle);



/** @fn void PutText(ECMP_handle ecmpHandle, int8_t *text)
*   @brief Sends a string of characters over SCI
*
*	@param[in]	ecmpHandle	Handle for the ECMP Module
*   @param[in]  text		The string of characters to send
*/
inline void PutText(ECMP_handle ecmpHandle, int8_t *text)
{
	while(*text != 0)
	{
		while(!SCITXREADY);
		SCITD = *text++;
	}
}

/** @fn void PutChar(ECMP_handle ecmpHandle, uint8_t c)
*   @brief Sends a character over SCI
*
*	@param[in]	ecmpHandle	Handle for the ECMP Module
*   @param[in]  c			The character to send
*/
inline void PutChar(ECMP_handle ecmpHandle, uint8_t c)
{
	while (!SCITXREADY);
    SCITD = c;
}

/** @fn uint8_t GetChar(ECMP_handle ecmpHandle)
*   @brief		Gets a character from the SCI Receive Buffer if one is available
*
*	@param[in]	ecmpHandle	Handle for the ECMP Module
*	@return		The character in the receive buffer, if one is available. If not, 0.
*/
inline uint8_t GetChar(ECMP_handle ecmpHandle)
{
   if (SCIRXREADY)
     return (SCIRD);
   else
     return 0;
}

/** @fn void ecmpRegToTerminal(void)
*   @brief sends ecmp register to terminal
*
*   Sends external companion register to terminal
*   sciInit() has to be launched before calling
*   this function
*/
inline void ecmpRegToTerminal(ECMP_handle ecmpHandle)
{
	ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;

    sciSend(scilinREG, 35, (uint8_t*) "Safety companion registers are:\r\n\n");

    for(ecmp->cnt = 0; ecmp->cnt < ecmp->ecmpRegisterLength; ecmp->cnt++)
    {
        snprintf((int8_t*)ecmp->dataStr, sizeof(ecmp->dataStr), "%-20s 0x%02X\r\n",
        		ecmp->ecmpReg[ecmp->cnt], (ecmp->EcmpRegisterValues[ecmp->cnt] & 0xFF));
        sciSend(scilinREG, strlen((const int8_t *) ecmp->dataStr),  (uint8_t *)ecmp->dataStr);
    }
}

/** @fn void ecmpReadRegisters(void)
*   @brief reads out ecmp registers
*
*
*   Reads out external companion registers
*   and stores them
*/
inline void ecmpReadRegisters(ECMP_handle ecmpHandle)
{
	ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;

    for(ecmp->k = 0; ecmp->k < ecmp->ecmRegisterArrayLength; ecmp->k++)
    {
        spiREG2->DAT1 = ecmp->ecmpReadRegAlias[ecmp->k];//read RD_SAFETY_STAT_5
        while((spiREG2->FLG & 0x100)!=0x100);
        ecmp->EcmpRegisterValues[ecmp->index] = (spiREG2->BUF);

        ecmp->index++;
    }

    ecmpRegToTerminal(ecmpHandle);
}

/** @fn unsigned short ecmpReadRegister(unsigned short regname)
*   @brief reads out ecmp register
*
*   @param[in]  regname - register alias
*   @return     register value
*
*   Reads out external companion register
*   value, removes status bits and returns
*   register value
*/
inline uint16_t ecmpReadRegister(ECMP_handle ecmpHandle, uint16_t regname)
{
	ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;

    spiREG2->DAT1 = regname;//read RD_SAFETY_STAT_5
    while((spiREG2->FLG & 0x100)!=0x100);
    ecmp->SPI2_RXDATA = (spiREG2->BUF) & 0xFF;

    return ecmp->SPI2_RXDATA;
}

/** @fn void ecmpSetRegister(unsigned short regname, unsigned short regbits)
*   @brief sets value in ecmp register
*
*   @param[in]  regname
*   @param[in] regbits
*
*   writes a defined value to companion register
*/
inline void ecmpSetRegister(ECMP_handle ecmpHandle, uint16_t regname, uint16_t regbits)
{
	ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;

    spiREG2->DAT1 = (regname << 8) | regbits;//read RD_SAFETY_STAT_5
    while((spiREG2->FLG & 0x100)!=0x100);
    ecmp->SPI2_RXDATA = (spiREG2->BUF);
}

inline uint16_t ecmpGetWriteAccess(ECMP_handle ecmpHandle)
{
	ecmpSetRegister(ecmpHandle, SW_UNLOCK,   0xAAU);
	ecmpSetRegister(ecmpHandle, WR_CHK_CTRL, 0x02U);
	ecmpSetRegister(ecmpHandle, WR_ERR_CFG,  0x00U);

	if (((ecmpReadRegister(ecmpHandle, RD_SAFETY_CHECK_CTRL) & 0x02) |
		 (ecmpReadRegister(ecmpHandle, RD_SAFETY_ERR_CFG) & 0x00)) == 0x02)
	{
	 sciSend(scilinREG, 22, (uint8_t *)"registers unlocked..\r\n");

	 return 1;
	}
	else
	{
	 return 0;
	}
}

/** @fn void ecmpConnectSysClock (void)
*   @brief multiplexes ecmp clock to diag out pin
*/
inline void ecmpConnectSysClock (ECMP_handle ecmpHandle)
{
 ecmpSetRegister(ecmpHandle, WR_DIAG_CFG, 0x81); /* MUX_EN +Digital MUX Mode */
 ecmpSetRegister(ecmpHandle, WR_MUX, 0x11); /* switch SYS_CLK to DIAG_OUT pin */
}

 /** @fn void ecmpConnectWDClock (void)
 *   @brief multiplexes wd clock to diag out pin
 */
inline void ecmpConnectWDClock (ECMP_handle ecmpHandle)
{
 ecmpSetRegister(ecmpHandle, WR_DIAG_CFG, 0x81); /* MUX_EN +Digital MUX Mode */
 ecmpSetRegister(ecmpHandle, WR_MUX, 0x13); /* switch WD_CLK to DIAG_OUT pin */
}

/** @fn unsigned ecmpClearErrorCnt(void)
*   @brief clears ecmp error count
*
*   @return 1 when successfully cleared, otherwise 0
*
*   clears external companion error count
*   in the Safety Error Stat register, returns 1 if
*   register was cleared successfully.
*/
inline uint16_t ecmpClearErrorCnt(ECMP_handle ecmpHandle)
{
    ecmpSetRegister(ecmpHandle, WR_ERR_STAT, 0x00);

    if(ecmpReadRegister(ecmpHandle, RD_SAFETY_ERR_STAT)==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/** @fn unsigned ecmpModifyRegister(unsigned short regname, unsigned char regbits, unsigned char setbit)
*   @brief modifies ecmp register and checks them
*
*   @param[in]  regname - register alias
*   @param[in]  regbits - bits to set / clear
*   @param[in]  setbit - 1 to set bits, 0 to clear bits
*
*   @return 1 if successfully modified register, otherwise 0
*
*   reads ecmp register modifies them and checks for
*   successful operation. Returns 1 if values are set
*   correctly. If failed, 0 will be returned.
*/
inline uint32_t ecmpModifyRegister(ECMP_handle ecmpHandle, uint16_t regname, uint8_t regbits, uint8_t setbit)
{
	ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;

    /* find index for regname in ecmpModifyRegAlias[][] */
    for(ecmp->index = 0; ecmp->index <= 15; ecmp->index++)
    {
        if (ecmp->ecmpModifyRegAlias2[ecmp->index] == regname)
        {
            break;
        }
    }

    /* read current register value */
    ecmp->value = ecmpReadRegister(ecmpHandle, ecmp->ecmpModifyRegAlias1[ecmp->index]);

    switch(setbit)
    {
    case 1:

        /* set bits in read out register */
        ecmp->value |= regbits;

        /* write modified value to register */
        ecmpSetRegister(ecmpHandle, ecmp->ecmpModifyRegAlias2[ecmp->index], ecmp->value);

        /* check if bit(s) were set */
        if(ecmpReadRegister(ecmpHandle, ecmp->ecmpModifyRegAlias1[ecmp->index]) & regbits)
        {
            return 1;
        }
        else
        {
            return 0;
        }

    case 0:

        /* clear bits in read out register */
        ecmp->value &= ~regbits;

        /* write modified value to register */
        ecmpSetRegister(ecmpHandle, ecmp->ecmpModifyRegAlias2[ecmp->index], ecmp->value);

        /* check if bit(s) were cleared */
        if((ecmpReadRegister(ecmpHandle, ecmp->ecmpModifyRegAlias1[ecmp->index]) & regbits) == 0 )
        {
            return 1;
        }
        else
        {
            return 0;
        }


    default:

        return 0;

    }

}

/** @fn unsigned ecmpStayinDIAGState (void)
*   @brief tries to put ecmp in debug state
*
*   @return 1 if successful, otherwise 0
*
*   sets DIAG_EXT_MASK bit (bit1) to stay in
*   DIAGNOSTIC state, clears WD_EN bit (bit3),
*   reads out registers to verify if registers
*   have been set and returns 1 if successful.
*   If failed returns 0.
*/
inline uint16_t ecmpStayinDIAGState(ECMP_handle ecmpHandle)
{
    /* stay in DIAGNOSTIC state (0x02) */
    return(ecmpModifyRegister(ecmpHandle, WR_CHK_CTRL, 0x02, 1) & ecmpModifyRegister(ecmpHandle, WR_FUNC_CFG, 0x08, 0));
}

/** @fn unsigned ecmpGotoACTIVEState (void)
*   @brief set registers to go to ACTIVE state
*
*   @return 1 if TPS65381 is in active state, otherwise 0
*
*   set companion register to go to ACTIVE
*   state, reads out registers to verify if
*   TPS65381 is in correct STATE and returns
*   1 if successful. If failed returns 0.
*/
uint32_t ecmpGotoACTIVEState (ECMP_handle ecmpHandle);


/** @fn unsigned char ecmpIsRegisterSet(unsigned short regName, unsigned char expValue)
*   @brief reads register value and compares it with expected value
*
*   @param[in] regName  - register alias
*   @param[in] expValue - expected register value
*   @return - expected value
*
*   read selected safety companion register and compares the
*   answer to expected value. If comparison is true, 1 will
*   be returned. Otherwise function returns 0.
*/
inline uint8_t ecmpIsRegisterSet(ECMP_handle ecmpHandle, uint16_t regName, uint8_t expValue)
{
    if (ecmpReadRegister(ecmpHandle, regName) == expValue )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/** @fn unsigned ecmpSetWdWin (unsigned short Topen, unsigned short Tclose)
*   @brief sets ecmp wd window reg and checks them
*
*   @param[in]  Topen  - open  window time period
*   @param[in]  Tclose - close window time period
*   @return     check  - 1 when set successful otherwise 0
*
*   sets ecmp watchdog window register and evaluates set
*   values, reads out registers to verify if registers
*   have been set, returns 1 if values are set correctly.
*   If failed, 0 will be returned.
*/
inline uint8_t ecmpSetWdWin(ECMP_handle ecmpHandle, uint16_t Topen, uint16_t Tclose)
{
    ecmpSetRegister(ecmpHandle, WR_OPEN_WD, Topen);
    ecmpSetRegister(ecmpHandle, WR_CLOSE_WD, Tclose);

    if(!(ecmpIsRegisterSet(ecmpHandle, RD_WD_OPEN_WIN_CFG, Topen)))
    	return 0;
    else
    	return (ecmpIsRegisterSet(ecmpHandle, RD_WD_CLOSE_WIN_CFG, Tclose));
}

/** @fn unsigned char ecmpWdFailCount(void)
*   @brief returns WD fail count
*
*   @return status
*
*   reads watchdog fail count from external
*   companion SAFETYSTAT2 register and returns
*   the count
*/
inline uint8_t ecmpWdFailCount(ECMP_handle ecmpHandle)
{
    return (ecmpReadRegister(ecmpHandle, RD_SAFETY_STAT2) & 0x7);
}

/** @fn void setDelay (unsigned delay, unsigned compare)
*   @brief sets delay until the very first WD Trigger / Answer Transition
*
*   @param[in] delay   - time until RTI IRQ is launched
*   @param[in] compare - used to differentiate between O/C or Q&A WD mode
*
*   sets the time for RTI module until IRQ is launched, two
*   counters (set via compare parameter) to be able to launch
*   watchdog and parallel error pin monitoring demo.
*/
inline void setDelay(ECMP_handle ecmpHandle, uint32_t delay, uint32_t compare)
{
    switch (compare)
    {
    case 02 :
        rtiREG1->CMP[2U].COMPx = delay;
        rtiREG1->CMP[2U].UDCPx = delay;
        break;

    case 03 :
        rtiREG1->CMP[3U].COMPx = delay;
        rtiREG1->CMP[3U].UDCPx = delay;
        break;
    }
}

/** @fn unsigned char getWDAnswrCnt (void)
*   @brief returns WD answer count
*
*   @return response - WD answer count
*
*/
inline uint8_t ecmpGetWdAnswrCnt(ECMP_handle ecmpHandle)
{
    return ((ecmpReadRegister(ecmpHandle, RD_WDT_STATUS) & 0xC0)>> 6);
}

/** @fn unsigned short ecmpCalcWdAnswr (unsigned short token)
*   @brief calculates WD answer
*
*   @param[in]  token - read out token
*   @return           - calculated answer
*
*
*   This function calculates the expected WD
*   answer from a given token
*/
inline uint16_t ecmpCalcWdAnswr(ECMP_handle ecmpHandle, uint16_t token)
{
	ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;

    ecmp->cnt = ecmpGetWdAnswrCnt(ecmpHandle);

    /* Create WD answer */
    ecmp->answer[0] = ((token & 0x1))    ^ (((ecmp->cnt & 0x2)  >>1) ^ ((token & 0x8) >> 3));
    ecmp->answer[1] = ((token & 0x1)<<1) ^ (((token & 0x4)>>1) ^ (token & 0x2))      ^ ((ecmp->cnt & 0x2));
    ecmp->answer[2] = ((token & 0x1)<<2) ^ (((token & 0x8)>>1) ^ ((token & 0x2)<<1)) ^ ((ecmp->cnt & 0x2)<<1);
    ecmp->answer[3] = ((token & 0x4)<<1) ^ (((token & 0x1)<<3) ^ (token & 0x8))      ^ ((ecmp->cnt & 0x2)<<2);
    ecmp->answer[4] = ((token & 0x2)<<3) ^ ((ecmp->cnt & 0x1)<<4);
    ecmp->answer[5] = ((token & 0x8)<<2) ^ ((ecmp->cnt & 0x1)<<5);
    ecmp->answer[6] = ((token & 0x1)<<6) ^ ((ecmp->cnt & 0x1)<<6);
    ecmp->answer[7] = ((token & 0x4)<<5) ^ ((ecmp->cnt & 0x1)<<7);

    return ecmp->answer[0] | ecmp->answer[1] | ecmp->answer[2] | ecmp->answer[3] | ecmp->answer[4] |
    		ecmp->answer[5] | ecmp->answer[6] | ecmp->answer[7];
}

/** @fn unsigned short ecmpGetWdToken(void)
*   @brief read WD Token and returns it
*
*   @return Wd token
*
*/
inline uint16_t ecmpGetWdToken(ECMP_handle ecmpHandle)
{
    return (ecmpReadRegister(ecmpHandle, RD_WDT_TOKEN) & 0x000F);
}

/** @fn unsigned short ecmpWdIsTimeOut(void)
*   @brief reads out TO flag
*
*   @return TO flag
*
*   This function reads out TPS65381 time
*   out flag and returns 1 when Timeout Flag
*   in WDT_STATUS register is set
*/
inline uint16_t ecmpWdIsTimeOut(ECMP_handle ecmpHandle)
{
    return ((ecmpReadRegister(ecmpHandle, RD_WDT_STATUS) & 0x02)>> 1);
}

/** @fn void ecmpWdQaSetOpenWinAnswr(void)
*   @brief send calculated open win answer to ecmp
*   @note This function works for open window
*   @note for close window answer call ecmpWdQaSetCloseWinAnswr()
*
*   This function reads out the WD token,
*   calculates the answer, checks the watchdog timeout flag
*   and sends it to the external companion chip.
*/
inline void ecmpWdQaSetOpenWinAnswr(ECMP_handle ecmpHandle)
{
	ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;

    ecmp->token = 0;

    ecmp->token = ecmpGetWdToken(ecmpHandle);

    /*wait for open window */
    while(ecmpWdIsTimeOut(ecmpHandle));

    /* set WDAnswr */
    ecmpSetRegister(ecmpHandle, WR_ANSWR, ecmpCalcWdAnswr(ecmpHandle, ecmp->token));
}

/** @fn void ecmpWdQaSetCloseWinAnswr(void)
*   @brief send calculated close win answer to ecmp
*   @note This function works for close window
*   @note for open window answer call ecmpWdQaSetOpenWinAnswr()
*
*   This function reads out the WD token,
*   calculates the answer and sends it to
*   the external companion chip.
*/
inline void ecmpWdQaSetCloseWinAnswr(ECMP_handle ecmpHandle)
{
    ecmpSetRegister(ecmpHandle, WR_ANSWR, ecmpCalcWdAnswr(ecmpHandle, ecmpGetWdToken(ecmpHandle)));
}

/** @fn void ecmpWdQaSendAnswer(unsigned char configure, unsigned openwin, unsigned closewin)
*   @brief send calculated answer to ecmp
*
*   @param[in]  configure - when set timing windows are configurable
*   @param[in]  openwin   - open timing window duration for RTI (set automatically)
*   @param[in]  closewin  - close timing window duration for RTI (set automatically)
*
*   This function differentiates between
*   open window and closed window and launches
*   functions to send the corresponding answers
*/
void ecmpWdQaSendAnswer(ECMP_handle ecmpHandle, uint8_t configure, uint32_t openwin, uint32_t closewin);


/** @fn void ecmpWdQaInit(unsigned Topen, unsigned Tclose)
*   @brief Q&A WD init function
*
*   @param[in]  Topen  - desired open window duration in mus
*   @param[in]  Tclose - desired close window duration in mus
*
*   @note ecmpWdStart() must be executed to start question and answer wd mode
*   @note Topen min: 3500mus, Topen max: 72000
*   @note Tclose min: 3000mus, Tclose max: 18000
*
*   This function has to be called before question and answer
*   watchdog mode can be launched. Parameters set the watchdog
*   open and close window durations and adjusts RTI IRQ calls
*   to ensure a working watchdog.
*/
void ecmpWdQaInit(ECMP_handle ecmpHandle, uint32_t Topen, uint32_t Tclose);

/** @fn void ecmpWdStart(void)
*   @brief WD start function
*   @note void ecmpWdQaInit(void) must be called before
*
*   starts rti Counter that triggers either open/close or
*   question and answer watchdog
*/

inline void ecmpWdStart(ECMP_handle ecmpHandle)
{
    rtiStartCounter(rtiCOUNTER_BLOCK1);
}


/** @fn unsigned ecmpErrorPinMonitoringInit(unsigned short allowedLowDuration)
*   @brief configures Error Pin Monitoring
*
*   @param[in] allowedLowDuration - allowed low duration for Error Pin in mus
*   @return 1 if NO_ERROR bit and ERROR_CFG bit set successfully
*
*   @note clearing NO_SAFE_TO bit causes a reset. If a transition to SAFE
*    state is desired, this bit should be set
*
*   This function initializes Error Pin monitoring.
*
*/
inline uint32_t ecmpErrorPinMonitoringInit(ECMP_handle ecmpHandle, uint16_t allowedLowDuration)
{
    ecmpSetRegister(ecmpHandle, WR_PWM_L, allowedLowDuration / 5); /**< converts allowed low duration to mus */

    /* set SAFE_LOCK_THR to 4 - neccessary for Error Pin monitor! */
    ecmpModifyRegister(ecmpHandle, WR_ERR_CFG, 0x08, 1);

    /* set NO_SAFE_TO bit --> this will cause a reset on Error Pin failure! */
    while(!ecmpModifyRegister(ecmpHandle, WR_FUNC_CFG, 0x80, 1));

    /* clear NO_ERROR bit (bit2) and set ERROR_CFG bit (bit6) */
    return(ecmpModifyRegister(ecmpHandle, WR_CHK_CTRL, 0x04, 0) & ecmpModifyRegister(ecmpHandle, WR_FUNC_CFG, 0x40, 1));
}

#endif /* ECMP_H_ */
