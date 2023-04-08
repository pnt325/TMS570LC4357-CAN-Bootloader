/**
 * @file       bl_main.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-07-31
 * @author     Thuan Le
 * @brief      The main file for the bootloader
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bl_config.h"
#include "sci_common.h"

#if defined(CAN_ENABLE_UPDATE)
#include "bl_can.h"
#endif

#if defined(RM57) || defined(TMS570LC43)
#include "HL_het.h"
#include "HL_gio.h"
#include "HL_sci.h"
#include "HL_system.h"
#include "HL_sys_common.h"
#include "HL_sys_core.h"
#else
#include "het.h"
#include "sci.h"
#include "gio.h"
#include "system.h"
#include "sys_common.h"
#include "sys_core.h"
#endif

#include "bl_check.h"
#include "bl_led_demo.h"

/* Private defines ---------------------------------------------------- */
#define E_PASS      (0)
#define E_FAIL      (0x1U)
#define E_TIMEOUT   (0x2U)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
// This holds the current remaining size in bytes to be downloaded.
uint32_t g_ulTransferSize;

// This holds the current address that is being written to during a download command 
uint32_t g_ulTransferAddress;

// This is the data buffer used during transfers to the boot loader.
uint32_t g_pulDataBuffer[BUFFER_SIZE];

// This is the data buffer used for update status.
// g_pulUpdateSuccess[] are used to store application update status and application image's version etc
uint32_t g_pulUpdateSuccess[8] = {0x5A5A5A5A, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
uint32_t g_ulUpdateStatusAddr = APP_STATUS_ADDRESS;

// 16 bytes or 4 32-bit words
uint32_t g_ulUpdateBufferSize = 32; 

// This is an specially aligned buffer pointer to g_pulDataBuffer to make
// copying to the buffer simpler.  It must be offset to end on an address that
// ends with 3.
uint8_t *g_pucDataBuffer;

extern unsigned int apiLoadStart;
extern unsigned int apiLoadSize;
extern unsigned int apiRunStart;

extern unsigned int constLoadStart;
extern unsigned int constLoadSize;
extern unsigned int constRunStart;

/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
void main(void)
{
  // Version number, 03.00, in 2019
  g_pulUpdateSuccess[3] = 0x30002019; 
  uint32_t fnRetValue = 0;

  // Initialize SCI Routines to receive Command and transmit data
  sciInit();

  // Copy the flash APIs to SRAM
  memcpy(&apiRunStart, &apiLoadStart, (uint32)&apiLoadSize);

  // Copy the .const section
  memcpy(&constRunStart, &constLoadStart, (uint32)&constLoadSize);

  UART_putString(UART, "\r Hercules MCU CAN BootLoader ");
  UART_putString(UART, "\r TI DSP Application Team, qjwang@ti.com \r\r");

  // See if an update should be performed.
  fnRetValue = CheckForceUpdate();

  if (!fnRetValue)
  {
    UART_putString(UART, "\r Jump to application...  ");
    g_ulTransferAddress = (uint32_t)APP_START_ADDRESS;
    ((void (*)(void))g_ulTransferAddress)();
  }

  // Configure the can device
  bl_can_init(CAN_PORT);

  bl_can_run(CAN_PORT);
}

/* Private function definitions ---------------------------------------- */
void delay(unsigned int val)
{
  while (val--)
    ;
}

/* End of file -------------------------------------------------------- */
