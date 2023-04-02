#include <stdio.h>
#include <windows.h>
#include <stdint.h>
#include "uart.h"



char port_name[20];
HANDLE hSerial;



/*
 * Close the current COM port connection 
 */
void
uart_close( void )
{
  CloseHandle(hSerial);
}



uint8_t
uart_setup( uint8_t cport, uint8_t rate )
{
  DCB dcb;
  COMMTIMEOUTS timeouts;

  /* create the COM port name from the int */
  sprintf(port_name, ((cport < 10) ? "COM%d" : "\\\\.\\COM%d"), cport);

  /* create a handle to connect to the port */
  hSerial = CreateFileA(port_name,
    GENERIC_READ | GENERIC_WRITE,
    0,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    NULL
  );

  /* check to see if handle is valid */
  if( hSerial == INVALID_HANDLE_VALUE ) {

    DWORD err = GetLastError ();

    printf ( "error: %d\n", err );

    if( err == ERROR_FILE_NOT_FOUND ) {
      printf("error: port %s was not found\n", port_name);
      return 1;
    }

    printf("error: unable to connect to port %s\n", port_name);
    return 1;
  }

  /* set port parameters (baud, etc) */
  dcb.DCBlength = sizeof(DCB);
  if ( !GetCommState(hSerial, &dcb) ) {
    printf("error: unable to retrieve DCB for port: %s\n", port_name);
    return 1;
  }

  switch( rate ) {
      case 1: dcb.BaudRate = CBR_9600; break;
      case 2: dcb.BaudRate = CBR_115200; break;
      case 3: dcb.BaudRate = 460800; break;
      case 4: dcb.BaudRate = 230400; break;
  }
  dcb.fBinary = TRUE;
  dcb.fParity = FALSE;
  dcb.fAbortOnError = FALSE;
  dcb.fNull = FALSE;
  /* disable XON/XOFF flow control */
  dcb.fOutX = FALSE;

  dcb.ByteSize = 8;
  dcb.StopBits = ONESTOPBIT;
  dcb.Parity = NOPARITY;

  /* write DCB changes back to connection */
  if( !SetCommState(hSerial, &dcb) ) {
    printf("error: unable to write DCB changes for port: %s\n", port_name);
    return 1;
  }

  /* assign the timeout values for the port */
  timeouts.ReadIntervalTimeout = 50;
  timeouts.ReadTotalTimeoutConstant = 50;
  timeouts.ReadTotalTimeoutMultiplier = 10;
  timeouts.WriteTotalTimeoutConstant = 50;
  timeouts.WriteTotalTimeoutMultiplier = 10;

  if( !SetCommTimeouts(hSerial, &timeouts) ) {
    printf("error: unable to set timeout values for port: %s\n", port_name);
    return 1;
  }
  PurgeComm(hSerial, PURGE_TXCLEAR | PURGE_RXCLEAR);

  /* success */
  return 0;
}



/*
** Application code uses this to receive a byte
** RETURN: 0 - success
**         1 - failed
*/
uint8_t
uart_rx( uint8_t *val )
{
  DWORD bytesRead = 0;
  if( !ReadFile(hSerial, val, 1, &bytesRead, NULL) )
  {
    return 1;
  }
  if(bytesRead <= 0) {
    return 1;
  }

  return 0;
}



/*
** Application code uses this to receive multiple bytes
** RETURN: 0 - success
**         1 - failed
*/
uint32_t
uart_rx_bytes( uint8_t *val, int max_bytes )
{
  DWORD bytesRead = 0;
  if( !ReadFile(hSerial, val, max_bytes, &bytesRead, NULL) )
  {
    return 0;
  }
  if(bytesRead <= 0) {
    return 0;
  }

  return bytesRead;
}



/* 
** Application code uses this to transmit a byte
** RETURN: 0 - success
**         1 - failed
*/
uint8_t
uart_tx( uint8_t val )
{
  uint8_t cnt = 0;
  DWORD bytesWritten = 0;
  /* tx character, wait for up to 1 second */
  printf("%x ", val);
  while( !WriteFile(hSerial, &val, 1, &bytesWritten, NULL) && bytesWritten <= 0 )
  {
    Sleep(5);
    cnt++;
    if( cnt > 200 ) {
      printf("error: rs-232 adapter failure\n");
      uart_close();
      exit(1);
    }
  }

  return 0;
}


uint8_t
uart_tx_bytes ( uint8_t *buf, uint16_t len )
{
  uint8_t cnt = 0;
  DWORD bytesWritten = 0;

  WriteFile ( hSerial, buf, len, &bytesWritten, NULL );

  return 0;
}
