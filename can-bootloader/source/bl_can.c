/**
 * @file       bl_can.c
 * @copyright  
 * @license    
 * @version    1.0.0
 * @date       2021-07-31
 * @author     
 * @brief      Bootloader file support CAN bus
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bl_config.h"

#if defined(CAN_ENABLE_UPDATE)

#include "bl_check.h"
#include "flash.h"
#include "bl_can.h"
#include "bl_commands.h"
#include "F021.h"
#include "bl_led_demo.h"
#include "sci_common.h"
#include "can_msg.h"
#include "version.h"

#if defined(RM57) || defined(TMS570LC43)
#include "HL_can.h"
#include "HL_gio.h"
#include "HL_sci.h"
#include "HL_system.h"
#else
#include "can.h"
#include "gio.h"
#include "sci.h"
#include "system.h"
#endif

/* Public defines ----------------------------------------------------- */
// The results that can be returned by the CAN APIs.
#define CAN_CMD_SUCCESS (0x00)
#define CAN_CMD_FAIL    (0x01)

// The message object number and index to the local message object memory to
// use when accessing the messages.
#define MSG_OBJ_BCAST_RX_ID   (1)
#define MSG_OBJ_BCAST_TX_ID   (2)

// Memory Map
#define MEM_MAP_START_ADDR    (APP_STATUS_ADDRESS)
#define MEM_MAP_SIZE          (0x8000)
#define MEM_MAP_END_ADDR      (MEM_MAP_START_ADDR + MEM_MAP_SIZE)

/* Private enumerate/structure ---------------------------------------- */
static uint16_t bl_checksum_received;
static uint16_t bl_checksum_calculated;
static uint32_t bl_app_writer_addr;
static bool start_send_data = true;

/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
// Holds the current address to write to when data is received via the Send Data Command.
extern uint32_t g_ulTransferAddress;

// Holds the remaining bytes expected to be received.
extern uint32_t g_ulTransferSize;

// The buffer used to receive data from the update.
static uint8_t *g_pucCommandBuffer;

// These globals are used to store the first two words to prevent a partial
// image from being booted.
extern uint32_t g_pulDataBuffer[BUFFER_SIZE];
extern uint32_t g_pulUpdateSuccess[8];
extern uint32_t g_ulUpdateStatusAddr;
extern uint32_t g_ulUpdateBufferSize; // 32 bytes or 8 32-bit words

/* Private variables -------------------------------------------------- */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
//   static const uint32_t g_ulCanByteOrder[] = {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U};
#else
static const uint32_t g_ulCanByteOrder[] = {3U, 2U, 1U, 0U, 7U, 6U, 5U, 4U};
#endif

// CRC16/XMODEM table using polynomial 0x1021
static const uint16_t crc16_table[] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0};

/* Private function prototypes ---------------------------------------- */
extern void delay();

static void CANMessageSetRx(canBASE_t *node);
static void CANMessageSetTx(canBASE_t *node, uint32_t ulId, const uint8_t *pucData, uint32_t ulSize);
static uint32_t CANMessageGetRx(canBASE_t *node, uint8_t *pucData, uint32_t *pulMsgID);

static uint32_t PacketRead(canBASE_t *node, uint8_t *pucData, uint32_t *pulSize);
static void PacketWrite(canBASE_t *node, uint32_t ulId, const uint8_t *pucData, uint32_t ulSize);

static void bl_can_handle_msg_get_memory_map(canBASE_t *node, uint8_t *data, uint32_t len);
static void bl_can_handle_msg_write_data(canBASE_t *node, uint8_t *data, uint32_t len);
static void bl_can_handle_msg_set_start_address(canBASE_t *node, uint8_t *data, uint32_t len);
static void bl_can_handle_msg_version_request(canBASE_t *node, uint8_t *data, uint32_t len);
static void bl_can_handle_msg_cpu_reset(canBASE_t *node, uint8_t *data, uint32_t len);
static void bl_can_handle_msg_stop(canBASE_t *node, uint8_t *data, uint32_t len);
static void bl_can_handle_msg_app_erase(canBASE_t *node, uint8_t *data, uint32_t len);

