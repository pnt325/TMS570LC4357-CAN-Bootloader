/**
 * @file      eeprom.h
 * @brief     EEPROM Header
 * @date      03/24/23
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void eeprom_init(void);
void eeprom_write(uint8_t* data);
void eeprom_read(uint8_t* buf);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EEPROM_H_ */
