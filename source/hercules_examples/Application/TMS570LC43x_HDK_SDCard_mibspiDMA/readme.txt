SD card using FAT file system on Hercules HDK

This example application demonstrates reading a file system from an SD card.  It makes use of FatFs, a FAT file system driver.  
It provides a simple command console via a serial port for issuing commands to view and navigate the file system on the SD card.

The first UART, which is connected to the USB debug virtual serial port on the HDK board, is configured for 19200 bits per second, 
and 8-N-1 mode. When the program is started a message will be printed to the terminal.  Type ``help'' for command help.

The main commands used for this demo are:
1. ls -- to list all the folders and files in the SD card
2. cat -- to show the content of a text file. For example: cat 123.txt
This demo doesn't provide SD Card write feature.

The MibSPI2 is used to interface SD card on HDK:
1. MibSPI2 SIMO  --- write data to SD card
2. MibSPI2 SOMI  --- read data from SD card
3. MibSPI2 CS0   --- chip select to enable SD Card: DESELECT() and SELECT() are to assert CS0 and deassert CS0
4. MibSPI2 ENA   --- SD card insertion detection


SIMO and SOMI are configured as SPI functionality, but CS0 and ENA are configured as GPIO through MibSPI PC0 register.
The initial SPI baudrate is 300KHz. The maximum speed for SD SPI mode is 400KHz. After the SD card is initialized, the 
SPI baudrate is switch to higher rate by calling set_max_speed(void). 

The default setting of set_max_speed(void) is 25MHz.

The MibSPI2 configuration: done using HALCoGen
1. MibSPI2: master, 
2. Data format 0: used for TG0, charlen=8, baudrate=300KHz; parity=0, and phase=0
3. Data format 1: used for TG1, charlen=8, baudrate=300KHz; parity=0, and phase=0
4. C2TDELAY and T2CDELAY: 52 VCLK clock cycles
5. TG0: CS0, DataFormat 0, BuffMode=4, Oneshot mode, length=1, and no trigger
6. TG1: CS0, DataFormat 1, BuffMode=4, Oneshot mode, length=127, and no trigger
7. TG2: CS0, DataFormat 1, BuffMode=4, Oneshot mode, length=1, and no trigger

Writing dummy data to SD card and reading data from SD card use TG1, but writing SD card commands and reading SD response
use TG0. The default TG1 length is 127 buffers, and it's configurable in the code. If different TG1 length is used, please
modify: "#define TG1_LENGTH   127" in sdc-hdk-hercules.c (line 56)

The MibSPI DMA read/write are performed in "rcvr_spi_dma (BYTE *dst, unsigned int spiPktLen)".

The RTI compare0 is used for timer used bt FatFs.

The SD card should be format to FAT32 first (from window), and txt file can be created using window tool (notepad,..).

The data buffer: g_pcTmpBuf[] and FS file structure: g_sFileObject are mapped to SDRAM.

The address of g_pcTmpBuf[] (starting at 0x80000000, SDRAM first location) is the destination address of the MibSPI RX DMA
trnasfer packet.

You can dump the data displayed on terminal and compare with the file content manually. or you can add a breakpoint at
line #612: if(iFResult != FR_OK) in sd_card.c file to check the conetnt of g_pcTmpBuf[].




 





 