/* Function definitions ----------------------------------------------- */
//*****************************************************************************
//
// This is the main routine for handling updating over CAN.
//
// This function accepts boot loader commands over CAN to perform a firmware
// update over the CAN bus.  This function assumes that the CAN bus timing
// and message objects have been configured elsewhere.
//
// \return None.
//
//*****************************************************************************
void bl_can_run(canBASE_t *node)
{
  uint32_t data_len, msg_id;

  // This ensures proper alignment of the global buffer so that the one byte
  // size parameter used by the packetized format is easily skipped for data
  // transfers.
  g_pucCommandBuffer = ((uint8_t *)g_pulDataBuffer);

  // Insure that the COMMAND_SEND_DATA cannot be sent to erase the boot
  // loader before the application is erased.
  g_ulTransferAddress = 0xFFFFFFFF;

  while (1)
  {
    data_len = 0;
    msg_id = PacketRead(node, g_pucCommandBuffer, &data_len);

    switch (msg_id)
    {
    case CAN_ID_BL_APP_ERASE:
    {
      bl_can_handle_msg_app_erase(node, g_pucCommandBuffer, data_len);
      break;
    }

    case CAN_ID_BL_STOP:
    {
      bl_can_handle_msg_stop(node, g_pucCommandBuffer, data_len);
      break;
    }

    case CAN_ID_BL_CPU_RESET:
    {
      bl_can_handle_msg_cpu_reset(node, g_pucCommandBuffer, data_len);
      break;
    }

    case CAN_ID_BL_VER_REQ:
    {
      bl_can_handle_msg_version_request(node, g_pucCommandBuffer, data_len);
      break;
    }

    case CAN_ID_BL_MAP_REQ:
    {
      bl_can_handle_msg_get_memory_map(node, g_pucCommandBuffer, data_len);
      break;
    }

    // This is a start download packet. The address must be same as Application Start Address defined in bl_config.h
    // and same as address used in bootloader linker cmd file.
    case CAN_ID_BL_ADDR:
    {
      bl_can_handle_msg_set_start_address(node, g_pucCommandBuffer, data_len);
      break;
    }

    case CAN_ID_BL_DATA:
    {
      bl_can_handle_msg_write_data(node, g_pucCommandBuffer, data_len);
      break;
    }
    }
  }
}

//*****************************************************************************
//
// Generic configuration is handled in this function.
//
// This function is called by the start up code to perform any configuration
// necessary before calling the update routine.
//
// \return None.
//
//*****************************************************************************
void bl_can_init(canBASE_t *node)
{
  //
  // Init the CAN controller.
  //
  canInit();

  //
  // Configure the broadcast receive message object.
  //
  CANMessageSetRx(node);
}

/* Private function definitions ---------------------------------------- */
//*****************************************************************************
//
//! This function configures the message object used to receive commands.
//!
//! This function configures the message object used to receive all firmware
//! update messages.  This will not actually read the data from the message it
//! is used to prepare the message object to receive the data when it is sent.
//!
//! \return None.
//
//*****************************************************************************
static void CANMessageSetRx(canBASE_t *node)
{
  uint8_t usCmdReg;
  uint32_t usMaskReg;
  uint32_t usArbReg;
  uint32_t usMsgCtrl;

  //
  // Wait for busy bit to clear
  //
  while (node->IF1STAT & CAN_IFCMD_BUSY)
  {
  }

  //
  // This is always a write to the Message object as this call is setting a
  // message object.  This call will also always set all size bits so it sets
  // both data bits.  The call will use the CONTROL register to set control
  // bits so this bit needs to be set as well.
  //
  // Set the MASK bit so that this gets transferred to the Message Object.
  // Set the Arb bit so that this gets transferred to the Message object.
  //
  usCmdReg = (CAN_IFCMD_WRNRD | CAN_IFCMD_DATAA | CAN_IFCMD_DATAB |
              CAN_IFCMD_CONTROL | CAN_IFCMD_MASK | CAN_IFCMD_ARB);

  //
  // Set the UMASK bit to enable using the mask register.
  // Set the data length since this is set for all transfers.  This is also a
  // single transfer and not a FIFO transfer so set EOB bit.
  //
  usMsgCtrl = CAN_IFMCTL_UMASK | CAN_IFMCTL_EOB;

  //
  // Configure the Mask Registers.
  //
  usMaskReg = CAN_API_UPD << 18;

  // Configure the arbitration register
  usArbReg = ((CAN_API_UPD << 18) & CAN_IFARB_ID_M) | (CAN_IFARB_MSGVAL);

  //
  // Write out the registers to program the message object.
  //
  node->IF1CMD = usCmdReg;
  node->IF1MSK = usMaskReg;
  node->IF1ARB = usArbReg;
  node->IF1MCTL = usMsgCtrl;

  //
  // Transfer the message object to the message object specific by ID
  //
  node->IF1NO = (MSG_OBJ_BCAST_RX_ID & CAN_IFCMD_MNUM_M); // 1
}

