/*****************************************************************************
*
* TMS570_TCAN45x.h  : Functions to burst read and write from/to TCAN4550
*
* Updated by: QJ Wang, Dat3: May 15, 2018
* Version 1.4
* Changes Notes:
* --using 1 function to replace 3 functions
* --using SPI cshold instead of GIO as spi cs
*
* Updated by: Jonathan Valdez, Date: 8/3/2017
* Version: 1.3
*
* Change Notes 1.3 (8/3/2017):
* - Cleaning up function names
* - Getting rid of unused functions
*
* Change Notes 1.2 (4/23/2017):
* - Changed defines for latest register map
*
* Change Notes 1.1:
* - Modified code to make sure SPI byte is complete to prevent race condition on MSP430
* - Made 32-bit functions more efficient by doing direct memory reads rather than bitwise ands and then shift operations
******************************************************************************/
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

//AHB Burst Write Fixed Length 	0x61 - 4 address bytes, 2 length bytes, 32 bytes to write
uint32_t AHB_WRITE_B_FL_32(uint16_t address, uint32_t data);

//AHB Burst Read Fixed Length 	0x41 - 4 address bytes, 2 length bytes, 32 bytes to read data
uint32_t AHB_READ_B_FL_32(uint16_t address);

/* Burst read with a 1 dummy read byte*/
uint32_t AHB_READ_B_FL_32_WAIT(uint16_t address);

/*AHB Burst Write varied Length of data*/
uint32_t AHB_Write_Burst(uint16_t address, uint8_t* dataBuff, uint32_t len);

/* AHB Burst Write varied Length */
uint32_t AHB_Read_Burst(uint16_t address, uint8_t DataLength, uint8_t * destbuff);

/* Burst read with a 1 dummy read byte*/
uint32_t AHB_Read_Burst_Wait(uint16_t address, uint8_t DataLength, uint8_t * destbuff);

//-----------------------------------------------------------------------------------------------

//AHB Access Commands
//*****************************************************************************
#define AHB_WRITE_B_FL_OPCODE				0x61
#define AHB_READ_B_FL_OPCODE				0x41
#define AHB_READ_B_FL_WAIT_OPCODE           0x85

//*****************************************************************************


//*****************************************************************************
//Register Address Sections
//*****************************************************************************
#define SPI_CONFIG							0x0000
#define DEV_CONFIG							0x0800
#define MCAN								0x1000
#define PN									0x2000
#define MRAM								0x8000
#define MRAM_SIZE							2048

//*****************************************************************************
// SPI Registers and Device ID Register Addresses: 	0x0000 Prefix
//*****************************************************************************
#define SPI_DEVICE_ID0						0x0000
#define SPI_DEVICE_ID1						0x0004
#define SPI_REVISION						0x0008
#define SPI_STATUS							0x000C
#define SPI_ERROR_STATUS_MASK				0x0010
#define SPI_CONTROL							0x0014
#define SPI_MISC							0x0018


//*****************************************************************************
// Device Configuration Register Addresses: 	0x0800 Prefix
//*****************************************************************************
#define DEV_MODE_PINS						0x0800
#define DEV_TIMESTAMP_PRESCALER				0x0804
#define DEV_TEST_REGISTERS					0x0808
#define DEV_IR                              0x0820
#define DEV_IE								0x0830


//*****************************************************************************
// MCAN Register Addresses: 	0x1000 Prefix
//*****************************************************************************
#define M_CAN_CREL							0x1000
#define M_CAN_ENDN							0x1004
#define M_CAN_CUST							0x1008
#define M_CAN_DBTP							0x100C
#define M_CAN_TEST							0x1010
#define M_CAN_RWD							0x1014
#define M_CAN_CCCR							0x1018
#define M_CAN_NBTP							0x101C
#define M_CAN_TSCC							0x1020
#define M_CAN_TSCV							0x1024
#define M_CAN_TOCC							0x1028
#define M_CAN_TOCV							0x102C
#define M_CAN_ECR							0x1040
#define M_CAN_PSR							0x1044
#define M_CAN_TDCR							0x1048
#define M_CAN_IR							0x1050
#define M_CAN_IE							0x1054
#define M_CAN_ILS							0x1058
#define M_CAN_ILE							0x105C
#define M_CAN_GFC							0x1080
#define M_CAN_SIDFC							0x1084
#define M_CAN_XIDFC							0x1088
#define M_CAN_XIDAM							0x1090
#define M_CAN_HPMS							0x1094
#define M_CAN_NDAT1							0x1098
#define M_CAN_NDAT2							0x109C
#define M_CAN_RXF0C							0x10A0
#define M_CAN_RXF0S							0x10A4
#define M_CAN_RXF0A							0x10A8
#define M_CAN_RXBC							0x10AC
#define M_CAN_RXF1C							0x10B0
#define M_CAN_RXF1S							0x10B4
#define M_CAN_RXF1A							0x10B8
#define M_CAN_RXESC							0x10BC
#define M_CAN_TXBC							0x10C0
#define M_CAN_TXFQS							0x10C4
#define M_CAN_TXESC							0x10C8
#define M_CAN_TXBRP							0x10CC
#define M_CAN_TXBAR							0x10D0
#define M_CAN_TXBCR							0x10D4
#define M_CAN_TXBTO							0x10D8
#define M_CAN_TXBCF							0x10DC
#define M_CAN_TXBTIE						0x10E0
#define M_CAN_TXBCIE						0x10E4
#define M_CAN_TXEFC							0x10F0
#define M_CAN_TXEFS							0x10F4
#define M_CAN_TXEFA							0x10F8
//*****************************************************************************

