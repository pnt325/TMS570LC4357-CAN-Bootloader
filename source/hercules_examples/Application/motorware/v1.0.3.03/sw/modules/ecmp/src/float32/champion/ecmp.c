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
//! \file   ~modules/ecmp/src/float32/champion/ecmp.c
//! \brief  Contains the various functions related to the ECMP object
//!
//! (C) Copyright 2011, Texas Instruments, Inc.

// **************************************************************************
// the includes

#include "modules/ecmp/src/float32/champion/ecmp.h"

// **************************************************************************
// the global variables

/** global variable for printing register names to terminal */
int8_t *ecmpReg[27] =
{
		"DEV_ID",
		"DEV_REV",
	    "SAFETY_STAT1",
	    "SAFETY_STAT2",
	    "SAFETY_STAT3",
	    "SAFETY_STAT4",
	    "SAFETY_STAT5",
	    "SAFETY_ERR_CFG",
	    "SAFETY_ERR_STAT",
	    "SAFETY_PWD_THR_CFG",
	    "SAFETY_CHECK_CTRL",
	    "SAFETY_BIST_CTRL",
	    "WD_OPEN_WIN_CFG",
	    "WD_CLOSE_WIN_CFG",
	    "WDT_TOKEN",
	    "WDT_STATUS",
	    "DEV_STAT",
	    "VMON_STAT_1",
	    "VMON_STAT_2",
	    "SENS_CTRL",
	    "SAFETY_FUNC_CFG",
	    "SAFE_CFG_CRC",
	    "DIAG_CFG_CTRL",
	    "DIAG_MUX_SEL",
	    "SAFETY_ERR_PWM_H",
	    "SAFETY_ERR_PWM_L",
	    "WDT_TOKEN_FDBCK"
};

// **************************************************************************
// the function definitions

ECMP_handle ECMPInit(void *pMemory, const size_t numBytes)
{
	ECMP_handle ecmpHandle;

	if(numBytes < sizeof(ECMP_Obj))
		return((ECMP_handle)NULL);

	// assign the handle
	ecmpHandle = (ECMP_handle)pMemory;

	return(ecmpHandle);
}