//*****************************************************************************
//
//! This function reads data from the receive message object.
//!
//! \param pucData is a pointer to the buffer to store the data read from the
//! CAN controller.
//! \param pulMsgID is a pointer to the ID that was received with the data.
//!
//! This function will reads and acknowledges the data read from the message
//! object used to receive all CAN firmware update messages.  It will also
//! return the message identifier as this holds the API number that was
//! attached to the data.  This message identifier should be one of the
//! CAN_COMMAND_* definitions.
//!
//! \return The number of valid bytes returned in the \e pucData buffer or
//! 0xffffffff if data was overwritten in the buffer.
//
//*****************************************************************************
static uint32_t CANMessageGetRx(canBASE_t *node, uint8_t *pucData, uint32_t *pulMsgID)
{
  uint8_t usCmdReg;
  uint32_t usArbReg;
  uint32_t usMsgCtrl;
  uint32_t data_len;
  uint8_t *pusData;
  uint32_t i;

  //
  // This is always a read to the Message object as this call is setting a
  // message object.
  // Clear a pending interrupt and new data in a message object.
  //
  usCmdReg = (CAN_IFCMD_DATAA | CAN_IFCMD_DATAB |
              CAN_IFCMD_CONTROL | CAN_IFCMD_CLRINTPND |
              CAN_IFCMD_ARB);

  //
  // Set up the request for data from the message object.
  //
  node->IF1CMD = usCmdReg;

  //
  // Transfer the message object to the message object specific by
  // MSG_OBJ_BCAST_RX_ID.
  //
  node->IF1NO = (MSG_OBJ_BCAST_RX_ID & CAN_IFCMD_MNUM_M); // msg box 1

  //
  // Wait for busy bit to clear
  //
  while (node->IF1STAT & CAN_IFCMD_BUSY)
  {
  }

  //
  // Read out the IF Registers.
  //
  usArbReg = node->IF1ARB;
  usMsgCtrl = node->IF1MCTL;

  //
  // Set the 29 bit version of the Identifier for this message object.
  //
#if (__CONFIG_CAN_ID_29_BITS_ENABLE)
  *pulMsgID = (usArbReg & CAN_IFARB_29ID_M);
#else
  *pulMsgID = (usArbReg & CAN_IFARB_11ID_M) >> 18;
#endif // __CONFIG_CAN_ID_29_BITS_ENABLE

  //
  // See if there is new data available.
  //
  if ((usMsgCtrl & (CAN_IFMCTL_NEWDAT | CAN_IFMCTL_MSGLST)) == CAN_IFMCTL_NEWDAT)
  {
    //
    // Get the amount of data needed to be read.
    //
    data_len = (usMsgCtrl & CAN_IFMCTL_DLC_M);

    //
    // Read out the data from the CAN registers 16 bits at a time.
    //
    pusData = (uint8_t *)pucData;

    /** - Copy RX data into destination buffer */
    for (i = 0U; i < data_len; i++)
    {
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
      *pusData++ = node->IF1DATx[i];
#else
      *pusData++ = node->IF1DATx[g_ulCanByteOrder[i]];
#endif
    }

    //
    // Now clear out the new data flag.
    //
    node->IF1CMD = CAN_IFCMD_NEWDAT;

    //
    // Transfer the message object to the message object specific by
    // MSG_OBJ_BCAST_RX_ID.
    //
    node->IF1NO = MSG_OBJ_BCAST_RX_ID;

    //
    // Wait for busy bit to clear
    //
    while (node->IF1STAT & CAN_IFCMD_BUSY)
    {
    }
  }
  else
  {
    //
    // Data was lost so inform the caller.
    //
    data_len = 0xffffffff;
  }
  return (data_len);
}

