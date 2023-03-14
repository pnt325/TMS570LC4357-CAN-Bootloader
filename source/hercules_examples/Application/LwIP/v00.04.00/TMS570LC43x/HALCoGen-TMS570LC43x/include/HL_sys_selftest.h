/** @file HL_sys_selftest.h
*   @brief System Memory Header File
*   @date 04.Oct.2013
*   @version 03.07.00
*   
*   This file contains:
*   - Efuse Self Test Functions
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __sys_selftest_H__
#define __sys_selftest_H__

#include "HL_reg_pbist.h"
#include "HL_reg_stc.h"
#include "HL_reg_efc.h"
#include "HL_sys_core.h"
#include "HL_system.h"
#include "HL_sys_vim.h"
#include "HL_adc.h"
#include "HL_can.h"
#include "HL_mibspi.h"
#include "HL_het.h"
#include "HL_htu.h"
#include "HL_esm.h"
/* USER CODE BEGIN (0) */
/* USER CODE END */

#define flash1bitError	(*(volatile uint32 *)(0xF00803F0U))
#define flash2bitError	(*(volatile uint32 *)(0xF00803F8U))

#define l2ramw1bitError	(*(volatile uint32 *)(0x08400000U))
#define l2ramw2bitError (*(volatile uint32 *)(0x08400010U))

#define l2ramw1bit		(*(volatile uint64 *)(0x08000000U))
#define l2ramw2bit		(*(volatile uint64 *)(0x08000010U))

#define flashBadECC_SingleBit		(*(volatile uint32 *)(0x20000000U))
#define flashBadECC_DoubleBit		(*(volatile uint32 *)(0x20000010U))


#define mibspi1ECCLOC	(*(volatile uint32 *)(0xFF0E0400U))
#define mibspi2ECCLOC	(*(volatile uint32 *)(0xFF080400U))
#define mibspi3ECCLOC	(*(volatile uint32 *)(0xFF0C0400U))
#define mibspi4ECCLOC	(*(volatile uint32 *)(0xFF060400U))
#define mibspi5ECCLOC	(*(volatile uint32 *)(0xFF0A0400U))

#ifndef __PBIST_H__
#define __PBIST_H__

/** @enum pbistPort
*   @brief Alias names for pbist Port number
*
*   This enumeration is used to provide alias names for the pbist Port number
*     - PBIST_PORT0
*     - PBIST_PORT1
*/
enum pbistPort
{
    PBIST_PORT0 = 0U, /**< Alias for PBIST Port 0 */
    PBIST_PORT1 = 1U  /**< Alias for PBIST Port 1 */
};
/** @enum pbistAlgo
*   @brief Alias names for pbist Algorithm
*
*   This enumeration is used to provide alias names for the pbist Algorithm
*     - PBIST_TripleReadSlow    
*     - PBIST_TripleReadFast    
*     - PBIST_March13N_DP       
*     - PBIST_March13N_SP       
*     - PBIST_DOWN2_SP          
*     - PBIST_DOWN2_DP          
*     - PBIST_MarchDistubInc_SP 
*     - PBIST_MarchDistubInc_DP 
*     - PBIST_MarchDistubDec_SP 
*     - PBIST_MarchDistubDec_DP 
*     - PBIST_MarchDistubInc2_SP
*     - PBIST_MarchDistubInc2_DP
*     - PBIST_MarchDistubDec2_SP
*     - PBIST_MarchDistubDec2_DP
*     - PBIST_MapColumn_SP      
*     - PBIST_MapColumn_DP      
*     - PBIST_Precharge_SP      
*     - PBIST_Precharge_DP      
*     - PBIST_Flip10_SP         
*     - PBIST_Flip10_DP         
*     - PBIST_DTXN2_SP          
*     - PBIST_DTXN2_DP          
*     - PBIST_PMOSOpenSlice1_SP 
*     - PBIST_PMOSOpenSlice1_DP 
*     - PBIST_PMOSOpenSlice2_DP 
*/
enum pbistAlgo
{
    PBIST_TripleReadSlow     = 0x00000001U,
    PBIST_TripleReadFast     = 0x00000002U,
    PBIST_March13N_DP        = 0x00000004U,
    PBIST_March13N_SP        = 0x00000008U,
    PBIST_DOWN2_SP           = 0x00000010U,
    PBIST_DOWN2_DP           = 0x00000020U,
    PBIST_MarchDistubInc_SP  = 0x00000040U,
    PBIST_MarchDistubInc_DP  = 0x00000080U,
    PBIST_MarchDistubDec_SP  = 0x00000100U,
    PBIST_MarchDistubDec_DP  = 0x00000200U,
    PBIST_MarchDistubInc2_SP = 0x00000400U,
    PBIST_MarchDistubInc2_DP = 0x00000800U,
    PBIST_MarchDistubDec2_SP = 0x00001000U,
    PBIST_MarchDistubDec2_DP = 0x00002000U,
    PBIST_MapColumn_SP       = 0x00004000U,
    PBIST_MapColumn_DP       = 0x00008000U,
    PBIST_Precharge_SP       = 0x00010000U,
    PBIST_Precharge_DP       = 0x00020000U,
    PBIST_Flip10_SP          = 0x00040000U,
    PBIST_Flip10_DP          = 0x00080000U,
    PBIST_DTXN2_SP           = 0x00100000U,
    PBIST_DTXN2_DP           = 0x00200000U,
    PBIST_PMOSOpenSlice1_SP  = 0x00400000U,
    PBIST_PMOSOpenSlice1_DP  = 0x00800000U,
    PBIST_PMOSOpenSlice2_DP  = 0x01000000U
};
/* PBIST configuration registers */
typedef struct pbist_config_reg
{
    uint32 CONFIG_RAMT;
    uint32 CONFIG_DLR;
    uint32 CONFIG_PACT;
    uint32 CONFIG_PBISTID;
    uint32 CONFIG_OVER;
    uint32 CONFIG_FSRDL1;
    uint32 CONFIG_ROM;
    uint32 CONFIG_ALGO;
    uint32 CONFIG_RINFOL;
    uint32 CONFIG_RINFOU;
} pbist_config_reg_t;

