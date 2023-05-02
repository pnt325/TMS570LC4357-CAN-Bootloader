#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "stdint.h"
#include "uart.h"
#include "ihex.h"
#include "canid.h"
#include "vna.h"
#include "vna_232.h"
#include "can.h"
#include "net.h"



/* converts a msb first buf to unsigned 32 */
uint32_t
bufto32_msb( uint8_t *buf )
{
  uint32_t ret;

  ret = buf[0];
  ret <<= 8;
  ret |= buf[1];
  ret <<= 8;
  ret |= buf[2];
  ret <<= 8;
  ret |= buf[3];

  return ret;
}



void
_32tobuf_msb( uint8_t *buf, uint32_t val )
{
  buf[3] = (uint8_t) val;
  val >>= 8;
  buf[2] = (uint8_t) val;
  val >>= 8;
  buf[1] = (uint8_t) val;
  val >>= 8;
  buf[0] = (uint8_t) val;
}



int32_t
usage_check ( int32_t argc, int8_t *argv[] )
{
  uint8_t cnt;

  /* check to make sure the command line is ok */
  if( argc != 4 )
    return 1;

  if( strlen(argv[1]) > 2 )
    return 1;

  /* make sure port is all numbers */
  for( cnt = 0; cnt < strlen(argv[1]); cnt++ )
    if( (argv[1][cnt] < '0') || (argv[1][cnt] > '9') )
      return 1;

  return 0;
}



int32_t
usage ( int32_t argc, uint8_t *argv[], FILE **file_arm, FILE **file_c2k,
        uint8_t *cport )
{
  if( usage_check(argc,argv) != 0 ) { 

    printf("usage: flash232_CAN <port> <arm> <c2k>\n");
    printf("\n");
    printf("  ver. 1.0\n");
    printf("\n");
    printf("  port: comm port\n");
    printf("\n");
    printf("  arm: hex file for ARM CPU update\n");
    printf("\n");
    printf("  c2k: hex file for C2K CPU update\n");

    return 1;
  }

  /* get port */
  *cport = (uint8_t)strtol(argv[1], 0, 10);

  if( (*file_arm = fopen(argv[2], "rt")) == 0 ) {
  
    printf("error: unable to open %s\n", argv[2]);
    return 1;
  }
  if( (*file_c2k = fopen(argv[3], "rt")) == 0 ) {
  
    printf("error: unable to open %s\n", argv[2]);
    return 1;
  }

  return 0;
}



/*
** Setup the VNA for CAN operations on network 0.
*/
void
main_can_setup ( uint16_t rate )
{
  uint8_t buf[20];
  #if 0
  buf[0] = VNA_MSG_CAN_SET;
  buf[1] = 0;                     // port

  if( rate == 250 ) {
    buf[2] = CAN_250K_BRP;          // CAN BRP
    buf[3] = CAN_250K_PRSEG;        // CAN Propagation
    buf[4] = CAN_250K_SEG1PH;       // CAN TSEG1
    buf[5] = CAN_250K_SEG2PH;       // CAN TSEG2
  } else if( rate == 500 ) {
    buf[2] = CAN_500K_BRP;          // CAN BRP
    buf[3] = CAN_500K_PRSEG;        // CAN Propagation
    buf[4] = CAN_500K_SEG1PH;       // CAN TSEG1
    buf[5] = CAN_500K_SEG2PH;       // CAN TSEG2
  } else if( rate == 1000 ) {
    buf[2] = CAN_1000K_BRP;          // CAN BRP
    buf[3] = CAN_1000K_PRSEG;        // CAN Propagation
    buf[4] = CAN_1000K_SEG1PH;       // CAN TSEG1
    buf[5] = CAN_1000K_SEG2PH;       // CAN TSEG2
  }
  #else
  uint32_t type = NET_TYPE_RAW;
  uint32_t baud = rate * 1000;
  buf[0] = 29;
  buf[1] = 0;
  buf[2] = type >> 24;
  buf[3] = type >> 16;
  buf[4] = type >> 8;
  buf[5] = type;
  buf[6] = baud >> 24;
  buf[7] = baud >> 16;
  buf[8] = baud >> 8;
  buf[9] = baud;
  #endif

  vna_232_tx_msg(buf,10);
}



/*
** Transmit 29-bit CAN message.
*/
void
main_can_tx_ext ( uint32_t id, uint8_t *buf, uint8_t buf_len )
{
  uint8_t cnt;
  uint8_t msg[20];
  
  msg[0] = VNA_MSG_TX_CAN;
  msg[1] = 0;                    // port
  _32tobuf_msb( &msg[2], id );   // load id
  msg[2] |= 0x80;                // mark as 29-bit frame

  for( cnt = 0; cnt < buf_len; cnt++ )
    msg[6+cnt] = buf[cnt];

  vna_232_tx_msg(msg,(uint16_t)(6+buf_len));
}