//*****************************************************************************
//
//! This function sends data using the transmit message object.
//!
//! \param ulId is the ID to use with this message.
//! \param pucData is a pointer to the buffer with the data to be sent.
//! \param ulSize is the number of bytes to send and should not be more than
//! 8 bytes.
//!
//! This function will reads and acknowledges the data read from the message
//! object used to receive all CAN firmware update messages.  It will also
//! return the message identifier as this holds the API number that was
//! attached to the data.  This message identifier should be one of the
//! CAN_COMMAND_* definitions.
//!
//! \return None.
//
//*****************************************************************************
static void CANMessageSetTx(canBASE_t *node, uint32_t ulId, const uint8_t *pucData, uint32_t ulSize)
{
  uint8_t usCmdReg;
  uint32_t usArbReg, i;
  uint32_t usMsgCtrl;

  //
  // Wait for busy bit to clear
  //
  while (node->IF1STAT & CAN_IFCMD_BUSY)
  {
  }

  //
  // This is always a write to the Message object as this call is setting a
  // message object.  This call will also always set all size bits so it sets
  // both data bits.  The call will use the CONTROL register to set control
  // bits so this bit needs to be set as well.
  //
  usCmdReg = (CAN_IFCMD_WRNRD | CAN_IFCMD_DATAA | CAN_IFCMD_DATAB |
              CAN_IFCMD_CONTROL | CAN_IFCMD_ARB);

  //
  // Mark the message as valid and set the extended ID bit.
  //
#if (__CONFIG_CAN_ID_29_BITS_ENABLE)
  usArbReg = (ulId | (CAN_IFARB_DIR | CAN_IFARB_MSGVAL | CAN_IFARB_XTD));
#else
  usArbReg = (((ulId << 18) & CAN_IFARB_11ID_M) | (CAN_IFARB_DIR | CAN_IFARB_MSGVAL));
#endif // __CONFIG_CAN_ID_29_BITS_ENABLE

  //
  // Set the TXRQST bit and the reset the rest of the register.
  // Set the data length since this is set for all transfers.  This is also a
  // single transfer and not a FIFO transfer so set EOB bit.
  //
  //
  usMsgCtrl = (CAN_IFMCTL_TXRQST | CAN_IFMCTL_EOB | (ulSize & CAN_IFMCTL_DLC_M));

  //
  // Write the data out to the CAN Data registers if needed.
  //
  for (i = 0U; i < 8U; i++)
  {
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    node->IF1DATx[i] = *pucData++;
#else
    node->IF1DATx[g_ulCanByteOrder[i]] = *pucData++;
#endif
  }

  //
  // Write out the registers to program the message object.
  //
  node->IF1CMD = usCmdReg;
  node->IF1ARB = usArbReg;
  node->IF1MCTL = usMsgCtrl;

  //
  // Transfer the message object to the message object specifiec by
  // MSG_OBJ_BCAST_RX_ID.
  //
  node->IF1NO = (MSG_OBJ_BCAST_TX_ID) & (CAN_IFCMD_MNUM_M); // msg box 2
}

//*****************************************************************************
//
// Reads the next packet that is sent to the boot loader.
//
//*****************************************************************************
static uint32_t PacketRead(canBASE_t *node, uint8_t *pucData, uint32_t *pulSize)
{
  uint32_t ulMsgID;

  uint32_t messageBox = 1;

  uint32_t regIndex = (messageBox - 1U) >> 5U;
  uint32_t bitIndex = 1U << ((messageBox - 1U) & 0x1FU);

  //
  // Wait until a packet has been received.
  //
  while ((node->NWDATx[regIndex] & bitIndex) == 0)
  {
  }

  //
  // Read the packet.
  //
  *pulSize = CANMessageGetRx(node, pucData, &ulMsgID);

  //
  // Return the message ID of the packet that was received.
  //
  return (ulMsgID);
}

//*****************************************************************************
//
// Sends a packet to the controller that is communicating with the boot loader.
//
//*****************************************************************************
static void PacketWrite(canBASE_t *node, uint32_t ulId, const uint8_t *pucData, uint32_t ulSize)
{
  uint32_t ulIdx;

  uint32_t messageBox = 2;

  uint32_t regIndex = (messageBox - 1U) >> 5U;
  uint32_t bitIndex = 1U << ((messageBox - 1U) & 0x1FU);

  //
  // Wait until the previous packet has been sent, providing a time out so
  // that the boot loader does not hang here.
  //
  for (ulIdx = 1000; (ulIdx != 0) && ((node->TXRQx[regIndex] & bitIndex) != 0); ulIdx--)
  {
  }

  //
  // If the previous packet was sent, then send this packet.
  //
  if (ulIdx != 0)
  {
    CANMessageSetTx(node, ulId, pucData, ulSize);
  }
}

