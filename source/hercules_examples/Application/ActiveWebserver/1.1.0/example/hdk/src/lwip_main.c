/** @file sys_main.c 
*   @brief Application main file
*   @date 15.July.2009
*   @version 1.01.000
*
*   This file contains the initialization & control path for the LwIP & EMAC driver
*   and can be called from system main.
*/

/* (c) Texas Instruments 2011, All rights reserved. */

#if defined(_TMS570LC43x_) || defined(_RM57Lx_)
#include "HL_sys_common.h"
#include "HL_system.h"
#include "HL_emac.h"
#include "HL_mdio.h"
#include "HL_phy_dp83640.h"
#include "HL_sci.h"
#include "HL_rti.h"
#include <stdio.h>
#else
#include "rti.h"
#include "sys_common.h"
#include "system.h"
#include "emac.h"
#include "mdio.h"
#include "phy_dp83640.h"
#include "sci.h"
#endif

#include "lwip/opt.h"
#include "utils/lwiplib.h"
#include "httpserver_raw/httpd.h"
#include "lwip\inet.h"
#include "utils/locator.h"

#define TMS570_MDIO_BASE_ADDR 	0xFCF78900u /* Same base address for TMS570 & RM48 devices */
#define TMS570_EMAC_BASE_ADDR	0xFCF78000u /* Same base address for TMS570 & RM48 devices */
#define DPS83640_PHYID			0x20005CE1u	/** PHY ID Register 1 & 2 values for DPS83640 (Same for TMS570 & RM devices */
#define PHY_ADDR				1			/** EVM/Hardware dependent & is same for TMS570 & RM48 HDKs */
//*****************************************************************************
//
// SSI tag indices for each entry in the g_pcSSITags array.
//
//*****************************************************************************
#define SSI_INDEX_LEDSTATE  0
#define SSI_INDEX_FORMVARS  1
#define SSI_INDEX_SPEED     2

//*****************************************************************************
//
// This array holds all the strings that are to be recognized as SSI tag
// names by the HTTPD server.  The server will call SSIHandler to request a
// replacement string whenever the pattern <!--#tagname--> (where tagname
// appears in the following array) is found in ".ssi", ".shtml" or ".shtm"
// files that it serves.
//
//*****************************************************************************
static const char *g_pcConfigSSITags[] =
{
    "LEDtxt",        // SSI_INDEX_LEDSTATE
    "FormVars",      // SSI_INDEX_FORMVARS
    "speed"          // SSI_INDEX_SPEED
};

//*****************************************************************************
//
// The number of individual SSI tags that the HTTPD server can expect to
// find in our configuration pages.
//
//*****************************************************************************
#define NUM_CONFIG_SSI_TAGS     (sizeof(g_pcConfigSSITags) / sizeof (char *))

//*****************************************************************************
//
// Prototypes for the various CGI handler functions.
//
//*****************************************************************************
static char *ControlCGIHandler(int32_t iIndex, int32_t i32NumParams,
                               char *pcParam[], char *pcValue[]);
static char *SetTextCGIHandler(int32_t iIndex, int32_t i32NumParams,
                               char *pcParam[], char *pcValue[]);

//*****************************************************************************
//
// Prototype for the main handler used to process server-side-includes for the
// application's web-based configuration screens.
//
//*****************************************************************************
static int32_t SSIHandler(int32_t iIndex, char *pcInsert, int32_t iInsertLen);

//*****************************************************************************
//
// CGI URI indices for each entry in the g_psConfigCGIURIs array.
//
//*****************************************************************************
#define CGI_INDEX_CONTROL       0
#define CGI_INDEX_TEXT          1

//*****************************************************************************
//
// This array is passed to the HTTPD server to inform it of special URIs
// that are treated as common gateway interface (CGI) scripts.  Each URI name
// is defined along with a pointer to the function which is to be called to
// process it.
//
//*****************************************************************************
static const tCGI g_psConfigCGIURIs[] =
{
    { "/iocontrol.cgi", (tCGIHandler)ControlCGIHandler }, // CGI_INDEX_CONTROL
    { "/settxt.cgi", (tCGIHandler)SetTextCGIHandler }     // CGI_INDEX_TEXT
};