//DBTP
#define MCAN_DBTP_TDC_EN					0x00800000

//TEST
#define MCAN_TEST_RX_DOM					0x00000000
#define MCAN_TEST_RX_REC					0x00000080
#define MCAN_TEST_TX_SP						0x00000020
#define MCAN_TEST_TX_DOM					0x00000040
#define MCAN_TEST_TX_REC					0x00000060
#define MCAN_TEST_LOOP_BACK					0x00000010

//CCCR
#define MCAN_CCCR_NISO_ISO					0x00000000
#define MCAN_CCCR_NISO_BOSCH				0x00008000
#define MCAN_CCCR_TXP						0x00004000
#define MCAN_CCCR_EFBI						0x00002000
#define MCAN_CCCR_PXHD_DIS					0x00001000
#define MCAN_CCCR_BRSE						0x00000200
#define MCAN_CCCR_FDOE						0x00000100
#define MCAN_CCCR_TEST						0x00000080
#define MCAN_CCCR_DAR_DIS					0x00000040
#define MCAN_CCCR_MON						0x00000020
#define MCAN_CCCR_CSR						0x00000010
#define MCAN_CCCR_CSA						0x00000008
#define MCAN_CCCR_ASM						0x00000004
#define MCAN_CCCR_CCE						0x00000002
#define MCAN_CCCR_INIT						0x00000001

//IE
#define MCAN_IE_ARAE						0x20000000
#define MCAN_IE_PEDE						0x10000000
#define MCAN_IE_PEAE						0x08000000
#define MCAN_IE_WDIE						0x04000000
#define MCAN_IE_BOE							0x02000000
#define MCAN_IE_EWE							0x01000000
#define MCAN_IE_EPE							0x00800000
#define MCAN_IE_ELOE						0x00400000
#define MCAN_IE_BEUE						0x00200000
#define MCAN_IE_BECE						0x00100000
#define MCAN_IE_DRXE						0x00080000
#define MCAN_IE_TOOE						0x00040000
#define MCAN_IE_MRAFE						0x00020000
#define MCAN_IE_TSWE						0x00010000
#define MCAN_IE_TEFLE						0x00008000
#define MCAN_IE_TEFFE						0x00004000
#define MCAN_IE_TEFWE						0x00002000
#define MCAN_IE_TEFNE						0x00001000
#define MCAN_IE_TFEE						0x00000800
#define MCAN_IE_TCFE						0x00000400
#define MCAN_IE_TCE							0x00000200
#define MCAN_IE_HPME						0x00000100
#define MCAN_IE_RF1LE						0x00000080
#define MCAN_IE_RF1FE						0x00000040
#define MCAN_IE_RF1WE						0x00000020
#define MCAN_IE_RF1NE						0x00000010
#define MCAN_IE_RF0LE						0x00000008
#define MCAN_IE_RF0FE						0x00000004
#define MCAN_IE_RF0WE						0x00000002
#define MCAN_IE_RF0NE						0x00000001

