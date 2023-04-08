/**
 * @file       eeprom.h
 * @brief      EEPROM Source
 * @date       03/24/23
 */

/* Include ===================================================================*/

/* Project include */
#include "eeprom.h"

/* SDK Include */
#include "ti_fee.h"

/* Macro =====================================================================*/


/* Type ======================================================================*/


/* Functions =================================================================*/
static void eeprom_delay(void);

/* Variables =================================================================*/



/*============================================================================*/
/* PUBLIC FUNCTION                                                            */
/*============================================================================*/

void eeprom_init(void)
{
  uint16_t status;
  TI_Fee_Init();
  do
  {
    TI_Fee_MainFunction();
    eeprom_delay();
    status = TI_Fee_GetStatus(0);
  } while (status != IDLE);
}

void eeprom_write(uint8_t* data)
{
  uint16_t status;
  TI_Fee_WriteAsync(0, data);
  do
  {
    TI_Fee_MainFunction();
    eeprom_delay();
    status = TI_Fee_GetStatus(0);
  } while (status != IDLE);
}

void eeprom_read(uint8_t* buf)
{
  uint16_t status;
  TI_Fee_ReadSync(0, 0, buf, 8);
  do
  {
    TI_Fee_MainFunction();
    eeprom_delay();
    status = TI_Fee_GetStatus(0);
  } while (status != IDLE);
}

/*============================================================================*/
/* PRIVATE FUNCTION                                                           */
/*============================================================================*/

static void eeprom_delay(void)
{
  unsigned int dummycnt = 0x0000FFU;
  do
  {
    dummycnt--;
  } while (dummycnt > 0);
}