//*****************************************************************************
//
// The number of individual CGI URIs that are configured for this system.
//
//*****************************************************************************
#define NUM_CONFIG_CGI_URIS     (sizeof(g_psConfigCGIURIs) / sizeof(tCGI))

//*****************************************************************************
//
// The file sent back to the browser by default following completion of any
// of our CGI handlers.  Each individual handler returns the URI of the page
// to load in response to it being called.
//
//*****************************************************************************
#define DEFAULT_CGI_RESPONSE    "/io_cgi.ssi"

//*****************************************************************************
//
// The file sent back to the browser in cases where a parameter error is
// detected by one of the CGI handlers.  This should only happen if someone
// tries to access the CGI directly via the broswer command line and doesn't
// enter all the required parameters alongside the URI.
//
//*****************************************************************************
#define PARAM_ERROR_RESPONSE    "/perror.htm"

#define JAVASCRIPT_HEADER                                                     \
    "<script type='text/javascript' language='JavaScript'><!--\n"
#define JAVASCRIPT_FOOTER                                                     \
    "//--></script>\n"

/* Choosing the SCI module used depending upon the device HDK */
#if defined(_TMS570LC43x_) || defined(_RM57Lx_)
#define sciREGx	sciREG1
#else
#define sciREGx	scilinREG
#endif

uint8_t		txtCRLF[]			= {'\r', '\n'};
uint8_t  	txtTitle[] 			= {"HERCULES MICROCONTROLLERS"};
uint8_t		txtTI[]				= {"Texas Instruments"};
uint8_t		txtLittleEndian[] 	= {"Little Endian device"};
uint8_t		txtBigEndian[]		= {"Big Endian device"};
uint8_t		txtEnetInit[]		= {"Initializing ethernet (DHCP)"};
uint8_t		txtIPAddrTxt[]		= {"Device IP Address: "};
uint8_t		txtNote1[]			= {"Webserver accessible @ http:\\\\"};
uint8_t		txtErrorInit[]		= {"-------- ERROR INITIALIZING HARDWARE --------"};
uint8_t		 * txtIPAddrItoA;  


void 	iommUnlock			(void);
void 	iommLock			(void);
void 	iommMuxEnableMdio	(void);
void 	iommMuxEnableRmii	(void);
void 	iommMuxEnableMii	(void);
void 	IntMasterIRQEnable	(void);
void 	smallDelay			(void);
void 	sciDisplayText		(sciBASE_t *sci, uint8_t *text,uint32_t length);


//*****************************************************************************
//
// This CGI handler is called whenever the web browser requests iocontrol.cgi.
//
//*****************************************************************************
static char *
ControlCGIHandler(int32_t iIndex, int32_t i32NumParams, char *pcParam[],
                  char *pcValue[])
{
    int32_t i32LEDState, i32Speed;
    bool bParamError;

    //
    // We have not encountered any parameter errors yet.
    //
    bParamError = false;

    //
    // Get each of the expected parameters.
    //
    i32LEDState = FindCGIParameter("LEDOn", pcParam, i32NumParams);
    i32Speed = GetCGIParam("speed_percent", pcParam, pcValue, i32NumParams,
            &bParamError);

    //
    // Was there any error reported by the parameter parser?
    //
    if(bParamError || (i32Speed < 0) || (i32Speed > 100))
    {
        return(PARAM_ERROR_RESPONSE);
    }

    //
    // We got all the parameters and the values were within the expected ranges
    // so go ahead and make the changes.
    //
    io_set_led((i32LEDState == -1) ? false : true);
    io_set_animation_speed(i32Speed);

    //
    // Send back the default response page.
    //
    return(DEFAULT_CGI_RESPONSE);
}