//IR
#define MCAN_IR_ARA							0x20000000
#define MCAN_IR_PED							0x10000000
#define MCAN_IR_PEA							0x08000000
#define MCAN_IR_WDI							0x04000000
#define MCAN_IR_BO							0x02000000
#define MCAN_IR_EW							0x01000000
#define MCAN_IR_EP							0x00800000
#define MCAN_IR_ELO							0x00400000
#define MCAN_IR_BEU							0x00200000
#define MCAN_IR_BEC							0x00100000
#define MCAN_IR_DRX							0x00080000
#define MCAN_IR_TOO							0x00040000
#define MCAN_IR_MRAF						0x00020000
#define MCAN_IR_TSW							0x00010000
#define MCAN_IR_TEFL						0x00008000
#define MCAN_IR_TEFF						0x00004000
#define MCAN_IR_TEFW						0x00002000
#define MCAN_IR_TEFN						0x00001000
#define MCAN_IR_TFE							0x00000800
#define MCAN_IR_TCF							0x00000400
#define MCAN_IR_TC							0x00000200
#define MCAN_IR_HPM							0x00000100
#define MCAN_IR_RF1L						0x00000080
#define MCAN_IR_RF1F						0x00000040
#define MCAN_IR_RF1W						0x00000020
#define MCAN_IR_RF1N						0x00000010
#define MCAN_IR_RF0L						0x00000008
#define MCAN_IR_RF0F						0x00000004
#define MCAN_IR_RF0W						0x00000002
#define MCAN_IR_RF0N						0x00000001

//ILS
#define MCAN_IE_ARAL						0x20000000
#define MCAN_IE_PEDL						0x10000000
#define MCAN_IE_PEAL						0x08000000
#define MCAN_IE_WDIL						0x04000000
#define MCAN_IE_BOL							0x02000000
#define MCAN_IE_EWL							0x01000000
#define MCAN_IE_EPL							0x00800000
#define MCAN_IE_ELOL						0x00400000
#define MCAN_IE_BEUL						0x00200000
#define MCAN_IE_BECL						0x00100000
#define MCAN_IE_DRXL						0x00080000
#define MCAN_IE_TOOL						0x00040000
#define MCAN_IE_MRAFL						0x00020000
#define MCAN_IE_TSWL						0x00010000
#define MCAN_IE_TEFLL						0x00008000
#define MCAN_IE_TEFFL						0x00004000
#define MCAN_IE_TEFWL						0x00002000
#define MCAN_IE_TEFNL						0x00001000
#define MCAN_IE_TFEL						0x00000800
#define MCAN_IE_TCFL						0x00000400
#define MCAN_IE_TCL							0x00000200
#define MCAN_IE_HPML						0x00000100
#define MCAN_IE_RF1LL						0x00000080
#define MCAN_IE_RF1FL						0x00000040
#define MCAN_IE_RF1WL						0x00000020
#define MCAN_IE_RF1NL						0x00000010
#define MCAN_IE_RF0LL						0x00000008
#define MCAN_IE_RF0FL						0x00000004
#define MCAN_IE_RF0WL						0x00000002
#define MCAN_IE_RF0NL						0x00000001

//ILE
#define MCAN_ILE_EINT1						0x00000002
#define MCAN_ILE_EINT0						0x00000001

//GFC
#define MCAN_GFC_ANFS_FIFO0					0x00000000
#define MCAN_GFC_ANFS_FIFO1					0x00000010
#define MCAN_GFC_ANFE_FIFO0					0x00000000
#define MCAN_GFC_ANFE_FIFO1					0x00000004
#define MCAN_GFC_RRFS						0x00000002
#define MCAN_GFC_RRFE						0x00000001

//NDAT1

//NDAT2

//RXF0C
#define MCAN_RXF0C_F0OM_OVERWRITE			0x80000000

//RXESC
#define MCAN_RXESC_RBDS_8B					0x00000000
#define MCAN_RXESC_RBDS_12B					0x00000100
#define MCAN_RXESC_RBDS_16B					0x00000200
#define MCAN_RXESC_RBDS_20B					0x00000300
#define MCAN_RXESC_RBDS_24B					0x00000400
#define MCAN_RXESC_RBDS_32B					0x00000500
#define MCAN_RXESC_RBDS_48B					0x00000600
#define MCAN_RXESC_RBDS_64B					0x00000700
#define MCAN_RXESC_F1DS_8B					0x00000000
#define MCAN_RXESC_F1DS_12B					0x00000010
#define MCAN_RXESC_F1DS_16B					0x00000020
#define MCAN_RXESC_F1DS_20B					0x00000030
#define MCAN_RXESC_F1DS_24B					0x00000040
#define MCAN_RXESC_F1DS_32B					0x00000050
#define MCAN_RXESC_F1DS_48B					0x00000060
#define MCAN_RXESC_F1DS_64B					0x00000070
#define MCAN_RXESC_F0DS_8B					0x00000000
#define MCAN_RXESC_F0DS_12B					0x00000001
#define MCAN_RXESC_F0DS_16B					0x00000002
#define MCAN_RXESC_F0DS_20B					0x00000003
#define MCAN_RXESC_F0DS_24B					0x00000004
#define MCAN_RXESC_F0DS_32B					0x00000005
#define MCAN_RXESC_F0DS_48B					0x00000006
#define MCAN_RXESC_F0DS_64B					0x00000007

