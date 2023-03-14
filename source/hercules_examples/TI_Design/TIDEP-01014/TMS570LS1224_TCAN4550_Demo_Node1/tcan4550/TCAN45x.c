/*
 * TCAN45x.c
 *
 *  Updated on Feb 22, 2018 for TMS570 MCU; QJ Wang; qjwang@ti.com
 *    1. Re-wrote several functions:MCAN_ReadNextFIFO(), MCAN_ReadRXBuffer(), MCAN_WriteTXFIFO()
 *    2. Corrected an error in TCAN45x0_ConfigureCCCRRegister()
 *    3. Added several new functions
 *
 *  First created on: Apr 3, 2017 for MSP430 MCU; Jonathan Valdez
 *
 */
/*
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com
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
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#include <TCAN45x.h>
#include <TMS570_TCAN45x.h>
#include "hw_config.h"

/* Set Init bit and CCE bit, the configuration registers can be accessed */
uint8_t TCAN45x0_EnableProtectedRegisters(void)
{
	uint8_t i;
	uint32_t temp,firstRead;

	firstRead = AHB_READ_B_FL_32(M_CAN_CCCR);

	if ((firstRead & 0xF) == MCAN_CCCR_CCE + MCAN_CCCR_INIT)
		return CONFIG_SUCCESS_FIRST;

	firstRead = firstRead & 0xFFFFFFFC;
	// Try up to 5 times to set the CCCR register, if not, then fail config, since we need these bits set to configure the device.
	for (i = 5; i > 0; i--) {
		AHB_WRITE_B_FL_32(M_CAN_CCCR, firstRead + MCAN_CCCR_CCE + MCAN_CCCR_INIT);
        /*Readback the written value*/
		temp = AHB_READ_B_FL_32(M_CAN_CCCR);
		if ((temp & 0x3) == MCAN_CCCR_CCE + MCAN_CCCR_INIT) {
			break;
		} else if (i == 1) {
			return CONFIG_FAIL;
		}
	}
	return CONFIG_SUCCESS;
}

/*RESET the Init bit and the CCE bit*/
uint8_t TCAN45x0_DisableProtectedRegisters(void)
{
	uint8_t i;
	uint32_t temp;

	temp = AHB_READ_B_FL_32(M_CAN_CCCR);
	if ((temp & 0xF) == 0)
		return CONFIG_SUCCESS_FIRST;

	// Try up to 5 times to unset the CCCR register, if not, then fail config, since we need these bits set to configure the device.
	for (i = 5; i > 0; i--) {
		AHB_WRITE_B_FL_32(M_CAN_CCCR, (temp & 0xFFFFFFFC));
        /* Readback the written value*/
		temp = AHB_READ_B_FL_32(M_CAN_CCCR);
		if ((temp & 0x3) == 0) {
			break;
		} else if (i == 1) {
			return CONFIG_FAIL;
		}
	}
	return CONFIG_SUCCESS;
}

/* Write CCCR configuration value to CCCR register; then readback and compare them*/
uint8_t TCAN45x0_ConfigureCCCRRegister(TCAN45x0_CCCR_Config *cccrConfig)
{
	uint32_t value, readValue;
	uint8_t cccr;

	value = (uint32_t) TCAN45x0_REG_VALUE cccrConfig;
	value = value & 0x0000F3F4;		// Bitwise AND to get the valid bits (ignore reserved bits and the CCE and INIT)

	cccr = TCAN45x0_EnableProtectedRegisters();
	if (cccr == CONFIG_FAIL)
		return CONFIG_FAIL;

	// If we made it here, we can update the registers
	value |= MCAN_CCCR_INIT + MCAN_CCCR_CCE;

	AHB_WRITE_B_FL_32(M_CAN_CCCR, value);
	readValue = AHB_READ_B_FL_32(M_CAN_CCCR);

	// Need to do these bitwise ANDs to make this work for clock stop requests and not trigger a false fail.
	if ((readValue & 0xF3E4) != (value & 0xF3E4)) {
		// If we enabled the CCE and INIT bits in this function, then let's disable them before we fail.
       if (cccr == CONFIG_SUCCESS) {
			if (TCAN45x0_DisableProtectedRegisters() == CONFIG_FAIL)
				return CONFIG_FAIL;
		}
		return CONFIG_FAIL;
	}

	// Turn off the initialization/protected mode if we had to enable it ourselves (this is a register update rather than a fresh config)
	if (cccr != CONFIG_SUCCESS_FIRST) {
		if (TCAN45x0_DisableProtectedRegisters() == CONFIG_FAIL)
			return CONFIG_FAIL;
	}
	return CONFIG_SUCCESS;
}

/* Readback the Data bit timing */
uint8_t TCAN45x0_MCANTimingFDRead(TCAN45x0_CANFD_Timing *dataTiming)
{
	uint32_t regData;

	regData = AHB_READ_B_FL_32(M_CAN_DBTP);

	// These registers are only writable if CCE and INIT are both set. Sets the nominal bit timing and prescaler information
	dataTiming->DataBitRatePrescaler = ((regData >> 16) & 0x1F) + 1;
	dataTiming->DataTimeSeg1andProp = ((regData >> 8) & 0x1F) + 1;
	dataTiming->DataTimeSeg2 = ((regData >> 4) & 0xF) + 1;
	dataTiming->DataSyncJumpWidth = (regData & 0xF) + 1;

	if (regData & 0x00800000) {
		regData = AHB_READ_B_FL_32(M_CAN_TDCR);
		dataTiming->TDCOffset = ((regData >> 8) & 0x7F);
		dataTiming->TDCFilter = (regData & 0x7F);
	} else {
		dataTiming->TDCOffset = 0;
		dataTiming->TDCFilter = 0;
	}

	return CONFIG_SUCCESS;
}

/* Write the data bit timing to Data Bit Timing & Prescaler register (0x100C)*/
uint8_t TCAN45x0_ConfigureMCANTimingFD(TCAN45x0_CANFD_Timing *dataTiming)
{
	uint8_t cccr;
	uint32_t temp;

	// Enable protected writes, and determine if it was already done for us or not.
	cccr = TCAN45x0_EnableProtectedRegisters();
	if (cccr == CONFIG_FAIL)
		return CONFIG_FAIL;

	// These registers are only writable if CCE and INIT are both set. Sets the nominal bit timing and prescaler information
	temp = ((uint32_t)(dataTiming->DataBitRatePrescaler & 0x1F) - 1) << 16;
	temp |= ((uint32_t)(dataTiming->DataTimeSeg1andProp & 0x1F) - 1 ) << 8;
	temp |= ((uint32_t)(dataTiming->DataTimeSeg2 & 0x0F) - 1) << 4;
	temp |= ((uint32_t)(dataTiming->DataSyncJumpWidth & 0x0F) - 1);
	if ((dataTiming->TDCOffset > 0) || (dataTiming->TDCFilter > 0)) {
		// If either of these are set, then enable transmitter delay compensation
		temp |= 0x00800000;
		AHB_WRITE_B_FL_32( M_CAN_DBTP, temp);

		temp = (uint32_t)(dataTiming->TDCOffset & 0x7F) << 8;
		temp |= (uint32_t)(dataTiming->TDCFilter & 0x7F);
		AHB_WRITE_B_FL_32( M_CAN_TDCR, temp);
	} else {
		AHB_WRITE_B_FL_32( M_CAN_DBTP, temp);
	}

	/* 10 – External timestamp counter value used; this is required to be 2 for CAN FD support */
	AHB_WRITE_B_FL_32(M_CAN_TSCC, 0x0002);
	/* Timestamp counter configuration register at 0x1020
	 * TCP = 0  Configures the timestamp and timeout counters time unit in multiples of can bit times, but register value + 1, so 0 = 1 bit time used. Note that can FD requires an external counter for timestamp
	 * TSS = 2  timestamp select, 2 = external timestamp counter value used (this is required to be 2 for CAN FD support)
	 */

	// Turn off the initialization/protected mode if we had to enable it ourselves (this is a register update rather than a fresh config)
	if (cccr != CONFIG_SUCCESS_FIRST) {
		if (TCAN45x0_DisableProtectedRegisters() == CONFIG_FAIL)
			return CONFIG_FAIL;
	}

#ifdef FUNCTION_SAFETY
	unit8_t i;
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        if (AHB_READ_B_FL_32(M_CAN_DBTP) != temp) {
            AHB_WRITE_B_FL_32(( M_CAN_DBTP), temp);
            break;
        } else if (i == 1) {
            return CONFIG_FAIL;
        }
    }
