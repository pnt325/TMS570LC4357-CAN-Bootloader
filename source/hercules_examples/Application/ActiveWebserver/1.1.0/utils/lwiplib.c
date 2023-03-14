/**
*  \file lwiplib.c
*
*  \brief lwip related initializations
*/
/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
*/

/*
** Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
** ALL RIGHTS RESERVED
*/

/*
** lwIP Compile Time Options for HDK.
*/
#include "lwiplib.h"
#if defined(_TMS570LC43x_) || defined(_RM57Lx_)
#include "HL_emac.h"
#else
#include "emac.h"
#endif

/*
** lwIP high-level API/Stack/IPV4/SNMP/Network Interface/PPP codes
*/
#include "api/api_lib.c"
#include "api/api_msg.c"
#include "api/err.c"
#include "api/netbuf.c"
#include "api/netdb.c"
#include "api/netifapi.c"
#include "api/tcpip.c"
#include "api/sockets.c"

#include "core/dhcp.c"
#include "core/dns.c"
#include "core/init.c"
#include "core/mem.c"
#include "core/memp.c"
#include "core/netif.c"
#include "core/pbuf.c"
#include "core/raw.c"
#include "core/stats.c"
#include "core/sys.c"
#include "core/tcp.c"
#include "core/tcp_in.c"
#include "core/tcp_out.c"
#include "core/timers.c"
#include "core/def.c"
#include "core/udp.c"

#include "core/ipv4/autoip.c"
#include "core/ipv4/icmp.c"
#include "core/ipv4/igmp.c"
#include "core/ipv4/inet.c"
#include "core/ipv4/inet_chksum.c"
#include "core/ipv4/ip.c"
#include "core/ipv4/ip_addr.c"
#include "core/ipv4/ip_frag.c"

#include "core/snmp/asn1_dec.c"
#include "core/snmp/asn1_enc.c"
#include "core/snmp/mib2.c"
#include "core/snmp/mib_structs.c"
#include "core/snmp/msg_in.c"
#include "core/snmp/msg_out.c"

#include "netif/etharp.c"
#include "netif/loopif.c"

#include "netif/ppp/auth.c"
#include "netif/ppp/chap.c"
#include "netif/ppp/chpms.c"
#include "netif/ppp/fsm.c"
#include "netif/ppp/ipcp.c"
#include "netif/ppp/lcp.c"
#include "netif/ppp/magic.c"
#include "netif/ppp/md5.c"
#include "netif/ppp/pap.c"
#include "netif/ppp/ppp.c"
#include "netif/ppp/ppp_oe.c"
#include "netif/ppp/randm.c"
#include "netif/ppp/vj.c"

/*
** HDK-specific lwIP interface/porting layer code.
*/
#include "ports/hdk/perf.c"
#include "ports/hdk/sys_arch.c"
#include "ports/hdk/netif/hdkif.c"


//*****************************************************************************
//
// The lwIP network interface structure for the Tiva Ethernet MAC.
//
//*****************************************************************************
static struct netif g_sNetIF;

 //*****************************************************************************
 //
 // The link detect polling interval.
 //
 //*****************************************************************************
 #define LINK_TMR_INTERVAL       10

//*****************************************************************************
//
// The local time for the lwIP Library Abstraction layer, used to support the
// Host and lwIP periodic callback functions.
//
//*****************************************************************************
#if NO_SYS
uint32_t g_ui32LocalTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the TCP timer was last serviced.
//
//*****************************************************************************
#if NO_SYS
static uint32_t g_ui32TCPTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the HOST timer was last serviced.
//
//*****************************************************************************
#if NO_SYS && HOST_TMR_INTERVAL
static uint32_t g_ui32HostTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the ARP timer was last serviced.
//
//*****************************************************************************
#if NO_SYS && LWIP_ARP
static uint32_t g_ui32ARPTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the AutoIP timer was last serviced.
//
//*****************************************************************************
#if NO_SYS && LWIP_AUTOIP
static uint32_t g_ui32AutoIPTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the DHCP Coarse timer was last serviced.
//
//*****************************************************************************
#if NO_SYS && LWIP_DHCP
static uint32_t g_ui32DHCPCoarseTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the DHCP Fine timer was last serviced.
//
//*****************************************************************************
#if NO_SYS && LWIP_DHCP
static uint32_t g_ui32DHCPFineTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the IP Reassembly timer was last serviced.
//
//*****************************************************************************
#if NO_SYS && IP_REASSEMBLY
static uint32_t g_ui32IPReassemblyTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the IGMP timer was last serviced.
//
//*****************************************************************************
#if NO_SYS && LWIP_IGMP
static uint32_t g_ui32IGMPTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the DNS timer was last serviced.
//
//*****************************************************************************
#if NO_SYS && LWIP_DNS
static uint32_t g_ui32DNSTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the link detect timer was last serviced.
//
//*****************************************************************************
#if NO_SYS && (LWIP_AUTOIP || LWIP_DHCP)
static uint32_t g_ui32LinkTimer = 0;
#endif

