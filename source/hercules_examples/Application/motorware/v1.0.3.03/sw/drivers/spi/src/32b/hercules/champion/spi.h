/** @file spi.h
*   @brief SPI Driver Definition File
*   @date 15.Mar.2012
*   @version 03.01.00
*   
*   (c) Texas Instruments 2009-2012, All rights reserved.
*/


#ifndef __SPI_H__
#define __SPI_H__

#include "sys_common.h"
#include "gio.h"

#ifndef BOOL
#define BOOL  uint32_t char
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/** @enum chipSelect
*   @brief Transfer Group Chip Select
*/
enum spiChipSelect
{
    SPI_CS_NONE = 0xFF,
    SPI_CS_0    = 0xFE,
    SPI_CS_1    = 0xFD,
    SPI_CS_2    = 0xFB,
    SPI_CS_3    = 0xF7,
    SPI_CS_4    = 0xEF,
    SPI_CS_5    = 0xDF,
    SPI_CS_6    = 0xBF,
    SPI_CS_7    = 0x7F
};

/** @enum spiPinSelect
*   @brief spi Pin Select
*/
enum spiPinSelect
{
    SPI_PIN_CS0    = 0,
    SPI_PIN_CS1    = 1,
    SPI_PIN_CS2    = 2,
    SPI_PIN_CS3    = 3,
    SPI_PIN_CS4    = 4,
    SPI_PIN_CS5    = 5,
    SPI_PIN_CS6    = 6,
    SPI_PIN_CS7    = 7,
    SPI_PIN_ENA    = 8,
    SPI_PIN_CLK    = 9,
    SPI_PIN_SIMO   = 10,
    SPI_PIN_SOMI   = 11,
    SPI_PIN_SIMO_1 = 17,
    SPI_PIN_SIMO_2 = 18,
    SPI_PIN_SIMO_3 = 19,
    SPI_PIN_SIMO_4 = 20,
    SPI_PIN_SIMO_5 = 21,
    SPI_PIN_SIMO_6 = 22,
    SPI_PIN_SIMO_7 = 23,
    SPI_PIN_SOMI_1 = 25,
    SPI_PIN_SOMI_2 = 26,
    SPI_PIN_SOMI_3 = 27,
    SPI_PIN_SOMI_4 = 28,
    SPI_PIN_SOMI_5 = 29,
    SPI_PIN_SOMI_6 = 30,
    SPI_PIN_SOMI_7 = 31
};

/** @enum dataformat
*   @brief SPI dataformat register select
*/
typedef enum dataformat
{
    SPI_FMT_0 = 0,
    SPI_FMT_1 = 1,
    SPI_FMT_2 = 2,
    SPI_FMT_3 = 3
}SPIDATAFMT;


/** @struct spiDAT1RegConfig
*   @brief SPI data register configuration
*/
typedef struct spiDAT1RegConfig
{
    uint32_t CS_HOLD;
    uint32_t WDEL;
    uint32_t DFSEL;
    uint32_t CSNR;
}spiDAT1_t;

