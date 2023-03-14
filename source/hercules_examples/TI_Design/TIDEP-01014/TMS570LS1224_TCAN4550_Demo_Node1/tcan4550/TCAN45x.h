/*
 * TCAN45x.h
 *
 *  Updated on Feb 22, 2018 for TMS570 MCU; QJ Wang; qjwang@ti.com
 *  First created on: Apr 3, 2017 for MSP430 MCU; Jonathan Valdez
 *
 *  Information: This file stores the general setup methods to be used to setup the TCAN4550
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

#include "sys_common.h"


#define CONFIG_SUCCESS_FIRST	0x02
#define CONFIG_SUCCESS			0x01
#define CONFIG_FAIL				0x00

#define STATUS_SUCCESS  0x01
#define STATUS_FAIL     0x00

#define SPI_READ_SUCCESS  0x01
#define SPI_READ_FAIL     0x00

typedef struct TCAN45x0_DevID_reg
{
    uint32 Device_ID0;   //TCAN
    uint32 Device_ID1;   //4550
    uint32 Device_REV;
}TCAN45x0_DevID_reg_t;


typedef struct TCAN45x0_Device_config_reg
{
    uint32 CONFIG_DEV_MODE_PINS;
    uint32 CONFIG_DEV_TIMESTAMP_PRESCALER;
    uint32 CONFIG_DEV_TEST_REGISTERS;
    uint32 CONFIG_DEV_IE;
}TCAN45x0_Device_config_reg_t;

typedef struct TCAN45x0_MCAN_config_reg
{
    uint32 CONFIG_MCAN_DBTP;     //0x100C
    uint32 CONFIG_MCAN_TEST;     //0x1010
    uint32 CONFIG_MCAN_RAMWD;    //0x1014
    uint32 CONFIG_MCAN_CCCR;     //0x1018
    uint32 CONFIG_MCAN_NBTP;     //0x101C

    uint32 CONFIG_MCAN_TSCC;     //0x1020
    uint32 CONFIG_MCAN_TOCC;     //0x1028

    uint32 CONFIG_MCAN_TDCR;     //0x1048
    uint32 CONFIG_MCAN_IR;       //0x1050
    uint32 CONFIG_MCAN_IE;       //0x1054
    uint32 CONFIG_MCAN_ILS;      //0x1058
    uint32 CONFIG_MCAN_ILE;      //0x105C

    uint32 CONFIG_MCAN_GFC;      //0x1080
    uint32 CONFIG_MCAN_SIDFC;    //0x1084
    uint32 CONFIG_MCAN_XIDFC;    //0x1088
    uint32 CONFIG_MCAN_XIDAM;    //0x1090

    uint32 CONFIG_MCAN_RXF0C;    //0x10A0
    uint32 CONFIG_MCAN_RXF0S;    //0x10A4
    uint32 CONFIG_MCAN_RXF0A;    //0x10A8
    uint32 CONFIG_MCAN_RXBC;     //0x10AC
    uint32 CONFIG_MCAN_RXF1C;    //0x10B0
    uint32 CONFIG_MCAN_RXF1S;    //0x10B4
    uint32 CONFIG_MCAN_RXF1A;    //0x10B8
    uint32 CONFIG_MCAN_RXESC;    //0x10BC
    uint32 CONFIG_MCAN_TXBC;     //0x10C0
    uint32 CONFIG_MCAN_TXFQS;    //0x10C4
    uint32 CONFIG_MCAN_TXESC;    //0x10C8
    uint32 CONFIG_MCAN_TXBRP;    //0x10CC
    uint32 CONFIG_MCAN_TXBAR;    //0x10D0
    uint32 CONFIG_MCAN_TXBCR;    //0x10D4
    uint32 CONFIG_MCAN_TXBTO;    //0x10D8
    uint32 CONFIG_MCAN_TXBCF;    //0x10DC
    uint32 CONFIG_MCAN_TXBTIE;   //0x10E0
    uint32 CONFIG_MCAN_TXBCIE;   //0x10E4
    uint32 CONFIG_MCAN_TXEFC;    //0x10F0
    uint32 CONFIG_MCAN_TXEFS;    //0x10F4
    uint32 CONFIG_MCAN_TXEFA;    //0x10F8
}TCAN45x0_MCAN_config_reg_t;


//*****************************************************************************
//
//! \brief Used to setup the timing parameters of the MCAN module
//
//*****************************************************************************
typedef struct TCAN45x0_CANFD_Timing
{

	//! DBRP: The prescaler value from the MCAN system clock. Actual value is this register + 1.
	//! \n Valid range is: 0 to 31
	uint8_t DataBitRatePrescaler : 5;

	//! DTSEG1: Data time segment 1 + prop segment value. Actual value is this register + 1.
	//! \n Valid values are: 0 to 31
	uint8_t DataTimeSeg1andProp : 5;

	//! DTSEG2: Data time segment 2. Actual value is this register + 1.
	//! \n Valid values are: 0 to 15
	uint8_t DataTimeSeg2 : 4;

	//! DSJW: Data Resynchronization jump width. Actual value is this register + 1.
	//! \n Valid values are: 0 to 15
	uint8_t DataSyncJumpWidth : 4;

	//! TDCO: Transmitter delay compensation offset.
	//! \n Valid values are 0 to 127 mtq
	uint8_t TDCOffset : 7;

	//! TDCO: Transmitter delay compensation offset.
	//! \n Valid values are 0 to 127 mtq
	uint8_t TDCFilter : 7;

} TCAN45x0_CANFD_Timing;


typedef struct TCAN45x0_Nominal_Timing
{
	//! NBRP: The prescaler value from the MCAN system clock. Actual value is this register + 1.
	//! \n Valid range is: 0 to 511
	uint16_t NominalBitRatePrescaler : 9;

	//! NTSEG1: Data time segment 1 + prop segment value. Actual value is this register + 1.
	//! \n Valid values are: 1 to 255
	uint8_t NominalTimeSeg1andProp : 8;

	//! NTSEG2: Data time segment 2. Actual value is this register + 1.
	//! \n Valid values are: 1 to 127
	uint8_t NominalTimeSeg2 : 7;

	//! NSJW: Nominal time Resynchronization jump width. Actual value is this register + 1.
	//! \n Valid values are: 0 to 127
	uint8_t NominalSyncJumpWidth : 7;
} TCAN45x0_Nominal_Timing;


#define MRAM_8_Byte_Data		0x0
#define MRAM_12_Byte_Data		0x1
#define MRAM_16_Byte_Data		0x2
#define MRAM_20_Byte_Data		0x3
#define MRAM_24_Byte_Data		0x4
#define MRAM_32_Byte_Data		0x5
#define MRAM_48_Byte_Data		0x6
#define MRAM_64_Byte_Data		0x7
typedef struct TCAN45x0_MRAM_Config
{

	/************************
	 *  	ID Elements		*
	 ************************/

	//! Standard ID Number of Elements: The number of 11-bit filters the user would like.
	//! \n Valid range is: 0 to 128
	uint8_t SIDNumElements : 8;

	//! Extended ID Number of Elements: The number of 29-bit filters the user would like.
	//! \n Valid range is: 0 to 64
	uint8_t XIDNumElements : 7;


	/************************
	 *  RX FIFO Elements	*
	 ************************/

	//! RX FIFO 0 number of elements: The number of elements for the RX FIFO 0
	//! \n Valid range is: 0 to 64
	uint8_t Rx0NumElements : 7;

	//! RX FIFO 0 element size: The number of bytes for the RX 0 FIFO (data payload)
	//! \n Valid values are:
	//! \n MRAM_8_Byte_Data		: 0b000
	//! \n MRAM_12_Byte_Data	: 0b001
	//! \n MRAM_16_Byte_Data	: 0b010
	//! \n MRAM_20_Byte_Data	: 0b011
	//! \n MRAM_24_Byte_Data	: 0b100
	//! \n MRAM_32_Byte_Data	: 0b101
	//! \n MRAM_48_Byte_Data	: 0b110
	//! \n MRAM_64_Byte_Data	: 0b111
	uint8_t Rx0ElementSize : 3;

	//! RX FIFO 1 number of elements: The number of elements for the RX FIFO 1
	//! \n Valid range is: 0 to 64
	uint8_t Rx1NumElements : 7;

	//! RX FIFO 1 element size: The number of bytes for the RX 1 FIFO (data payload)
	//! \n Valid values are:
	//! \n MRAM_8_Byte_Data		: 0b000
	//! \n MRAM_12_Byte_Data	: 0b001
	//! \n MRAM_16_Byte_Data	: 0b010
	//! \n MRAM_20_Byte_Data	: 0b011
	//! \n MRAM_24_Byte_Data	: 0b100
	//! \n MRAM_32_Byte_Data	: 0b101
	//! \n MRAM_48_Byte_Data	: 0b110
	//! \n MRAM_64_Byte_Data	: 0b111
	uint8_t Rx1ElementSize : 3;

	//! RX Buffers number of elements: The number of elements for the RX Buffers (Not the FIFO)
	//! \n Valid range is: 0 to 64
	uint8_t RxBufNumElements : 7;

	//! RX Buffers element size: The number of bytes for the RX Buffers (data payload), not the FIFO
	//! \n Valid values are:
	//! \n MRAM_8_Byte_Data		: 0b000
	//! \n MRAM_12_Byte_Data	: 0b001
	//! \n MRAM_16_Byte_Data	: 0b010
	//! \n MRAM_20_Byte_Data	: 0b011
	//! \n MRAM_24_Byte_Data	: 0b100
	//! \n MRAM_32_Byte_Data	: 0b101
	//! \n MRAM_48_Byte_Data	: 0b110
	//! \n MRAM_64_Byte_Data	: 0b111
	uint8_t RxBufElementSize : 3;

	/************************
	 *  TX Buffer Elements	*
	 ************************/

	//! TX Event FIFO number of elements: The number of elements for the TX Event FIFO
	//! \n Valid range is: 0 to 32
	uint8_t TxEventFIFONumElements : 6;

	//! TX Buffers number of elements: The number of elements for the TX Buffers
	//! \n Valid range is: 0 to 32
	uint8_t TxBufferNumElements : 6;

	//! TX Buffers element size: The number of bytes for the TX Buffers (data payload)
	//! \n Valid values are:
	//! \n MRAM_8_Byte_Data		: 0b000
	//! \n MRAM_12_Byte_Data	: 0b001
	//! \n MRAM_16_Byte_Data	: 0b010
	//! \n MRAM_20_Byte_Data	: 0b011
	//! \n MRAM_24_Byte_Data	: 0b100
	//! \n MRAM_32_Byte_Data	: 0b101
	//! \n MRAM_48_Byte_Data	: 0b110
	//! \n MRAM_64_Byte_Data	: 0b111
	uint8_t TxBufferElementSize : 3;

} TCAN45x0_MRAM_Config;