//*****************************************************************************
//
// The default IP address acquisition mode.
//
//*****************************************************************************
static uint32_t g_ui32IPMode = IPADDR_USE_STATIC;

//*****************************************************************************
//
// The most recently detected link state.
//
//*****************************************************************************
#if LWIP_AUTOIP || LWIP_DHCP
static bool g_bLinkActive = false;
#endif

//*****************************************************************************
//
// The IP address to be used.  This is used during the initialization of the
// stack and when the interface configuration is changed.
//
//*****************************************************************************
static uint32_t g_ui32IPAddr;

//*****************************************************************************
//
// The netmask to be used.  This is used during the initialization of the stack
// and when the interface configuration is changed.
//
//*****************************************************************************
static uint32_t g_ui32NetMask;

//*****************************************************************************
//
// The gateway address to be used.  This is used during the initialization of
// the stack and when the interface configuration is changed.
//
//*****************************************************************************
static uint32_t g_ui32GWAddr;

//*****************************************************************************
//
// The stack size for the interrupt task.
//
//*****************************************************************************
#if !NO_SYS
#define STACKSIZE_LWIPINTTASK   128
#endif

//*****************************************************************************
//
// The handle for the "queue" (semaphore) used to signal the interrupt task
// from the interrupt handler.
//
//*****************************************************************************
#if !NO_SYS
static xQueueHandle g_pInterrupt;
#endif


//*****************************************************************************

/******************************************************************************
**                       INTERNAL VARIABLE DEFINITIONS
******************************************************************************/
/*
** The lwIP network interface structure for the HDK Ethernet MAC.
*/
static struct netif hdkNetIF[MAX_EMAC_INSTANCE];

/******************************************************************************
**                          FUNCTION DEFINITIONS
******************************************************************************/
//*****************************************************************************
//
// This function performs a periodic check of the link status and responds
// appropriately if it has changed.
//
//*****************************************************************************
#if LWIP_AUTOIP || LWIP_DHCP
static void
lwIPLinkDetect(void)
{
    bool bHaveLink;
    struct ip_addr ip_addr;
    struct ip_addr net_mask;
    struct ip_addr gw_addr;

    //
    // See if there is an active link.
    //
    bHaveLink = lwIPLinkStatusGet(0);

    //
    // Return without doing anything else if the link state hasn't changed.
    //
    if(bHaveLink == g_bLinkActive)
    {
        return;
    }

    //
    // Save the new link state.
    //
    g_bLinkActive = bHaveLink;

    //
    // Clear any address information from the network interface.
    //
    ip_addr.addr = 0;
    net_mask.addr = 0;
    gw_addr.addr = 0;
    netif_set_addr(&g_sNetIF, &ip_addr, &net_mask, &gw_addr);

    //
    // See if there is a link now.
    //
    if(bHaveLink)
    {
        //
        // Start DHCP, if enabled.
        //
#if LWIP_DHCP
        if(g_ui32IPMode == IPADDR_USE_DHCP)
        {
            dhcp_start(&g_sNetIF);
        }
#endif

        //
        // Start AutoIP, if enabled and DHCP is not.
        //
#if LWIP_AUTOIP
        if(g_ui32IPMode == IPADDR_USE_AUTOIP)
        {
            autoip_start(&g_sNetIF);
        }
#endif
    }
    else
    {
        //
        // Stop DHCP, if enabled.
        //
#if LWIP_DHCP
        if(g_ui32IPMode == IPADDR_USE_DHCP)
        {
            dhcp_stop(&g_sNetIF);
        }
#endif

        //
        // Stop AutoIP, if enabled and DHCP is not.
        //
#if LWIP_AUTOIP
        if(g_ui32IPMode == IPADDR_USE_AUTOIP)
        {
            autoip_stop(&g_sNetIF);
        }
#endif
    }
}
#endif