/* Bootloader CAN Bus handle message ------------------------------------ */
static void _32tobuf_msb(uint8_t *buf, uint32_t val)
{
  buf[3] = (uint8_t)val;
  val >>= 8;
  buf[2] = (uint8_t)val;
  val >>= 8;
  buf[1] = (uint8_t)val;
  val >>= 8;
  buf[0] = (uint8_t)val;
}

static void bl_can_handle_msg_get_memory_map(canBASE_t *node, uint8_t *data, uint32_t len)
{
  uint8_t mem_map_arm[8];

  _32tobuf_msb(&mem_map_arm[0], MEM_MAP_START_ADDR);
  _32tobuf_msb(&mem_map_arm[4], MEM_MAP_END_ADDR);

  PacketWrite(node, CAN_ID_BL_MAP_REQ_RSP_ARM, mem_map_arm, 8);
}

uint16_t crc16_incremental(uint16_t crc, uint8_t *data, uint32_t len)
{
  const unsigned char *d = (const unsigned char *)data;
  unsigned int tbl_idx;

  // Ensure that the length is not too long, else we'd try to read data that is not accessible.
  // This would lead to a memory access error / data abort.
  if (len > 0xA0000)
    return 0;

  while (len--)
  {
    tbl_idx = ((crc >> 8) ^ *d) & 0xff;
    crc = (crc16_table[tbl_idx] ^ (crc << 8)) & 0xffff;
    d++;
  }

  return crc & 0xffff;
}

uint16_t crc16(uint8_t *data, uint32_t len)
{
  return crc16_incremental(0, data, len);
}

static void bl_can_handle_msg_write_data(canBASE_t *node, uint8_t *data, uint32_t len)
{
  uint32_t return_check;
  uint8_t status;

  // Check if there are any more bytes to receive.
  if (g_ulTransferSize >= len)
  {
    // Initialize the Flash Wrapper registers
    return_check = Fapi_BlockProgram(bl_app_writer_addr, (uint32_t)&data[0], len);

    // Return an error if an access violation occurred.
    if (return_check)
    {
      // Indicate that the flash programming failed.
      status = CAN_CMD_FAIL;
      UART_putString(UART, "\r Program Flash failed:  ");
    }
    else
    {
      // Now update the address to program.
      g_ulTransferSize -= len;
      bl_app_writer_addr += len;
    }
  }
  else
  {
    // This indicates that too much data is being sent to the device.
    status = CAN_CMD_FAIL;
  }

  // See if the command was successful.
  if (status == CAN_CMD_SUCCESS)
  {
    if (start_send_data)
    {
      bl_checksum_calculated = crc16(data, len);
      start_send_data = false;
    }
    else
    {
      bl_checksum_calculated = crc16_incremental(bl_checksum_calculated, data, len);
    }

    PacketWrite(node, CAN_ID_BL_DATA_APOS, &status, 1);
  }
  else
  {
    PacketWrite(node, CAN_ID_BL_DATA_ANEG, &status, 1);
  }
}

static void bl_can_handle_msg_set_start_address(canBASE_t *node, uint8_t *data, uint32_t len)
{
  uint8_t status;

  // A simple do/while(0) control loop to make error exits easier.
  do
  {
    // See if a full packet was received.
   if (len != 5)
   {
     // Set the code to an error to indicate that the last
     // command failed.  This informs the updater program
     // that the download command failed.
     status = CAN_CMD_FAIL;

     // This packet has been handled.
     goto __LBL_BL_ADDR_END__;
   }

    // Get the address and size from the command. Where to swap the bytes?
    // The data is transferred most significant bit (MSB) first. This is used for RM48 which is little endian device
    g_ulTransferAddress = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3] << 0);
    g_pulUpdateSuccess[1] = g_ulTransferAddress;

    // Update writer address
    bl_app_writer_addr = g_ulTransferAddress;

    // Tell bootloader how many bytes the host will transfer for the whole application
    g_ulTransferSize = data[4];
  }
  while (0);

__LBL_BL_ADDR_END__:
  // See if the command was successful.
  if (status == CAN_CMD_SUCCESS)
  {
    PacketWrite(node, CAN_ID_BL_ADDR_APOS, &status, 1);
  }
  else
  {
    PacketWrite(node, CAN_ID_BL_ADDR_ANEG, &status, 1);

    // Setting g_ulTransferSize to zero makes COMMAND_SEND_DATA
    // fail to accept any data.
    g_ulTransferSize = 0;
  }
}