//TXBC
#define MCAN_TXBC_TFQM						0x40000000

//TXESC
#define MCAN_TXESC_TBDS_8					0x00000000
#define MCAN_TXESC_TBDS_12					0x00000001
#define MCAN_TXESC_TBDS_16					0x00000002
#define MCAN_TXESC_TBDS_20					0x00000003
#define MCAN_TXESC_TBDS_24					0x00000004
#define MCAN_TXESC_TBDS_32					0x00000005
#define MCAN_TXESC_TBDS_48					0x00000006
#define MCAN_TXESC_TBDS_64					0x00000007

//DLC
#define MCAN_DLC_0B							0x00000000
#define MCAN_DLC_1B							0x00000001
#define MCAN_DLC_2B							0x00000002
#define MCAN_DLC_3B							0x00000003
#define MCAN_DLC_4B							0x00000004
#define MCAN_DLC_5B							0x00000005
#define MCAN_DLC_6B							0x00000006
#define MCAN_DLC_7B							0x00000007
#define MCAN_DLC_8B							0x00000008
#define MCAN_DLC_12B						0x00000009
#define MCAN_DLC_16B						0x0000000A
#define MCAN_DLC_20B						0x0000000B
#define MCAN_DLC_24B						0x0000000C
#define MCAN_DLC_32B						0x0000000D
#define MCAN_DLC_48B						0x0000000E
#define MCAN_DLC_64B						0x0000000F

//TSCC
#define MCAN_TSCC_0							0x00000000
#define MCAN_TSCC_1							0x00000001
#define MCAN_TSCC_2							0x00000002

//TXBAR
#define MCAN_TXBAR_AR31						0x80000000
#define MCAN_TXBAR_AR30						0x40000000
#define MCAN_TXBAR_AR29						0x20000000
#define MCAN_TXBAR_AR28						0x10000000
#define MCAN_TXBAR_AR27						0x08000000
#define MCAN_TXBAR_AR26						0x04000000
#define MCAN_TXBAR_AR25						0x02000000
#define MCAN_TXBAR_AR24						0x01000000
#define MCAN_TXBAR_AR23						0x00800000
#define MCAN_TXBAR_AR22						0x00400000
#define MCAN_TXBAR_AR21						0x00200000
#define MCAN_TXBAR_AR20						0x00100000
#define MCAN_TXBAR_AR19						0x00080000
#define MCAN_TXBAR_AR18						0x00040000
#define MCAN_TXBAR_AR17						0x00020000
#define MCAN_TXBAR_AR16						0x00010000
#define MCAN_TXBAR_AR15						0x00008000
#define MCAN_TXBAR_AR14						0x00004000
#define MCAN_TXBAR_AR13						0x00002000
#define MCAN_TXBAR_AR12						0x00001000
#define MCAN_TXBAR_AR11						0x00000800
#define MCAN_TXBAR_AR10						0x00000400
#define MCAN_TXBAR_AR9						0x00000200
#define MCAN_TXBAR_AR8						0x00000100
#define MCAN_TXBAR_AR7						0x00000080
#define MCAN_TXBAR_AR6						0x00000040
#define MCAN_TXBAR_AR5						0x00000020
#define MCAN_TXBAR_AR4						0x00000010
#define MCAN_TXBAR_AR3						0x00000008
#define MCAN_TXBAR_AR2						0x00000004
#define MCAN_TXBAR_AR1						0x00000002
#define MCAN_TXBAR_AR0						0x00000001