void ECMPSetup(ECMP_handle ecmpHandle)
{
	ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;
	ecmp->Err_Count = 5;
	ecmp->SP2_Complete = 0;
	ecmp->SPI2_RXDATA = 0;
	ecmp->ecmpIsInActiveState = ECMP_INACTIVE;
	ecmp->DiagFlag = 1;

	// Conversion used for watchdog timing adjustment
	ecmp->conversion = 565;

	ecmp->ecmpModifyRegAlias1[0] = RD_SAFETY_ERR_CFG;
	ecmp->ecmpModifyRegAlias1[0] = RD_SAFETY_ERR_CFG;
	ecmp->ecmpModifyRegAlias1[1] = RD_SAFETY_ERR_STAT;
	ecmp->ecmpModifyRegAlias1[2] = RD_SAFETY_PWD_THR_CFG;
	ecmp->ecmpModifyRegAlias1[3] = RD_SAFETY_CHECK_CTRL;
	ecmp->ecmpModifyRegAlias1[4] = RD_SAFETY_BIST_CTRL;
	ecmp->ecmpModifyRegAlias1[5] = RD_WD_OPEN_WIN_CFG;
	ecmp->ecmpModifyRegAlias1[6] = RD_WD_CLOSE_WIN_CFG;
	ecmp->ecmpModifyRegAlias1[7] = RD_SENS_CTRL;
	ecmp->ecmpModifyRegAlias1[8] = RD_SAFETY_FUNC_CFG;
	ecmp->ecmpModifyRegAlias1[9] = RD_SAFE_CFG_CRC;
	ecmp->ecmpModifyRegAlias1[10] = RD_DIAG_CFG_CTRL;
	ecmp->ecmpModifyRegAlias1[11] = RD_DIAG_MUX_SEL;
	ecmp->ecmpModifyRegAlias1[12] = RD_SAFETY_ERR_PWM_H;
	ecmp->ecmpModifyRegAlias1[13] = RD_SAFETY_ERR_PWM_L;
	ecmp->ecmpModifyRegAlias1[14] = RD_WDT_TOKEN;
	ecmp->ecmpModifyRegAlias2[0] = WR_ERR_CFG;
	ecmp->ecmpModifyRegAlias2[1] = WR_ERR_STAT;
	ecmp->ecmpModifyRegAlias2[2] = WR_PWD_CFG;
	ecmp->ecmpModifyRegAlias2[3] = WR_CHK_CTRL;
	ecmp->ecmpModifyRegAlias2[4] = WR_BIST_CTRL;
	ecmp->ecmpModifyRegAlias2[5] = WR_OPEN_WD;
	ecmp->ecmpModifyRegAlias2[6] = WR_CLOSE_WD;
	ecmp->ecmpModifyRegAlias2[7] = WR_SENS;
	ecmp->ecmpModifyRegAlias2[8] = WR_FUNC_CFG;
	ecmp->ecmpModifyRegAlias2[9] = WR_CRC;
	ecmp->ecmpModifyRegAlias2[10] = WR_DIAG_CFG;
	ecmp->ecmpModifyRegAlias2[11] = WR_MUX;
	ecmp->ecmpModifyRegAlias2[12] = WR_PWM_H;
	ecmp->ecmpModifyRegAlias2[13] = WR_PWM_L;
	ecmp->ecmpModifyRegAlias2[14] = WR_TOKEN;

	ecmp->ecmpReadRegAlias[0] = RD_DEV_ID;
	ecmp->ecmpReadRegAlias[1] = RD_DEV_REV;
	ecmp->ecmpReadRegAlias[2] = RD_SAFETY_STAT1;
	ecmp->ecmpReadRegAlias[3] = RD_SAFETY_STAT2;
	ecmp->ecmpReadRegAlias[4] = RD_SAFETY_STAT3;
	ecmp->ecmpReadRegAlias[5] = RD_SAFETY_STAT4;
	ecmp->ecmpReadRegAlias[6] = RD_SAFETY_STAT5;
	ecmp->ecmpReadRegAlias[7] = RD_SAFETY_ERR_CFG;
	ecmp->ecmpReadRegAlias[8] = RD_SAFETY_ERR_STAT;
	ecmp->ecmpReadRegAlias[9] = RD_SAFETY_PWD_THR_CFG;
	ecmp->ecmpReadRegAlias[10] = RD_SAFETY_CHECK_CTRL;
	ecmp->ecmpReadRegAlias[11] = RD_SAFETY_BIST_CTRL;
	ecmp->ecmpReadRegAlias[12] = RD_WD_OPEN_WIN_CFG;
	ecmp->ecmpReadRegAlias[13] = RD_WD_CLOSE_WIN_CFG;
	ecmp->ecmpReadRegAlias[14] = RD_WDT_TOKEN;
	ecmp->ecmpReadRegAlias[15] = RD_WDT_STATUS;
	ecmp->ecmpReadRegAlias[16] = RD_DEV_STAT;
	ecmp->ecmpReadRegAlias[17] = RD_VMON_STAT_1;
	ecmp->ecmpReadRegAlias[18] = RD_VMON_STAT_2;
	ecmp->ecmpReadRegAlias[19] = RD_SENS_CTRL;
	ecmp->ecmpReadRegAlias[20] = RD_SAFETY_FUNC_CFG;
	ecmp->ecmpReadRegAlias[21] = RD_SAFE_CFG_CRC;
	ecmp->ecmpReadRegAlias[22] = RD_DIAG_CFG_CTRL;
	ecmp->ecmpReadRegAlias[23] = RD_DIAG_MUX_SEL;
	ecmp->ecmpReadRegAlias[24] = RD_SAFETY_ERR_PWM_H;
	ecmp->ecmpReadRegAlias[25] = RD_SAFETY_ERR_PWM_L;
	ecmp->ecmpReadRegAlias[26] = RD_WDT_TOKEN_FDBCK;

    ecmp->ecmpReg = ecmpReg;

	ecmp->ecmRegisterArrayLength = sizeof(ecmp->ecmpReg) / sizeof(ecmp->ecmpReg[0]);
	ecmp->ecmRegisterArrayLength = sizeof(ecmp->ecmpReadRegAlias) / sizeof(ecmp->ecmpReadRegAlias[0]);
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
void ecmpWdQaSendAnswer(ECMP_handle ecmpHandle, uint8_t configure, uint32_t openwin, uint32_t closewin)
{
	//ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;

	ecmpHandle->k = 0;

    switch(configure)
    {
    case 1:

    	ecmpHandle->trgPulseOpen  = openwin / 3;
    	ecmpHandle->trgPulseClose = closewin / 2 + openwin * 2 / 3;

        break;

    case 0:
        switch (ecmpHandle->wdWindow)
        {

        /** send three answers during open window */
        case ECMP_WINDOW_OPEN  :
        	(*(volatile unsigned int *)(0xFFFFFF0C))=1;
        	/** if error count == 0 enable WD and enable Driver */

        	if((ecmpHandle->Err_Count == 0) && (ecmpHandle->ecmpIsInActiveState == ECMP_INACTIVE))
        	{

        	    /* set enable Driver output high */

        		ecmpSetRegister(ecmpHandle, WR_CHK_CTRL, 0x27);
        		if(ecmpHandle->DiagFlag) PutText(ecmpHandle, "Ed");
        		ecmpHandle->Curr_Sta  = (ecmpReadRegister(ecmpHandle, RD_SAFETY_CHECK_CTRL));
        		if((ecmpHandle->Curr_Sta & 0x37) != 0x27)
        		{
        			if(ecmpHandle->DiagFlag) PutChar(ecmpHandle, 'F');
        		}
        		else
        		{
        			if(ecmpHandle->DiagFlag) PutChar(ecmpHandle, 'S');
        			ecmpHandle->ecmpIsInActiveState = ECMP_ENADRV;
        		}
        		ecmpHandle->Curr_Sta  = (ecmpReadRegister(ecmpHandle, RD_SAFETY_CHECK_CTRL));

        	}
        	else if((ecmpHandle->Err_Count == 0) && (ecmpHandle->ecmpIsInActiveState == ECMP_ENADRV))
        	{
        		ecmpHandle->ecmpIsInActiveState = ECMP_SETWATD;
        		ecmpHandle->Err_Count++;
        		/* enable Q&A WD */
        		ecmpSetRegister(ecmpHandle, WR_FUNC_CFG, 0xA8);
        	}

        	else if((ecmpHandle->Err_Count == 0) && (ecmpHandle->ecmpIsInActiveState == ECMP_SETWATD))
        	{
        		ecmpSetRegister(ecmpHandle, WR_ERR_STAT, 0x00);
        		ecmpHandle->Curr_Sta = ecmpReadRegister(ecmpHandle, RD_SAFETY_ERR_STAT);
        		if(ecmpHandle->Curr_Sta!=0)
        		{
        			if(ecmpHandle->DiagFlag) PutChar(ecmpHandle, 'w');
        		}
        	    else
        	    {
        	    	ecmpHandle->ecmpIsInActiveState = ECMP_CLRERR;
        	    }

        	}
        	else if((ecmpHandle->Err_Count == 0) && (ecmpHandle->ecmpIsInActiveState == ECMP_CLRERR))
        	{
        	    // Switch to Active Mode
        		ecmpSetRegister(ecmpHandle, WR_CHK_CTRL, 0x25);
        		ecmpHandle->Curr_Sta  = (ecmpReadRegister(ecmpHandle, RD_SAFETY_CHECK_CTRL));
        		if((ecmpHandle->Curr_Sta & 0x37) != 0x25)
        		{
        			if(ecmpHandle->DiagFlag) PutText(ecmpHandle, "GaF");
        		}
        		else
        		{
        			if(ecmpHandle->DiagFlag) PutText(ecmpHandle, "GaS");
        			ecmpHandle->ecmpIsInActiveState = ECMP_ACTIVE;
        		}
        		ecmpHandle->Curr_Sta  = (ecmpReadRegister(ecmpHandle, RD_SAFETY_CHECK_CTRL));
        	}

        	while(ecmpHandle->k != 3)
        	{
        		ecmpWdQaSetOpenWinAnswr(ecmpHandle);
        	    ecmpHandle->k++;
        	}

        		//ecmp->Curr_Sta  = (ecmp->Curr_Sta & 0x7) + ((ecmp->Curr_Sta & 0x20)>>2);
        		//PutChar(ecmpHandle, ecmp->Curr_Sta + '0');




        	/* set next RTI IRQ */
            rtiREG1->CMP[2U].UDCPx = ecmpHandle->trgPulseOpen;

            ecmpHandle->wdWindow = ECMP_WINDOW_CLOSE;

            break;

        /** send last answer during close window */
        case ECMP_WINDOW_CLOSE :
			(*(volatile unsigned int *)(0xFFFFFF0C))=0;

			ecmpWdQaSetCloseWinAnswr(ecmpHandle);

			/* set next RTI IRQ */
			rtiREG1->CMP[2U].UDCPx = ecmpHandle->trgPulseClose;

			/* print WD error count to terminal */
			ecmpHandle->Err_Count = ecmpWdFailCount(ecmpHandle);
			ecmpHandle->Curr_Sta = ecmpReadRegister(ecmpHandle, RD_SAFETY_STAT5);
			if(ecmpHandle->DiagFlag)
			{
				PutText(ecmpHandle, " A");
				PutChar(ecmpHandle, ecmpHandle->Err_Count + '0');
				PutChar(ecmpHandle, ecmpHandle->Curr_Sta + '0');
			}

			ecmpHandle->wdWindow = ECMP_WINDOW_OPEN;

			break;
        }
        break;
    }
}

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
void ecmpWdQaInit(ECMP_handle ecmpHandle, uint32_t Topen, uint32_t Tclose)
{
	//ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;

    ecmpWdQaSendAnswer(ecmpHandle, 1, Topen, Tclose);

    /* getting write access to protected ecmp registers  */
    while(ecmpGetWriteAccess(ecmpHandle) != 1);

    ecmpHandle->tOpen  = Topen / ecmpHandle->conversion;
    ecmpHandle->tClose = Tclose / ecmpHandle->conversion;

    /* configure ecmp watchdog windows */
    while(!ecmpSetWdWin(ecmpHandle, ecmpHandle->tOpen, ecmpHandle->tClose));

    /* enable WD, must set before going to ACTIVE state! */
    ecmpSetRegister(ecmpHandle, WR_FUNC_CFG, 0xA0);

    ecmpClearErrorCnt(ecmpHandle);

    rtiInit();

    rtiEnableNotification(rtiNOTIFICATION_COMPARE2);
    while((ecmpReadRegister(ecmpHandle, RD_WDT_STATUS) & 0x02) == 0x0);//wait until timeout, syc the MCU and the TPS65381

    ecmpHandle->wdWindow=ECMP_WINDOW_OPEN;//watchdog window is open.
    rtiREG1->CMP[2U].COMPx = ecmpHandle->tOpen / 3;//write to the open window in the middle of Topen
    rtiREG1->CMP[2U].UDCPx = ecmpHandle->tOpen *2/3 + ecmpHandle->tClose / 2;////write to the open window in the middle of Tclose
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
uint32_t ecmpGotoACTIVEState (ECMP_handle ecmpHandle)
{
	char Temp_Safy_Check;
	//ECMP_Obj *ecmp = (ECMP_Obj *)ecmpHandle;

	//ecmpHandle->value  = ecmpReadRegister(ecmpHandle, RD_SAFETY_CHECK_CTRL);
	//ecmpHandle->value &= 0xFD;
	//ecmpHandle->value |= 0x01;

    /** go to ACTIVE state (0x05) */
	if(ecmpHandle->DiagFlag) PutText(ecmpHandle, "Ga");
    ecmpSetRegister(ecmpHandle, WR_CHK_CTRL, ecmpHandle->value);
    Temp_Safy_Check = ecmpReadRegister(ecmpHandle, RD_SAFETY_CHECK_CTRL) & 0x3;

    if(Temp_Safy_Check == 0x1)
    {
    	if(ecmpHandle->DiagFlag) PutChar(ecmpHandle, 'S');
    	ecmpHandle->ecmpIsInActiveState = ECMP_ACTIVE;
    	ecmpHandle->DiagFlag = 0;
        return 1;
    }
    else
    {
    	if(ecmpHandle->DiagFlag) PutChar(ecmpHandle, 'F');
    	 PutChar(ecmpHandle, Temp_Safy_Check+'0');
        return 0;
    }
}



