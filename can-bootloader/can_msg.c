/**
 * @file       can_msg.h
 * @brief      CAN Message Source
 * @date       03/23/23
 */

/* Include ===================================================================*/

/* Project include */
#include "can_msg.h"

/* SDK Include */


/* Macro =====================================================================*/


/* Type ======================================================================*/


/* Functions =================================================================*/


/* Variables =================================================================*/



/*============================================================================*/
/* PUBLIC FUNCTION                                                            */
/*============================================================================*/

/**
 * @brief Check that is erase message format
 * 
 * @param buf Point to buffer
 * @return true Success
 * @return false Failure
 */
bool can_is_msg_erase(const uint8_t *buf)
{
  int i;
  uint8_t erase_msg[] = CAN_MSG_APP_ERASE;
  for (i = 0; i < 8; i++)
  {
    if (buf[i] != erase_msg[i])
    {
      break;
    }
  }
  return (i == 8);
}

/*============================================================================*/
/* PRIVATE FUNCTION                                                           */
/*============================================================================*/