//TXBCR
#define MCAN_TXBCR_CR31						0x80000000
#define MCAN_TXBCR_CR30						0x40000000
#define MCAN_TXBCR_CR29						0x20000000
#define MCAN_TXBCR_CR28						0x10000000
#define MCAN_TXBCR_CR27						0x08000000
#define MCAN_TXBCR_CR26						0x04000000
#define MCAN_TXBCR_CR25						0x02000000
#define MCAN_TXBCR_CR24						0x01000000
#define MCAN_TXBCR_CR23						0x00800000
#define MCAN_TXBCR_CR22						0x00400000
#define MCAN_TXBCR_CR21						0x00200000
#define MCAN_TXBCR_CR20						0x00100000
#define MCAN_TXBCR_CR19						0x00080000
#define MCAN_TXBCR_CR18						0x00040000
#define MCAN_TXBCR_CR17						0x00020000
#define MCAN_TXBCR_CR16						0x00010000
#define MCAN_TXBCR_CR15						0x00008000
#define MCAN_TXBCR_CR14						0x00004000
#define MCAN_TXBCR_CR13						0x00002000
#define MCAN_TXBCR_CR12						0x00001000
#define MCAN_TXBCR_CR11						0x00000800
#define MCAN_TXBCR_CR10						0x00000400
#define MCAN_TXBCR_CR9						0x00000200
#define MCAN_TXBCR_CR8						0x00000100
#define MCAN_TXBCR_CR7						0x00000080
#define MCAN_TXBCR_CR6						0x00000040
#define MCAN_TXBCR_CR5						0x00000020
#define MCAN_TXBCR_CR4						0x00000010
#define MCAN_TXBCR_CR3						0x00000008
#define MCAN_TXBCR_CR2						0x00000004
#define MCAN_TXBCR_CR1						0x00000002
#define MCAN_TXBCR_CR0						0x00000001

//TXBTIE
#define MCAN_TXBTIE_TIE31					0x80000000
#define MCAN_TXBTIE_TIE30					0x40000000
#define MCAN_TXBTIE_TIE29					0x20000000
#define MCAN_TXBTIE_TIE28					0x10000000
#define MCAN_TXBTIE_TIE27					0x08000000
#define MCAN_TXBTIE_TIE26					0x04000000
#define MCAN_TXBTIE_TIE25					0x02000000
#define MCAN_TXBTIE_TIE24					0x01000000
#define MCAN_TXBTIE_TIE23					0x00800000
#define MCAN_TXBTIE_TIE22					0x00400000
#define MCAN_TXBTIE_TIE21					0x00200000
#define MCAN_TXBTIE_TIE20					0x00100000
#define MCAN_TXBTIE_TIE19					0x00080000
#define MCAN_TXBTIE_TIE18					0x00040000
#define MCAN_TXBTIE_TIE17					0x00020000
#define MCAN_TXBTIE_TIE16					0x00010000
#define MCAN_TXBTIE_TIE15					0x00008000
#define MCAN_TXBTIE_TIE14					0x00004000
#define MCAN_TXBTIE_TIE13					0x00002000
#define MCAN_TXBTIE_TIE12					0x00001000
#define MCAN_TXBTIE_TIE11					0x00000800
#define MCAN_TXBTIE_TIE10					0x00000400
#define MCAN_TXBTIE_TIE9					0x00000200
#define MCAN_TXBTIE_TIE8					0x00000100
#define MCAN_TXBTIE_TIE7					0x00000080
#define MCAN_TXBTIE_TIE6					0x00000040
#define MCAN_TXBTIE_TIE5					0x00000020
#define MCAN_TXBTIE_TIE4					0x00000010
#define MCAN_TXBTIE_TIE3					0x00000008
#define MCAN_TXBTIE_TIE2					0x00000004
#define MCAN_TXBTIE_TIE1					0x00000002
#define MCAN_TXBTIE_TIE0					0x00000001

//TXBCIE
#define MCAN_TXBCIE_CFIE31					0x80000000
#define MCAN_TXBCIE_CFIE30					0x40000000
#define MCAN_TXBCIE_CFIE29					0x20000000
#define MCAN_TXBCIE_CFIE28					0x10000000
#define MCAN_TXBCIE_CFIE27					0x08000000
#define MCAN_TXBCIE_CFIE26					0x04000000
#define MCAN_TXBCIE_CFIE25					0x02000000
#define MCAN_TXBCIE_CFIE24					0x01000000
#define MCAN_TXBCIE_CFIE23					0x00800000
#define MCAN_TXBCIE_CFIE22					0x00400000
#define MCAN_TXBCIE_CFIE21					0x00200000
#define MCAN_TXBCIE_CFIE20					0x00100000
#define MCAN_TXBCIE_CFIE19					0x00080000
#define MCAN_TXBCIE_CFIE18					0x00040000
#define MCAN_TXBCIE_CFIE17					0x00020000
#define MCAN_TXBCIE_CFIE16					0x00010000
#define MCAN_TXBCIE_CFIE15					0x00008000
#define MCAN_TXBCIE_CFIE14					0x00004000
#define MCAN_TXBCIE_CFIE13					0x00002000
#define MCAN_TXBCIE_CFIE12					0x00001000
#define MCAN_TXBCIE_CFIE11					0x00000800
#define MCAN_TXBCIE_CFIE10					0x00000400
#define MCAN_TXBCIE_CFIE9					0x00000200
#define MCAN_TXBCIE_CFIE8					0x00000100
#define MCAN_TXBCIE_CFIE7					0x00000080
#define MCAN_TXBCIE_CFIE6					0x00000040
#define MCAN_TXBCIE_CFIE5					0x00000020
#define MCAN_TXBCIE_CFIE4					0x00000010
#define MCAN_TXBCIE_CFIE3					0x00000008
#define MCAN_TXBCIE_CFIE2					0x00000004
#define MCAN_TXBCIE_CFIE1					0x00000002
#define MCAN_TXBCIE_CFIE0					0x00000001