/* PBIST congiruration registers initial value */
#define PBIST_RAMT_CONFIGVALUE 0U
#define PBIST_DLR_CONFIGVALUE 0U
#define PBIST_PACT_CONFIGVALUE 0U
#define PBIST_PBISTID_CONFIGVALUE 0U
#define PBIST_OVER_CONFIGVALUE 0U
#define PBIST_FSRDL1_CONFIGVALUE 0U
#define PBIST_ROM_CONFIGVALUE 0U
#define PBIST_ALGO_CONFIGVALUE 0U
#define PBIST_RINFOL_CONFIGVALUE 0U
#define PBIST_RINFOU_CONFIGVALUE 0U
#define PBIST_ROM 0x0000000000000001ULL
#define PBIST_STC1_1_ROM_R5 0x0000000000000002ULL
#define PBIST_STC1_2_ROM_R5 0x0000000000000004ULL
#define PBIST_STC2_ROM_N2HET 0x0000000000000008ULL

#define PBIST_AWM1_RINFO 0x0000000000000010ULL
#define PBIST_DCAN1_RINFO 0x0000000000000020ULL
#define PBIST_DCAN2_RINFO 0x0000000000000040ULL
#define PBIST_DMA_RINFO 0x0000000000000080ULL
#define PBIST_HTU1_RINFO 0x0000000000000100ULL
#define PBIST_MIBSPI1_RINFO 0x0000000000000200ULL
#define PBIST_MIBSPI2_RINFO 0x0000000000000400ULL
#define PBIST_MIBSPI3_RINFO 0x0000000000000800ULL
#define PBIST_NHET1_RINFO 0x0000000000001000ULL
#define PBIST_VIM_RINFO 0x0000000000002000ULL
#define PBIST_RTP_RINFO 0x0000000000008000ULL
#define PBIST_ATB_RINFO 0x0000000000010000ULL
#define PBIST_AWM2_RINFO 0x0000000000020000ULL
#define PBIST_DCAN3_RINFO 0x0000000000040000ULL
#define PBIST_DCAN4_RINFO 0x0000000000080000ULL
#define PBIST_HTU2_RINFO 0x0000000000100000ULL
#define PBIST_MIBSPI4_RINFO 0x0000000000200000ULL
#define PBIST_MIBSPI5_RINFO 0x0000000000400000ULL
#define PBIST_NHET2_RINFO 0x0000000000800000ULL
#define PBIST_FTU_RINFO 0x0000000001000000ULL
#define PBIST_FRAY_INBUF_OUTBUF_RINFO 0x0000000002000000ULL
#define PBIST_CPGMAC_STATE_RXADDR_RINFO 0x0000000004000000ULL
#define PBIST_CPGMAC_STAT_FIFO_RINFO 0x0000000008000000ULL
#define PBIST_L2RAMW1_RINFO_SP 0x0000000010000000ULL
#define PBIST_L2RAMW2_RINFO_SP 0x0000000020000000ULL
#define PBIST_R5ICACHE_RINFO_SP 0x0000000040000000ULL
#define PBIST_R5DCACHE_RINFO_SP 0x0000000080000000ULL
#define PBIST_FRAY_TRBUF_MSGRAM_SP 0x0000000400000000ULL
#define PBIST_CPGMAC_CPPI_SP 0x0000000800000000ULL
#define PBIST_R5_DCACHE_DIRTY_SP 0x0000001000000000ULL