#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
typedef struct TCAN45x0_CCCR_Config {
	uint8_t reserved : 2;

	//! ASM: Restricted Operation Mode
	uint8_t ASM : 1;

	uint8_t reserved2 : 1;

	//! CSR: Clock stop request
	uint8_t CSR : 1;

	//! MON: Bus monitoring mode
	uint8_t MON : 1;

	//! DAR: Disable automatic retransmission
	uint8_t DAR : 1;

	//! TEST: Test mode enable
	uint8_t TEST : 1;

	//! FDOE: Can FD mode enabled
	uint8_t FDOE : 1;

	//! BRSE: Bit rate switch enabled for can FD
	uint8_t BRSE : 1;

	uint8_t reserved3 : 2;

	//! PXHD: Protocol exception handling disable
	//! 0 = Protocol exception handling enabled [default]
	//! 1 = protocol exception handling disabled
	uint8_t PXHD : 1;

	//! EFBI: Edge filtering during bus integration. 0 Disables this [default]
	uint8_t EFBI : 1;

	//! TXP: Transmit Pause: Pause for 2 can bit times before next transmission
	uint8_t TXP : 1;

	//! NSIO: Non Iso Operation
	//! 0: CAN FD frame format according to ISO 11898-1:2015 [default]
	//! 1: CAN FD frame format according to Bosch CAN FD Spec v1
	uint8_t NISO : 1;
	uint16_t cccr_rsv0 : 16;
} TCAN45x0_CCCR_Config;

