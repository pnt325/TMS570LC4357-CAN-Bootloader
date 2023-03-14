/** @file spi.c
*   @brief SPI Driver Implementation File
*   @date 15.Mar.2012
*   @version 03.01.00
*
*   (c) Texas Instruments 2009-2012, All rights reserved.
*/

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "spi.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @struct g_spiPacket
*   @brief globals
*
*/
struct g_spiPacket
{
    uint32_t  mode;
    uint32_t  length;
    uint16_t  *data;
} g_spiPacket[2];

/* SPI Data Format */
spiDAT1_t g_spiDataFormat;


/** @fn void spiInit(void)
*   @brief Initializes the SPI Driver
*
*   This function initializes the SPI module.
*/
void spiInit(void)
{
/* USER CODE BEGIN (2) */
    /** @b intalise @b SPI3 */

    /** bring SPI out of reset */
    spiREG3->GCR0 = 1U;

    /** SPI3 master mode and clock configuration */
    spiREG3->GCR1 = (1 << 1)  /* CLOKMOD */
                  | 1;  /* MASTER */

    /** SPI3 enable pin configuration */
    spiREG3->ENAHIGHZ = 0;  /* ENABLE HIGHZ */

    /** - Delays */
    spiREG3->DELAY = (1 << 24)  /* C2TDELAY */
                   | (0 << 16)  /* T2CDELAY */
                   | (0 << 8)  /* T2EDELAY */
                   | 0;  /* C2EDELAY */

    /** - Data Format 0 */
    spiREG3->FMT0 = (0 << 24)  /* wdelay */
                  | (0 << 23)  /* parity Polarity */
                  | (0 << 22)  /* parity enable */
                  | (0 << 21)  /* wait on enable */
                  | (0 << 20)  /* shift direction */
                  | (0 << 17)  /* clock polarity */
                  | (0 << 16)  /* clock phase */
                  | (39 << 8) /* baudrate prescale */
                  | 16;  /* data word length */

    /** - Data Format 1 */
    spiREG3->FMT1 = (0 << 24)  /* wdelay */
                  | (0 << 23)  /* parity Polarity */
                  | (0 << 22)  /* parity enable */
                  | (0 << 21)  /* wait on enable */
                  | (0 << 20)  /* shift direction */
                  | (0 << 17)  /* clock polarity */
                  | (0 << 16)  /* clock phase */
                  | (79 << 8) /* baudrate prescale */
                  | 16;  /* data word length */

    /** - Data Format 2 */
    spiREG3->FMT2 = (0 << 24)  /* wdelay */
                  | (0 << 23)  /* parity Polarity */
                  | (0 << 22)  /* parity enable */
                  | (0 << 21)  /* wait on enable */
                  | (0 << 20)  /* shift direction */
                  | (0 << 17)  /* clock polarity */
                  | (0 << 16)  /* clock phase */
                  | (79 << 8) /* baudrate prescale */
                  | 16;  /* data word length */

    /** - Data Format 3 */
    spiREG3->FMT3 = (0 << 24)  /* wdelay */
                  | (0 << 23)  /* parity Polarity */
                  | (0 << 22)  /* parity enable */
                  | (0 << 21)  /* wait on enable */
                  | (0 << 20)  /* shift direction */
                  | (0 << 17)  /* clock polarity */
                  | (0 << 16)  /* clock phase */
                  | (79 << 8) /* baudrate prescale */
                  | 16;  /* data word length */

    /** - set interrupt levels */
    spiREG3->LVL = (0 << 9)  /* TXINT */
                 | (0 << 8)  /* RXINT */
                 | (0 << 6)  /* OVRNINT */
                 | (0 << 4)  /* BITERR */
                 | (0 << 3)  /* DESYNC */
                 | (0 << 2)  /* PARERR */
                 | (0 << 1) /* TIMEOUT */
                 | (0);  /* DLENERR */

    /** - clear any pending interrupts */
    spiREG3->FLG = 0xFFFFU;

    /** - enable interrupts */
    spiREG3->INT0 = (0 << 9)  /* TXINT */
                  | (0 << 8)  /* RXINT */
                  | (0 << 6)  /* OVRNINT */
                  | (0 << 4)  /* BITERR */
                  | (0 << 3)  /* DESYNC */
                  | (0 << 2)  /* PARERR */
                  | (0 << 1) /* TIMEOUT */
                  | (0);  /* DLENERR */

    /** @b initialize @b SPI3 @b Port */

    /** - SPI3 Port output values */
    spiREG3->PCDOUT =  0        /* SCS[0] */
                    | (0 << 1)  /* SCS[1] */
                    | (0 << 8)  /* ENA */
                    | (0 << 9)  /* CLK */
                    | (0 << 10)  /* SIMO */
                    | (0 << 11); /* SOMI */

    /** - SPI3 Port direction */
    spiREG3->PCDIR  =  1        /* SCS[0] */
                    | (1 << 1)  /* SCS[1] */
                    | (0 << 8)  /* ENA */
                    | (1 << 9)  /* CLK */
                    | (1 << 10)  /* SIMO */
                    | (0 << 11); /* SOMI */

    /** - SPI3 Port open drain enable */
    spiREG3->PCPDR  =  0        /* SCS[0] */
                    | (0 << 1)  /* SCS[1] */
                    | (0 << 8)  /* ENA */
                    | (0 << 9)  /* CLK */
                    | (0 << 10)  /* SIMO */
                    | (0 << 11); /* SOMI */

    /** - SPI3 Port pullup / pulldown selection */
    spiREG3->PCPSL  =  1        /* SCS[0] */
                    | (1 << 1)  /* SCS[1] */
                    | (1 << 8)  /* ENA */
                    | (1 << 9)  /* CLK */
                    | (1 << 10)  /* SIMO */
                    | (1 << 11); /* SOMI */

    /** - SPI3 Port pullup / pulldown enable*/
    spiREG3->PCDIS  =  0        /* SCS[0] */
                    | (0 << 1)  /* SCS[1] */
                    | (0 << 8)  /* ENA */
                    | (0 << 9)  /* CLK */
                    | (0 << 10)  /* SIMO */
                    | (0 << 11); /* SOMI */

    /* SPI3 set all pins to functional */
    spiREG3->PCFUN  =  1        /* SCS[0] */
                    | (0 << 1)  /* SCS[1] */
                    | (0 << 8)  /* ENA */
                    | (1 << 9)  /* CLK */
                    | (1 << 10)  /* SIMO */
                    | (1 << 11); /* SOMI */

    /** - Finaly start SPI3 */
    spiREG3->ENA = 1U;

/* USER CODE END */
    /** @b intalise @b SPI2 */

    /** bring SPI out of reset */
    spiREG2->GCR0 = 1U;

    /** SPI2 master mode and clock configuration */
    spiREG2->GCR1 = (1 << 1)  /* CLOKMOD */
                  | 1;  /* MASTER */

    /** SPI2 enable pin configuration */
    spiREG2->ENAHIGHZ = 0;  /* ENABLE HIGHZ */

    /** - Delays */
    spiREG2->DELAY = (1 << 24)  /* C2TDELAY */
                   | (0 << 16)  /* T2CDELAY */
                   | (0 << 8)  /* T2EDELAY */
                   | 0;  /* C2EDELAY */

    /** - Data Format 0 */
    spiREG2->FMT0 = (0 << 24)  /* wdelay */
                  | (0 << 23)  /* parity Polarity */
                  | (0 << 22)  /* parity enable */
                  | (0 << 21)  /* wait on enable */
                  | (0 << 20)  /* shift direction */
                  | (0 << 17)  /* clock polarity */
                  | (0 << 16)  /* clock phase */
                  | (9 << 8) /* baudrate prescale */
                  | 16;  /* data word length */

    /** - Data Format 1 */
    spiREG2->FMT1 = (0 << 24)  /* wdelay */
                  | (0 << 23)  /* parity Polarity */
                  | (0 << 22)  /* parity enable */
                  | (0 << 21)  /* wait on enable */
                  | (0 << 20)  /* shift direction */
                  | (0 << 17)  /* clock polarity */
                  | (0 << 16)  /* clock phase */
                  | (79 << 8) /* baudrate prescale */
                  | 16;  /* data word length */

    /** - Data Format 2 */
    spiREG2->FMT2 = (0 << 24)  /* wdelay */
                  | (0 << 23)  /* parity Polarity */
                  | (0 << 22)  /* parity enable */
                  | (0 << 21)  /* wait on enable */
                  | (0 << 20)  /* shift direction */
                  | (0 << 17)  /* clock polarity */
                  | (0 << 16)  /* clock phase */
                  | (79 << 8) /* baudrate prescale */
                  | 16;  /* data word length */

    /** - Data Format 3 */
    spiREG2->FMT3 = (0 << 24)  /* wdelay */
                  | (0 << 23)  /* parity Polarity */
                  | (0 << 22)  /* parity enable */
                  | (0 << 21)  /* wait on enable */
                  | (0 << 20)  /* shift direction */
                  | (0 << 17)  /* clock polarity */
                  | (0 << 16)  /* clock phase */
                  | (79 << 8) /* baudrate prescale */
                  | 16;  /* data word length */

    /** - set interrupt levels */
    spiREG2->LVL = (0 << 9)  /* TXINT */
                 | (0 << 8)  /* RXINT */
                 | (0 << 6)  /* OVRNINT */
                 | (0 << 4)  /* BITERR */
                 | (0 << 3)  /* DESYNC */
                 | (0 << 2)  /* PARERR */
                 | (0 << 1) /* TIMEOUT */
                 | (0);  /* DLENERR */

    /** - clear any pending interrupts */
    spiREG2->FLG = 0xFFFFU;

    /** - enable interrupts */
    spiREG2->INT0 = (0 << 9)  /* TXINT */
                  | (0 << 8)  /* RXINT */
                  | (0 << 6)  /* OVRNINT */
                  | (0 << 4)  /* BITERR */
                  | (0 << 3)  /* DESYNC */
                  | (0 << 2)  /* PARERR */
                  | (0 << 1) /* TIMEOUT */
                  | (0);  /* DLENERR */

    /** @b initialize @b SPI2 @b Port */

    /** - SPI2 Port output values */
    spiREG2->PCDOUT =  0        /* SCS[0] */
                    | (0 << 1)  /* SCS[1] */
                    | (0 << 8)  /* ENA */
                    | (0 << 9)  /* CLK */
                    | (0 << 10)  /* SIMO */
                    | (0 << 11); /* SOMI */

    /** - SPI2 Port direction */
    spiREG2->PCDIR  =  1        /* SCS[0] */
                    | (1 << 1)  /* SCS[1] */
                    | (0 << 8)  /* ENA */
                    | (1 << 9)  /* CLK */
                    | (1 << 10)  /* SIMO */
                    | (0 << 11); /* SOMI */

    /** - SPI2 Port open drain enable */
    spiREG2->PCPDR  =  0        /* SCS[0] */
                    | (0 << 1)  /* SCS[1] */
                    | (0 << 8)  /* ENA */
                    | (0 << 9)  /* CLK */
                    | (0 << 10)  /* SIMO */
                    | (0 << 11); /* SOMI */

    /** - SPI2 Port pullup / pulldown selection */
    spiREG2->PCPSL  =  1        /* SCS[0] */
                    | (1 << 1)  /* SCS[1] */
                    | (1 << 8)  /* ENA */
                    | (1 << 9)  /* CLK */
                    | (1 << 10)  /* SIMO */
                    | (1 << 11); /* SOMI */

    /** - SPI2 Port pullup / pulldown enable*/
    spiREG2->PCDIS  =  0        /* SCS[0] */
                    | (0 << 1)  /* SCS[1] */
                    | (0 << 8)  /* ENA */
                    | (0 << 9)  /* CLK */
                    | (0 << 10)  /* SIMO */
                    | (0 << 11); /* SOMI */

    /* SPI2 set all pins to functional */
    spiREG2->PCFUN  =  1        /* SCS[0] */
                    | (0 << 1)  /* SCS[1] */
                    | (0 << 8)  /* ENA */
                    | (1 << 9)  /* CLK */
                    | (1 << 10)  /* SIMO */
                    | (1 << 11); /* SOMI */

    /** - Finaly start SPI2 */
    spiREG2->ENA = 1U;


}