/**
 *
 * \brief Initializes the lwIP TCP/IP stack.
 *
 * \param instNum  The instance index of the EMAC module
 * \param macArray Pointer to the MAC Address
 * \param ipAddr   The IP address to be used 
 * \param netMask  The network mask to be used 
 * \param gwAddr   The Gateway address to be used 
 * \param ipMode   The IP Address Mode.
 *        ipMode can take the following values\n
 *             IPADDR_USE_STATIC - force static IP addressing to be used \n
 *             IPADDR_USE_DHCP - force DHCP with fallback to Link Local \n
 *             IPADDR_USE_AUTOIP - force  Link Local only
 *
 * This function performs initialization of the lwIP TCP/IP stack for the
 * HDK EMAC, including DHCP and/or AutoIP, as configured.
 *
 * \return IP Address.
*/
 unsigned int lwIPInit(unsigned int instNum, unsigned char *macArray,
                       unsigned int ipAddr, unsigned int netMask,
                       unsigned int gwAddr, unsigned int ipMode)
 {
     struct ip_addr ip_addr;
     struct ip_addr net_mask;
     struct ip_addr gw_addr;
     volatile unsigned char *state;
     unsigned int *ipAddrPtr;
     volatile unsigned int cnt = 0x3FFFFFFF;

     lwip_init();

     /* Setup the network address values. */
     if(ipMode == IPADDR_USE_STATIC)
     {
         ip_addr.addr = htonl(ipAddr);
         net_mask.addr = htonl(netMask);
         gw_addr.addr = htonl(gwAddr);
     }

     else
     {
         ip_addr.addr = 0;
         net_mask.addr = 0;
         gw_addr.addr = 0;
     }

     hdkif_macaddrset(instNum, macArray);

     /*
     ** Create, configure and add the Ethernet controller interface with
     ** default settings.  ip_input should be used to send packets directly to
     ** the stack. The lwIP will internaly call the hdkif_init function.
     */
     if(NULL ==
        netif_add(&hdkNetIF[instNum], &ip_addr, &net_mask, &gw_addr, &instNum,
               hdkif_init, ip_input))
     {
         return 0;
     };

     netif_set_default(&hdkNetIF[instNum]);

     /* Start DHCP, if enabled. */
 #if LWIP_DHCP
 if(ipMode == IPADDR_USE_DHCP)
 {
 	unsigned int dhcp_flag = 0;
 	unsigned int dhcp_tries = 5;
 	unsigned int count;
 	unsigned int delay;
 	while(dhcp_tries--)
 	{


 	dhcp_start(&hdkNetIF[instNum]);
 	count = 10;
 	/* Check for DHCP completion for 'count' number of times, each for the given delay. */
 		while(count--)
 		{
 			delay = 0x8FFFFU;
 			while(delay--);
 			state = &(hdkNetIF[instNum].dhcp->state);
 			if(DHCP_BOUND == *state)
 			{
 				dhcp_flag = 1;
 			    ipAddrPtr = (unsigned int*)&(hdkNetIF[instNum].ip_addr);
 			    return (*ipAddrPtr);
 			}
 		}

 	}
 	/* In case of DHCP failure, return 0. */
 	if(dhcp_flag == 0)
 		return 0;
 }
 #endif

     /* Start AutoIP, if enabled and DHCP is not. */
 #if LWIP_AUTOIP
     if(ipMode == IPADDR_USE_AUTOIP)
     {
         autoip_start(&hdkNetIF[instNum]);
     }
 #endif

     if((ipMode == IPADDR_USE_STATIC)
     	       ||(ipMode == IPADDR_USE_AUTOIP))
     {
        /* Bring the interface up */
        netif_set_up(&hdkNetIF[instNum]);
     }

     ipAddrPtr = (unsigned int*)&(hdkNetIF[instNum].ip_addr);

     return (*ipAddrPtr);
 }

/*
 * \brief   Checks if the ethernet link is up
 *
 * \param   instNum  The instance number of EMAC module 
 *
 * \return  Interface status.
*/
unsigned int lwIPNetIfStatusGet(unsigned int instNum) 
{
    
    return (hdkif_netif_status(&hdkNetIF[instNum]));
}

/*
 * \brief   Checks if the ethernet link is up
 *
 * \param   instNum  The instance number of EMAC module 
 *
 * \return  The link status.
*/
unsigned int lwIPLinkStatusGet(unsigned int instNum) 
{
    return (hdkif_link_status(&hdkNetIF[instNum]));     
}

/**
 * \brief   Interrupt handler for Receive Interrupt. Directly calls the
 *          HDK interface receive interrupt handler.
 *
 * \param   instNum  The instance number of EMAC module for which receive 
 *                   interrupt happened
 *
 * \return  None.
*/
void lwIPRxIntHandler(unsigned int instNum) 
{
    hdkif_rx_inthandler(&hdkNetIF[instNum]);
}

/**
 * \brief   Interrupt handler for Transmit Interrupt. Directly calls the 
 *          HDK interface transmit interrupt handler.
 *
 * \param   instNum  The instance number of EMAC module for which transmit
 *                   interrupt happened
 *
 * \return  None.
*/
void lwIPTxIntHandler(unsigned int instNum)
{
    hdkif_tx_inthandler(&hdkNetIF[instNum]);
}