#else
typedef struct TCAN45x0_CCCR_Config {
    uint16_t cccr_rsv0 : 16;
    uint8_t NISO : 1;
    uint8_t TXP : 1;
    uint8_t EFBI : 1;
    uint8_t PXHD : 1;
    uint8_t reserved3 : 2;

    //! BRSE: Bit rate switch enabled for can FD
    uint8_t BRSE : 1;

    //! FDOE: Can FD mode enabled
    uint8_t FDOE : 1;

    //! TEST: Test mode enable
    uint8_t TEST : 1;

    //! DAR: Disable automatic retransmission
    uint8_t DAR : 1;
    //! MON: Bus monitoring mode
    uint8_t MON : 1;
    //! CSR: Clock stop request
    uint8_t CSR : 1;
    uint8_t reserved2 : 1;
    //! ASM: Restricted Operation Mode
    uint8_t ASM : 1;
    uint8_t reserved : 2;
} TCAN45x0_CCCR_Config;
#endif


#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
typedef struct TCAN45x0_CAN_Interrupt_Register
{

	//! IR[0] RF0N: Rx FIFO 0 new message
	uint8_t RF0N : 1;

	//! IR[1] RF0W: Rx FIFO 0 watermark reached
	uint8_t RF0W : 1;

	//! IR[2] RF0F: Rx FIFO 0 full
	uint8_t RF0F : 1;

	//! IR[3] RF0L: Rx FIFO 0 message lost
	uint8_t RF0L : 1;

	//! IR[4] RF1N: Rx FIFO 1 new message
	uint8_t RF1N : 1;

	//! IR[5]  RF1W: RX FIFO 1 watermark reached
	uint8_t RF1W : 1;

	//! IR[6] RF1F: Rx FIFO 1 full
	uint8_t RF1F : 1;

	//! IR[7] RF1L: Rx FIFO 1 message lost
	uint8_t RF1L : 1;

	//! IR[8] HPM: High priority message
	uint8_t HPM : 1;

	//! IR[9] TC: Transmission completed
	uint8_t TC : 1;

	//! IR[10] TCF: Transmission cancellation finished
	uint8_t TCF : 1;

	//! IR[11] TFE: Tx FIFO Empty
	uint8_t TFE : 1;

	//! IR[12] TEFN: Tx Event FIFO new entry
	uint8_t TEFN : 1;

	//! IR[13] TEFW: Tx Event FIFO watermark reached
	uint8_t TEFW : 1;

	//! IR[14] TEFF: Tx Event FIFO full
	uint8_t TEFF : 1;

	//! IR[15] TEFL: Tx Event FIFO element lost
	uint8_t TEFL : 1;

	//! IR[16] TSW: Timestamp wraparound
	uint8_t TSW : 1;

	//! IR[17] MRAF: Message RAM access failure
	uint8_t MRAF : 1;

	//! IR[18] TOO: Time out occured
	uint8_t TOO : 1;

	//! IR[19] DRX: Message stored to dedicated RX buffer
	uint8_t DRX : 1;

	//! IR[20] BEC: MRAM Bit error corrected
	uint8_t BEC : 1;

	//! IR[21] BEU: MRAM Bit error uncorrected
	uint8_t BEU : 1;

	//! IR[22] ELO: Error logging overflow
	uint8_t ELO : 1;

	//! IR[23] EP: Error_passive status changed
	uint8_t EP : 1;

	//! IR[24] EW: Error_warning status changed
	uint8_t EW : 1;

	//! IR[25] BO: Bus_off status changed
	uint8_t BO : 1;

	//! IR[26] WDI: MRAM Watchdog Interrupt
	uint8_t WDI : 1;

	//! IR[27] PEA Protocol Error in arbitration phase (nominal bit time used)
	uint8_t PEA : 1;

	//! IR[28] PED: Protocol error in data phase (data bit time is used)
	uint8_t PED : 1;

	//! IR[29] ARA: Access to reserved address
	uint8_t ARA : 1;

	//! IR[30:31] Reserved, not writable
	uint8_t reserved : 2;

} TCAN45x0_CAN_Interrupt_Register;
#else
typedef struct TCAN45x0_CAN_Interrupt_Register
{
    //! IR[30:31] Reserved, not writable
    uint8_t reserved : 2;
    //! IR[29] ARA: Access to reserved address
    uint8_t ARA : 1;
    //! IR[28] PED: Protocol error in data phase (data bit time is used)
    uint8_t PED : 1;
    //! IR[27] PEA Protocol Error in arbitration phase (nominal bit time used)
    uint8_t PEA : 1;
    //! IR[26] WDI: MRAM Watchdog Interrupt
    uint8_t WDI : 1;
    //! IR[25] BO: Bus_off status changed
    uint8_t BO : 1;
    //! IR[24] EW: Error_warning status changed
    uint8_t EW : 1;
    //! IR[23] EP: Error_passive status changed
    uint8_t EP : 1;
    //! IR[22] ELO: Error logging overflow
    uint8_t ELO : 1;
    //! IR[21] BEU: MRAM Bit error uncorrected
    uint8_t BEU : 1;
    //! IR[20] BEC: MRAM Bit error corrected
    uint8_t BEC : 1;
    //! IR[19] DRX: Message stored to dedicated RX buffer
    uint8_t DRX : 1;
    //! IR[18] TOO: Time out occured
    uint8_t TOO : 1;
    //! IR[17] MRAF: Message RAM access failure
    uint8_t MRAF : 1;
    //! IR[16] TSW: Timestamp wraparound
    uint8_t TSW : 1;
    //! IR[15] TEFL: Tx Event FIFO element lost
    uint8_t TEFL : 1;
    //! IR[14] TEFF: Tx Event FIFO full
    uint8_t TEFF : 1;
    //! IR[13] TEFW: Tx Event FIFO watermark reached
    uint8_t TEFW : 1;
    //! IR[12] TEFN: Tx Event FIFO new entry
    uint8_t TEFN : 1;
    //! IR[11] TFE: Tx FIFO Empty
    uint8_t TFE : 1;
    //! IR[10] TCF: Transmission cancellation finished
    uint8_t TCF : 1;
    //! IR[9] TC: Transmission completed
    uint8_t TC : 1;
    //! IR[8] HPM: High priority message
    uint8_t HPM : 1;
    //! IR[7] RF1L: Rx FIFO 1 message lost
    uint8_t RF1L : 1;
    //! IR[6] RF1F: Rx FIFO 1 full
    uint8_t RF1F : 1;
    //! IR[5]  RF1W: RX FIFO 1 watermark reached
    uint8_t RF1W : 1;
    //! IR[4] RF1N: Rx FIFO 1 new message
    uint8_t RF1N : 1;
    //! IR[3] RF0L: Rx FIFO 0 message lost
    uint8_t RF0L : 1;
    //! IR[2] RF0F: Rx FIFO 0 full
    uint8_t RF0F : 1;
    //! IR[1] RF0W: Rx FIFO 0 watermark reached
    uint8_t RF0W : 1;
    //! IR[0] RF0N: Rx FIFO 0 new message
    uint8_t RF0N : 1;
} TCAN45x0_CAN_Interrupt_Register;
#endif

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
typedef struct TCAN45x0_CAN_Interrupt_Enable_Register
{

	//! IE[0] RF0NE: Rx FIFO 0 new message
	uint8_t RF0NE : 1;

	//! IE[1] RF0WE: Rx FIFO 0 watermark reached
	uint8_t RF0WE : 1;

	//! IE[2] RF0FE: Rx FIFO 0 full
	uint8_t RF0FE : 1;

	//! IE[3] RF0LE: Rx FIFO 0 message lost
	uint8_t RF0LE : 1;

	//! IE[4] RF1NE: Rx FIFO 1 new message
	uint8_t RF1NE : 1;

	//! IE[5]  RF1WE: RX FIFO 1 watermark reached
	uint8_t RF1WE : 1;

	//! IE[6] RF1FE: Rx FIFO 1 full
	uint8_t RF1FE : 1;

	//! IE[7] RF1LE: Rx FIFO 1 message lost
	uint8_t RF1LE : 1;

	//! IE[8] HPME: High priority message
	uint8_t HPME : 1;

	//! IE[9] TCE: Transmission completed
	uint8_t TCE : 1;

	//! IE[10] TCFE: Transmission cancellation finished
	uint8_t TCFE : 1;

	//! IE[11] TFEE: Tx FIFO Empty
	uint8_t TFEE : 1;

	//! IE[12] TEFNE: Tx Event FIFO new entry
	uint8_t TEFNE : 1;

	//! IE[13] TEFWE: Tx Event FIFO watermark reached
	uint8_t TEFWE : 1;

	//! IE[14] TEFFE: Tx Event FIFO full
	uint8_t TEFFE : 1;

	//! IE[15] TEFLE: Tx Event FIFO element lost
	uint8_t TEFLE : 1;

	//! IE[16] TSWE: Timestamp wraparound
	uint8_t TSWE : 1;

	//! IE[17] MRAFE: Message RAM access failure
	uint8_t MRAFE : 1;

	//! IE[18] TOOE: Time out occured
	uint8_t TOOE : 1;

	//! IE[19] DRXE: Message stored to dedicated RX buffer
	uint8_t DRXE : 1;

	//! IE[20] BECE: MRAM Bit error corrected
	uint8_t BECE : 1;

	//! IE[21] BEUE: MRAM Bit error uncorrected
	uint8_t BEUE : 1;

	//! IE[22] ELOE: Error logging overflow
	uint8_t ELOE : 1;

	//! IE[23] EPE: Error_passive status changed
	uint8_t EPE : 1;

	//! IE[24] EWE: Error_warning status changed
	uint8_t EWE : 1;

	//! IE[25] BOE: Bus_off status changed
	uint8_t BOE : 1;

	//! IE[26] WDIE: MRAM Watchdog Interrupt
	uint8_t WDIE : 1;

	//! IE[27] PEAE Protocol Error in arbitration phase (nominal bit time used)
	uint8_t PEAE : 1;

	//! IE[28] PEDE: Protocol error in data phase (data bit time is used)
	uint8_t PEDE : 1;

	//! IE[29] ARAE: Access to reserved address
	uint8_t ARAE : 1;

	//! IE[30:31] Reserved, not writable
	uint8_t reserved : 2;

} TCAN45x0_CAN_Interrupt_Enable_Register;
#else
typedef struct TCAN45x0_CAN_Interrupt_Enable_Register
{
    //! IE[30:31] Reserved, not writable
    uint8_t reserved : 2;
    //! IE[29] ARAE: Access to reserved address
    uint8_t ARAE : 1;
    //! IE[28] PEDE: Protocol error in data phase (data bit time is used)
    uint8_t PEDE : 1;
    //! IE[27] PEAE Protocol Error in arbitration phase (nominal bit time used)
    uint8_t PEAE : 1;
    //! IE[26] WDIE: MRAM Watchdog Interrupt
    uint8_t WDIE : 1;
    //! IE[25] BOE: Bus_off status changed
    uint8_t BOE : 1;
    //! IE[24] EWE: Error_warning status changed
    uint8_t EWE : 1;
    //! IE[23] EPE: Error_passive status changed
    uint8_t EPE : 1;
    //! IE[22] ELOE: Error logging overflow
    uint8_t ELOE : 1;
    //! IE[21] BEUE: MRAM Bit error uncorrected
    uint8_t BEUE : 1;
    //! IE[20] BECE: MRAM Bit error corrected
    uint8_t BECE : 1;
    //! IE[19] DRXE: Message stored to dedicated RX buffer
    uint8_t DRXE : 1;
    //! IE[18] TOOE: Time out occured
    uint8_t TOOE : 1;
    //! IE[17] MRAFE: Message RAM access failure
    uint8_t MRAFE : 1;
    //! IE[16] TSWE: Timestamp wraparound
    uint8_t TSWE : 1;
    //! IE[15] TEFLE: Tx Event FIFO element lost
    uint8_t TEFLE : 1;
    //! IE[14] TEFFE: Tx Event FIFO full
    uint8_t TEFFE : 1;
    //! IE[13] TEFWE: Tx Event FIFO watermark reached
    uint8_t TEFWE : 1;
    //! IE[12] TEFNE: Tx Event FIFO new entry
    uint8_t TEFNE : 1;
    //! IE[11] TFEE: Tx FIFO Empty
    uint8_t TFEE : 1;
    //! IE[10] TCFE: Transmission cancellation finished
    uint8_t TCFE : 1;
    //! IE[9] TCE: Transmission completed
    uint8_t TCE : 1;
    //! IE[8] HPME: High priority message
    uint8_t HPME : 1;
    //! IE[7] RF1LE: Rx FIFO 1 message lost
    uint8_t RF1LE : 1;
    //! IE[6] RF1FE: Rx FIFO 1 full
    uint8_t RF1FE : 1;
    //! IE[5]  RF1WE: RX FIFO 1 watermark reached
    uint8_t RF1WE : 1;
    //! IE[4] RF1NE: Rx FIFO 1 new message
    uint8_t RF1NE : 1;
    //! IE[3] RF0LE: Rx FIFO 0 message lost
    uint8_t RF0LE : 1;
    //! IE[2] RF0FE: Rx FIFO 0 full
    uint8_t RF0FE : 1;
    //! IE[1] RF0WE: Rx FIFO 0 watermark reached
    uint8_t RF0WE : 1;
    //! IE[0] RF0NE: Rx FIFO 0 new message
    uint8_t RF0NE : 1;
} TCAN45x0_CAN_Interrupt_Enable_Register;