/** @fn void spiSetFunctional(spiBASE_t *spi, uint32_t port)
*   @brief Change functional behaviour of pins at runtime.
*   @param[in] spi   - Spi module base address
*   @param[in] port  - Value to write to PCFUN register
*
*   Change the value of the PCFUN register at runtime, this allows to
*   dynaimcaly change the functionality of the SPI pins between functional
*   and GIO mode.
*/
void spiSetFunctional(spiBASE_t *spi, uint32_t port)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    spi->PCFUN = port;

/* USER CODE BEGIN (4) */
/* USER CODE END */
}


/** @fn uint32_t spiReceiveData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *destbuff)
*   @brief Receives Data using polling method
*   @param[in] spi   		- Spi module base address
*   @param[in] dataconfig_t	- Spi DAT1 register configuration
*   @param[in] blocksize	- number of data
*   @param[in] destbuff		- Pointer to the destination data (16 bit).
*
*   @return flag register value.
*
*   This function transmits blocksize number of data from source buffer using polling method.
*/
uint32_t spiReceiveData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *destbuff)
{
/* USER CODE BEGIN (5) */
/* USER CODE END */

    do
    {
        if(spi->FLG & 0x000000FF)
        {
          break;
        }
        spi->DAT1 = dataconfig_t->DFSEL   << 24 |
                    dataconfig_t->CSNR    << 16 |
                    dataconfig_t->WDEL    << 26 |
                    dataconfig_t->CS_HOLD << 28 |
                    0x0000;
       while((spi->FLG & 0x00000100) != 0x00000100)
       {
       }
       *destbuff++ = spi->BUF;
    }while(blocksize-- > 0);

/* USER CODE BEGIN (6) */
/* USER CODE END */

    return (spi->FLG & 0xFF);
}


