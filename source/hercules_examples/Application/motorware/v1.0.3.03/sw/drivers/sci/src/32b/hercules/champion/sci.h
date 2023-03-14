/** @file sci.h
*   @brief SCI Driver Definition File
*   @date 15.Mar.2012
*   @version 03.01.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */


#ifndef __SCI_H__
#define __SCI_H__

#include "sys_common.h"
#include "gio.h"


/** @enum sciIntFlags
*   @brief Interrupt Flag Definitions
*
*   Used with sciEnableNotification, sciDisableNotification
*/
enum sciIntFlags
{
    SCI_FE_INT    = 0x04000000,  /* framming error */
    SCI_OE_INT    = 0x02000000,  /* overrun error */
    SCI_PE_INT    = 0x01000000,  /* parity error */
    SCI_RX_INT    = 0x00000200,  /* receive buffer ready */
    SCI_TX_INT    = 0x00000100,  /* transmit buffer ready */
    SCI_WAKE_INT  = 0x00000002,  /* wakeup */
    SCI_BREAK_INT = 0x00000001   /* break detect */
};


/** @struct sciBase
*   @brief SCI Register Definition
*
*   This structure is used to access the SCI module egisters.
*/
/** @typedef sciBASE_t
*   @brief SCI Register Frame Type Definition
*
*   This type is used to access the SCI Registers.
*/

enum sciPinSelect
{
    PIN_SCI_TX = 0,
    PIN_SCI_RX = 1
};

/** @struct sciBase
*   @brief SCI Base Register Definition
*
*   This structure is used to access the SCI module egisters.
*/
/** @typedef sciBASE_t
*   @brief SCI Register Frame Type Definition
*
*   This type is used to access the SCI Registers.
*/
typedef volatile struct sciBase
{
    uint32_t GCR0;          /**< 0x0000 Global Control Register 0 */
    uint32_t GCR1;          /**< 0x0004 Global Control Register 1 */
    uint32_t GCR2;          /**< 0x0008 Global Control Register 2 */
    uint32_t SETINT;        /**< 0x000C Set Interrupt Enable Register */
    uint32_t CLRINT;        /**< 0x0010 Clear Interrupt Enable Register */
    uint32_t SETINTLVL;     /**< 0x0014 Set Interrupt Level Register */
    uint32_t CLRINTLVL;     /**< 0x0018 Set Interrupt Level Register */
    uint32_t FLR;           /**< 0x001C Interrupt Flag Register */
    uint32_t INTVECT0;      /**< 0x0020 Interrupt Vector Offset 0 */
    uint32_t INTVECT1;      /**< 0x0024 Interrupt Vector Offset 1 */
    uint32_t LENGTH;        /**< 0x0028 Format Control Register */
    uint32_t BAUD;          /**< 0x002C Baud Rate Selection Register */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint8_t ED;       /**< 0x0033 Emulation Register */
    uint32_t : 24U;
    uint8_t RD;       /**< 0x0037 Receive Data Buffer */
    uint32_t : 24U;
    uint8_t TD;       /**< 0x003B Transmit Data Buffer */
    uint32_t : 24U;  
#else
    uint32_t : 24U;
    uint8_t ED;       /**< 0x0033 Emulation Register */
    uint32_t : 24U;
    uint8_t RD;       /**< 0x0037 Receive Data Buffer */
    uint32_t : 24U;
    uint8_t TD;       /**< 0x003B Transmit Data Buffer */
#endif
    uint32_t FUN;           /**< 0x003C Pin Function Register */
    uint32_t DIR;           /**< 0x0040 Pin Direction Register */
    uint32_t DIN;           /**< 0x0044 Pin Data In Register */
    uint32_t DOUT;          /**< 0x0048 Pin Data Out Register */
    uint32_t SET;           /**< 0x004C Pin Data Set Register */
    uint32_t CLR;           /**< 0x0050 Pin Data Clr Register */
    uint32_t ODR;           /**< 0x0054: Pin Open Drain Output Enable Register */
    uint32_t PD;            /**< 0x0058: Pin Pullup/Pulldown Disable Register */
    uint32_t PSL;           /**< 0x005C: Pin Pullup/Pulldown Selection Register */
    uint32_t  : 32U;        /**< 0x060: Reserved                               */
    uint32_t  : 32U;        /**< 0x064: Reserved                               */
    uint32_t  : 32U;        /**< 0x068: Reserved                               */
    uint32_t  : 32U;        /**< 0x06C: Reserved                               */
    uint32_t  : 32U;        /**< 0x070: Reserved                               */
    uint32_t  : 32U;        /**< 0x074: Reserved                               */
    uint32_t  : 32U;        /**< 0x078: Reserved                               */
    uint32_t  : 32U;        /**< 0x07C: Reserved                               */
    uint32_t  : 32U;        /**< 0x080: Reserved                               */
    uint32_t  : 32U;        /**< 0x084: Reserved                               */
    uint32_t  : 32U;        /**< 0x088: Reserved                               */
    uint32_t  : 32U;        /**< 0x08C: Reserved                               */
    uint32_t IODFTCTRL;     /**< 0x0090: I/O Error Enable Register */
} sciBASE_t;


/** @def sciREG
*   @brief  Register Frame Pointer
*
*   This pointer is used by the SCI driver to access the sci module registers.
*/
#define sciREG ((sciBASE_t *)0xFFF7E500U)


/** @def sciPORT
*   @brief SCI GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SCI
*   (use the GIO drivers to access the port pins).
*/
#define sciPORT ((gioPORT_t *)0xFFF7E540U)


/** @def scilinREG
*   @brief SCILIN (LIN - Compatibility Mode)  Register Frame Pointer
*
*   This pointer is used by the SCI driver to access the sci module registers.
*/
#define scilinREG ((sciBASE_t *)0xFFF7E400U)


/** @def scilinPORT
*   @brief SCILIN (LIN - Compatibility Mode)  Register Frame Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of LIN
*   (use the GIO drivers to access the port pins).
*/
#define scilinPORT ((gioPORT_t *)0xFFF7E440U)


/* SCI Interface Functions */
void sciInit(void);
void sciSetFunctional(sciBASE_t *sci, uint32_t port);
void sciSetBaudrate(sciBASE_t *sci, uint32_t baud);
int  sciIsTxReady(sciBASE_t *sci);
void sciSendByte(sciBASE_t *sci, uint8_t byte);
void sciSend(sciBASE_t *sci, uint32_t length, uint8_t *data);
int  sciIsRxReady(sciBASE_t *sci);
int  sciRxError(sciBASE_t *sci);
int  sciReceiveByte(sciBASE_t *sci);
void sciReceive(sciBASE_t *sci, uint32_t length, uint8_t *data);
void sciEnableNotification(sciBASE_t *sci, uint32_t flags);
void sciDisableNotification(sciBASE_t *sci, uint32_t flags);


/** @fn void sciNotification(sciBASE_t *sci, uint32_t flags)
*   @brief Interrupt callback
*   @param[in] sci   - sci module base address
*   @param[in] flags - copy of error interrupt flags
*
* This is a callback that is provided by the application and is called apon
* an interrupt.  The parameter passed to the callback is a copy of the 
* interrupt flag register.
*/
void sciNotification(sciBASE_t *sci, uint32_t flags);

#endif