/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void memoryPort0TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data)
*   @brief Memory Port 0 test fail notification
*   @param[in] groupSelect Failing Ram group select:
*   @param[in] dataSelect Failing Ram data select:
*   @param[in] address Failing Ram offset:
*   @param[in] data Failing data at address:
*
*   @note This function has to be provide by the user.
*/
void memoryPort0TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data);

/** @fn void memoryPort1TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data)
*   @brief Memory Port 1 test fail notification
*   @param[in] groupSelect Failing Ram group select:
*   @param[in] dataSelect Failing Ram data select:
*   @param[in] address Failing Ram offset:
*   @param[in] data Failing data at address:
*
*   @note This function has to be provide by the user.
*/
void memoryPort1TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data);

void pbistGetConfigValue(pbist_config_reg_t *config_reg, config_value_type_t type);
#endif

#ifndef __STC_H__
#define __STC_H__

/* STC General Definitions */

/* STC Test Intervals supported in the Device */
#define STC_INTERVAL 40U
#define STC_MAX_TIMEOUT 0xFFFFFFFFU



/* Configuration registers */
typedef struct stc_config_reg
{
	uint32 CONFIG_STCGCR0;
    uint32 CONFIG_STCGCR1;
    uint32 CONFIG_STCTPR;
    uint32 CONFIG_STCSCSCR;
} stc_config_reg_t;

/* Configuration registers initial value */
#define STC_STCGCR0_CONFIGVALUE	0xFFFF0000U
#define STC_STCGCR1_CONFIGVALUE	0x5U
#define STC_STCTPR_CONFIGVALUE	0xFFFFFFFFU
#define STC_STCSCSCR_CONFIGVALUE 0x5U

void stcGetConfigValue(stc_config_reg_t *config_reg, config_value_type_t type);

#endif

#ifndef __EFC_H__
#define __EFC_H__

#define INPUT_ENABLE         0x0000000FU
#define INPUT_DISABLE        0x00000000U

#define SYS_WS_READ_STATES   0x00000000U


#define SYS_REPAIR_EN_0      0x00000000U
#define SYS_REPAIR_EN_3      0x00000100U
#define SYS_REPAIR_EN_5      0x00000200U

#define SYS_DEID_AUTOLOAD_EN 0x00000400U

#define EFC_FDI_EN            0x00000800U
#define EFC_FDI_DIS           0x00000000U

#define SYS_ECC_OVERRIDE_EN   0x00001000U
#define SYS_ECC_OVERRIDE_DIS  0x00000000U

#define SYS_ECC_SELF_TEST_EN  0x00002000U
#define SYS_ECC_SELF_TEST_DIS 0x00000000U

#define OUTPUT_ENABLE         0x0003C000U
#define OUTPUT_DISABLE        0x00000000U

/*********** OUTPUT **************/

#define EFC_AUTOLOAD_ERROR_EN    0x00040000U
#define EFC_INSTRUCTION_ERROR_EN 0x00080000U
#define EFC_INSTRUCTION_INFO_EN  0x00100000U
#define EFC_SELF_TEST_ERROR_EN   0x00200000U


#define EFC_AUTOLOAD_ERROR_DIS    0x00000000U
#define EFC_INSTRUCTION_ERROR_DIS 0x00000000U
#define EFC_INSTRUCTION_INFO_DIS  0x00000000U
#define EFC_SELF_TEST_ERROR_DIS   0x00000000U

#define DISABLE_READ_ROW0         0x00800000U

/********************************************************************/

#define SYS_REPAIR_0         0x00000010U
#define SYS_REPAIR_3         0x00000010U
#define SYS_REPAIR_5         0x00000020U

#define SYS_DEID_AUTOLOAD    0x00000040U
#define SYS_FCLRZ            0x00000080U
#define EFC_READY            0x00000100U
#define SYS_ECC_OVERRIDE     0x00000200U
#define EFC_AUTOLOAD_ERROR   0x00000400U
#define EFC_INSTRUCTION_ERROR 0x00000800U
#define EFC_INSTRUCTION_INFO  0x00001000U
#define SYS_ECC_SELF_TEST    0x00002000U
#define EFC_SELF_TEST_ERROR  0x00004000U
#define EFC_SELF_TEST_DONE   0x00008000U

