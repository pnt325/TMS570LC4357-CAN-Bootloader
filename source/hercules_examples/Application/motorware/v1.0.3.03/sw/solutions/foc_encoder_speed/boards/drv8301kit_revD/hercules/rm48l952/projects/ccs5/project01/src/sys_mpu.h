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
/** @file sys_mpu.h
*   @brief System Mpu Header File
*   @date 15.December.2011
*   @version 03.00.00
*   
*   This file contains:
*   - Mpu Interface Functions
*   .
*   which are relevant for the memory protection unit driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef __SYS_MPU_H__
#define __SYS_MPU_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/** @def mpuREGION1
*   @brief Mpu region 1
*
*   Alias for Mpu region 1
*/
#define mpuREGION1 0U

/** @def mpuREGION2
*   @brief Mpu region 2
*
*   Alias for Mpu region 1
*/
#define mpuREGION2 1U

/** @def mpuREGION3
*   @brief Mpu region 3
*
*   Alias for Mpu region 3
*/
#define mpuREGION3 2U

/** @def mpuREGION4
*   @brief Mpu region 4
*
*   Alias for Mpu region 4
*/
#define mpuREGION4 3U

/** @def mpuREGION5
*   @brief Mpu region 5
*
*   Alias for Mpu region 5
*/
#define mpuREGION5 4U

/** @def mpuREGION6
*   @brief Mpu region 6
*
*   Alias for Mpu region 6
*/
#define mpuREGION6 5U

/** @def mpuREGION7
*   @brief Mpu region 7
*
*   Alias for Mpu region 7
*/
#define mpuREGION7 6U

/** @def mpuREGION8
*   @brief Mpu region 8
*
*   Alias for Mpu region 8
*/
#define mpuREGION8 7U

/** @def mpuREGION9
*   @brief Mpu region 9
*
*   Alias for Mpu region 9
*/
#define mpuREGION9 8U

/** @def mpuREGION10
*   @brief Mpu region 10
*
*   Alias for Mpu region 10
*/
#define mpuREGION10 9U

/** @def mpuREGION11
*   @brief Mpu region 11
*
*   Alias for Mpu region 11
*/
#define mpuREGION11 10U

/** @def mpuREGION12
*   @brief Mpu region 12
*
*   Alias for Mpu region 12
*/
#define mpuREGION12 11U