/** @fn uint32_t spiGetData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *destbuff)
*   @brief Receives Data using interrupt method
*   @param[in] spi   		- Spi module base address
*   @param[in] dataconfig_t	- Spi DAT1 register configuration
*   @param[in] blocksize	- number of data
*   @param[in] destbuff		- Pointer to the destination data (16 bit).
*
*   @return flag register value.
*
*   This function transmits blocksize number of data from source buffer using interrupt method.
*/
void spiGetData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *destbuff)
{
     int index = spi == spiREG2 ? 0 : 1;

/* USER CODE BEGIN (7) */
/* USER CODE END */

     g_spiPacket[index].length = blocksize;
     g_spiPacket[index].data   = destbuff;

     spi->INT0 |= 0x0100;

     while(g_spiPacket[index].length-- > 0)
     {
       if(spi->FLG & 0x000000FF)
       {
          break;
       }
       spi->DAT1 = dataconfig_t->DFSEL   << 24 |
                   dataconfig_t->CSNR    << 16 |
                   dataconfig_t->WDEL    << 26 |
                   dataconfig_t->CS_HOLD << 28 |
                   0x0000;
     };
     spi->INT0 &= ~(0x0100);

/* USER CODE BEGIN (8) */
/* USER CODE END */
}


/** @fn uint32_t spiTransmitData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *srcbuff)
*   @brief Transmits Data using polling method
*   @param[in] spi   		- Spi module base address
*   @param[in] dataconfig_t	- Spi DAT1 register configuration
*   @param[in] blocksize	- number of data
*   @param[in] srcbuff		- Pointer to the source data ( 16 bit).
*
*   @return flag register value.
*
*   This function transmits blocksize number of data from source buffer using polling method.
*/
uint32_t spiTransmitData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *srcbuff)
{

    volatile uint32_t SpiBuf;

/* USER CODE BEGIN (9) */
/* USER CODE END */

    do
    {
       if(spi->FLG & 0x000000FF)
       {
          break;
       }
       spi->DAT1 = dataconfig_t->DFSEL   << 24 |
                   dataconfig_t->CSNR    << 16 |
                   dataconfig_t->WDEL    << 26 |
                   dataconfig_t->CS_HOLD << 28 |
                   *srcbuff++;
       while((spi->FLG & 0x00000100) != 0x00000100)
       {
       }
       SpiBuf = spi->BUF;
    
    }while(blocksize-- > 0);

/* USER CODE BEGIN (10) */
/* USER CODE END */

    return (spi->FLG & 0xFF);
}


