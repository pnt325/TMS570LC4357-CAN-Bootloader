/**
 * @file       bl_can.h
 * @copyright  
 * @license    
 * @version    1.0.0
 * @date       2021-07-31
 * @author     
 * @brief      Definitions for the CAN transport functions.
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BL_CAN_H
#define __BL_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bl_config.h"

#if defined (RM57) || defined (TMS570LC43)
#include "HL_can.h"
#include "HL_sys_common.h"
#else
#include "can.h"
#include "sys_common.h"
#endif

/* Public defines ----------------------------------------------------- */
//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_IFCMD register.
//
//*****************************************************************************
#define CAN_IFCMD_BUSY         (0x80)           // Busy Flag
#define CAN_IFCMD_MNUM_M       (0xFF)           // Message Number
#define CAN_IFCMD_MNUM_RSVD    (0x00000000)     // 0 is not a valid message number;
#define CAN_IFCMD_MNUM_S       (0)

#define CAN_IFCMD_WRNRD        (0x80)  // Write, Not Read
#define CAN_IFCMD_MASK         (0x40)  // Access Mask Bits
#define CAN_IFCMD_ARB          (0x20)  // Access Arbitration Bits
#define CAN_IFCMD_CONTROL      (0x10)  // Access Control Bits
#define CAN_IFCMD_CLRINTPND    (0x08)  // Clear Interrupt Pending Bit
#define CAN_IFCMD_NEWDAT       (0x04)  // Access New Data
#define CAN_IFCMD_TXRQST       (0x04)  // Access Transmission Request
#define CAN_IFCMD_DATAA        (0x02)  // Access Data Byte 0 to 3
#define CAN_IFCMD_DATAB        (0x01)  // Access Data Byte 4 to 7

//*****************************************************************************
//
// The following are defines for the bit fields in the IF1MSK register.
//
//*****************************************************************************
#define CAN_IFMSK_MXTD         (0x80000000)  // Mask Extended Identifier
#define CAN_IFMSK_MDIR         (0x40000000)  // Mask Message Direction
#define CAN_IFMSK_IDMSK_M      (0x1FFFFFFF)  // Identifier Mask
#define CAN_IFMSK_IDMSK_S      (0)

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1ARB2 register.
//
//*****************************************************************************
#define CAN_IFARB_MSGVAL       (0x80000000)  // Message Valid
#define CAN_IFARB_XTD          (0x40000000)  // Extended Identifier
#define CAN_IFARB_DIR          (0x20000000)  // Message Direction
#define CAN_IFARB_ID_M         (0x1FFFFFFF)  // Message Identifier
#define CAN_IFARB_11ID_M       (0x1FFC0000)  // Message Identifier
#define CAN_IFARB_29ID_M       (0x1FFFFFFF)  // Message Identifier
#define CAN_IFARB_ID_S         (0)

//*****************************************************************************
//
// The following are defines for the bit fields in the IF1MCTL register.
//
//*****************************************************************************
#define CAN_IFMCTL_NEWDAT       (0x00008000)  // New Data
#define CAN_IFMCTL_MSGLST       (0x00004000)  // Message Lost
#define CAN_IFMCTL_INTPND       (0x00002000)  // Interrupt Pending
#define CAN_IFMCTL_UMASK        (0x00001000)  // Use Acceptance Mask
#define CAN_IFMCTL_TXIE         (0x00000800)  // Transmit Interrupt Enable
#define CAN_IFMCTL_RXIE         (0x00000400)  // Receive Interrupt Enable
#define CAN_IFMCTL_RMTEN        (0x00000200)  // Remote Enable
#define CAN_IFMCTL_TXRQST       (0x00000100)  // Transmit Request
#define CAN_IFMCTL_EOB          (0x00000080)  // End of Buffer
#define CAN_IFMCTL_DLC_M        (0x0000000F)  // Data Length Code
#define CAN_IFMCTL_DLC_S        (0)

/* Public enumerate/structure ----------------------------------------- */
typedef struct 
{
  uint32_t app_update_status;
  uint32_t image_version;
  uint32_t image_size;
  uint32_t image_crc;
}
bl_status_t;

/* Private variables -------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
void bl_can_init(canBASE_t *node);
void bl_can_run(canBASE_t *node);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BL_CAN_H

/* End of file -------------------------------------------------------- */