static void bl_can_handle_msg_version_request(canBASE_t *node, uint8_t *data, uint32_t len)
{
  uint8_t version_resp[4];

  // Prepare version response
  version_resp[0] = SOFTWARE_VERSION;
  version_resp[1] = PRODUCT_ID;
  version_resp[2] = HARDWARE_VERSION;
  version_resp[3] = BOOTLOADER_VERSION;

  // Send can message
  PacketWrite(node, CAN_ID_BL_VER_REQ_RSP, version_resp, 4);
}

static void bl_can_handle_msg_cpu_reset(canBASE_t *node, uint8_t *data, uint32_t len)
{
  uint8_t status;

  // Note: This command should handler int the application code

  start_send_data = true;
  bl_checksum_received = 0;

  // Perform a software reset request.  This will cause the
  // microcontroller to reset; no further code will be executed.
  // Use the reset function in the flash patch if appropriate.
  PacketWrite(node, CAN_ID_BL_CPU_RESET_APOS, &status, 1);

  // Perform a software reset request.  This will cause the
  // microcontroller to reset; no further code will be executed.
  // Use the reset in SYSECR register.
  // systemREG1->SYSECR = (0x10) << 14;

  // // The microcontroller should have reset, so this should never
  // // be reached.  Just in case, loop forever.
  // while (1)
  // {
  // }
}

static void bl_can_handle_msg_stop(canBASE_t *node, uint8_t *data, uint32_t len)
{
  uint8_t status;

  bl_checksum_received = (data[0] << 8) | data[1];

 if (bl_checksum_received == bl_checksum_calculated)
  {
    PacketWrite(node, CAN_ID_BL_STOP_APOS, &status, 1);
    g_ulTransferAddress = 0x00000000;

    Fapi_UpdateStatusProgram(g_ulUpdateStatusAddr, (uint32_t)&g_pulUpdateSuccess[0], g_ulUpdateBufferSize);
    UART_putString(UART, "\r Application was loaded successful!  ");

    // Branch to the specified address.  This should never return.
    // If it does, very bad things will likely happen since it is
    // likely that the copy of the boot loader in SRAM will have
    // been overwritten.

    ((void (*)(void))g_ulTransferAddress)();

    // In case this ever does return and the boot loader is still
    // intact, simply reset the device.
    // Use the reset in SYSECR register.
    systemREG1->SYSECR = (0x10) << 14;

    // The microcontroller should have reset, so this should
    // never be reached.  Just in case, loop forever.
    while (1)
    {
    }
  }
  else
  {
    PacketWrite(node, CAN_ID_BL_STOP_ANEG, &status, 1);
  }
}

static void bl_can_handle_msg_app_erase(canBASE_t *node, uint8_t *data, uint32_t len)
{
  uint32_t return_check;
  uint8_t status;

  // A simple do/while(0) control loop to make error exits easier.
 do
 {
   // See if a full packet was received.
   if (len != 8)
   {
     // Set the code to an error to indicate that the last
     // command failed.  This informs the updater program
     // that the download command failed.
     status = CAN_CMD_FAIL;

     // This packet has been handled.
     goto __LBL_BL_APP_ERASE_END__;
   }

   // Get the address from the command.
   // The data is transferred most significant bit (MSB) first. This is used for RM48 which is little endian device
   g_ulTransferAddress = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3] << 0);;

   // Tell bootloader how many bytes the host will transfer for the whole application
   g_ulTransferSize = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | (data[7] << 0);;

   return_check = Fapi_BlockErase(g_ulTransferAddress, g_ulTransferSize);

   // Return an error if an access violation occurred.
   if (return_check)
   {
     status = CAN_CMD_FAIL;
   }
 } while (0);

__LBL_BL_APP_ERASE_END__:
  // See if the command was successful.
  if (status == CAN_CMD_SUCCESS)
  {
    PacketWrite(node, CAN_ID_BL_APP_ERASE_APOS, &status, 1);
  }
  else
  {
    PacketWrite(node, CAN_ID_BL_APP_ERASE_ANEG, &status, 1);
  }
}

#endif // CAN_ENABLE_UPDATE

/* End of file -------------------------------------------------------- */