#endif

/* Interrupt Line Select (address = 1058) [reset = 0000 0000]*/
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
typedef struct TCAN45x0_CAN_Interrupt_Line_Select_Register
{

    //! IE[0] RF0NE: Rx FIFO 0 new message
    uint8_t RF0NL : 1;

    //! IE[1] RF0WE: Rx FIFO 0 watermark reached
    uint8_t RF0WL : 1;

    //! IE[2] RF0FE: Rx FIFO 0 full
    uint8_t RF0FL : 1;

    //! IE[3] RF0LE: Rx FIFO 0 message lost
    uint8_t RF0LL : 1;

    //! IE[4] RF1NE: Rx FIFO 1 new message
    uint8_t RF1NL : 1;

    //! IE[5]  RF1WE: RX FIFO 1 watermark reached
    uint8_t RF1WL : 1;

    //! IE[6] RF1FE: Rx FIFO 1 full
    uint8_t RF1FL : 1;

    //! IE[7] RF1LE: Rx FIFO 1 message lost
    uint8_t RF1LL : 1;

    //! IE[8] HPME: High priority message
    uint8_t HPML : 1;

    //! IE[9] TCE: Transmission completed
    uint8_t TCL : 1;

    //! IE[10] TCFE: Transmission cancellation finished
    uint8_t TCFL : 1;

    //! IE[11] TFEE: Tx FIFO Empty
    uint8_t TFEL : 1;

    //! IE[12] TEFNE: Tx Event FIFO new entry
    uint8_t TEFNL : 1;

    //! IE[13] TEFWE: Tx Event FIFO watermark reached
    uint8_t TEFWL : 1;

    //! IE[14] TEFFE: Tx Event FIFO full
    uint8_t TEFFL : 1;

    //! IE[15] TEFLE: Tx Event FIFO element lost
    uint8_t TEFLL : 1;

    //! IE[16] TSWE: Timestamp wraparound
    uint8_t TSWL : 1;

    //! IE[17] MRAFE: Message RAM access failure
    uint8_t MRAFL : 1;

    //! IE[18] TOOE: Time out occured
    uint8_t TOOL : 1;

    //! IE[19] DRXE: Message stored to dedicated RX buffer
    uint8_t DRXL : 1;

    //! IE[20] BECE: MRAM Bit error corrected
    uint8_t BECL : 1;

    //! IE[21] BEUE: MRAM Bit error uncorrected
    uint8_t BEUL : 1;

    //! IE[22] ELOE: Error logging overflow
    uint8_t ELOL : 1;

    //! IE[23] EPE: Error_passive status changed
    uint8_t EPL : 1;

    //! IE[24] EWE: Error_warning status changed
    uint8_t EWL : 1;

    //! IE[25] BOE: Bus_off status changed
    uint8_t BOL : 1;

    //! IE[26] WDIE: MRAM Watchdog Interrupt
    uint8_t WDIL : 1;

    //! IE[27] PEAE Protocol Error in arbitration phase (nominal bit time used)
    uint8_t PEAL : 1;

    //! IE[28] PEDE: Protocol error in data phase (data bit time is used)
    uint8_t PEDL : 1;

    //! IE[29] ARAE: Access to reserved address
    uint8_t ARAL : 1;

    //! IE[30:31] Reserved, not writable
    uint8_t reserved : 2;

} TCAN45x0_CAN_Interrupt_Line_Select_Register;
#else
typedef struct TCAN45x0_CAN_Interrupt_Line_Select_Register
{
    //! IE[30:31] Reserved, not writable
    uint8_t reserved : 2;
    //! IE[29] ARAE: Access to reserved address
    uint8_t ARAL : 1;
    //! IE[28] PEDE: Protocol error in data phase (data bit time is used)
    uint8_t PEDL : 1;
    //! IE[27] PEAE Protocol Error in arbitration phase (nominal bit time used)
    uint8_t PEAL : 1;
    //! IE[26] WDIE: MRAM Watchdog Interrupt
    uint8_t WDIL : 1;
    //! IE[25] BOE: Bus_off status changed
    uint8_t BOL : 1;
    //! IE[24] EWE: Error_warning status changed
    uint8_t EWL : 1;
    //! IE[23] EPE: Error_passive status changed
    uint8_t EPL : 1;
    //! IE[22] ELOE: Error logging overflow
    uint8_t ELOL : 1;
    //! IE[21] BEUE: MRAM Bit error uncorrected
    uint8_t BEUL : 1;
    //! IE[20] BECE: MRAM Bit error corrected
    uint8_t BECL : 1;
    //! IE[19] DRXE: Message stored to dedicated RX buffer
    uint8_t DRXL : 1;
    //! IE[18] TOOE: Time out occured
    uint8_t TOOL : 1;
    //! IE[17] MRAFE: Message RAM access failure
    uint8_t MRAFL : 1;
    //! IE[16] TSWE: Timestamp wraparound
    uint8_t TSWL : 1;
    //! IE[15] TEFLE: Tx Event FIFO element lost
    uint8_t TEFLL : 1;
    //! IE[14] TEFFE: Tx Event FIFO full
    uint8_t TEFFL : 1;
    //! IE[13] TEFWE: Tx Event FIFO watermark reached
    uint8_t TEFWL : 1;
    //! IE[12] TEFNE: Tx Event FIFO new entry
    uint8_t TEFNL : 1;
    //! IE[11] TFEE: Tx FIFO Empty
    uint8_t TFEL : 1;
    //! IE[10] TCFE: Transmission cancellation finished
    uint8_t TCFL : 1;
    //! IE[9] TCE: Transmission completed
    uint8_t TCL : 1;
    //! IE[8] HPME: High priority message
    uint8_t HPML : 1;
    //! IE[7] RF1LE: Rx FIFO 1 message lost
    uint8_t RF1LL : 1;
    //! IE[6] RF1FE: Rx FIFO 1 full
    uint8_t RF1FL : 1;
    //! IE[5]  RF1WE: RX FIFO 1 watermark reached
    uint8_t RF1WL : 1;
    //! IE[4] RF1NE: Rx FIFO 1 new message
    uint8_t RF1NL : 1;
    //! IE[3] RF0LE: Rx FIFO 0 message lost
    uint8_t RF0LL : 1;
    //! IE[2] RF0FE: Rx FIFO 0 full
    uint8_t RF0FL : 1;
    //! IE[1] RF0WE: Rx FIFO 0 watermark reached
    uint8_t RF0WL : 1;
    //! IE[0] RF0NE: Rx FIFO 0 new message
    uint8_t RF0NL : 1;
} TCAN45x0_CAN_Interrupt_Line_Select_Register;