/** @fn void spiSendData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *srcbuff)
*   @brief Transmits Data using interrupt method
*   @param[in] spi   		- Spi module base address
*   @param[in] dataconfig_t	- Spi DAT1 register configuration
*   @param[in] blocksize	- number of data
*   @param[in] srcbuff		- Pointer to the source data ( 16 bit).
*
*   @return flag register value.
*
*   This function transmits blocksize number of data from source buffer using interrupt method.
*/
void spiSendData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32_t blocksize, uint16_t *srcbuff)
{
     int index = spi == spiREG2 ? 0 : 1;

/* USER CODE BEGIN (11) */
/* USER CODE END */

     g_spiPacket[index].length = blocksize;
     g_spiPacket[index].data   = srcbuff;

     g_spiDataFormat = *dataconfig_t;

     spi->INT0 = 0x0200;

/* USER CODE BEGIN (12) */
/* USER CODE END */
}

/** @fn void spiEnableLoopback(spiBASE_t *spi, Loopbacktype_t Loopbacktype)
*   @brief Enable Loopback mode for self test
*   @param[in] spi        - spi module base address
*   @param[in] Loopbacktype  - Digital or Analog
*
*   This function enables the Loopback mode for self test.
*/

/** @fn void spiDisableLoopback(spiBASE_t *spi)
*   @brief Enable Loopback mode for self test
*   @param[in] spi        - spi module base address
*
*   This function disable the Loopback mode.
*/
void spiDisableLoopback(spiBASE_t *spi)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */
    
	/* Disable Loopback Mode */
    spi->IOLPKTSTCR = 0x000005000;
	
/* USER CODE BEGIN (16) */
/* USER CODE END */
}


/** @fn spiEnableNotification(spiBASE_t *spi, uint32_t flags)
*   @brief Enable interrupts
*   @param[in] spi   - spi module base address
*   @param[in] flags - Interrupts to be enabled, can be ored value of:
*/
void spiEnableNotification(spiBASE_t *spi, uint32_t flags)
{
/* USER CODE BEGIN (17) */
/* USER CODE END */

    spi->INT0 = flags;

/* USER CODE BEGIN (18) */
/* USER CODE END */
}

/** @fn spiDisableNotification(spiBASE_t *spi, uint32_t flags)
*   @brief Enable interrupts
*   @param[in] spi   - spi module base address
*   @param[in] flags - Interrupts to be enabled, can be ored value of:
*/
void spiDisableNotification(spiBASE_t *spi, uint32_t flags)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */

    spi->INT0 &= ~flags;

/* USER CODE BEGIN (20) */
/* USER CODE END */
}