//*****************************************************************************
//
// This CGI handler is called whenever the web browser requests settxt.cgi.
//
//*****************************************************************************
static char *
SetTextCGIHandler(int32_t i32Index, int32_t i32NumParams, char *pcParam[],
                  char *pcValue[])
{
    long lStringParam;
    char pcDecodedString[48];

    //
    // Find the parameter that has the string we need to display.
    //
    lStringParam = FindCGIParameter("DispText", pcParam, i32NumParams);

    //
    // If the parameter was not found, show the error page.
    //
    if(lStringParam == -1)
    {
        return(PARAM_ERROR_RESPONSE);
    }

    //
    // The parameter is present. We need to decode the text for display.
    //
    DecodeFormString(pcValue[lStringParam], pcDecodedString, 48);

    //
    // Print sting over the UART
    //

    sciDisplayText(sciREGx, pcDecodedString, strlen(pcDecodedString));
    sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));

    //
    // Tell the HTTPD server which file to send back to the client.
    //
    return(DEFAULT_CGI_RESPONSE);
}

//*****************************************************************************
//
// This function is called by the HTTP server whenever it encounters an SSI
// tag in a web page.  The iIndex parameter provides the index of the tag in
// the g_pcConfigSSITags array. This function writes the substitution text
// into the pcInsert array, writing no more than iInsertLen characters.
//
//*****************************************************************************
static int32_t
SSIHandler(int32_t iIndex, char *pcInsert, int32_t iInsertLen)
{
    //
    // Which SSI tag have we been passed?
    //
    switch(iIndex)
    {
        case SSI_INDEX_LEDSTATE:
            io_get_ledstate(pcInsert, iInsertLen);
            break;

        case SSI_INDEX_FORMVARS:
            sprintf(pcInsert,
                    "%sls=%d;\nsp=%d;\n%s",
                    JAVASCRIPT_HEADER,
                    io_is_led_on(),
                    io_get_animation_speed(),
                    JAVASCRIPT_FOOTER);
            break;

        case SSI_INDEX_SPEED:
            io_get_animation_speed_string(pcInsert, iInsertLen);
            break;

        default:
            sprintf(pcInsert,"??");
            break;
    }

    //
    // Tell the server how many characters our insert string contains.
    //
    return(strlen(pcInsert));
}

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void smallDelay(void) {
	  static volatile unsigned int delayval;
	  delayval = 10000;   // 100000 are about 10ms
	  while(delayval--);
}
/* USER CODE END */

void EMAC_LwIP_Main (uint8_t * macAddress)
{
    unsigned int 	ipAddr;
    uint8_t 		testChar;
    struct in_addr 	devIPAddress;

	//iommUnlock();
	//iommMuxEnableMdio();
	//iommMuxEnableMii();
	//iommLock();
	gioInit();
	rtiInit();
	sciInit();
#if defined(_TMS570LC43x_) || defined(_RM57Lx_)
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE0);
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE2);
#else
    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);
    rtiEnableNotification(rtiNOTIFICATION_COMPARE2);
#endif

	
	/* Enable the interrupt generation in CPSR register */
	IntMasterIRQEnable();
	_enable_FIQ();

	sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
	sciDisplayText(sciREGx, txtTitle, sizeof(txtTitle));
	sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
	sciDisplayText(sciREGx, txtTI, sizeof(txtTI));
	sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
#ifdef __little_endian__        
    sciDisplayText(sciREGx, txtLittleEndian, sizeof(txtLittleEndian));
    sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
#else        
    sciDisplayText(sciREGx, txtBigEndian, sizeof(txtBigEndian));
    sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