/* ************************************ *
 * 			DEVICE REGISTERS			*
 * ************************************ */

// Modes of Operation and Pin Configuration Registers (0x0800)
//Wake pin
#define DEVICE_MODE_WAKE_PIN_DIS			0x00000000
#define DEVICE_MODE_WAKE_PIN_RISING			0x40000000
#define DEVICE_MODE_WAKE_PIN_FALLING		0x80000000
#define DEVICE_MODE_WAKE_PIN_BOTHEDGE		0xC0000000
//WD_Timer
#define DEVICE_MODE_WD_TIMER_MASK			0x30000000
#define DEVICE_MODE_WD_TIMER_8MS			0x00000000
#define DEVICE_MODE_WD_TIMER_16MS			0x10000000
#define DEVICE_MODE_WD_TIMER_24MS			0x20000000
#define DEVICE_MODE_WD_TIMER_32MS			0x30000000
//WD_TIMER_CLK_REF
#define DEVICE_MODE_WD_CLK_20MHZ			0x03000000
#define DEVICE_MODE_WD_CLK_25MHZ			0x04000000
#define DEVICE_MODE_WD_CLK_30MHZ			0x05000000
#define DEVICE_MODE_WD_CLK_35MHZ			0x06000000
#define DEVICE_MODE_WD_CLK_40MHZ			0x07000000
#define DEVICE_MODE_WD_CLK_45MHZ			0x08000000
#define DEVICE_MODE_WD_CLK_50MHZ			0x09000000
#define DEVICE_MODE_WD_CLK_55MHZ			0x0A000000
#define DEVICE_MODE_WD_CLK_60MHZ			0x0B000000
//GPO2 Pin Configuration
#define DEVICE_MODE_GPO2_CAN_FAULT			0x00000000
#define DEVICE_MODE_GPO2_MCAN_INT0			0x00400000
#define DEVICE_MODE_GPO2_WDT				0x00800000
#define DEVICE_MODE_GPO2_NINT				0x00C00000
//GPO2 Pin Function Select
#define DEVICE_MODE_GPO2_INPUT				0x00200000
#define DEVICE_MODE_GPO2_OUTPUT				0x00000000
//GPIO2 Pin GPI Function Select
#define DEVICE_MODE_GPO2_WDT_INPUT			0x00000000
//nWKRQ Pin GPO Voltage Rail COnfiguration
#define DEVICE_MODE_NWKRQ_VOLT_INTERNAL		0x00000000
#define DEVICE_MODE_NWKRQ_VOLT_VIO			0x00080000
//WD_BIT
#define DEVICE_MODE_WDT_RESET_BIT			0x00040000
//WD_ACTION
#define DEVICE_MODE_WDT_ACTION_INT			0x00000000
#define DEVICE_MODE_WDT_ACTION_INH_PULSE	0x00010000
#define DEVICE_MODE_WDT_ACTION_WDT_PULSE	0x00020000
//CLKOUT/GPO1 Pin Mode Select
#define DEVICE_MODE_GPO1_MODE_GPO			0x00000000
#define DEVICE_MODE_GPO1_MODE_CLKOUT		0x00004000
#define DEVICE_MODE_GPO1_MODE_GPI			0x00008000
//CLKOUT Prescaler
#define DEVICE_MODE_CLKOUT_1DIV				0x00000000
#define DEVICE_MODE_CLKOUT_2DIV				0x00001000
#define DEVICE_MODE_CLKOUT_4DIV				0x00002000
#define DEVICE_MODE_CLKOUT_8DIV				0x00003000
//GPO1 Function Select
#define DEVICE_MODE_GPO1_FUNC_SPI_INT		0x00000000
#define DEVICE_MODE_GPO1_FUNC_MCAN_INT1		0x00000400
#define DEVICE_MODE_GPO1_FUNC_UVLO_THERM	0x00000800
#define DEVICE_MODE_GPO1_FUNC_WDT_EVENT		0x00000C00
//INH Pin Disable
#define DEVICE_MODE_INH_DIS					0x00000200
#define DEVICE_MODE_INH_EN					0x00000000
//Mode of Operation
#define GPIO2_CONFIG_MASK                   0x00C00000  //QJ
#define GPIO1_CONFIG_MASK                   0x0000CC00  //QJ
#define DEVICE_MODE_DEVICEMODE_MASK			0x000000C0
#define DEVICE_MODE_DEVICEMODE_SLEEP		0x00000000
#define DEVICE_MODE_DEVICEMODE_STANDBY		0x00000040
#define DEVICE_MODE_DEVICEMODE_NORMAL		0x00000080
#define DEVICE_MODE_DEVICEMODE_TEST			0x000000C0
//MCAN_CONFIG
#define DEVICE_MODE_MCAN_NOTCONFIGURED		0x00000000
#define DEVICE_MODE_MCAN_CONFIGURED			0x00000020
//Selective Wake
#define DEVICE_MODE_SELECTIVEWAKE_EN		0x00000010
#define DEVICE_MODE_SELECTIVEWAKE_DIS		0x00000000
//WDT_DIS
#define DEVICE_MODE_WDT_EN					0x00000008
#define DEVICE_MODE_WDT_DIS					0x00000000
//Dev Reset
#define DEVICE_MODE_DEVICE_RESET			0x00000004
//Test Mode Configuration
#define DEVICE_MODE_TESTMODE_NORMAL			0x00000000
#define DEVICE_MODE_TESTMODE_CANTEST		0x00000001
#define DEVICE_MODE_TESTMODE_LOOP			0x00000002
#define DEVICE_MODE_TESTMODE_DIGLOOP		0x00000003