#endif

	return CONFIG_SUCCESS;
}

/* Readback the Nominal bit timing from Nominal Bit Timing & Prescaler Register (0x101C)*/
uint8_t TCAN45x0_MCANTimingRead(TCAN45x0_Nominal_Timing *nomTiming)
{
	uint32_t regData;

	regData = AHB_READ_B_FL_32(M_CAN_NBTP);

	// These registers are only writable if CCE and INIT are both set. Sets the nominal bit timing and prescaler information
	nomTiming->NominalSyncJumpWidth = ((regData >> 25) & 0x7F) + 1;
	nomTiming->NominalBitRatePrescaler = ((regData >> 16) & 0x1FF) + 1;
	nomTiming->NominalTimeSeg1andProp = ((regData >> 8) & 0xFF) + 1;
	nomTiming->NominalTimeSeg2 = (regData & 0x7F) + 1;

	return CONFIG_SUCCESS;
}

/* Write Nominal bit timing to Nominal Bit Timing & Prescaler Register (0x101C). This register is protected*/
uint8_t TCAN45x0_ConfigureMCANTiming(TCAN45x0_Nominal_Timing *nomTiming)
{
	uint8_t cccr;
	uint32_t temp;

	// Enable protected writes, and determine if it was already done for us or not.
	cccr = TCAN45x0_EnableProtectedRegisters();
	if (cccr == CONFIG_FAIL)
		return CONFIG_FAIL;

	// These registers are only writable if CCE and INIT are both set. Sets the nominal bit timing and prescaler information
	temp = ((uint32_t)(nomTiming->NominalSyncJumpWidth & 0x7F)-1) << 25;
	temp |= ((uint32_t)(nomTiming->NominalBitRatePrescaler & 0x1FF) - 1) << 16;
	temp |= ((uint32_t)(nomTiming->NominalTimeSeg1andProp) - 1) << 8;
	temp |= ((uint32_t)(nomTiming->NominalTimeSeg2 & 0x7F) - 1);
	AHB_WRITE_B_FL_32(M_CAN_NBTP, temp);

#ifdef FUNCTION_SAFETY
    unit8_t i;
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        if (AHB_READ_B_FL_32(M_CAN_NBTP) != temp) {
            AHB_WRITE_B_FL_32(( M_CAN_NBTP), temp);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif

    // Turn off the initialization/protected mode if we had to enable it ourselves (this is a register update rather than a fresh config)
    if (cccr != CONFIG_SUCCESS_FIRST) {
        if (TCAN45x0_DisableProtectedRegisters() == CONFIG_FAIL)
            return CONFIG_FAIL;
    }

	return CONFIG_SUCCESS;
}

/* Set the device mode in Modes of Operation and Pin Configuration Register (0x0800)
 * TCAN45x0_GPIO1_MCAN_INT1; TCAN45x0_GPIO1_SPIFAULT_INT
 * TCAN45x0_GPIO2_MCAN_INT0; TCAN45x0_GPIO2_CANBUS_INT
 * */
uint8_t TCAN45x0_Config_GPIOMode(uint8_t gpio1_mode, uint8_t gpio2_mode)
{
    uint32_t out = AHB_READ_B_FL_32(DEV_MODE_PINS) & ~GPIO1_CONFIG_MASK &  ~GPIO2_CONFIG_MASK;

    out &= ~(0x3 << 14);  //CLKOUT_GPIO1_CONFIG: GPIO mode

    out |= ((gpio2_mode & 0x03) << 22) | ((gpio1_mode & 0x03) << 10);

    AHB_WRITE_B_FL_32(DEV_MODE_PINS, out);

#ifdef FUNCTION_SAFETY
    unit8_t i;
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        if (AHB_READ_B_FL_32(DEV_MODE_PINS) != out) {
            AHB_WRITE_B_FL_32(( DEV_MODE_PINS), out);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif
    return CONFIG_SUCCESS;
}

/* Set the device mode in Modes of Operation and Pin Configuration Register (0x0800)*/
uint8_t TCAN45x0_SetDeviceMode(uint8_t mode)
{
	uint32_t out = (AHB_READ_B_FL_32(DEV_MODE_PINS) & ~DEVICE_MODE_DEVICEMODE_MASK);  //out = 0xC8000428 at default

	switch (mode & 0x03) {
		case TCAN45x0_MODE_NORMAL:
			out |= DEVICE_MODE_DEVICEMODE_NORMAL;
			break;

		case TCAN45x0_MODE_SLEEP:
			out |= DEVICE_MODE_DEVICEMODE_SLEEP;
			break;

		case TCAN45x0_MODE_STANDBY:
			out |= DEVICE_MODE_DEVICEMODE_STANDBY;
			break;

		case TCAN45x0_MODE_TEST:
			out |= DEVICE_MODE_DEVICEMODE_TEST | (0x1 < 21); //changed by QJ, 2019
			break;

		default:
			return CONFIG_FAIL;
	}

	if (out & TCAN45x0_MODE_MCAN_CONFIGURED) { //mode --> out changed by QJ 2018
		out |= DEVICE_MODE_MCAN_CONFIGURED;
	} else {
		out &= ~DEVICE_MODE_MCAN_CONFIGURED;
	}

	AHB_WRITE_B_FL_32(DEV_MODE_PINS, out);
//	if ( AHB_READ_B_FL_32(DEV_MODE_PINS) == out )
//		return CONFIG_SUCCESS;
//	else
//		return CONFIG_FAIL;
#ifdef FUNCTION_SAFETY
    unit8_t i;
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        if (AHB_READ_B_FL_32(DEV_MODE_PINS) != out) {
            AHB_WRITE_B_FL_32(( DEV_MODE_PINS), out);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif
    return CONFIG_SUCCESS;

}

/* Set the WatchDog in Modes of Operation and Pin Configuration Register (0x0800)*/
uint8_t TCAN45x0_SetWDT(uint8_t WDTtimeout)
{
	uint32_t readData = AHB_READ_B_FL_32(DEV_MODE_PINS);
	readData &= ~DEVICE_MODE_WD_TIMER_MASK;					// Clear the bits that we are setting

	// Set the appropriate bits depending on the passed in value
	switch (WDTtimeout)
	{
	case TCAN45x0_WDT_8MS:
		readData |= DEVICE_MODE_WD_TIMER_8MS;
		break;

	case TCAN45x0_WDT_16MS:
		readData |= DEVICE_MODE_WD_TIMER_16MS;
		break;

	case TCAN45x0_WDT_24MS:
		readData |= DEVICE_MODE_WD_TIMER_24MS;
		break;

	case TCAN45x0_WDT_32MS:
		readData |= DEVICE_MODE_WD_TIMER_32MS;
		break;

	default: return CONFIG_FAIL;							// If an invalid value was passed, then we will return fail
	}
	AHB_WRITE_B_FL_32(DEV_MODE_PINS, readData);				// Write the updated values
#ifdef FUNCTION_SAFETY
    unit8_t i;
    uint32_t temp;

    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        temp = AHB_READ_B_FL_32(DEV_MODE_PINS);
        if (temp != readData) {
            AHB_WRITE_B_FL_32(( DEV_MODE_PINS), readData);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif
	return CONFIG_SUCCESS;
}

/* Enable the WatchDog in Modes of Operation and Pin Configuration Register (0x0800)*/
uint8_t TCAN45x0_EnableWDT(void)
{
	uint32_t regData = AHB_READ_B_FL_32(DEV_MODE_PINS) | DEVICE_MODE_WDT_EN;
	AHB_WRITE_B_FL_32(DEV_MODE_PINS, regData);		// Enable the watch dog timer

	// Check that we did successfully enable it
	regData = AHB_READ_B_FL_32(DEV_MODE_PINS);
	if (regData & DEVICE_MODE_WDT_EN)
		return CONFIG_SUCCESS;
	else
		return CONFIG_FAIL;
}

/* Disable the WatchDog in Modes of Operation and Pin Configuration Register (0x0800)*/
uint8_t TCAN45x0_DisableWDT(void)
{
	uint32_t regData = AHB_READ_B_FL_32(DEV_MODE_PINS) & ~DEVICE_MODE_WDT_EN;

#ifdef PIN_OUT_TEST_MODE
	regData |= 0x000000C0;									// This ensures a reset
#endif
	AHB_WRITE_B_FL_32(DEV_MODE_PINS, regData);		// Disable the watch dog timer

	// Check that we did successfully enable it
	regData = AHB_READ_B_FL_32(DEV_MODE_PINS);
	if (regData & DEVICE_MODE_WDT_EN)
		return CONFIG_FAIL;
	else
		return CONFIG_SUCCESS;
}

/* Reset the WatchDog in Modes of Operation and Pin Configuration Register (0x0800)*/
uint8_t TCAN45x0_ResetWDT(void)
{
	uint32_t regData = AHB_READ_B_FL_32(DEV_MODE_PINS) | DEVICE_MODE_WDT_RESET_BIT;

#ifdef PIN_OUT_TEST_MODE
	regData |= 0x000000C0;									// This ensures a reset
#endif
	AHB_WRITE_B_FL_32(DEV_MODE_PINS, regData);		// Reset the watch dog timer

	return CONFIG_SUCCESS;
}


uint8_t TCAN45x0_ConfigureMRAM(TCAN45x0_MRAM_Config *MRAMConfig)
{
	uint16_t startAddress = 0x0000;		// Used to hold the start and end addresses for each section as we write them into the appropriate registers
	uint32_t registerValue = 0;				// Used to create the 32-bit word to write to each register
	uint8_t MRAMValue, cccr;

	// First we need to make sure we have protected register access since these are protected
	cccr = TCAN45x0_EnableProtectedRegisters();
	if (cccr == CONFIG_FAIL)
		return CONFIG_FAIL;

	/* First the 11-bit filter section can be setup.
	 * Standard ID Filter Configuration Register: 0x1084, SIDFC
	 * */
	/*Number of standard Message ID filter elements: 1~128*/
	MRAMValue = MRAMConfig->SIDNumElements;
	if (MRAMValue > 128)
		MRAMValue = 128; /*Values greater than 128 are interpreted as 128*/
	if (MRAMValue == 0) {
		registerValue = 0;
	} else {
		registerValue = ((uint32_t)(MRAMValue) << 16) | ((uint32_t)startAddress);
	}
	startAddress += (4 * (uint16_t)MRAMValue);  /* 4 bytes per element*/
	AHB_WRITE_B_FL_32(( M_CAN_SIDFC), registerValue);
#ifdef FUNCTION_SAFETY
    uint32_t temp;
    unit8_t i;
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        temp = AHB_READ_B_FL_32(M_CAN_SIDFC);
        if (temp != registerValue) {
            AHB_WRITE_B_FL_32(( M_CAN_SIDFC), registerValue);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif

	/* The 29-bit extended filter section
	 * Extended ID Filter Configuration Register: 0x1088, XIDFC
	 * */
    /* Number of extended Message ID filter elements: 1~64*/
	MRAMValue = MRAMConfig->XIDNumElements;
	if (MRAMValue > 64)
		MRAMValue = 64;   /*Values greater than 64 are interpreted as 64*/
	if (MRAMValue == 0) {
		registerValue = 0;
	} else {
		registerValue = ((uint32_t)(MRAMValue) << 16) | ((uint32_t)startAddress);
	}
	startAddress += (8 * (uint16_t)MRAMValue);   /* 8 bytes per element*/
	AHB_WRITE_B_FL_32(( M_CAN_XIDFC), registerValue);
#ifdef FUNCTION_SAFETY
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        temp = AHB_READ_B_FL_32(M_CAN_XIDFC);
        if (temp != registerValue) {
            AHB_WRITE_B_FL_32((M_CAN_XIDFC), registerValue);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif
	/* RX FIFO 0
	 * Rx FIFO 0 Configuration Register: 0x10A0,
	 * */
	/* Number of Rx FIFO 0 elements */
	MRAMValue = MRAMConfig->Rx0NumElements;
	if (MRAMValue > 64)
		MRAMValue = 64;  /*Values greater than 64 are interpreted as 64*/
	if (MRAMValue == 0) {
		registerValue = 0;
	} else {
		registerValue = ((uint32_t)(MRAMValue) << 16) | ((uint32_t)startAddress);
	}
	startAddress += (((uint32_t)MCAN_TXRXESC_DataByteValue(MRAMConfig->Rx0ElementSize) + 8) * (uint16_t)MRAMValue);
	AHB_WRITE_B_FL_32(( M_CAN_RXF0C), registerValue);
#ifdef FUNCTION_SAFETY
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        temp = AHB_READ_B_FL_32(M_CAN_RXF0C);
        if (temp != registerValue) {
            AHB_WRITE_B_FL_32((M_CAN_RXF0C), registerValue);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif

	/* RX FIFO 1
	 * Rx FIFO 1 Configuration Register: 0x10B0,
	 * */
	/* Number of Rx FIFO 1 elements */
	MRAMValue = MRAMConfig->Rx1NumElements;
	if (MRAMValue > 64)
		MRAMValue = 64;   /*Values greater than 64 are interpreted as 64*/

	if (MRAMValue == 0) {
		registerValue = 0;
	} else {
		registerValue = ((uint32_t)(MRAMValue) << 16) | ((uint32_t)startAddress);
	}
	startAddress += (((uint32_t)MCAN_TXRXESC_DataByteValue(MRAMConfig->Rx1ElementSize) + 8) * (uint16_t)MRAMValue);
	AHB_WRITE_B_FL_32(( M_CAN_RXF1C), registerValue);
#ifdef FUNCTION_SAFETY
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        temp = AHB_READ_B_FL_32(M_CAN_RXF1C);
        if (temp != registerValue) {
            AHB_WRITE_B_FL_32((M_CAN_RXF1C), registerValue);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif

	/* RX Buffers
	 * Since RXBuffers are a little weird, you don't actually tell MCAN how many elements you have. Instead,
	 * you tell it indirectly through filters.
	 * For example, you would have to setup a filter to tell it which value to go to
	 * Rx Buffer Configuration Register: 0x10AC
	 * */
	MRAMValue = MRAMConfig->RxBufNumElements;
	if (MRAMValue > 64)
		MRAMValue = 64;

	if (MRAMValue == 0) {
		registerValue = 0;
	} else {
		registerValue = ((uint32_t)startAddress);
	}
	startAddress += (((uint32_t)MCAN_TXRXESC_DataByteValue(MRAMConfig->RxBufElementSize) + 8) * (uint16_t)MRAMValue);
	AHB_WRITE_B_FL_32(M_CAN_RXBC, registerValue);
#ifdef FUNCTION_SAFETY
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        temp = AHB_READ_B_FL_32(M_CAN_RXBC);
        if (temp != registerValue) {
            AHB_WRITE_B_FL_32((M_CAN_RXBC), registerValue);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif
	/* TX Event FIFO
	 * Tx Event FIFO Configuration Register: 0x10F0
	 * */
	/* Number of Tx Event FIFO elements: 1~32*/
	MRAMValue = MRAMConfig->TxEventFIFONumElements;
	if (MRAMValue > 32)
		MRAMValue = 32;

	if (MRAMValue == 0) {
		registerValue = 0;
	} else {
		registerValue = ((uint32_t)(MRAMValue) << 16) | ((uint32_t)startAddress);
	}
	startAddress += (8 * (uint16_t)MRAMValue);   /* 8 bytes per element*/
	AHB_WRITE_B_FL_32(( M_CAN_TXEFC), registerValue);
#ifdef FUNCTION_SAFETY
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        temp = AHB_READ_B_FL_32(M_CAN_TXEFC);
        if (temp != registerValue) {
            AHB_WRITE_B_FL_32((M_CAN_TXEFC), registerValue);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif
	/* TX Buffer
	 * Tx Buffer Configuration Register: 0x10C0
	 * */
	/* Number of Tx Buffers used for Tx FIFO/Queue: 1~32*/
	MRAMValue = MRAMConfig->TxBufferNumElements;
	if (MRAMValue > 32)
		MRAMValue = 32;

	// The below line sets TFQM to 0 (FIFO mode, not queue mode), and sets all registers to be generic non-dedicated buffers.
	if (MRAMValue == 0) {
		registerValue = 0;
	} else {
		registerValue = ((uint32_t)(MRAMValue) << 24) | ((uint32_t)startAddress); //| 0x40000000;
	}
	AHB_WRITE_B_FL_32(( M_CAN_TXBC), registerValue);
#ifdef FUNCTION_SAFETY
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        temp = AHB_READ_B_FL_32(M_CAN_TXBC);
        if (temp != registerValue) {
            AHB_WRITE_B_FL_32((M_CAN_TXBC), registerValue);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif

	/* Set the RX Element Size Register
	 * Rx Buffer/FIFO Element Size Configuration Register: 0x10BC
	 * */
	registerValue = ((uint32_t)(MRAMConfig->RxBufElementSize) << 8) | ((uint32_t)(MRAMConfig->Rx1ElementSize) << 4) | (uint32_t)(MRAMConfig->Rx0ElementSize);
	AHB_WRITE_B_FL_32(( M_CAN_RXESC), registerValue);
#ifdef FUNCTION_SAFETY
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        temp = AHB_READ_B_FL_32(M_CAN_RXESC);
        if (temp != registerValue) {
            AHB_WRITE_B_FL_32((M_CAN_RXESC), registerValue);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif
	/* Set the TX Element Size Register
	 * Rx Buffer/FIFO Element Size Configuration Register: 0x10C8
	 * */
	registerValue = (uint32_t)(MRAMConfig->TxBufferElementSize);
	AHB_WRITE_B_FL_32(( M_CAN_TXESC), registerValue);
#ifdef FUNCTION_SAFETY
    for (i = 3; i > 0; i--) {
        /*Readback the written value*/
        temp = AHB_READ_B_FL_32(M_CAN_TXESC);
        if (temp != registerValue) {
            AHB_WRITE_B_FL_32((M_CAN_TXESC), registerValue);
            break;
        } else {
            i=0;
            break;
        }
    }
#endif
	// Turn off the initialization/protected mode if we had to enable it ourselves (this is a register update rather than a fresh config)
	if (cccr != CONFIG_SUCCESS_FIRST) {
		if (TCAN45x0_DisableProtectedRegisters() == CONFIG_FAIL)
			return CONFIG_FAIL;
	}
	return CONFIG_SUCCESS;
}

void TCAN45x0_ClearMRAM()
{
	uint16_t curAddr, endAddr;

	// Need to write 0's to the entire MRAM
	curAddr = MRAM;
	endAddr = MRAM + MRAM_SIZE;

	while (curAddr < endAddr)
	{
		AHB_WRITE_B_FL_32(curAddr, 0x00000000);
		curAddr += 4;
	}

}

uint8_t MCAN_ReadNextFIFO(uint8_t FIFONum, TCAN45x0_RX_HEADER *header, uint8_t dataPayload[])
{
	uint32_t readData;
	uint16_t startAddress;
	uint8_t i, getIndex, elementSize, readBuff[72];

	// Get the get buffer location and size, depending on the source type
	switch (FIFONum)
	{
	default: // RXFIFO0 is default
		readData = AHB_READ_B_FL_32(M_CAN_RXF0S);  /*Rx FIFO 0 Status Register*/
		getIndex = (uint8_t) ((readData & 0x3F00) >> 8);  /*Rx FIFO 0 read index pointer, range 0 to 63*/
		// Get the RX 0 Start location and size...
		readData = AHB_READ_B_FL_32(M_CAN_RXF0C);
		startAddress = (uint16_t)(readData & 0x0000FFFF) + MRAM;
		readData = (AHB_READ_B_FL_32(M_CAN_RXESC) & 0x07);
		elementSize = MCAN_TXRXESC_DataByteValue(readData); // Maximum theoretical data payload supported by this MCAN configuration
		// Calculate the actual start address for the latest index
		startAddress += (((uint32_t)elementSize + 8) * getIndex);
		break;

	case RXFIFO1:
		readData = AHB_READ_B_FL_32(M_CAN_RXF1S);  /*Rx FIFO 1 Status Register*/
		getIndex = (uint8_t) ((readData & 0x3F00) >> 8);
		/* Get the RX 1 Start location and size...*/
		readData = AHB_READ_B_FL_32(M_CAN_RXF1C);
		startAddress = (uint16_t)(readData & 0x0000FFFF) + MRAM;
		readData = (AHB_READ_B_FL_32(M_CAN_RXESC) & 0x70) >> 4;
		elementSize = MCAN_TXRXESC_DataByteValue(readData); // Maximum theoretical data payload supported by this MCAN configuration
		/* Calculate the actual start address for the latest index*/
		startAddress += (((uint32_t)elementSize + 8) * getIndex);
		break;
	}

	AHB_Read_Burst(startAddress, 2, &readBuff[0]);

	/*There are (2+1) 32-bit words returned from the burst read function*/
	/*The first 4 bytes are the dummy data*/
	readData =  (readBuff[4] << 24) | (readBuff[5] << 16) | (readBuff[6] << 8) | (readBuff[7] << 0);
    header->ESI = (readData & 0x80000000) >> 31;
    header->XTD = (readData & 0x40000000) >> 30;
    header->RTR = (readData & 0x20000000) >> 29;

    if (header->XTD)
        header->ID  = (readData & 0x1FFFFFFF);
    else
        header->ID  = (readData & 0x1FFC0000) >> 18;

    readData =  (readBuff[8] << 24) | (readBuff[9] << 16) | (readBuff[10] << 8) | (readBuff[11] << 0);
    header->RXTS    = (readData & 0x0000FFFF);
    header->DLC     = (readData & 0x000F0000) >> 16;
    header->BRS     = (readData & 0x00100000) >> 20;
    header->FDF     = (readData & 0x00200000) >> 21;
    header->FIDX    = (readData & 0x7F000000) >> 24;
    header->ANMF    = (readData & 0x80000000) >> 31;

	// Get the actual data
	// If the data payload size of the header is smaller than the maximum we can store, then update the new element size to read only what we need to (prevents accidentical overflow reading)
	if (MCAN_DLCtoBytes(header->DLC) < elementSize )
		elementSize = MCAN_DLCtoBytes(header->DLC); // Returns the number of data bytes

	// Start a burst read for the number of data bytes we require at the data payload area of the MRAM
	// The equation below ensures that we will always read the correct number of words since the divide truncates any remainders, and we need a ceil()-like function
    AHB_Read_Burst(startAddress+8, (elementSize + 3) >> 2, &readBuff[0]);

    /* swizzle the received data to payload; the first 4 bytes are dummy read*/
    /* Word1 in MRAM: DB3[7:0]--DB2[7:0]--DB1[7:0]--DB0[7:0]
     * Word2 in MRAM: DB7[7:0]--DB6[7:0]--DB5[7:0]--DB4[7:0]
     *
     * TCAN SPI protocol: DB3[7:0](spiData[0])--DB2[7:0](spiData[1])--DB1[7:0]--DB0[7:0]
     * The first 4 bytes are the dummy data
     * */
    for(i=0; i<(elementSize+3); i=i+4){
        dataPayload[i]   = readBuff[i+7];
        dataPayload[i+1] = readBuff[i+6];
        dataPayload[i+2] = readBuff[i+5];
        dataPayload[i+3] = readBuff[i+4];
    }

	// Acknowledge the FIFO read
	switch (FIFONum)
	{
	default: // RXFIFO0
		AHB_WRITE_B_FL_32(M_CAN_RXF0A, getIndex);
		break;

	case RXFIFO1:
		AHB_WRITE_B_FL_32(M_CAN_RXF1A, getIndex);
		break;
	}
	return i-4;	// Return the number of bytes retrieved
}

uint8_t MCAN_ReadRXBuffer(uint8_t bufferNum, TCAN45x0_RX_HEADER *header, uint8_t dataPayload[])
{
	    uint32_t readData;
		uint16_t startAddress;
		uint8_t i, getIndex, elementSize, readBuff[72];

		// Get the get buffer location and size
		getIndex = bufferNum;
		if (getIndex > 64)
			getIndex = 64;

		// Get the RX Buffer Start location and size...
		readData = AHB_READ_B_FL_32(M_CAN_RXBC);
		startAddress = (uint16_t)(readData & 0x0000FFFF) + MRAM;
		readData = (AHB_READ_B_FL_32(M_CAN_RXESC) & 0x0700) >> 8;
		elementSize = MCAN_TXRXESC_DataByteValue(readData); // Maximum theoretical data payload supported by this MCAN configuration
		// Calculate the actual start address for the latest index
		startAddress += (((uint32_t)elementSize + 8) * getIndex);

		AHB_Read_Burst(startAddress, 2, &readBuff[0]);

        /*There are (2+1) 32-bit words returned from the burst read function*/
        /*The first 4 bytes are the dummy data*/
	    readData =  (readBuff[4] << 24) | (readBuff[5] << 16) | (readBuff[6] << 8) | (readBuff[7] << 0);
		header->ESI	= (readData & 0x80000000) >> 31;
		header->XTD	= (readData & 0x40000000) >> 30;
		header->RTR	= (readData & 0x20000000) >> 29;
		if (header->XTD)
			header->ID	= (readData & 0x1FFFFFFF);
		else
			header->ID	= (readData & 0x1FFC0000) >> 18;

	    readData =  (readBuff[8] << 24) | (readBuff[9] << 16) | (readBuff[10] << 8) | (readBuff[11] << 0);
		header->RXTS	= (readData & 0x0000FFFF);
		header->DLC		= (readData & 0x000F0000) >> 16;
		header->BRS		= (readData & 0x00100000) >> 20;
		header->FDF		= (readData & 0x00200000) >> 21;
		header->FIDX	= (readData & 0x7F000000) >> 24;
		header->ANMF	= (readData & 0x80000000) >> 31;

		// Get the actual data
		// If the data payload size of the header is smaller than the maximum we can store, then update the new element size to read only what we need to (prevents accidentical overflow reading)
		if (MCAN_DLCtoBytes(header->DLC) < elementSize )
			elementSize = MCAN_DLCtoBytes(header->DLC); // Returns the number of data bytes

		// Start a burst read for the number of data bytes we require at the data payload area of the MRAM
		// The equation below ensures that we will always read the correct number of words since the divide truncates any remainders, and we need a ceil()-like function
		AHB_Read_Burst(startAddress+8, (elementSize + 3) >> 2, &readBuff[0]);
	    /* swizzle the received data to payload; the first 4 bytes are dummy read*/
	    /* Word1 in MRAM: DB3[7:0]--DB2[7:0]--DB1[7:0]--DB0[7:0]
	     * Word2 in MRAM: DB7[7:0]--DB6[7:0]--DB5[7:0]--DB4[7:0]
	     *
	     * TCAN SPI protocol: DB3[7:0](spiData[0])--DB2[7:0](spiData[1])--DB1[7:0]--DB0[7:0]
	     * */
	    for(i=0; i<(elementSize+3); i=i+4){
	        dataPayload[i]   = readBuff[i+7];
	        dataPayload[i+1] = readBuff[i+6];
	        dataPayload[i+2] = readBuff[i+5];
	        dataPayload[i+3] = readBuff[i+4];
	    }

		// Acknowledge the FIFO read
		if (getIndex < 32)
		{
			AHB_WRITE_B_FL_32(M_CAN_NDAT1, 1 << getIndex);
		} else {
			AHB_WRITE_B_FL_32(M_CAN_NDAT2, 1 << (getIndex-32));
		}

		return (elementSize + 3) >> 2;	// Return the number of bytes retrieved
}


/* MCAN Write to TX FIFO
 * Description: Will write data payload to the TX FIFO, and returns the hex value of the buffer required from the MCAN_TXBAR register
 * Parameters:	position: a 0-63 decimal value. If value is outside the of the configured limits, then method returns 0
 * 				TCAN45x0_TX_HEADER header: Contains the configuration information for the packet.
 * 				dataPayload[]: A uint8_t array that must have at least the number of bytes described in the DLC field in the header
 * Requirements: 	- Must pass the address of a TCAN45x0_TX_HEADER address (& infront of variable name)
 * 					- dataPayload[] must be at least as large as the DLC parameter describes in the header
 *
 * Returns: The hex value of the buffer required from the MCAN_TXBAR register.
 */
uint32_t MCAN_WriteTXFIFO(uint8_t fifoNumber, TCAN45x0_TX_HEADER *header, uint8_t dataPayload[])
{
	// Step 1: Get the start address of the
	uint32_t SPIData;
	uint16_t startAddress;
	uint8_t i, elementSize0, elementSize, temp;
	uint8_t txData[72];

    /* Check Tx FIFO/Queue Status register (TXFQS: 0x10C4) bits [5:0] to make sure the free level
     * is greater than 0 (meaning that at least 1 buffer is open/free) and that TFQF bit is
     * set to 0*/
//	SPIData = AHB_READ_B_FL_32(M_CAN_TXFQS);
//	putIndex = (SPIData >> 0x8) & 0x1F;        /*TFGI[4:0]: TX FIFO Get Index. Changed from 0x0F to 0x1F: QJ, Jan 2019*/

	/* Get the TX Start location and size from Tx Buffer Configuration Register
	 * TXBC: 0x10C0. [16:2] Tx Buffers Start Address Start address of Tx Buffers section in Message RAM (32-bit word address)
	 *               [29:24] Transmit FIFO Size:1-32. Values greater than 32 are interpreted as 32
	 *               [21:16] Number of Dedicated Transmit Buffers:1-32. Values greater than 32 are interpreted as 32
	 * */
	/* TxBufferNumElements is programmed in ConfigureMRAM() */
	SPIData = AHB_READ_B_FL_32(M_CAN_TXBC);
	/* The start address must be on a 4 byte boundary: 0x00, 0x04, 0x08, 0x0C */
	startAddress = (uint16_t)(SPIData & 0x0000FFFF) + 0x8000;  /*MSG RAM starting address is 0x8000*/
	/* Transmit FIFO and queue numbers */
	temp = (uint8_t)((SPIData >> 24) & 0x3F);
	elementSize = temp > 32 ? 32 : temp;
	/* Dedicated transmit buffers*/
	temp = (uint8_t)((SPIData >> 16) & 0x3F);
	elementSize += temp > 32 ? 32 : temp;

	if (fifoNumber > (elementSize-1)) {
		return 0;
	}

	/* Get the actual element size of each TX element from Tx Buffer Element Size Configuration Register
	 * Tx Buffer Data Field Size: 000 - 8 byte data field, 001 - 12 byte data field....
	 * */
    /* The Tx Buffer Data Field Size (TxBufferElementSize) is programmed in ConfigureMRAM()*/
	SPIData = AHB_READ_B_FL_32(M_CAN_TXESC);
	/* Tx Buffer Element Size from TXESC Register + 8*/
	elementSize = MCAN_TXRXESC_DataByteValue(SPIData & 0x07) + 8;

	/* Calculate the actual start address for the latest index*/
	startAddress += ((uint32_t)elementSize * fifoNumber);

	// Now we need to actually check how much data we are writing (because we don't need to fill a 64-byte FIFO if we are sending an 8 byte can packet)
	elementSize0 = (MCAN_DLCtoBytes(header->DLC & 0x0F) + 8) >> 2; // Convert it to words for easier reading by dividing by 4, and only look at data payload
	if (MCAN_DLCtoBytes(header->DLC & 0x0F) % 4) {	// If we don't have a whole word worth of data... We need to round up to the nearest word (by default it truncates). Can be done by simply adding another word.
		elementSize0 += 1;
	}

	/* Read the data, start with a burst read*/

    SPIData = 0;
    SPIData         |= ((uint32_t)header->ESI & 0x01) << 31;
    SPIData         |= ((uint32_t)header->XTD & 0x01) << 30;
    SPIData         |= ((uint32_t)header->RTR & 0x01) << 29;
    if (header->XTD)
        SPIData     |= ((uint32_t)header->ID & 0x1FFFFFFF);
    else
        SPIData     |= ((uint32_t)header->ID & 0x07FF) << 18;

    txData[0] = (SPIData >> 24) & 0xFF;
    txData[1] = (SPIData >> 16) & 0xFF;
    txData[2] = (SPIData >> 8) & 0xFF;
    txData[3] = (SPIData >> 0) & 0xFF;
/*
    if (header->XTD)
        txData[0]  = 0x00000000 | ((uint32_t)header->ESI & 0x01) << 31
                    | ((uint32_t)header->XTD & 0x01) << 30
                    | ((uint32_t)header->RTR & 0x01) << 29
                    | ((uint32_t)header->ID & 0x1FFFFFFF);
    else
        txData[0]  = 0x00000000 | ((uint32_t)header->ESI & 0x01) << 31
                    | ((uint32_t)header->XTD & 0x01) << 30
                    | ((uint32_t)header->RTR & 0x01) << 29
                    | ((uint32_t)header->ID & 0x07FF) << 18;
*/
    SPIData = 0;
    SPIData  |= ((uint32_t)header->DLC & 0x0F) << 16;
    SPIData  |= ((uint32_t)header->BRS & 0x01) << 20;
    SPIData  |= ((uint32_t)header->FDF & 0x01) << 21;
    SPIData  |= ((uint32_t)header->EFC & 0x01) << 23;
    SPIData  |= ((uint32_t)header->MM & 0xFF)  << 24;

    txData[4] = (SPIData >> 24) & 0xFF;
    txData[5] = (SPIData >> 16) & 0xFF;
    txData[6] = (SPIData >> 8)  & 0xFF;
    txData[7] = (SPIData >> 0)  & 0xFF;

/*
    txData[1]  = 0x00000000 | ((uint32_t)header->DLC & 0x0F) << 16
                | ((uint32_t)header->BRS & 0x01) << 20
                | ((uint32_t)header->FDF & 0x01) << 21
                | ((uint32_t)header->EFC & 0x01) << 23
                | ((uint32_t)header->MM & 0xFF)  << 24;
*/

    /* Get the actual data
     * In case the data length code DLC of a Tx Buffer element is configured to a value higher than the
     * Tx Buffer data field size TXESC.TBDS, the bytes not defined by the Tx Buffer are
     * transmitted as “0xCC” (padding bytes).
     * */
    elementSize = MCAN_DLCtoBytes(header->DLC & 0x0F); // Returns the number of data bytes

    /* swizzle the received data to payload; the first 4 bytes are dummy read*/
    /* Word1 in MRAM: DB3[7:0]--DB2[7:0]--DB1[7:0]--DB0[7:0]
     * Word2 in MRAM: DB7[7:0]--DB6[7:0]--DB5[7:0]--DB4[7:0]
     * TCAN SPI protocol: DB3[7:0](spiData[0])--DB2[7:0](spiData[1])--DB1[7:0]--DB0[7:0]
     * */

    for(i=0; i<elementSize; i=i+4){
        txData[i+8]  = dataPayload[i+3];
        txData[i+9]  = dataPayload[i+2];
        txData[i+10] = dataPayload[i+1];
        txData[i+11] = dataPayload[i];
    }
/*
    i = 0;  // Used to count the number of bytes we have read.
    uint8_t j=2;
    while (i < elementSize) {
        SPIData = 0;
        // If elementSize - i < 4, then this means we are on our last word, with a word that is less than 4 bytes long
        if ((elementSize - i) < 4) {
            while (i < elementSize)
            {
                SPIData |= ((uint32_t)dataPayload[i] << ((i % 4) * 8));
                i++;
            }
        } else {
            SPIData |= ((uint32_t)dataPayload[i++]);
            SPIData |= ((uint32_t)dataPayload[i++]) << 8;
            SPIData |= ((uint32_t)dataPayload[i++]) << 16;
            SPIData |= ((uint32_t)dataPayload[i++]) << 24;
        }
        txData[j++] = SPIData;

        if (i > elementSize)
            i = elementSize;
    }
*/

    /* elementSize0 is number of 32-bit words including the header and payload*/
    AHB_Write_Burst(startAddress, &txData[0], elementSize0);
	return 0x00000001 << fifoNumber;	// Return the number of bytes retrieved
}

uint32_t MCAN_ReadTXFIFO(uint8_t fifoNumber, uint8_t *readBuff)
{
    // Step 1: Get the start address of the
    uint32_t SPIData;
    uint16_t startAddress;
    uint8_t i, elementSize, temp;
    uint8_t readData[72];

    /* Check Tx FIFO/Queue Status register (TXFQS: 0x10C4) bits [5:0] to make sure the free level
     * is greater than 0 (meaning that at least 1 buffer is open/free) and that TFQF bit is
     * set to 0*/
    SPIData = AHB_READ_B_FL_32(M_CAN_TXFQS);
//    putIndex = (SPIData >> 0x8) & 0x0F;

    /* Get the TX Start location and size from Tx Buffer Configuration Register
     * TXBC: 0x10C0. [16:2] Tx Buffers Start Address Start address of Tx Buffers section in Message RAM (32-bit word address)
     *               [29:24] Transmit FIFO Size:1-32. Values greater than 32 are interpreted as 32
     *               [21:16] Number of Dedicated Transmit Buffers:1-32. Values greater than 32 are interpreted as 32
     * */
    /* TxBufferNumElements is programmed in ConfigureMRAM() */
    SPIData = AHB_READ_B_FL_32(M_CAN_TXBC);
    /* The start address must be on a 4 byte boundary: 0x00, 0x04, 0x08, 0x0C */
    startAddress = (uint16_t)(SPIData & 0x0000FFFF) + 0x8000;  /*MSG RAM starting address is 0x8000*/
    /* Transmit FIFO and queue numbers */
    temp = (uint8_t)((SPIData >> 24) & 0x3F);
    elementSize = temp > 32 ? 32 : temp;
    /* Dedicated transmit buffers*/
    temp = (uint8_t)((SPIData >> 16) & 0x3F);
    elementSize += temp > 32 ? 32 : temp;

    if (fifoNumber > (elementSize-1)) {
        return 0;
    }

    /* Get the actual element size of each TX element from Tx Buffer Element Size Configuration Register
     * Tx Buffer Data Field Size: 000 - 8 byte data field, 001 - 12 byte data field....
     * */
    /* The Tx Buffer Data Field Size (TxBufferElementSize) is programmed in ConfigureMRAM()*/
    SPIData = AHB_READ_B_FL_32(M_CAN_TXESC);
    /* Tx Buffer Element Size from TXESC Register + 8*/
    elementSize = MCAN_TXRXESC_DataByteValue(SPIData & 0x07) + 8;

    /* Calculate the actual start address for the latest index*/
    startAddress += ((uint32_t)elementSize * fifoNumber);

    /* elementSize0 is number of 32-bit words including the header and payload*/
    AHB_Read_Burst(startAddress, 72, &readData[0]);

    /* swizzle the received data to payload; the first 4 bytes are dummy read*/
    for(i=12; i<(72-4); i=i+4){
        readBuff[i-12]   = readData[i+3];
        readBuff[i-11]   = readData[i+2];
        readBuff[i-10]   = readData[i+1];
        readBuff[i-9]    = readData[i];
    }

    return 0x00000001 << fifoNumber;    // Return the number of bytes retrieved
}

uint8_t MCAN_WriteSIDFilter(uint8_t fifoNumber, TCAN45x0_SID_FILTER *filter)
{
	uint32_t readData, writeData;
	uint16_t startAddress;
	uint8_t getIndex;

	readData = AHB_READ_B_FL_32(M_CAN_SIDFC);
	getIndex = (readData & 0x00FF0000) >> 16;
	if (fifoNumber > getIndex) // Check if the fifo number is valid and within range. If not, then fail
		return STATUS_FAIL;
	else
		getIndex = fifoNumber;

	startAddress = (uint16_t)(readData & 0x0000FFFF) + MRAM;
	// Calculate the actual start address for the latest index
	startAddress += (getIndex << 2);	// Multiply by 4 and add to start address

	writeData = TCAN45x0_REG_VALUE filter;
	AHB_WRITE_B_FL_32(startAddress, writeData);		// Write the value to the register

	readData = AHB_READ_B_FL_32(startAddress);
	if (readData != writeData)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}

uint8_t MCAN_WriteXIDFilter(uint8_t fifoNumber, TCAN45x0_XID_FILTER *filter)
{
	uint32_t readData, writeData;
	uint16_t startAddress;
	uint8_t getIndex;

	readData = AHB_READ_B_FL_32(M_CAN_XIDFC);
	getIndex = (readData & 0x00FF0000) >> 16;
	if (fifoNumber > getIndex) // Check if the fifo number is valid and within range. If not, then fail
		return STATUS_FAIL;
	else
		getIndex = fifoNumber;

	startAddress = (uint16_t)(readData & 0x0000FFFF) + MRAM;
	// Calculate the actual start address for the latest index
	startAddress += (getIndex << 3);	// Multiply by 4 and add to start address

	// Write the 2 words to memory
	writeData = (uint32_t)(filter->EFEC) << 29;
	writeData |= (uint32_t)(filter->EFID1);
	AHB_WRITE_B_FL_32(startAddress, writeData);		// Write the value to the register
	readData = AHB_READ_B_FL_32(startAddress);
	if (readData != writeData)
		return STATUS_FAIL;

	startAddress += 4;
	writeData = (uint32_t)(filter->EFT) << 30;
	writeData |= (uint32_t)(filter->EFID2);
	AHB_WRITE_B_FL_32(startAddress, writeData);		// Write the value to the register
	readData = AHB_READ_B_FL_32(startAddress);
	if (readData != writeData)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}

void MCAN_ReadInterruptRegister(TCAN45x0_CAN_Interrupt_Register *ir)
{
	TCAN45x0_REG_VALUE ir = AHB_READ_B_FL_32(M_CAN_IR);
}

void MCAN_ReadInterruptEnableRegister(TCAN45x0_CAN_Interrupt_Enable_Register *ie)
{
	TCAN45x0_REG_VALUE ie = AHB_READ_B_FL_32(M_CAN_IE);
}

void MCAN_SetInterruptEnableRegister(TCAN45x0_CAN_Interrupt_Enable_Register *ie) {
	AHB_WRITE_B_FL_32(M_CAN_IE, TCAN45x0_REG_VALUE ie);
}

void MCAN_SetInterruptLineEnableRegister(TCAN45x0_CAN_Interrupt_Line_Enable_Register *ile) {
    AHB_WRITE_B_FL_32(M_CAN_ILE, TCAN45x0_REG_VALUE ile);
}

void MCAN_SetInterruptLineSelectRegister(TCAN45x0_CAN_Interrupt_Line_Select_Register *ils) {
    AHB_WRITE_B_FL_32(M_CAN_ILS, TCAN45x0_REG_VALUE ils);
}

uint8_t MCAN_DLCtoBytes(uint8_t input) {
	const static uint8_t lookup[7] = {12, 16, 20, 24, 32, 48, 64};

	if (input < 9)
		return input;

	if (input < 16)
		return lookup[input-9];

	return 0;

}

uint8_t MCAN_TXRXESC_DataByteValue(uint8_t input)
{
	const static unsigned char lookup[8] = {8, 12, 16, 20, 24, 32, 48, 64};
	return lookup[(unsigned int)(input & 0x07)];
}

/* Check if the SPI communication for reading works correctly*/
uint8_t TCAN45x0_Check_spiRead(void)
{
    uint32_t spiDevID0, spiDevID1, spiDevRevNum;
    uint32_t error=0;

    spiDevID0    = AHB_READ_B_FL_32(SPI_DEVICE_ID0);     //0x4E414354
    spiDevID1    = AHB_READ_B_FL_32(SPI_DEVICE_ID1);     //0x30353534
    spiDevRevNum = AHB_READ_B_FL_32(SPI_REVISION);       //0x100; Device REV_ID Major is 1

    if (spiDevID0 != TCAN45x_DEVICE_ID0)
        error++;
    if (spiDevID1 != TCAN45x_DEVICE_ID1)
        error++;
    if (spiDevRevNum != TCAN45x_DEVICE_REV)
        error++;

    if (error == 0 ){
        return SPI_READ_SUCCESS;
    }else{
        return SPI_READ_FAIL;
    }

}

/** This function will copy the initial or current value (depending on the parameter 'type')
*   of the configuration registers to the struct pointed by config_reg
*/
void MCAN_GetMRAMConfigValue(TCAN45x0_MCAN_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {
        config_reg->CONFIG_MCAN_DBTP   = MCAN_DBTP_CONFIGVALUE;     //0x100C
        //config_reg->CONFIG_MCAN_TEST   = MCAN_TEST_CONFIGVALUE;     //0x1010
        config_reg->CONFIG_MCAN_RAMWD  = MCAN_RAMWD_CONFIGVALUE;    //0x1014
        config_reg->CONFIG_MCAN_CCCR   = MCAN_CCCR_CONFIGVALUE;     //0x1018
        config_reg->CONFIG_MCAN_NBTP   = MCAN_NBTP_CONFIGVALUE;     //0x101C
        //config_reg->CONFIG_MCAN_TSCC   = MCAN_TSCC_CONFIGVALUE;     //0x1020
        //config_reg->CONFIG_MCAN_TOCC   = MCAN_TOCC_CONFIGVALUE;     //0x1028
        //config_reg->CONFIG_MCAN_TDCR   = MCAN_TDCR_CONFIGVALUE;     //0x1048
        //config_reg->CONFIG_MCAN_IR     = MCAN_IR_CONFIGVALUE;       //0x1050
        config_reg->CONFIG_MCAN_IE     = MCAN_IE_CONFIGVALUE;       //0x1054
        config_reg->CONFIG_MCAN_ILS    = MCAN_ILS_CONFIGVALUE;      //0x1058
        config_reg->CONFIG_MCAN_ILE    = MCAN_ILE_CONFIGVALUE;      //0x105C
        config_reg->CONFIG_MCAN_GFC    = MCAN_GFC_CONFIGVALUE;      //0x1080
        config_reg->CONFIG_MCAN_SIDFC  = MCAN_SIDFC_CONFIGVALUE;    //0x1084
        config_reg->CONFIG_MCAN_XIDFC  = MCAN_XIDFC_CONFIGVALUE;    //0x1088
        config_reg->CONFIG_MCAN_XIDAM  = MCAN_XIDAM_CONFIGVALUE;    //0x1090
        config_reg->CONFIG_MCAN_RXF0C  = MCAN_RXF0C_CONFIGVALUE;    //0x10A0
        config_reg->CONFIG_MCAN_RXF1C  = MCAN_RXF1C_CONFIGVALUE;    //0x10B0
        config_reg->CONFIG_MCAN_RXESC  = MCAN_RXESC_CONFIGVALUE;    //0x10BC
        config_reg->CONFIG_MCAN_TXBC   = MCAN_TXBC_CONFIGVALUE;     //0x10C0
        config_reg->CONFIG_MCAN_TXESC  = MCAN_TXESC_CONFIGVALUE;    //0x10C8
        config_reg->CONFIG_MCAN_TXBTIE = MCAN_TXBTIE_CONFIGVALUE;   //0x10E0
        config_reg->CONFIG_MCAN_TXBCIE = MCAN_TXBCIE_CONFIGVALUE;   //0x10E4
        config_reg->CONFIG_MCAN_TXEFC  = MCAN_TXEFC_CONFIGVALUE;    //0x10F0
    }
    else
    {
         config_reg->CONFIG_MCAN_DBTP   = AHB_READ_B_FL_32(M_CAN_DBTP);     //0x100C
         //config_reg->CONFIG_MCAN_TEST   = AHB_READ_B_FL_32(M_CAN_TEST);     //0x1010
         config_reg->CONFIG_MCAN_RAMWD  = AHB_READ_B_FL_32(M_CAN_RWD);      //0x1014
         config_reg->CONFIG_MCAN_CCCR   = AHB_READ_B_FL_32(M_CAN_CCCR);     //0x1018
         config_reg->CONFIG_MCAN_NBTP   = AHB_READ_B_FL_32(M_CAN_NBTP);     //0x101C
         //config_reg->CONFIG_MCAN_TSCC   = AHB_READ_B_FL_32(M_CAN_TSCC);     //0x1020
         //config_reg->CONFIG_MCAN_TOCC   = AHB_READ_B_FL_32(M_CAN_TOCC);     //0x1028
         //config_reg->CONFIG_MCAN_TDCR   = AHB_READ_B_FL_32(M_CAN_TDCR);     //0x1048
         //config_reg->CONFIG_MCAN_IR     = AHB_READ_B_FL_32(M_CAN_IR);       //0x1050
         config_reg->CONFIG_MCAN_IE     = AHB_READ_B_FL_32(M_CAN_IE);       //0x1054
         config_reg->CONFIG_MCAN_ILS    = AHB_READ_B_FL_32(M_CAN_ILS);      //0x1058
         config_reg->CONFIG_MCAN_ILE    = AHB_READ_B_FL_32(M_CAN_ILE);      //0x105C
         config_reg->CONFIG_MCAN_GFC    = AHB_READ_B_FL_32(M_CAN_GFC);      //0x1080
         config_reg->CONFIG_MCAN_SIDFC  = AHB_READ_B_FL_32(M_CAN_SIDFC);    //0x1084
         config_reg->CONFIG_MCAN_XIDFC  = AHB_READ_B_FL_32(M_CAN_XIDFC);    //0x1088
         config_reg->CONFIG_MCAN_XIDAM  = AHB_READ_B_FL_32(M_CAN_XIDAM);    //0x1090
         config_reg->CONFIG_MCAN_RXF0C  = AHB_READ_B_FL_32(M_CAN_RXF0C);    //0x10A0
         config_reg->CONFIG_MCAN_RXF1C  = AHB_READ_B_FL_32(M_CAN_RXF1C);    //0x10B0
         config_reg->CONFIG_MCAN_RXESC  = AHB_READ_B_FL_32(M_CAN_RXESC);    //0x10BC
         config_reg->CONFIG_MCAN_TXBC   = AHB_READ_B_FL_32(M_CAN_TXBC);     //0x10C0
         config_reg->CONFIG_MCAN_TXESC  = AHB_READ_B_FL_32(M_CAN_TXESC);    //0x10C8
         config_reg->CONFIG_MCAN_TXBTIE = AHB_READ_B_FL_32(M_CAN_TXBTIE);   //0x10E0
         config_reg->CONFIG_MCAN_TXBCIE = AHB_READ_B_FL_32(M_CAN_TXBCIE);   //0x10E4
         config_reg->CONFIG_MCAN_TXEFC  = AHB_READ_B_FL_32(M_CAN_TXEFC);    //0x10F0
    }
}

void MCAN_GetDevConfigValue(TCAN45x0_Device_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {
        config_reg->CONFIG_DEV_MODE_PINS            = DEV_MODES_CONFIGVALUE;     //0x0800
        config_reg->CONFIG_DEV_TIMESTAMP_PRESCALER  = DEV_TSTAMP_CONFIGVALUE;    //0x0804
        config_reg->CONFIG_DEV_TEST_REGISTERS       = DEV_TEST_CONFIGVALUE;      //0x0808
        config_reg->CONFIG_DEV_IE                   = DEV_IE_CONFIGVALUE;        //0x0830

    }
    else
    {
        config_reg->CONFIG_DEV_MODE_PINS            = AHB_READ_B_FL_32(DEV_MODE_PINS);
        config_reg->CONFIG_DEV_TIMESTAMP_PRESCALER  = AHB_READ_B_FL_32(DEV_TIMESTAMP_PRESCALER);
        config_reg->CONFIG_DEV_TEST_REGISTERS       = AHB_READ_B_FL_32(DEV_TEST_REGISTERS);
        config_reg->CONFIG_DEV_IE                   = AHB_READ_B_FL_32(DEV_IE);
    }
}