/** @enum mpuRegionAccessPermission
*   @brief Alias names for mpu region access permissions
*
*   This enumeration is used to provide alias names for the mpu region access permission:
*     - MPU_PRIV_NA_USER_NA_EXEC no access in priviledged mode, no access in user mode and execute
*     - MPU_PRIV_RW_USER_NA_EXEC read/write in priviledged mode, no access in user mode and execute
*     - MPU_PRIV_RW_USER_RO_EXEC read/write in priviledged mode, read only in user mode and execute
*     - MPU_PRIV_RW_USER_RW_EXEC read/write in priviledged mode, read/write in user mode and execute
*     - MPU_PRIV_RO_USER_NA_EXEC read only in priviledged mode, no access in user mode and execute
*     - MPU_PRIV_RO_USER_RO_EXEC read only in priviledged mode, read only in user mode and execute
*     - MPU_PRIV_NA_USER_NA_NOEXEC no access in priviledged mode, no access in user mode and no execution
*     - MPU_PRIV_RW_USER_NA_NOEXEC read/write in priviledged mode, no access in user mode and no execution
*     - MPU_PRIV_RW_USER_RO_NOEXEC read/write in priviledged mode, read only in user mode and no execution
*     - MPU_PRIV_RW_USER_RW_NOEXEC read/write in priviledged mode, read/write in user mode and no execution
*     - MPU_PRIV_RO_USER_NA_NOEXEC read only in priviledged mode, no access in user mode and no execution
*     - MPU_PRIV_RO_USER_RO_NOEXEC read only in priviledged mode, read only in user mode and no execution
*
*/
enum mpuRegionAccessPermission
{
    MPU_PRIV_NA_USER_NA_EXEC   = 0x0000, /**< Alias no access in priviledged mode, no access in user mode and execute */
    MPU_PRIV_RW_USER_NA_EXEC   = 0x0100, /**< Alias no read/write in priviledged mode, no access in user mode and execute */
    MPU_PRIV_RW_USER_RO_EXEC   = 0x0200, /**< Alias no read/write in priviledged mode, read only in user mode and execute */
    MPU_PRIV_RW_USER_RW_EXEC   = 0x0300, /**< Alias no read/write in priviledged mode, read/write in user mode and execute */
    MPU_PRIV_RO_USER_NA_EXEC   = 0x0500, /**< Alias no read only in priviledged mode, no access in user mode and execute */
    MPU_PRIV_RO_USER_RO_EXEC   = 0x0600, /**< Alias no read only in priviledged mode, read only in user mode and execute */
    MPU_PRIV_NA_USER_NA_NOEXEC = 0x1000, /**< Alias no access in priviledged mode, no access in user mode and no execution */
    MPU_PRIV_RW_USER_NA_NOEXEC = 0x1100, /**< Alias no read/write in priviledged mode, no access in user mode and no execution */
    MPU_PRIV_RW_USER_RO_NOEXEC = 0x1200, /**< Alias no read/write in priviledged mode, read only in user mode and no execution */
    MPU_PRIV_RW_USER_RW_NOEXEC = 0x1300, /**< Alias no read/write in priviledged mode, read/write in user mode and no execution */
    MPU_PRIV_RO_USER_NA_NOEXEC = 0x1500, /**< Alias no read only in priviledged mode, no access in user mode and no execution */
    MPU_PRIV_RO_USER_RO_NOEXEC = 0x1600  /**< Alias no read only in priviledged mode, read only in user mode and no execution */
};

/** @enum mpuRegionType
*   @brief Alias names for mpu region type
*
*   This enumeration is used to provide alias names for the mpu region type:
*     - MPU_STRONGLYORDERED_SHAREABLE Memory type strongly ordered and shareable
*     - MPU_DEVICE_SHAREABLE          Memory type device and shareable
*     - MPU_NORMAL_OIWTNOWA_NONSHARED Memory type normal outer and inner write-through, no write allocate and non shared
*     - MPU_NORMAL_OIWTNOWA_SHARED    Memory type normal outer and inner write-through, no write allocate and shared
*     - MPU_NORMAL_OIWBNOWA_NONSHARED Memory type normal outer and inner write-back, no write allocate and non shared
*     - MPU_NORMAL_OIWBNOWA_SHARED    Memory type normal outer and inner write-back, no write allocate and shared
*     - MPU_NORMAL_OINC_NONSHARED     Memory type normal outer and inner non-cachable and non shared
*     - MPU_NORMAL_OINC_SHARED        Memory type normal outer and inner non-cachable and shared
*     - MPU_NORMAL_OIWBWA_NONSHARED   Memory type normal outer and inner write-back, write allocate and non shared
*     - MPU_NORMAL_OIWBWA_SHARED      Memory type normal outer and inner write-back, write allocate and shared
*     - MPU_DEVICE_NONSHAREABLE       Memory type device and non shareable
*/
enum mpuRegionType
{
    MPU_STRONGLYORDERED_SHAREABLE = 0x0000, /**< Memory type strongly ordered and shareable */
    MPU_DEVICE_SHAREABLE          = 0x0001, /**< Memory type device and shareable */
    MPU_NORMAL_OIWTNOWA_NONSHARED = 0x0002, /**< Memory type normal outer and inner write-through, no write allocate and non shared */
    MPU_NORMAL_OIWBNOWA_NONSHARED = 0x0003, /**< Memory type normal outer and inner write-back, no write allocate and non shared */
    MPU_NORMAL_OIWTNOWA_SHARED    = 0x0006, /**< Memory type normal outer and inner write-through, no write allocate and shared */
    MPU_NORMAL_OIWBNOWA_SHARED    = 0x0007, /**< Memory type normal outer and inner write-back, no write allocate and shared */
    MPU_NORMAL_OINC_NONSHARED     = 0x0008, /**< Memory type normal outer and inner non-cachable and non shared */
    MPU_NORMAL_OIWBWA_NONSHARED   = 0x000B, /**< Memory type normal outer and inner write-back, write allocate and non shared */
    MPU_NORMAL_OINC_SHARED        = 0x000C, /**< Memory type normal outer and inner non-cachable and shared */
    MPU_NORMAL_OIWBWA_SHARED      = 0x000F, /**< Memory type normal outer and inner write-back, write allocate and shared */
    MPU_DEVICE_NONSHAREABLE       = 0x0010  /**< Memory type device and non shareable */
};