/** @struct spiBase
*   @brief SPI Register Definition
*
*   This structure is used to access the SPI module egisters.
*/
/** @typedef spiBASE_t
*   @brief SPI Register Frame Type Definition
*
*   This type is used to access the SPI Registers.
*/
typedef volatile struct spiBase
{
    uint32_t  GCR0;                 /**< 0x0000: Global Control 0 */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t  GCR1          :  8U;  /**< 0x0007: Global Control 1 */
    uint32_t  PD            :  1U;  /**< 0x0006: Power down bit */
    uint32_t                :  7U;
    uint32_t  LB            :  1U;  /**< 0x0005: Loop back bit */
    uint32_t                :  7U;
    uint32_t  ENA           :  1U;  /**< 0x0004: SPI Enable bit */
    uint32_t                :  7U;  
    uint32_t  INT0          : 16U;  /**< 0x000A: Interrupt Enable bits */
    uint32_t  DMAREQEN      :  1U;  /**< 0x0009: DMA Request enable */
    uint32_t                :  7U;
    uint32_t  ENAHIGHZ      :  1U;  /**< 0x0008: Enable HIGHZ outputs */
    uint32_t                :  7U;
#else
    uint32_t                :  7U;  
    uint32_t  ENA           :  1U;  /**< 0x0004: SPI Enable bit */
    uint32_t                :  7U;
    uint32_t  LB            :  1U;  /**< 0x0005: Loop back bit */
    uint32_t                :  7U;
    uint32_t  PD            :  1U;  /**< 0x0006: Power down bit */
    uint32_t  GCR1          :  8U;  /**< 0x0007: Global Control 1 */
    uint32_t                :  7U;
    uint32_t  ENAHIGHZ      :  1U;  /**< 0x0008: Enable HIGHZ outputs */
    uint32_t                :  7U;
    uint32_t  DMAREQEN      :  1U;  /**< 0x0009: DMA Request enable */
    uint32_t  INT0          : 16U;  /**< 0x000A: Interrupt Enable bits */
#endif
    uint32_t  LVL;                  /**< 0x000C: Interrupt Level */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t  FLG           : 16U;  /**< 0x0012: Interrupt flags */
    uint32_t                :  8U;
    uint32_t  BUFINIT       :  1U;  /**< 0x0010: Buffer inialisation active flag */
    uint32_t                :  7U;
#else
    uint32_t                :  7U;
    uint32_t  BUFINIT       :  1U;  /**< 0x0010: Buffer inialisation active flag */
    uint32_t                :  8U;
    uint32_t  FLG           : 16U;  /**< 0x0012: Interrupt flags */
#endif
    uint32_t  PCFUN;                /**< 0x0014: Function Pin Enable */
    uint32_t  PCDIR;                /**< 0x0018: Pin Direction */
    uint32_t  PCDIN;                /**< 0x001C: Pin Input Latch */
    uint32_t  PCDOUT;               /**< 0x0020: Pin Output Latch */
    uint32_t  PCSET;                /**< 0x0024: Output Pin Set */
    uint32_t  PCCLR;                /**< 0x0028: Output Pin Clr */
    uint32_t  PCPDR;                /**< 0x002C: Open Drain Output Enable */
    uint32_t  PCDIS;                /**< 0x0030: Pullup/Pulldown Disable */
    uint32_t  PCPSL;                /**< 0x0034: Pullup/Pulldown Selection */
    uint32_t  DAT0;                 /**< 0x0038: Transmit Data */
    uint32_t  DAT1;                 /**< 0x003C: Transmit Data with Format and Chip Select */
    uint32_t  BUF;                  /**< 0x0040: Receive Buffer */
    uint32_t  EMU;                  /**< 0x0044: Emulation Receive Buffer */
    uint32_t  DELAY;                /**< 0x0048: Delays */
    uint32_t  CSDEF;                /**< 0x004C: Default Chip Select */
    uint32_t  FMT0;                 /**< 0x0050: Data Format 0 */
    uint32_t  FMT1;                 /**< 0x0054: Data Format 1 */
    uint32_t  FMT2;                 /**< 0x0058: Data Format 2 */
    uint32_t  FMT3;                 /**< 0x005C: Data Format 3 */
    uint32_t  INTVECT0;             /**< 0x0060: Interrupt Vector 0 */
    uint32_t  INTVECT1;             /**< 0x0064: Interrupt Vector 1 */
    uint32_t  SRSEL;                /**< 0x0068: Slew Rate Select */
    uint32_t  RESERVED[51U];        /**< 0x006C to 0x0130: Reserved */	
    uint32_t  IOLPKTSTCR;           /**< 0x0134: IO loopback */
} spiBASE_t;

/** @def spiREG2
*   @brief SPI2 Register Frame Pointer
*
*   This pointer is used by the SPI driver to access the spi module registers.
*/
#define spiREG2 ((spiBASE_t *)0xFFF7F600U)
#define spiREG3 ((spiBASE_t *)0xFFF7F800U)


/** @def spiPORT2
*   @brief SPI2 GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SPI2
*   (use the GIO drivers to access the port pins).
*/
#define spiPORT2 ((gioPORT_t *)0xFFF7F618U)
#define spiPORT3 ((gioPORT_t *)0xFFF7F818U)

/** @def spiREG4
*   @brief SPI4 Register Frame Pointer
*
*   This pointer is used by the SPI driver to access the spi module registers.
*/
#define spiREG4 ((spiBASE_t *)0xFFF7FA00U)


/** @def spiPORT4
*   @brief SPI4 GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of SPI4
*   (use the GIO drivers to access the port pins).
*/
#define spiPORT4 ((gioPORT_t *)0xFFF7FA18U)


/* SPI Interface Functions */
void spiInit(void);
void spiSetFunctional(spiBASE_t *spi, uint32_t port);
void spiEnableNotification(spiBASE_t *spi, uint32_t flags);
void spiDisableNotification(spiBASE_t *spi, uint32_t flags);
uint32_t spiTransmitData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *srcbuff);
void spiSendData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *srcbuff);
uint32_t spiReceiveData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *destbuff);
void spiGetData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *destbuff);
void spiDisableLoopback(spiBASE_t *spi);

/** @fn void spiNotification(spiBASE_t *spi, uint32_t flags)
*   @brief Interrupt callback
*   @param[in] spi   - Spi module base address
*   @param[in] flags - Copy of error interrupt flags
*
* This is a callback that is provided by the application and is called upon
* an interrupt.  The parameter passed to the callback is a copy of the 
* interrupt flag register.
*/
void spiNotification(spiBASE_t *spi, uint32_t flags);

#endif