//*****************************************************************************
//
// This function services all of the lwIP periodic timers, including TCP and
// Host timers.  This should be called from the lwIP context, which may be
// the Ethernet interrupt (in the case of a non-RTOS system) or the lwIP
// thread, in the event that an RTOS is used.
//
//*****************************************************************************
#if NO_SYS
static void
lwIPServiceTimers(void)
{
    //
    // Service the host timer.
    //
#if HOST_TMR_INTERVAL
    if((g_ui32LocalTimer - g_ui32HostTimer) >= HOST_TMR_INTERVAL)
    {
        g_ui32HostTimer = g_ui32LocalTimer;
        lwIPHostTimerHandler();
    }
#endif

    //
    // Service the ARP timer.
    //
#if LWIP_ARP
    if((g_ui32LocalTimer - g_ui32ARPTimer) >= ARP_TMR_INTERVAL)
    {
        g_ui32ARPTimer = g_ui32LocalTimer;
        etharp_tmr();
    }
#endif

    //
    // Service the TCP timer.
    //
#if LWIP_TCP
    if((g_ui32LocalTimer - g_ui32TCPTimer) >= TCP_TMR_INTERVAL)
    {
        g_ui32TCPTimer = g_ui32LocalTimer;
        tcp_tmr();
    }
#endif

    //
    // Service the AutoIP timer.
    //
#if LWIP_AUTOIP
    if((g_ui32LocalTimer - g_ui32AutoIPTimer) >= AUTOIP_TMR_INTERVAL)
    {
        g_ui32AutoIPTimer = g_ui32LocalTimer;
        autoip_tmr();
    }
#endif

    //
    // Service the DCHP Coarse Timer.
    //
#if LWIP_DHCP
    if((g_ui32LocalTimer - g_ui32DHCPCoarseTimer) >= DHCP_COARSE_TIMER_MSECS)
    {
        g_ui32DHCPCoarseTimer = g_ui32LocalTimer;
        dhcp_coarse_tmr();
    }
#endif

    //
    // Service the DCHP Fine Timer.
    //
#if LWIP_DHCP
    if((g_ui32LocalTimer - g_ui32DHCPFineTimer) >= DHCP_FINE_TIMER_MSECS)
    {
        g_ui32DHCPFineTimer = g_ui32LocalTimer;
        dhcp_fine_tmr();
    }
#endif

    //
    // Service the IP Reassembly Timer
    //
#if IP_REASSEMBLY
    if((g_ui32LocalTimer - g_ui32IPReassemblyTimer) >= IP_TMR_INTERVAL)
    {
        g_ui32IPReassemblyTimer = g_ui32LocalTimer;
        ip_reass_tmr();
    }
#endif

    //
    // Service the IGMP Timer
    //
#if LWIP_IGMP
    if((g_ui32LocalTimer - g_ui32IGMPTimer) >= IGMP_TMR_INTERVAL)
    {
        g_ui32IGMPTimer = g_ui32LocalTimer;
        igmp_tmr();
    }
#endif

    //
    // Service the DNS Timer
    //
#if LWIP_DNS
    if((g_ui32LocalTimer - g_ui32DNSTimer) >= DNS_TMR_INTERVAL)
    {
        g_ui32DNSTimer = g_ui32LocalTimer;
        dns_tmr();
    }
#endif

    //
    // Service the link timer.
    //
#if LWIP_AUTOIP || LWIP_DHCP
    if((g_ui32LocalTimer - g_ui32LinkTimer) >= LINK_TMR_INTERVAL)
    {
        g_ui32LinkTimer = g_ui32LocalTimer;
        lwIPLinkDetect();
    }
#endif
}
#endif

//*****************************************************************************
//
//! Handles periodic timer events for the lwIP TCP/IP stack.
//!
//! \param ui32TimeMS is the incremental time for this periodic interrupt.
//!
//! This function will update the local timer by the value in \e ui32TimeMS.
//! If the system is configured for use without an RTOS, an Ethernet interrupt
//! will be triggered to allow the lwIP periodic timers to be serviced in the
//! Ethernet interrupt.
//!
//! \return None.
//
//*****************************************************************************
#if NO_SYS
void
lwIPTimer(void)
{
    //
    // Increment the lwIP Ethernet timer.
    //
    EMACTxIntPulseDisable(EMAC_0_BASE, EMAC_CTRL_0_BASE, 0, 0);
    EMACRxIntPulseDisable(EMAC_0_BASE, EMAC_CTRL_0_BASE, 0, 0);
    g_ui32LocalTimer += 10;
    lwIPServiceTimers();
    EMACTxIntPulseEnable(EMAC_0_BASE, EMAC_CTRL_0_BASE, 0, 0);
    EMACRxIntPulseEnable(EMAC_0_BASE, EMAC_CTRL_0_BASE, 0, 0);
}
#endif
/***************************** End Of File ***********************************/