#endif

/* */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
typedef struct TCAN45x0_CAN_Interrupt_Line_Enable_Register {
    //! EINT0: Enable Interrupt Line 0
    uint8_t EINT0 : 1;
    //! EINT1: Enable Interrupt Line 1
    uint8_t EINT1 : 1;

    uint16_t rserved1 : 14;
    uint16_t rserved0 : 16;
} TCAN45x0_CAN_Interrupt_Line_Enable_Register;
#else
typedef struct TCAN45x0_CAN_Interrupt_Line_Enable_Register {

    uint16_t rserved0 : 16;
    uint16_t rserved1 : 14;
    //! EINT1: Enable Interrupt Line 1
    uint8_t EINT1 : 1;
    //! EINT0: Enable Interrupt Line 0
    uint8_t EINT0 : 1;
} TCAN45x0_CAN_Interrupt_Line_Enable_Register;

#endif

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
typedef struct TCAN45x0_RX_HEADER {
	//! CAN ID
	uint32_t ID : 29;

	//! Remote Transmission Request
	uint8_t RTR : 1;

	//! Extended Identifier
	uint8_t XTD : 1;

	//! Error state indicator
	uint8_t ESI : 1;

	//! Receive time stamp
	uint16_t RXTS : 16;

	//! Data length code
	uint8_t DLC : 4;

	//! Bit rate switch used
	uint8_t BRS : 1;

	//! CAN FD Format
	uint8_t FDF : 1;

	//! Reserved
	uint8_t reserved : 2;

	//! Filter index
	uint8_t FIDX : 7;

	//! Accepted non matching frame
	uint8_t ANMF : 1;

} TCAN45x0_RX_HEADER ;
#else
typedef struct TCAN45x0_RX_HEADER {
    //! Accepted non matching frame
    uint8_t ANMF : 1;
    //! Filter index
    uint8_t FIDX : 7;
    //! Reserved
    uint8_t reserved : 2;
    //! CAN FD Format
    uint8_t FDF : 1;
    //! Bit rate switch used
    uint8_t BRS : 1;
    //! Data length code
    uint8_t DLC : 4;
    //! Receive time stamp
    uint16_t RXTS : 16;
    //! Error state indicator
    uint8_t ESI : 1;
    //! Extended Identifier
    uint8_t XTD : 1;
    //! Remote Transmission Request
    uint8_t RTR : 1;
    //! CAN ID
    uint32_t ID : 29;
} TCAN45x0_RX_HEADER ;
#endif

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
typedef struct TCAN45x0_TX_HEADER {
	//! CAN ID
	uint32_t ID : 29;

	//! Remote Transmission Request
	uint8_t RTR : 1;

	//! Extended Identifier
	uint8_t XTD : 1;

	//! Error state indicator
	uint8_t ESI : 1;

	//! Data length code
	uint8_t DLC : 4;

	//! Bit rate switch used
	uint8_t BRS : 1;

	//! CAN FD Format
	uint8_t FDF : 1;

	//! Reserved
	uint8_t reserved : 1;

	//! Event FIFO Control, store tx events or not
	uint8_t EFC : 1;

	//! Message Marker
	uint8_t MM : 8;

} TCAN45x0_TX_HEADER ;
#else
typedef struct TCAN45x0_TX_HEADER {
    //! Message Marker
    uint8_t MM : 8;
    //! Event FIFO Control, store tx events or not
    uint8_t EFC : 1;
    //! Reserved
    uint8_t reserved : 1;
    //! CAN FD Format
    uint8_t FDF : 1;
    //! Bit rate switch used
    uint8_t BRS : 1;
    //! Data length code
    uint8_t DLC : 4;
    //! Error state indicator
    uint8_t ESI : 1;
    //! Extended Identifier
    uint8_t XTD : 1;
    //! Remote Transmission Request
    uint8_t RTR : 1;
    //! CAN ID
    uint32_t ID : 29;
} TCAN45x0_TX_HEADER ;

