#include "HL_sys_common.h"
#include "tftp.h"
#include "bl_flash.h"
#include "bl_config.h"
#include "uartstdio.h"
#include <string.h>


static uint8_t image_buf[512]={0};
extern tBoolean last_packet;
extern tBoolean image_download;

extern uint32_t g_pulUpdateSuccess[8];
extern uint32_t g_ulUpdateStatusAddr;
extern uint32_t g_ulUpdateBufferSize;
uint32_t FlashDestination = APP_START_ADDRESS;
uint32_t erase_length = APPLICATION_IMAGE_SIZE;

extern void TFTPInit(tTFTPRequest pfnRequest);

//
//TFTP write Image into Flash
//
static tTFTPError
TFTP_WriteImage(tTFTPConnection *psTFTP)
{
	uint32_t oReturnCheck=0;

    memcpy(image_buf + psTFTP->ulDataRemaining, psTFTP->pucData, psTFTP->ulDataLength);

    if(last_packet)
    {
    	if((psTFTP->ulDataRemaining + psTFTP->ulDataLength) == TFTP_BLOCK_SIZE)
    	{
    		oReturnCheck = Fapi_BlockProgram(FlashDestination+(psTFTP->ulBlockNum - 1) * TFTP_BLOCK_SIZE,(uint32_t)(image_buf),TFTP_BLOCK_SIZE);
            // Return an error if an access violation occurred.
            if(oReturnCheck)
            {
                UARTprintf("\r Program Flash failed:  ");
            }else{
                UARTprintf("\r Block %d has been programmed!", psTFTP->ulBlockNum);
            }

    	}
    	else
    	{
            oReturnCheck = Fapi_BlockProgram(FlashDestination+(psTFTP->ulBlockNum - 1) * TFTP_BLOCK_SIZE, (uint32_t)(image_buf), (psTFTP->ulDataRemaining + psTFTP->ulDataLength) + 4 - (psTFTP->ulDataRemaining + psTFTP->ulDataLength)%4);
            if(oReturnCheck)
            {
                UARTprintf("\r Program Flash failed:  ");
            }
            g_pulUpdateSuccess[2] = (psTFTP->ulBlockNum - 1) * TFTP_BLOCK_SIZE + (psTFTP->ulDataRemaining + psTFTP->ulDataLength) + 4 - (psTFTP->ulDataRemaining + psTFTP->ulDataLength)%4;
            oReturnCheck = Fapi_UpdateStatusProgram(g_ulUpdateStatusAddr, (uint32_t)&g_pulUpdateSuccess[0], g_ulUpdateBufferSize);
            if(oReturnCheck)
            {
                UARTprintf("\r Program Flash failed:  ");
            }else{
                UARTprintf("\r Application was loaded successful!  ");
    	    	image_download=1;
            }
    	}
    	memset(image_buf,0xFF,512);
    	last_packet=0;
    }

    //
    // Did all go as planned?
    //

    if(!oReturnCheck)
    {
        //
        // Everything is fine.
        //
        return(TFTP_OK);
    }
    else
    {
        //
        // Oops - we can't erase the block.  Report an error.
        //
        psTFTP->pcErrorString = "Flash write failure.";
        return(TFTP_ERR_NOT_DEFINED);
    }
}

//*****************************************************************************
//
// Read a block of data from the Flash
//
//*****************************************************************************
static tTFTPError
TFTP_ReadImage(tTFTPConnection *psTFTP)
{
	//Didn't develop the read function
	return(TFTP_ERR_NOT_DEFINED);;
}


//*****************************************************************************
//
// Signals that the TFTP connection is being closed down.
//
//*****************************************************************************
static void
TFTP_Close(tTFTPConnection *psTFTP)
{
    //
    // Nothing to do here currently.
    //
}


//*****************************************************************************
//
// Checks incoming TFTP request to determine if we want to handle it.
//
// \param psTFTP points to the TFTP connection instance structure for this
// request.
// \param bGet is \b true of the request is a GET (read) or \b false if it is
// a PUT (write).
// \param pucFileName points to a NULL terminated string containing the
// requested filename.
// \param tTFTPMode indicates the requested transfer mode, ASCII or binary.
//
// This function is called by the TFTP server whenever a new request is
// received.  It checks the passed filename to determine whether it is valid.
// If the filename is valid, the function sets fields \e ulDataRemaining, \e
// pfnGetData and \e pfnClose in the \e psTFTP structure for a GET request or
// fields \e pfnPutData, \e pfnClosebefore returning
// \e TFTP_OK to continue processing the request.
//
// This implementation supports requests for "eeprom" which will read or write
// the image stored in the serial flash device and "extflash" which will
// access an image stored in the flash provided by the Flash/SRAM/LCD daughter
// board if this is installed.
//
// \return Returns \e TFTP_OK if the request should be processed or any other
// TFTP error code otherwise.  In cases where \e TFTP_OK is not returned, the
// field psTFTP->pcErrorString may be set with an ASCII error string which
// will be returned to the TFTP client.
//
//*****************************************************************************
static tTFTPError
TFTP_Request(tTFTPConnection *psTFTP, tBoolean bGet, char *pucFileName,
                tTFTPMode eMode)
{
    uint32_t oReturnCheck=0;
#ifdef MSG_DEBUG
    UARTprintf("TFTP Request to Erase Flash... \n\r");
#endif

    UARTprintf("Erasing flash ...... \n\r");
    oReturnCheck = Fapi_BlockErase(FlashDestination, erase_length);
    if(oReturnCheck)
    {
    	psTFTP->pcErrorString = "Flash erase failure.";
    	return(TFTP_ERR_NOT_DEFINED);
    }
    UARTprintf("Erase Done! \n\r");

    //
	// Set the appropriate callback functions depending upon the
	// type of request received.
	//
	psTFTP->pfnClose = TFTP_Close;

	//
	// Is this a GET or a PUT request?
	//
	if(bGet)
	{
		//
		// GET request - fill in the image size and the data transfer
		// function pointer.
		//
		psTFTP->pfnGetData = TFTP_ReadImage;
	}
	else
	{
		//
		// PUT request - fill in the data transfer function pointer.
		//
		psTFTP->pfnPutData = TFTP_WriteImage;
	}

    //
    // If we get here, all is well and the transfer can continue.
    //
    return(TFTP_OK);
}

//*****************************************************************************
//
// Initializes the TFTP server supporting the HDK board.
// \return None.
//
//*****************************************************************************
void TFTPQSInit(void)
{
    //
    // Initialize the TFTP module and pass it our board-specific GET and PUT
    // request handler function pointer.
    //
    TFTPInit(TFTP_Request);
}

