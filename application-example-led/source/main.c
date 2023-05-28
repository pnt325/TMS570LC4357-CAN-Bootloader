/**
 * @file       bl_main.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-07-31
 * @author     Thuan Le
 * @brief      The main file for the application
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "HL_het.h"
#include "HL_gio.h"
#include "HL_sci.h"
#include "HL_system.h"
#include "HL_sys_common.h"
#include "HL_sys_core.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
void run_LED_StartUp1(uint8_t ledNum)
{
  int temp, delay;
  // LED Number: 0, 31, 17, 29, 18, 25
  /** - Delay Parameter */
  delay = 0x20000;

  /** - This if statment is a placeholder for ArgoBoard/USBStick check */
  if (1)
  {
    /** - Configure NHET pins as output */
    hetREG1->DIR = 0 | (1 << 0) | (1 << 5) | (1 << 17) | (1 << 18) | (1 << 25) | (1 << 27) | (1 << 29) | (1 << 31);

    /** - Turn all LEDs off */
    hetREG1->DOUT = 0x00000000;

    /** - Simple Delay */
    for (temp = 0; temp < delay; temp++)
      ;

    /** - Set only NHET[0] */
    hetREG1->DOUT = (0x1 << ledNum);
    /** - Simple Delay */
    for (temp = 0; temp < delay; temp++)
      ;
  }
}

/* Function definitions ----------------------------------------------- */
void main(void)
{
  run_LED_StartUp1(0);
  run_LED_StartUp1(31);
  run_LED_StartUp1(17);
  run_LED_StartUp1(29);
  run_LED_StartUp1(18);
  run_LED_StartUp1(25);
  while (1);
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */
