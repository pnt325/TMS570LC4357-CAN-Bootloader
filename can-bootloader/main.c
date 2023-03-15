#include <string.h>
#include "bl_config.h"
#include "sci_common.h"
#include "bl_can.h"

#include "HL_het.h"
#include "HL_gio.h"
#include "HL_sci.h"
#include "HL_system.h"
#include "HL_sys_common.h"
#include "HL_sys_core.h"

#include "bl_check.h"
#include "bl_led_demo.h"
#include "flash.h"

/*****************************************************************************
 * bl_main
 ******************************************************************************/

/*****************************************************************************
 *
 * This holds the current remaining size in bytes to be downloaded.
 *
 ******************************************************************************/
uint32_t g_ulTransferSize;

/*****************************************************************************
 *
 * This holds the current address that is being written to during a download
 * command.
 *
 ******************************************************************************/
uint32_t g_ulTransferAddress;

/*****************************************************************************
 *
 * This is the data buffer used during transfers to the boot loader.
 *
 ******************************************************************************/
uint32_t g_pulDataBuffer[BUFFER_SIZE];

/*****************************************************************************
 *
 * This is the data buffer used for update status.
 *
 * g_pulUpdateSuccess[] are used to store application update status and application
 * image's version etc
 ******************************************************************************/

uint32_t g_pulUpdateSuccess[8] = {0x5A5A5A5A, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
uint32_t g_ulUpdateStatusAddr = APP_STATUS_ADDRESS;

uint32_t g_ulUpdateBufferSize = 32; /*16 bytes or 4 32-bit words*/

#define E_PASS 0
#define E_FAIL 0x1U
#define E_TIMEOUT 0x2U

/*****************************************************************************
 *
 * This is an specially aligned buffer pointer to g_pulDataBuffer to make
 * copying to the buffer simpler.  It must be offset to end on an address that
 * ends with 3.
 *
 ******************************************************************************/
uint8_t *g_pucDataBuffer;

extern unsigned int apiLoadStart;
extern unsigned int apiLoadSize;
extern unsigned int apiRunStart;

extern unsigned int constLoadStart;
extern unsigned int constLoadSize;
extern unsigned int constRunStart;

/*****************************************************************************
 *
 * This holds the current address that is being written to during a download
 * command.
 *
 ******************************************************************************/
void delay(unsigned int delayval)
{
	while (delayval--)
		;
}

static void flash_example(void);

// extern void _copyAPI2RAM_(unsigned int* r0, unsigned int* r1, unsigned int* r2);

void main(void)
{
	/* Initialize SCI Routines to receive Command and transmit data */
	sciInit();

	/* Copy the flash APIs to SRAM*/
	//_copyAPI2RAM_(&apiLoadStart, &apiRunStart, &apiLoadSize);
	memcpy(&apiRunStart, &apiLoadStart, (uint32)&apiLoadSize);

	/* Copy the .const section */
	//_copyAPI2RAM_(&constLoadStart, &constRunStart, &constLoadSize);
	memcpy(&constRunStart, &constLoadStart, (uint32)&constLoadSize);

	UART_putString(UART, "\r Hercules MCU CAN BootLoader ");

	flash_init();
	flash_example();

	while (1)
	{
	}
}

/******************************************************************************
 *
 * Configures the microcontroller.
 *
 * This function configures the peripherals and GPIOs of the microcontroller,
 * preparing it for use by the boot loader.  The interface that has been
 * selected as the update port will be configured, and auto-baud will be
 * performed if required.
 *
 * \return None.
 *
 ******************************************************************************/

static void flash_example(void)
{
	// Write some data to bank 2, sector 0, size = 128KB
	// flash address = 0x00200000
#define flash_start_addr 0x00200000
#define flash_size 0x00020000 /** 128KB */
	uint32_t ret;
	ret = flash_erase(flash_start_addr, flash_size);
	if (ret != 0)
	{
		UART_putString(UART, "Erase flash failure");
		return;
	}

	char wbuf[] = "Just write sample code to flash";
	int len = strlen(wbuf);
	char rbuf[128] = {};
	ret = flash_write(flash_start_addr, (uint32_t)wbuf, len);
	if (ret != 0)
	{
		UART_putString(UART, "Write data to flash failure");
		return;
	}

	memset(rbuf, 0, sizeof(rbuf));
	ret = flash_read(flash_start_addr, (uint32_t)rbuf, len);
	if (ret != 0)
	{
		UART_putString(UART, "Read data from flash failure");
		return;
	}

	/** Compare read and write data */
	if (memcmp(rbuf, wbuf, len) == 0)
	{
		UART_putString(UART, "Data read equal with write");
	}
	else
	{
		UART_putString(UART, "Data read not equal with write");
	}
}
