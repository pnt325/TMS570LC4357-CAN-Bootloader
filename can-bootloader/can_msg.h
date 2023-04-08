/**
 * @file       can_msg.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-07-31
 * @author     Thuan Le
 * @brief      CAN Message Header
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __CAN_MSG_H
#define __CAN_MSG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/* Public defines ----------------------------------------------------- */
#define CAN_MSG_APP_ERASE   {11,13,88,55,3,211,177,249}

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief 29 Bit CAN ID
 */
typedef enum
{
  /**
   * @brief Send this message ID to start erase flash
   * Success: CAN_ID_BL_APP_ERASE_APOS
   * Failure: CAN_ID_BL_APP_ERASE_ANEG
   * 
   * @note Message length = 8, with special data
   */
  CAN_ID_BL_APP_ERASE       = 0x0CFFD000,   /* app erase cmd */
  CAN_ID_BL_APP_ERASE_APOS  = 0x0CFFD001,   /* ack positive */
  CAN_ID_BL_APP_ERASE_ANEG  = 0x0CFFD002,   /* ack negative */

  /**
   * @brief 
   * 
   * @note Message length =  2;
   */
  CAN_ID_BL_STOP            = 0x0CFFD003,   /* stop cmd */
  CAN_ID_BL_STOP_APOS       = 0x0CFFD004,   /* ack positive */
  CAN_ID_BL_STOP_ANEG       = 0x0CFFD005,   /* ack negative */

  /**
   * @brief Reset from APP to bootloader
   * @note After reset to bootloader the device will be response 
   * the message id: CAN_ID_BL_CPU_RESET_APOS to indicate with host 
   * reset complete.
   * @note msg_len = 0
   */
  CAN_ID_BL_CPU_RESET       = 0x0CFFD006,   /* cpu reset cmd */
  CAN_ID_BL_CPU_RESET_APOS  = 0x0CFFD007,   /* ack positive */

  /**
   * @brief Request current app version info.
   * @note Message length  = 0
   * @note version define 
   * Response message ID: CAN_ID_BL_VER_REQ_RSP
   * [0] software version
   * [1] product id
   * [2] hardware version
   * [3] bootloader version
   */
  CAN_ID_BL_VER_REQ         = 0x0CFFD008,   /* req all version info */
  CAN_ID_BL_VER_REQ_RSP     = 0x0CFFD009,   /* all ver response */

  /**
   * @brief Request memory map
   * @note Message length = 0
   * @note Repsonse 
   */
  CAN_ID_BL_MAP_REQ         = 0x0CFFD00A,   /* req memory map info */
  CAN_ID_BL_MAP_REQ_RSP_ARM = 0x0CFFD00B,   /* memory map response */
  CAN_ID_BL_MAP_REQ_RSP_C2K = 0x0CFFD00C,

  CAN_ID_BL_ADDR            = 0x0CFFD020,   /* 32-bit address */
  CAN_ID_BL_ADDR_APOS       = 0x0CFFD021,   /* ack positive */
  CAN_ID_BL_ADDR_ANEG       = 0x0CFFD022,   /* ack negative */

  CAN_ID_BL_DATA            = 0x0CFFD023,   /* data */
  CAN_ID_BL_DATA_APOS       = 0x0CFFD024,   /* ack positive */
  CAN_ID_BL_DATA_ANEG       = 0x0CFFD025,   /* ack negative */
}
can_id_t;

/* Private variables -------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
bool can_is_msg_erase(const uint8_t* buf);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __CAN_MSG_H

/* End of file -------------------------------------------------------- */