uint8_t
main_can_rx_ext ( uint32_t *id, uint8_t *buf, uint8_t *buf_len )
{
  uint8_t cnt;
  uint8_t msg[20];
  uint16_t msg_len;

  if( (msg_len = vna_232_rx_msg(msg,(uint16_t)sizeof(msg))) >= 6 ) {

    /* check that it is an incoming extended can frame, max 8 bytes in it */
    if( (msg[0] == VNA_MSG_RX_CAN) && (msg[1] == 0) && (msg[2] & 0x80) && (msg_len <= 14) ) {

      msg[2] &= ~0x80; 
      *id = bufto32_msb(&msg[2]);
      *buf_len = (uint8_t) msg_len;
      
      for( cnt = 0; cnt < msg_len; cnt++ )
        buf[cnt] = msg[6+cnt];

      return 0; 
    }
    printf("rejected: %d\n",msg[0]);
  }

  return 1; 
}



/*
** Transmit request for version info. 
*/
uint8_t
main_tx_cpu_reset ( void )
{
  uint32_t id;
  uint16_t delay;
  uint8_t buf[20];
  uint8_t buf_len;

  /* send request for version */
  printf("info: tx reset cmd\n"); 
  main_can_tx_ext( CANID_BL_CPU_RESET, 0, 0 );

  /* wait up to 200 ms for response */
  for( delay = 0; delay < 200; delay++ ) {

    Sleep(1);
    if( main_can_rx_ext(&id,buf,&buf_len) == 0 ) {
      if( id == CANID_BL_CPU_RESET_APOS ) {
        return 0;
      }
    }
  }

  return 1;
}



/*
** Transmit request for version info. 
*/
uint8_t
main_tx_req_ver ( void )
{
  uint32_t id;
  uint16_t delay;
  uint8_t buf[20];
  uint8_t buf_len;

  /* send request for version */
  main_can_tx_ext( CANID_BL_VER_REQ, 0, 0 );

  /* wait up to 200 ms for response */
  for( delay = 0; delay < 200; delay++ ) {

    Sleep(1);
    if( main_can_rx_ext(&id,buf,&buf_len) == 0 ) {
      if( id == CANID_BL_VER_REQ_RSP ) {
        printf("info: software ver: %d\n", buf[0]);
        printf("      product id: %d\n", buf[1]);
        printf("      hardware ver: %d\n", buf[2]);
        printf("      bootloader ver: %d\n", buf[3]);
        return 0;
      }
    }
  }

  return 1;
}



/*
** Transmit erase application command.
*/
uint8_t
main_tx_app_erase ( void )
{
  uint32_t id;
  uint16_t delay;
  uint8_t buf[20];
  uint8_t buf_len;
  uint8_t tmp[8] = {11,13,88,55,3,211,177,249};

  /* send request for version */
  printf("info: tx erase app\n"); 
  main_can_tx_ext( CANID_BL_APP_ERASE, tmp, 8 );

  /* erase on 28035 can take up to 10 seconds per sector */
  for( delay = 0; delay < 2000; delay++ ) {

    Sleep(10);
    if( main_can_rx_ext(&id,buf,&buf_len) == 0 ) {
      if( id == CANID_BL_APP_ERASE_APOS ) {
        return 0;
      } else if( id == CANID_BL_APP_ERASE_ANEG ) {
        return 1;
      }
    }
  }

  return 1;
}



/*
** Transmit request for memory map.
*/
uint8_t
main_tx_req_map ( uint32_t *start_arm, uint32_t *end_arm,
                  uint32_t *start_c2k, uint32_t *end_c2k )
{
  uint32_t id;
  uint16_t delay;
  uint8_t buf[20];
  uint8_t buf_len;

  /* send request for version */
  main_can_tx_ext( CANID_BL_MAP_REQ, 0, 0 );

  /* wait up to 200 ms for response */
  for( delay = 0; delay < 200; delay++ ) {

    Sleep(1);
    if( main_can_rx_ext(&id,buf,&buf_len) == 0 ) {
      if( id == CANID_BL_MAP_REQ_RSP_ARM ) {
        *start_arm = bufto32_msb(&buf[0]);
        *end_arm = bufto32_msb(&buf[4]);
      } else if ( id == CANID_BL_MAP_REQ_RSP_C2K ) {
        *start_c2k = bufto32_msb(&buf[0]);
        *end_c2k = bufto32_msb(&buf[4]);
      }
    }
    if( *start_arm && *start_c2k ) {
      return 0;
    }
  }

  return 1;
}