#endif

	/* Initialze the lwIP library, using DHCP.*/
	sciDisplayText(sciREGx, txtEnetInit, sizeof(txtEnetInit));
	ipAddr = lwIPInit(0, macAddress, 0, 0, 0, IPADDR_USE_DHCP);
	/* Uncomment the following if you'd like to assign a static IP address. Change address as required, and uncomment the previous statement. */
	/*
	uint8 ip_addr[4] = { 192, 168, 2, 44 };
	uint8 netmask[4] = { 255, 255, 255, 0 };
	uint8 gateway[4] = { 192, 168, 2, 254 };
	ipAddr = lwIPInit(0, macAddress,
			*((uint32_t *)ip_addr),
			*((uint32_t *)netmask),
			*((uint32_t *)gateway),
			IPADDR_USE_STATIC);*/
	sciDisplayText(sciREGx, (uint8_t*)"..DONE", sizeof("..DONE"));
	sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
	
	if (0 == ipAddr) {
		sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
		sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
        sciDisplayText(sciREGx, txtErrorInit, sizeof(txtErrorInit));
        sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
        sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
	} else {
		/* Convert IP Address to string */
		devIPAddress.s_addr = ipAddr;
		txtIPAddrItoA = (uint8_t *)inet_ntoa(devIPAddress);
	    LocatorInit();
	    LocatorMACAddrSet(macAddress);
	    LocatorAppTitleSet("Launchpad iocontrol");

	
		/* Initialize the sample httpd server. */
		sciDisplayText(sciREGx, (uint8_t*)"Starting Web Server", sizeof("Starting Web Server"));
	    httpd_init();
	    sciDisplayText(sciREGx, (uint8_t*)"..DONE", sizeof("..DONE"));
	    sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));

	    //
	    // Pass our tag information to the HTTP server.
	    //
	    http_set_ssi_handler((tSSIHandler)SSIHandler, g_pcConfigSSITags,
	            NUM_CONFIG_SSI_TAGS);

	    //
	    // Pass our CGI handlers to the HTTP server.
	    //
	    http_set_cgi_handlers(g_psConfigCGIURIs, NUM_CONFIG_CGI_URIS);
	     /* Loop forever.  All the work is done in interrupt handlers. */

	        sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
	        
	        sciDisplayText(sciREGx, txtTitle, sizeof(txtTitle));
	        sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
	        
	        sciDisplayText(sciREGx, txtTI, sizeof(txtTI));
	        sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
#ifdef __little_endian__        
	        sciDisplayText(sciREGx, txtLittleEndian, sizeof(txtLittleEndian));
	        sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
#else        
	        sciDisplayText(sciREGx, txtBigEndian, sizeof(txtBigEndian));
	        sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
#endif
			sciDisplayText(sciREGx, txtIPAddrTxt, sizeof(txtIPAddrTxt));
	        sciDisplayText(sciREGx, txtIPAddrItoA, 16);
			sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
			
			sciDisplayText(sciREGx, txtNote1, sizeof(txtNote1));
			sciDisplayText(sciREGx, txtIPAddrItoA, 16);
			sciDisplayText(sciREGx, txtCRLF, sizeof(txtCRLF));
			
	        
	        /* Before printing the next set, wait for a character on the terminal */
	        //sciReceive(sciREGx, 1, &testChar);
	}
	/* start rti for handling tcp servicing and the io animation*/
	rtiStartCounter(rtiREG1,rtiCOUNTER_BLOCK0);
	/* initialize io demo after webserver is up*/
	io_init();
    while(1);
}


void iommUnlock(void) {
	/*Unlock the IOMM Register*/
	*(int *) 0xFFFFEA38  = 0x83E70B13;  /* kicker 0 register, unlock CPU write access to PINMMR registers */
    *(int *) 0xFFFFEA3C  = 0x95A4F1E0;  /* kicker 1 register, */
}

void iommLock(void) {
	/*lock the IOMM Register*/
	*(int *) 0xFFFFEA38  = 0x00000000;  /* kicker 0 register, lock CPU write access to PINMMR registers */
    *(int *) 0xFFFFEA3C  = 0x00000000;  /* kicker 1 register, */
}

void iommMuxEnableMdio(void) {
	*(int *) 0xFFFFEB2C  = 0x00000400; 
	*(int *) 0xFFFFEB30  = 0x00000400; 
}

void iommMuxEnableRmii(void) {
	*(int *) 0xFFFFEB38  = 0x02010204;//P10  //RMIIRXER
	*(int *) 0xFFFFEB3C  = 0x08020101;//P11  //RMII_RXD0
	*(int *) 0xFFFFEB40  = 0x01010204;//P12  //RMII RXD1
	*(int *) 0xFFFFEB54  = 0x02040200;//P17  //RMII_RMCRSDV
	*(int *) 0xFFFFEB44  = 0x01080808;//P13  //RMII_TXEN , RMII_TX_D1 ,RMII_TX_D0
	*(int *) 0xFFFFEB48  = 0x01010401;//P14; //RMII_REFCLK
}