#endif

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
typedef struct TCAN45x0_SID_FILTER {
	//!SFID2[10:0]
	uint16_t SFID2 : 11;

	//! Reserved
	uint8_t reserved : 5;

	//! SFID1[10:0]
	uint16_t SFID1 : 11;

	//! SFEC[2:0]   Standard filter element configuration
	uint8_t SFEC : 3;

	//! SFT Standard Filter Type
	uint8_t SFT : 2;
} TCAN45x0_SID_FILTER;
#else
typedef struct TCAN45x0_SID_FILTER {
    //! SFT Standard Filter Type
    uint8_t SFT : 2;
    //! SFEC[2:0]   Standard filter element configuration
    uint8_t SFEC : 3;
    //! SFID1[10:0]
    uint16_t SFID1 : 11;
    //! Reserved
    uint8_t reserved : 5;
    //!SFID2[10:0]
    uint16_t SFID2 : 11;
} TCAN45x0_SID_FILTER;
#endif

#define TCAN45x0_SID_SFT_DISABLED				0x3
#define TCAN45x0_SID_SFT_CLASSIC				0x2
#define TCAN45x0_SID_SFT_DUALID					0x1
#define TCAN45x0_SID_SFT_RANGE					0x0

#define TCAN45x0_SID_SFEC_DISABLED				0x0
#define TCAN45x0_SID_SFEC_STORERX0				0x1
#define TCAN45x0_SID_SFEC_STORERX1				0x2
#define TCAN45x0_SID_SFEC_REJECTMATCH			0x3
#define TCAN45x0_SID_SFEC_PRIORITY				0x4
#define TCAN45x0_SID_SFEC_PRIORITYSTORERX0		0x5
#define TCAN45x0_SID_SFEC_PRIORITYSTORERX1		0x6
#define TCAN45x0_SID_SFEC_STORERXBUFORDEBUG		0x7