// Device Interrupt Register values
#define DEVICE_IR_CANBUSNOM					0x80000000
#define DEVICE_IR_CANBUSTERMOPEN			0x40000000
#define DEVICE_IR_CANHCANL					0x20000000
#define DEVICE_IR_CANHBAT					0x10000000
#define DEVICE_IR_CANLGND					0x08000000
#define DEVICE_IR_CANBUSOPEN				0x04000000
#define DEVICE_IR_CANBUSGND					0x02000000
#define DEVICE_IR_CANBUSBAT					0x01000000
#define DEVICE_IR_UVCCOUT					0x00800000
#define DEVICE_IR_UVSUP						0x00400000
#define DEVICE_IR_UVIO						0x00200000
#define DEVICE_IR_PWRON						0x00100000
#define DEVICE_IR_TSD						0x00080000
#define DEVICE_IR_WDTO						0x00040000
//Reserved									0x00020000
#define DEVICE_IR_ECCERR					0x00010000
#define DEVICE_IR_CANINT					0x00008000
#define DEVICE_IR_LWU						0x00004000
#define DEVICE_IR_WKERR						0x00002000
#define DEVICE_IR_FRAME_OVF					0x00001000
//Reserved									0x00000800
#define DEVICE_IR_CANSLNT					0x00000400
#define DEVICE_IR_CANTO						0x00000200
#define DEVICE_IR_CANDOM					0x00000100
#define DEVICE_IR_GLOBALERR					0x00000080
#define DEVICE_IR_nWKRQ						0x00000040
#define DEVICE_IR_CANERR					0x00000020
#define DEVICE_IR_CBF						0x00000010
#define DEVICE_IR_SPIERR					0x00000008
#define DEVICE_IR_SWERR						0x00000004
#define DEVICE_IR_M_CAN_INT					0x00000002
#define DEVICE_IR_VTWD						0x00000001

// Device Interrupt Enable Register values
#define DEVICE_IE_CANBUSNOM					0x80000000
#define DEVICE_IE_CANBUSTERMOPEN			0x40000000
#define DEVICE_IE_CANHCANL					0x20000000
#define DEVICE_IE_CANHBAT					0x10000000
#define DEVICE_IE_CANLGND					0x08000000
#define DEVICE_IE_CANBUSOPEN				0x04000000
#define DEVICE_IE_CANBUSGND					0x02000000
#define DEVICE_IE_CANBUSBAT					0x01000000
#define DEVICE_IE_UVCCOUT					0x00800000
#define DEVICE_IE_UVSUP						0x00400000
#define DEVICE_IE_UVIO						0x00200000
#define DEVICE_IE_PWRON						0x00100000
#define DEVICE_IE_TSD						0x00080000
#define DEVICE_IE_WDTO						0x00040000
#define DEVICE_IE_SWCFG						0x00020000
#define DEVICE_IE_ECCERR					0x00010000
#define DEVICE_IE_CANINT					0x00008000
#define DEVICE_IE_LWU						0x00004000
#define DEVICE_IE_WKERR						0x00002000
#define DEVICE_IE_FRAME_OVF					0x00001000
//Reserved									0x00000800
#define DEVICE_IE_CANSLNT					0x00000400
#define DEVICE_IE_CANTO						0x00000200
#define DEVICE_IE_CANDOM					0x00000100
// Reserved									0x80-00