/*
** Transmit address.
*/
uint8_t
main_tx_addr ( uint32_t addr, uint8_t len )
{
  uint32_t id;
  uint16_t delay;
  uint8_t buf[20];
  uint8_t buf_len;

  /* send request for version */
  _32tobuf_msb( &buf[0], addr );
  buf[4] = len;
  main_can_tx_ext( CANID_BL_ADDR, buf, 5 );

  /* wait up to 200 ms for response */
  for( delay = 0; delay < 200; delay++ ) {

    Sleep(1);
    if( main_can_rx_ext( &id, buf, &buf_len ) == 0 ) {
      if( id == CANID_BL_ADDR_APOS ) {
        return 0;
      }
    }
  }

  /* address failed */
  return 1;
}



/*
** Send data to ECU
** RETURN 0: success
**        1: fail
*/
uint8_t
main_tx_line ( uint32_t addr, uint8_t *buf, uint8_t buf_len )
{
  uint8_t i;
  uint8_t len;
  uint32_t id;
  uint16_t delay;

  if( main_tx_addr(addr,buf_len) )
    return 1;

  i = 0;
  while( buf_len ) {

    len = (buf_len > 8) ? 8 : buf_len;
    main_can_tx_ext( CANID_BL_DATA, &buf[i], len );
    i += len;
    buf_len -= len;
  }

  /* wait up to 200 ms for response */
  for( delay = 0; delay < 200; delay++ ) {

    Sleep(1);
    if( main_can_rx_ext(&id,buf,&buf_len) == 0 ) {
      if( id == CANID_BL_DATA_APOS ) {
        return 0;
      }
    }
  }

  /* fail */
  return 1;
}



/*
** Transmit stop command.
*/
uint8_t
main_tx_stop ( void )
{
  uint32_t id;
  uint16_t delay;
  uint16_t cksum;
  uint8_t buf[20];
  uint8_t buf_len;

  /* send request for version */
  cksum = ihex_cksum_calc();
  buf[0] = cksum >> 8;
  buf[1] = (uint8_t)cksum;
  main_can_tx_ext( CANID_BL_STOP, buf, 2 );

  /* wait up to 200 ms for response */
  for( delay = 0; delay < 200; delay++ ) {

    Sleep(1);
    if( main_can_rx_ext(&id,buf,&buf_len) == 0 ) {
      if( id == CANID_BL_STOP_APOS ) {
        return 0;
      }
    }
  }

  return 1;
}



void
main ( int argc, char *argv[] )
{
  uint8_t ret;
  uint8_t cport;
  uint32_t start_arm = 0,start_c2k = 0,end_arm = 0,end_c2k = 0;
  FILE *fp_arm = 0;
  FILE *fp_c2k = 0;

  /* assume failure */
  ret = 1;

  /* check the command line */
  if( usage(argc,argv,&fp_arm,&fp_c2k,&cport) )
    return;

  /* if setup fails, do nothing */
  if( uart_setup(cport,3) )
    return;

  /* wait for RS-232 transceiver to stabilize */
  Sleep(100);

  /* setup vna at 1Mbps */
  main_can_setup( 500 );

  /* command node to reset, to force bootloader to start */
  if( main_tx_cpu_reset() == 0 ) {
  
    /* wait for the reset to happen */
    Sleep(100);

    if( main_tx_req_ver() == 0 ) {

      if( main_tx_app_erase() == 0 ) {

        if( main_tx_req_map(&start_arm,&end_arm,&start_c2k,&end_c2k) == 0 ) {

           printf("info: sending file\n");
           if( (ihex_ftx(fp_arm,start_arm,end_arm) == 0) &&
               (ihex_ftx(fp_c2k,start_c2k,end_c2k) == 0) ) {

             if( (ret = main_tx_stop()) )
               printf("error: sending stop failed\n");

           } else {

             printf("error: sending file failed\n");
           }

        } else {
  
          printf("error: memory map request failed\n");
        }

      } else {
  
        printf("error: app erase failed\n");
      }

    } else {

      printf("error: version request failed\n");
    }

  } else {

    printf("error: reset cmd failed\n");
  }

  /* close file and uart */
  printf("info: exiting\n");
  fclose(fp_arm);
  fclose(fp_c2k);
  uart_close();

  /* did we fail? */
  if( ret ) {
    printf("FAILED\n");
    exit(-1);
  }

  printf("PASSED\n");
  exit(0);
}