void iommMuxEnableMii(void) {
	*(int *) 0xFFFFEB38  &= 0xFFFFFF00; //P10[1]  //Mux 10 Rx_ER
	*(int *) 0xFFFFEB38  |= (1 << 1);   //P10[1]  //Mux 10 Rx_ER
	
	*(int *) 0xFFFFEB3C  &= 0x00FFFFFF; //P11[26]   //Mux 11 Rx[0]
	*(int *) 0xFFFFEB3C  |= (1 << 26);  //P11[26]   //Mux 11 Rx[0]

	*(int *) 0xFFFFEB40  &= 0x0000FF00;//P12[1,18,26]    //Mux 12 Rx[3],Rx[2],Rx[1]
	*(int *) 0xFFFFEB40  |= ((1<<26) | (1<<18) | (1<<1));//P12[1,18,26]    //Mux 12 Rx[3],Rx[2],Rx[1]

	*(int *) 0xFFFFEB44  &= 0x00000000;//P13[2, 10, 26,18]   //Mux 13 Tx[2],TxEn,Tx[1],Tx[0]
	*(int *) 0xFFFFEB44  |= ((1<<26)|(1<<18)|(1<<10)|(1<<2)); //P13[2, 10, 26,18]   //Mux 13 Tx[2],TxEn,Tx[1],Tx[0]

	*(int *) 0xFFFFEB48  &= 0xFFFF0000; //P14[9,2,11]   //Mux 14 Tx[3],RxClk
	*(int *) 0xFFFFEB48  |= ((1<<9)|(1<<2));    //P14[9,2]   //Mux 14 Tx[3],RxClk

	*(int *) 0xFFFFEB54  &= 0xFF00FF00      ;//P17[17,1,3]   //Mux 17 CRS,TxClk
	*(int *) 0xFFFFEB54  |= ((1<<17)|(1<<1));          //P17[17,1]   //Mux 17 CRS,TxClk

	*(int *) 0xFFFFEB5C  &= 0xFFFF00FF;  //P19[9]   //Mux 19 RxDV
	*(int *) 0xFFFFEB5C  |= (1<<9);      //P19[9]   //Mux 19 RxDV

	*(int *) 0xFFFFEB60  &= 0xFF00FFFF;  //P20[18]   //Mux 20 COL
	*(int *) 0xFFFFEB60  |= (1<<18);     //P20[18]   //Mux 20 COL

	*(int *) 0xFFFFEB84  &= 0x00FFFFFF;//P29[24]  //Mux 29 MII Select pin (24 bit - 0(MII),1(RMII))
	*(int *) 0xFFFFEB84  |= (0<<24);   //P29[24]  //Mux 29 MII Select pin (24 bit - 0(MII),1(RMII))
}


/*
** Interrupt Handler for Core 0 Receive interrupt
*/
volatile int countEMACCore0RxIsr = 0;
#pragma INTERRUPT(EMACCore0RxIsr, IRQ)
void EMACCore0RxIsr(void)
{
		countEMACCore0RxIsr++;
		lwIPRxIntHandler(0);
}

/*
** Interrupt Handler for Core 0 Transmit interrupt
*/
volatile int countEMACCore0TxIsr = 0;
#pragma INTERRUPT(EMACCore0TxIsr, IRQ)
void EMACCore0TxIsr(void)
{
	countEMACCore0TxIsr++;
    lwIPTxIntHandler(0);
}

void IntMasterIRQEnable(void)
{
	_enable_IRQ();
	return;
}

void IntMasterIRQDisable(void)
{
	_disable_IRQ();
	return;
}

unsigned int IntMasterStatusGet(void)
{
    return (0xC0 & _get_CPSR());
}

void sciDisplayText(sciBASE_t *sci, uint8_t *text,uint32_t length)
{
    while(length--)
    {
        while ((sci->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(sci,*text++);      /* send out text   */
    };
}

/* sci notification (Not used but must be provided) */
void sciNotification(sciBASE_t *sci, uint32_t flags)
{
	return;
}