/**************   0x3C error status register ******************************************************/

#define TIME_OUT 0x01
#define AUTOLOAD_NO_FUSEROM_DATA      0x02U 
#define AUTOLOAD_SIGN_FAIL            0x03U
#define AUTOLOAD_PROG_INTERRUPT       0x04U
#define AUTOLOAD_TWO_BIT_ERR          0x05U
#define PROGRAME_WR_P_SET             0x06U
#define PROGRAME_MNY_DATA_ITERTN      0x07U
#define PROGRAME_MNY_CNTR_ITERTN      0x08U
#define UN_PROGRAME_BIT_SET           0x09U
#define REDUNDANT_REPAIR_ROW          0x0AU
#define PROGRAME_MNY_CRA_ITERTN       0x0BU
#define PROGRAME_SAME_DATA            0x0CU
#define PROGRAME_CMP_SKIP			  0x0DU
#define PROGRAME_ABORT                0x0EU
#define PROGRAME_INCORRECT_KEY		  0x0FU
#define FUSEROM_LASTROW_STUCK		  0x10U
#define AUTOLOAD_SINGLE_BIT_ERR		  0x15U
#define DUMPWORD_TWO_BIT_ERR	      0x16U
#define DUMPWORD_ONE_BIT_ERR          0x17U
#define SELF_TEST_ERROR               0x18U

#define INSTRUCTION_DONE              0x20U

/**************   Efuse Instruction set ******************************************************/

#define TEST_UNPROGRAME_ROM  0x01000000U
#define PROGRAME_CRA         0x02000000U 
#define DUMP_WORD            0x04000000U
#define LOAD_FUSE_SCAN_CHAIN 0x05000000U
#define PROGRAME_DATA        0x07000000U
#define RUN_AUTOLOAD_8       0x08000000U
#define RUN_AUTOLOAD_A       0x0A000000U

/* Configuration registers */
typedef struct efc_config_reg
{
	uint32 CONFIG_BOUNDARY;
	uint32 CONFIG_PINS;
	uint32 CONFIG_SELFTESTCYCLES;
	uint32 CONFIG_SELFTESTSIGN;
}efc_config_reg_t;

/* Configuration registers initial value */
#define EFC_BOUNDARY_CONFIGVALUE	0x0000200FU
#define EFC_PINS_CONFIGVALUE		0x000082E0U
#define EFC_SELFTESTCYCLES_CONFIGVALUE	0x00000258U
#define EFC_SELFTESTSIGN_CONFIGVALUE	0x5362F97FU

void efcGetConfigValue(efc_config_reg_t *config_reg, config_value_type_t type);
#endif

#define CCMSELFCHECK_FAIL1            1U
#define CCMSELFCHECK_FAIL2            2U
#define CCMSELFCHECK_FAIL3            3U
#define CCMSELFCHECK_FAIL4            4U
#define PBISTSELFCHECK_FAIL1          5U
#define EFCCHECK_FAIL1                6U
#define EFCCHECK_FAIL2                7U
#define FMCECCCHECK_SINGLEBIT_FAIL           9U
#define FMCECCCHECK_DOUBLEBIT_FAIL           9U
#define RAMECCCHECK_SINGLEBIT_FAIL           9U
#define RAMECCCHECK_DOUBLEBIT_FAIL           9U
#define CHECKFLASHECC_FAIL1          11U
#define FMCECCCHECK_SINGLEBIT_FAIL           9U
#define FMCECCCHECK_DOUBLEBIT_FAIL           9U
#define VIMECCCHECK_SINGLEBIT_FAIL            12U
#define VIMECCCHECK_DOUBLEBIT_FAIL            12U
#define DMAECCCHECK_SINGLEBIT_FAIL            12U
#define DMAECCCHECK_DOUBLEBIT_FAIL            12U
#define HET1PARITYCHECK_FAIL        14U
#define HTU1PARITYCHECK_FAIL        15U
#define HET2PARITYCHECK_FAIL        16U
#define HTU2PARITYCHECK_FAIL        17U
#define ADC1PARITYCHECK_FAIL        18U
#define ADC2PARITYCHECK_FAIL        19U
#define CAN1ECCCHECK_SINGLEBIT_FAIL           20U
#define CAN1ECCCHECK_DOUBLEBIT_FAIL            21U
#define CAN2ECCCHECK_SINGLEBIT_FAIL           22U
#define CAN2ECCCHECK_DOUBLEBIT_FAIL           23U
#define CAN3ECCCHECK_SINGLEBIT_FAIL           20U
#define CAN3ECCCHECK_DOUBLEBIT_FAIL           21U
#define CAN4ECCCHECK_SINGLEBIT_FAIL           22U
#define CAN4ECCCHECK_DOUBLEBIT_FAIL           23U
#define MIBSPI1ECCCHECK_SINGLEBIT_FAIL           20U
#define MIBSPI1ECCCHECK_DOUBLEBIT_FAIL            21U
#define MIBSPI2ECCCHECK_SINGLEBIT_FAIL           20U
#define MIBSPI2ECCCHECK_DOUBLEBIT_FAIL            21U
#define MIBSPI3ECCCHECK_SINGLEBIT_FAIL           20U
#define MIBSPI3ECCCHECK_DOUBLEBIT_FAIL            21U
#define MIBSPI4ECCCHECK_SINGLEBIT_FAIL           20U
#define MIBSPI4ECCCHECK_DOUBLEBIT_FAIL            21U
#define MIBSPI5ECCCHECK_SINGLEBIT_FAIL           20U
#define MIBSPI5ECCCHECK_DOUBLEBIT_FAIL            21U
#define L2RAMECCCHECK_SINGLEBIT_FAIL	24U
#define L2RAMECCCHECK_DOUBLEBIT_FAIL	24U