typedef struct TCAN45x0_XID_FILTER {
	//!EFID2[28:0]
	uint32_t EFID2 : 29;

	//! Reserved
	uint8_t reserved : 1;

	//! EFT[1:0]
	uint8_t EFT : 2;

	//! EFID1[28:0]
	uint32_t EFID1 : 29;

	//! SFT Standard Filter Type
	uint8_t EFEC : 3;
} TCAN45x0_XID_FILTER;




#define TCAN45x0_XID_EFEC_DISABLED				0x0
#define TCAN45x0_XID_EFEC_STORERX0				0x1
#define TCAN45x0_XID_EFEC_STORERX1				0x2
#define TCAN45x0_XID_EFEC_REJECTMATCH			0x3
#define TCAN45x0_XID_EFEC_PRIORITY				0x4
#define TCAN45x0_XID_EFEC_PRIORITYSTORERX0		0x5
#define TCAN45x0_XID_EFEC_PRIORITYSTORERX1		0x6
#define TCAN45x0_XID_EFEC_STORERXBUFORDEBUG		0x7

#define TCAN45x0_XID_EFT_RANGENOMASK			0x3
#define TCAN45x0_XID_EFT_CLASSIC				0x2
#define TCAN45x0_XID_EFT_DUALID					0x1
#define TCAN45x0_XID_EFT_RANGE					0x0

#define TCAN45x0_REG_VALUE *(uint32_t*)

/* Enable Protected Registers
 * Description: Attempts to enable CCCR.CCE and CCCR.INIT to allow writes to protected registers for setup, returns CONFIG_SUCCESS or CONFIG_FAIL
 */
uint8_t TCAN45x0_EnableProtectedRegisters(void);

/* Disable Protected Registers
 * Description: Disables CCCR.CCE and CCCR.INIT to disallow writes to protected registers when done with setup, returns CONFIG_SUCCESS or CONFIG_FAIL
 */
uint8_t TCAN45x0_DisableProtectedRegisters(void);

/* Configure CCCR Register
 * Description: Configures the bits of the CCCR register to match the CCCR config struct, returns CONFIG_SUCCESS or CONFIG_FAIL
 */
uint8_t TCAN45x0_ConfigureCCCRRegister(TCAN45x0_CCCR_Config *cccr);

/* MCAN Read module for CANFD, note that values are in tq, not literal register values
 * Description: Reads the CANFD registers of the MCAN module, returns CONFIG_SUCCESS or CONFIG_FAIL
 */
uint8_t TCAN45x0_MCANTimingFDRead(TCAN45x0_CANFD_Timing *dataTiming);

/* Configure MCAN module for CANFD, note that values are in tq, not literal register values
 * Description: Configures the CANFD registers of the MCAN module, returns CONFIG_SUCCESS or CONFIG_FAIL
 */
uint8_t TCAN45x0_ConfigureMCANTimingFD(TCAN45x0_CANFD_Timing *dataTiming);

/* MCAN timing Read (Classic CAN only), note that values are in tq, not literal register values
 * Description: Reads the nominal and data timing registers of the MCAN module, returns CONFIG_SUCCESS or CONFIG_FAIL
 */
uint8_t TCAN45x0_MCANTimingRead(TCAN45x0_Nominal_Timing *nomTiming);

/* Configure MCAN timing (Classic CAN only), note that values are in tq, not literal register values
 * Description: Configures the nominal and data timing registers of the MCAN module, returns CONFIG_SUCCESS or CONFIG_FAIL
 */
uint8_t TCAN45x0_ConfigureMCANTiming(TCAN45x0_Nominal_Timing *nomTiming);

/* Configure MRAM Settings
 * Description: Configures the appropriate registers and MRAM formatting (size and number of elements)
 */
uint8_t TCAN45x0_ConfigureMRAM(TCAN45x0_MRAM_Config *MRAMConfig);

/* Clear MRAM
 * Description: Writes 0s to the entire MRAM. Useful when changing configuration of an already configured device
 */
void TCAN45x0_ClearMRAM();

/* Configure MCAN Set Device Mode
 * Description: Sets the device mode
 */

/*Added by QJ*/
#define TCAN45x0_GPIO1_MCAN_INT1            0x01         //QJ
#define TCAN45x0_GPIO1_SPIFAULT_INT         0x00         //QJ
#define TCAN45x0_GPIO2_MCAN_INT0            0x01         //QJ
#define TCAN45x0_GPIO2_CANBUS_INT           0x00         //QJ

#define TCAN45x0_MODE_SLEEP					0x00
#define TCAN45x0_MODE_STANDBY				0x01
#define TCAN45x0_MODE_NORMAL				0x02
#define TCAN45x0_MODE_TEST					0x03
#define TCAN45x0_MODE_MCAN_CONFIGURED		0x80
#define TCAN45x0_MODE_MCAN_UNCONFIGURED		0x00
uint8_t TCAN45x0_SetDeviceMode(uint8_t mode);

/* Set WDT value
 * Description: Will configure the WDT value based on the value passed to it. Returns CONFIG_SUCCESS or CONFIG_FAIL
 */
#define TCAN45x0_WDT_8MS					0x00
#define TCAN45x0_WDT_16MS					0x01
#define TCAN45x0_WDT_24MS					0x02
#define TCAN45x0_WDT_32MS					0x03
uint8_t TCAN45x0_SetWDT(uint8_t WDTtimeout);

/* All of the below functions will return CONFIG_SUCCESS or CONFIG_FAIL */
uint8_t TCAN45x0_EnableWDT(void);
uint8_t TCAN45x0_DisableWDT(void);
uint8_t TCAN45x0_ResetWDT(void);

/* Configure MCAN Example
 * Description: Configures the registers of the MCAN module for the standard example configuration, returns CONFIG_SUCCESS or CONFIG_FAIL
 */
uint8_t setup_MCANExample(TCAN45x0_Nominal_Timing *nomTiming, TCAN45x0_CANFD_Timing *dataTiming);



/* Updates the TCAN Interrupt register struct with a read to the MCAN module
 * Description: Reads and updates the TCAN45x0 Interrupt register struct
 */
void MCAN_ReadInterruptRegister(TCAN45x0_CAN_Interrupt_Register *ir);

/* Updates the TCAN Interrupt enable register struct with a read to the MCAN module
 * Description: Reads and updates the TCAN45x0 Interrupt enable register struct
 */
