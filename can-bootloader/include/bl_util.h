/**
 * @file       bl_util.h
 * @copyright  
 * @license    
 * @version    1.0.0
 * @date       2021-07-31
 * @author     
 * @brief      Util
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BL_UTIL_H
#define __BL_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "HL_sys_common.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
void bl_util_32tobuf_msb(uint8_t *buf, uint32_t val);
uint16_t bl_util_crc16_incremental(uint16_t crc, uint8_t *data, uint32_t len);
uint16_t bl_util_crc16(uint8_t *data, uint32_t len);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BL_UTIL_H

/* End of file -------------------------------------------------------- */

