/**
 * @file      can_msg.h
 * @brief     CAN Message Header
 * @date      03/23/23
 */

#ifndef CAN_MSG_H_
#define CAN_MSG_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum 
{
  CAN_ID_SRC = 0x300,     /** Device CAN ID handle */
  CAN_ID_DST = 0x301,     /** Host CAN ID handle */
} can_id_t;

typedef enum 
{
  CAN_MSG_ID_RESET         = 0x00,
  CAN_MSG_ID_CONNECT       = 0xFF,
  CAN_MSG_ID_GET_SEED      = 0xF8,
  CAN_MSG_ID_UNLOCK        = 0xF7,
  CAN_MSG_ID_START         = 0xD2,   /** Start program */
  CAN_MSG_ID_ERASE         = 0xD1,   /** Erase flash base on flash size and address */
  CAN_MSG_ID_MTA           = 0xF6,   /** Send request download: address and size */
  CAN_MSG_ID_KEY_REQ       = 0x06,
  CAN_MSG_ID_PROGRAM       = 0xD0,   /** Program data */
  CAN_MSG_ID_PROGRAM_RESET = 0xCF,   /** Reset device after bootloader success */
  CAN_MSG_ID_RESP          = 0xFF,   /** Response message to software */
} can_msg_id_t;

#define CAN_MSG_RESP_OK   {CAN_MSG_ID_RESP}     /** Response success */
#define CAN_MSG_RESP_FAIL {CAN_MSG_ID_RESP - 1} /** Response failure */

#define CAN_MSG_RESET     {CAN_MSG_ID_RESET}
#define CAN_MSG_CONNECT   {CAN_MSG_ID_CONNECT, 0x00}
#define CAN_MSG_GET_SEED  {CAN_MSG_ID_UNLOCK, 0x00, 0x00}
#define CAN_MSG_UNLOCK    {CAN_MSG_ID_UNLOCK, 0x06, 'P', 'S', 'S', 'W', 'R', 'D'}
#define CAN_MSG_START     {CAN_MSG_ID_START}
#define CAN_MSG_ERASE     {CAN_MSG_ID_ERASE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

// NOTE Flahs size and address is not clear.
/**
 * @brief Send request to download 
 * [0] = CAN_MSG_ID_MTA
 * [1,3] = ???
 * [4,7] = Address
 */
#define CAN_MSG_MTA       {CAN_MSG_ID_MTA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

typedef struct
{
  uint8_t id;
  uint8_t size;
  uint8_t buf[5];
} can_msg_program_t;

#define CAN_MSG_PROGRAM_RESET {CAN_MSG_ID_PROGRAM_RESET}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CAN_MSG_H_ */