#define CHECKCLOCKMONITOR_FAIL1      31U
#define CHECKFLASHEEPROMECC_FAIL1    32U 
#define CHECKFLASHEEPROMECC_FAIL2    33U
#define CHECKFLASHEEPROMECC_FAIL3    34U
#define CHECKFLASHEEPROMECC_FAIL4    35U
#define CHECKPLL1SLIP_FAIL1          36U
#define CHECKRAMADDRPARITY_FAIL1     37U
#define CHECKRAMADDRPARITY_FAIL2     38U
#define CHECKRAMUERRTEST_FAIL1       39U
#define CHECKRAMUERRTEST_FAIL2       40U
#define FMCBUS1PARITYCHECK_FAIL1     41U
#define FMCBUS1PARITYCHECK_FAIL2     42U

/* safety Init Interface Functions */
void ccmSelfCheck(void);

void stcSelfCheck(void);
void stcSelfCheckFail(void);
void cpuSelfTest(uint32 no_of_intervals, uint32 max_timeout, boolean restart_test);
void cpuSelfTestFail(void);

void memoryInit(uint32 ram);

void pbistSelfCheck(void);
void pbistRun(uint64 raminfo, uint32 algomask);
void pbistStop(void);
boolean pbistIsTestCompleted(void);
boolean pbistIsTestPassed(void);
boolean pbistPortTestStatus(uint32 port);
void pbistFail(void);

void efcCheck(void);
void efcSelfTest(void);
boolean efcStuckZeroTest(void);
boolean checkefcSelfTest(void);

void fmcBus2Check(void);
void fmcECCcheck(void);
void fmcBus1ParityCheck(void);

void checkB0RAMECC(void);
void checkB1RAMECC(void);

void checkFlashECC(void);

void vimECCCheck(void);
void dmaECCCheck(void);
void can1ECCCheck(void);
void can2ECCCheck(void);
void can3ECCCheck(void);
void can4ECCCheck(void);
void mibspi1ECCCheck(void);
void mibspi2ECCCheck(void);
void mibspi3ECCCheck(void);
void mibspi4ECCCheck(void);
void mibspi5ECCCheck(void);
void adc1ParityCheck(void);
void adc2ParityCheck(void);
void het1ParityCheck(void);
void htu1ParityCheck(void);
void het2ParityCheck(void);
void htu2ParityCheck(void);
void mibspi5ParityCheck(void);

void checkRAMECC(void);
void checkClockMonitor(void);
void checkFlashEEPROMECC(void);
void checkPLL1Slip(void);
void checkPLL2Slip(void);
void checkRAMAddrParity(void);
void checkRAMUERRTest(void);

void custom_dabort(void);
void selftestFailNotification(uint32 flag);

/* USER CODE BEGIN (2) */
/* USER CODE END */

/* Configuration registers */
typedef struct ccmr5_config_reg
{
	uint32 CONFIG_CCMKEYR;
}ccmr5_config_reg_t;

/* Configuration registers initial value */
#define CCMR5_CCMKEYR_CONFIGVALUE	0U

void ccmr5GetConfigValue(ccmr5_config_reg_t *config_reg, config_value_type_t type);
#endif