/* ************************************ *
 *		Partial Networking Registers	*
 *			(TCAN4650 Only)				*
 * ************************************ */
// Register addresses
#define SW_CFG1								0x2000
#define SW_CFG2								0x2004
#define SW_CFG3								0x2008
#define SW_CFG4								0x200C
#define SW_CNTRL1							0x2010
#define SW_CNTRL2							0x2014
#define SW_CNTRL3							0x2018
#define SW_CNTRL4							0x201C

// Selective Wake Config 1
#define SW_CFG1_IDE							0x00002000

// Selective Wake Control 1 (0x2010)
#define SW_CNTRL1_FRM_DET_EN				0x00000002
#define SW_CNTRL1_SPI_BUS_PRIORITY			0x00000001

// Selective Wake Control 3 (0x2018)
#define SW_CNTRL3_SAMPLE_DIV_1				0x00000000
#define SW_CNTRL3_SAMPLE_DIV_2				0x00000001
#define SW_CNTRL3_SAMPLE_DIV_3				0x00000004
#define SW_CNTRL3_SAMPLE_DIV_4				0x00000002
#define SW_CNTRL3_SAMPLE_DIV_5				0x00000003
#define SW_CNTRL3_SAMPLE_DIV_6				0x0000000C
#define SW_CNTRL3_SW_CONFIGURED				0x00000080
#define SW_CNTRL3_CANSYNC_FD				0x00000040
#define SW_CNTRL3_CANSYNC					0x00000020

//define the initial configuration value
#define  MCAN_DBTP_CONFIGVALUE    0x00000A33     //0x100C
#define  MCAN_TEST_CONFIGVALUE    0x00000000     //0x1010
#define  MCAN_RAMWD_CONFIGVALUE   0x00000000     //0x1014
#define  MCAN_CCCR_CONFIGVALUE    0x00000001     //0x1018
#define  MCAN_NBTP_CONFIGVALUE    0x06000A03     //0x101C
#define  MCAN_TSCC_CONFIGVALUE    0x00000000     //0x1020
#define  MCAN_TOCC_CONFIGVALUE    0xFFFF0000     //0x1028
#define  MCAN_TDCR_CONFIGVALUE    0x00000000     //0x1048
#define  MCAN_IR_CONFIGVALUE      0x00000000     //0x1050
#define  MCAN_IE_CONFIGVALUE      0x00000000     //0x1054
#define  MCAN_ILS_CONFIGVALUE     0x00000000     //0x1058
#define  MCAN_ILE_CONFIGVALUE     0x00000000     //0x105C
#define  MCAN_GFC_CONFIGVALUE     0x00000000     //0x1080
#define  MCAN_SIDFC_CONFIGVALUE   0x00000000     //0x1084
#define  MCAN_XIDFC_CONFIGVALUE   0x00000000     //0x1088
#define  MCAN_XIDAM_CONFIGVALUE   0x1FFFFFFF     //0x1090
#define  MCAN_RXF0C_CONFIGVALUE   0x00000000     //0x10A0
#define  MCAN_RXF1C_CONFIGVALUE   0x00000000     //0x10B0
#define  MCAN_RXESC_CONFIGVALUE   0x00000000     //0x10BC
#define  MCAN_TXBC_CONFIGVALUE    0x00000000     //0x10C0
#define  MCAN_TXESC_CONFIGVALUE   0x00000000     //0x10C8
#define  MCAN_TXBTIE_CONFIGVALUE  0x00000000     //0x10E0
#define  MCAN_TXBCIE_CONFIGVALUE  0x00000000     //0x10E4
#define  MCAN_TXEFC_CONFIGVALUE   0x00000000     //0x10F0

#define  DEV_MODES_CONFIGVALUE    0xC7004048
#define  DEV_TSTAMP_CONFIGVALUE   0x00000002
#define  DEV_TEST_CONFIGVALUE     0x00000000
#define  DEV_IE_CONFIGVALUE       0x00000000