void MCAN_ReadInterruptEnableRegister(TCAN45x0_CAN_Interrupt_Enable_Register *ie);

/* Updates the TCAN Interrupt enable register from the Interrupt enable struct
 * Description: Reads and updates the TCAN45x0 Interrupt enable register struct
 */
void MCAN_SetInterruptEnableRegister(TCAN45x0_CAN_Interrupt_Enable_Register *ie);

/* Updates the TCAN Interrupt Line enable register from the Interrupt enable struct
 * Description: Reads and updates the TCAN45x0 Interrupt Line enable register struct
 */
void MCAN_SetInterruptLineEnableRegister(TCAN45x0_CAN_Interrupt_Line_Enable_Register *ile);

/* Updates the TCAN Interrupt Line Select register from the Interrupt enable struct
 * Description: Reads and updates the TCAN45x0 Interrupt Line Select register struct
 */
void MCAN_SetInterruptLineSelectRegister(TCAN45x0_CAN_Interrupt_Line_Select_Register *ils);

/* MCAN Interrupt Service Routine
 * Description: Reads and responds to the main Interrupt requests within the MCAN module
 */
void MCAN_ISR(void);

/* MCAN RX Interrupt Service Routine
 * Description: Configures the registers of the MCAN module
 */
void MCAN_RX(void);

/* MCAN Get Next FIFO0
 * Description: Will retrieve the next received data payload
 * Parameter:		FIFONum: 0 = RXFIFO0, 1 = RXFIFO1, 2 = RXBUFFER (defines below)
 * Requirements: 	- Must pass the address of a TCAN45x0_RX_HEADER address (& infront of variable name)
 * 					- dataPayload[] must be as large as the biggest possible data payload in your application (64-bytes maximum)
 *
 * Returns: The number of bytes received/written to the dataPayload buffer.
 */
#define		RXFIFO0		0x00
#define		RXFIFO1		0x01
uint8_t MCAN_ReadNextFIFO(uint8_t FIFONum, TCAN45x0_RX_HEADER *header, uint8_t dataPayload[]);

/* MCAN Read RX Buffer
 * Description: Will retrieve the data at specified RX Buffer location
 * Parameter:		bufferNum is the RX Buffer index. There is no error checking on this value
 * Requirements: 	- Must pass the address of a TCAN45x0_RX_HEADER address (& infront of variable name)
 * 					- dataPayload[] must be as large as the biggest possible data payload in your application (64-bytes maximum)
 *
 * Returns: The number of bytes received/written to the dataPayload buffer.
 */
uint8_t MCAN_ReadRXBuffer(uint8_t bufferNum, TCAN45x0_RX_HEADER *header, uint8_t dataPayload[]);

/* MCAN Write to TX FIFO
 * Description: Will write data payload to the TX FIFO, and returns the hex value of the buffer required from the MCAN_TXBAR register
 * Parameters:	fifoNumber: a 0-63 decimal value. If value is outside the of the configured limits, then method returns 0
 * 				TCAN45x0_TX_HEADER header: Contains the configuration information for the packet.
 * 				dataPayload[]: A uint8_t array that must have at least the number of bytes described in the DLC field in the header
 * Requirements: 	- Must pass the address of a TCAN45x0_TX_HEADER address (& infront of variable name)
 * 					- dataPayload[] must be at least as large as the DLC parameter describes in the header
 *
 * Returns: The hex value of the buffer required from the MCAN_TXBAR register.
 */
uint32_t MCAN_WriteTXFIFO(uint8_t fifoNumber, TCAN45x0_TX_HEADER *header, uint8_t dataPayload[]);
uint32_t MCAN_ReadTXFIFO(uint8_t fifoNumber, uint8_t data[]);

/* MCAN Write SID Filter Element
 * Description: Writes the SID Filter element given to the requested SID filter FIFO element number
 * Parameters:	fifoNumber: a 0-63 decimal value. If value is outside the of the configured limits, then returns STATUS_FAIL
 * 				TCAN45x0_SID_FILTER filter: Contains the configuration information for the SID Filter
 * Requirements: 	- Must pass the address of a TCAN45x0_SID_FILTER address (& infront of variable name)
 *
 * Returns: STATUS_SUCCESS or STATUS_FAIL
 */
uint8_t MCAN_WriteSIDFilter(uint8_t fifoNumber, TCAN45x0_SID_FILTER *filter);

/* MCAN Write XID Filter Element
 * Description: Writes the XID Filter element given to the requested XID filter FIFO element number
 * Parameters:	fifoNumber: a 0-63 decimal value. If value is outside the of the configured limits, then returns STATUS_FAIL
 * 				TCAN45x0_XID_FILTER filter: Contains the configuration information for the XID Filter
 * Requirements: 	- Must pass the address of a TCAN45x0_XID_FILTER address (& infront of variable name)
 *
 * Returns: STATUS_SUCCESS or STATUS_FAIL
 */
uint8_t MCAN_WriteXIDFilter(uint8_t fifoNumber, TCAN45x0_XID_FILTER *filter);

/* MCAN DLC to Bytes
 * Description: Decode the DLC value to the number of bytes in the data payload. Does not check whether Classic CAN or CAN FD.
 */
uint8_t MCAN_DLCtoBytes(uint8_t input);

/* GetDataByte (Bitfield)
 * Description: Decodes the 3-bit data field size for RX and TX buffers to the numerical value
 */
uint8_t MCAN_TXRXESC_DataByteValue(uint8_t);

/*Configure the mode for GPIO1 and GPIO2 pins*/
uint8_t TCAN45x0_Config_GPIOMode(uint8_t gpio1_mode, uint8_t gpio2_mode);

// Debug crap
void debug_print_CAN_packet (TCAN45x0_RX_HEADER *MsgHeader, uint8_t data[], uint8_t numBytes);

void MCAN_GetDevConfigValue(TCAN45x0_Device_config_reg_t *config_reg, config_value_type_t type);

/* Get the configuration value of the device registers: 0800~08xx */
void MCAN_GetMRAMConfigValue(TCAN45x0_MCAN_config_reg_t *config_reg, config_value_type_t type);

/* Read SPI DEV ID0, ID1, and Dev Revision*/
uint8_t TCAN45x0_Check_spiRead(void);

/* Initialize TCAN bit timing, MRAM, and Interrupt*/
void tcan45xInit(void);