/** @enum mpuRegionSize
*   @brief Alias names for mpu region type
*
*   This enumeration is used to provide alias names for the mpu region type:
*     - MPU_STRONGLYORDERED_SHAREABLE Memory type strongly ordered and shareable
*     - MPU_32_BYTES Memory size in bytes
*     - MPU_64_BYTES Memory size in bytes
*     - MPU_128_BYTES Memory size in bytes
*     - MPU_256_BYTES Memory size in bytes
*     - MPU_512_BYTES Memory size in bytes
*     - MPU_1_KB Memory size in kB
*     - MPU_2_KB Memory size in kB
*     - MPU_4_KB Memory size in kB
*     - MPU_8_KB Memory size in kB
*     - MPU_16_KB Memory size in kB
*     - MPU_32_KB Memory size in kB
*     - MPU_64_KB Memory size in kB
*     - MPU_128_KB Memory size in kB
*     - MPU_256_KB  Memory size in kB
*     - MPU_512_KB Memory size in kB
*     - MPU_1_MB Memory size in MB
*     - MPU_2_MB Memory size in MB
*     - MPU_4_MB Memory size in MB
*     - MPU_8_MBv Memory size in MB
*     - MPU_16_MB Memory size in MB
*     - MPU_32_MB Memory size in MB
*     - MPU_64_MB Memory size in MB
*     - MPU_128_MB Memory size in MB
*     - MPU_256_MB Memory size in MB
*     - MPU_512_MB Memory size in MB
*     - MPU_1_GB Memory size in GB
*     - MPU_2_GB Memory size in GB
*     - MPU_4_GB Memory size in GB
*/
enum mpuRegionSize
{
    MPU_32_BYTES  = 0x04, /**< Memory size in bytes */
    MPU_64_BYTES  = 0x05, /**< Memory size in bytes */
    MPU_128_BYTES = 0x06, /**< Memory size in bytes */
    MPU_256_BYTES = 0x07, /**< Memory size in bytes */
    MPU_512_BYTES = 0x08, /**< Memory size in bytes */
    MPU_1_KB      = 0x09, /**< Memory size in kB */
    MPU_2_KB      = 0x0A, /**< Memory size in kB */
    MPU_4_KB      = 0x0B, /**< Memory size in kB */
    MPU_8_KB      = 0x0C, /**< Memory size in kB */
    MPU_16_KB     = 0x0D, /**< Memory size in kB */
    MPU_32_KB     = 0x0E, /**< Memory size in kB */
    MPU_64_KB     = 0x0F, /**< Memory size in kB */
    MPU_128_KB    = 0x10, /**< Memory size in kB */
    MPU_256_KB    = 0x11, /**< Memory size in kB */
    MPU_512_KB    = 0x12, /**< Memory size in kB */
    MPU_1_MB      = 0x13, /**< Memory size in MB */
    MPU_2_MB      = 0x14, /**< Memory size in MB */
    MPU_4_MB      = 0x15, /**< Memory size in MB */
    MPU_8_MB      = 0x16, /**< Memory size in MB */
    MPU_16_MB     = 0x17, /**< Memory size in MB */
    MPU_32_MB     = 0x18, /**< Memory size in MB */
    MPU_64_MB     = 0x19, /**< Memory size in MB */
    MPU_128_MB    = 0x1A, /**< Memory size in MB */
    MPU_256_MB    = 0x1B, /**< Memory size in MB */
    MPU_512_MB    = 0x1C, /**< Memory size in MB */
    MPU_1_GB      = 0x1D, /**< Memory size in GB */
    MPU_2_GB      = 0x1E, /**< Memory size in GB */
    MPU_4_GB      = 0x1F  /**< Memory size in GB */
};

/** @fn void _mpuInit_(void)
*   @brief Initialize Mpu
*
*   This function initalizes memory protection unit.
*/
void _mpuInit_(void);

/** @fn void _mpuEnable_(void)
*   @brief Enable Mpu
*
*   This function enables memory protection unit.
*/
void _mpuEnable_(void);

/** @fn void _mpuDisable_(void)
*   @brief Disable Mpu
*
*   This function disables memory protection unit.
*/
void _mpuDisable_(void);

/** @fn void _mpuEnableBackgroundRegion_(void)
*   @brief Enable Mpu background region
*
*   This function enables background region of the memory protection unit.
*/
void _mpuEnableBackgroundRegion_(void);

/** @fn void _mpuDisableBackgroundRegion_(void)
*   @brief Disable Mpu background region
*
*   This function disables background region of the memory protection unit.
*/
void _mpuDisableBackgroundRegion_(void);

/** @fn uint32_t _mpuGetNumberOfRegions_(void)
*   @brief Returns number of implemented Mpu regions
*   @return Number of implemented mpu regions
*
*   This function returns the number of implemented mpu regions.
*/
uint32_t _mpuGetNumberOfRegions_(void);

/** @fn uint32_t _mpuAreRegionsSeparate_(void)
*   @brief Returns the type of the implemented mpu regions
*   @return Mpu type of regions
*
*   This function returns 0 when mpu regions are of type unified atherwise regions are of type separate.
*/
uint32_t _mpuAreRegionsSeparate_(void);

/** @fn void _mpuSetRegion_(uint32_t region)
*   @brief Set mpu region number
*
*   This function selects one of the implemented mpu regions.
*/
void _mpuSetRegion_(uint32_t region);

/** @fn uint32_t _mpuGetRegion_(void)
*   @brief Returns the currently selected mpu region
*   @return Mpu region number
*
*   This function returns currently selected mpu region number.
*/
uint32_t _mpuGetRegion_(void);

/** @fn void _mpuSetRegionBaseAddress_(uint32_t address)
*   @brief Set base address of currently selected mpu region
*   @note The base address must always aligned with region size
*
*   This function sets the base address of currently selected mpu region.
*/
void _mpuSetRegionBaseAddress_(uint32_t address);

/** @fn uint32_t _mpuGetRegionBaseAddress_(void)
*   @brief Returns base address of currently selected mpu region
*   @return Current base address of selected mpu region
*
*   This function returns the base address of currently selected mpu region.
*/
uint32_t _mpuGetRegionBaseAddress_(void);

/** @fn void _mpuSetRegionTypeAndPermission_(uint32_t type, uint32_t permission)
*   @brief Set type of currently selected mpu region
*
*   This function sets the type of currently selected mpu region.
*/
void _mpuSetRegionTypeAndPermission_(uint32_t type, uint32_t permission);

/** @fn uint32_t _mpuGetRegionType_(void)
*   @brief Returns the type of currently selected mpu region
*   @return Current type of selected mpu region
*
*   This function returns the type of currently selected mpu region.
*/
uint32_t _mpuGetRegionType_(void);

/** @fn uint32_t _mpuGetRegionPermission_(void)
*   @brief Returns permission of currently selected mpu region
*   @return Current type of selected mpu region
*
*   This function returns permission of currently selected mpu region.
*/
uint32_t _mpuGetRegionPermission_(void);

/** @fn void _mpuSetRegionSizeRegister_(uint32_t value)
*   @brief Set mpu region size register value
*
*   This function sets mpu region size register value.
*/
void _mpuSetRegionSizeRegister_(uint32_t value);

#endif
