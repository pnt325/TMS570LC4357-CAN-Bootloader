#include <stdio.h>
#include "stdint.h"
#include "main.h"



uint32_t ihex_addr_start;
uint32_t ihex_addr_end;

#define IHEX_IMAGE_SIZE (1024UL*1024UL) 
uint16_t ihex_image[IHEX_IMAGE_SIZE];



void
ihex_cksum_store( uint32_t addr, uint8_t *buf, uint8_t buf_len ) {

  uint8_t cnt;

  for( cnt = 0; cnt < buf_len; cnt += 2, addr++ )
    if( (addr >= ihex_addr_start) && (addr <= ihex_addr_end) )
      ihex_image[addr-ihex_addr_start] = (buf[cnt] << 8) | buf[cnt+1];
}



uint16_t
ihex_cksum_calc( void ) {

  uint32_t cnt;
  uint32_t size;
  uint16_t accum;

  accum = 0;
  size = ihex_addr_end - ihex_addr_start;

  if (ihex_addr_end <= ihex_addr_start)
  {
    printf("The memory map receive is not correct. Size %d\n", size);
    printf("Checksum failed \n");
    return 0;
  }

  for( cnt = 0; cnt <= size; cnt++ )
    accum += ihex_image[cnt];

  return ((~accum)+1);
}



uint8_t
ascii2dec( int a ) {

  unsigned ret = 0;

  if( (a >= 'A') && (a <= 'F') ) {

    ret = a - 'A' + 10;

  } else if( (a >= 'a') && (a <= 'f') ) {

    ret = a - 'a' + 10;

  } else if( (a >= '0') && (a <= '9') ) {

    ret = a - '0';
  }

  return ret;
}



/*
** Reads in a hex file and sends it out over ISO 15765-4
** RETURN: 0 - success
**         1 - failure
*/
uint8_t
ihex_ftx( FILE *file, uint32_t start, uint32_t end )
{
  int tmp;
  uint32_t cnt;
  uint8_t buf[50];
  uint8_t rec_type;
  uint8_t byte_cnt;
  uint16_t load_addr;
  uint32_t base_addr;

  ihex_addr_start = start;
  ihex_addr_end = end;
  
  printf("started ihex\n");

  /* used by checksum routine, fill holes with 1s */
  for( cnt = 0; cnt < IHEX_IMAGE_SIZE; cnt++ )
    ihex_image[cnt] = 0xFFFF;

  /* assume a base address of zero */
  base_addr = 0;

  /* read character from file. if end of file, return ok. */
  while( (tmp = fgetc(file)) != EOF ) {
  
    /* if end of line read again */ 
    if( tmp == 10 )
      continue;

    /* if not ':' then error */
    if( tmp != ':' ) {
      printf("error: invalid start of line\n");
      return 1;
    }

    /* get number of bytes */
    byte_cnt = ascii2dec( fgetc(file) ) << 4;
    byte_cnt += ascii2dec( fgetc(file) );

    /* get load address */
    load_addr = ascii2dec( fgetc(file) ) << 12L;
    load_addr += ascii2dec( fgetc(file) ) << 8L;
    load_addr += ascii2dec( fgetc(file) ) << 4L;
    load_addr += ascii2dec( fgetc(file) ) << 0L;

    /* get record type */
    rec_type = ascii2dec( fgetc(file) ) << 4;
    rec_type += ascii2dec( fgetc(file) );

    /* get record */
    switch( rec_type ) {

      /* unhandled, just read the line and discard */
      case 2: 
      case 3: 
      case 5: 
      case 6: 
      case 7: 
      case 8: 
      case 9: 
        printf("error: unsupported record type\n");
        return 1;
        break;

      /* data record */
      case 0: {

        /* if not ':' then error */
        if( byte_cnt & 1 ) {
          printf("error: byte count must be even\n");
          return 1;
        }

        /* get data. there are twice the number of characters than bytes */
        for( cnt = 0; cnt < byte_cnt; cnt++ ) {

          buf[cnt] = ascii2dec( fgetc(file) ) << 4;
          buf[cnt] += ascii2dec( fgetc(file) );
        }

        /* discard checksum */
        fgetc(file);
        fgetc(file);

        ihex_cksum_store(base_addr+load_addr, buf, byte_cnt);

        /* if sending data fails, we stop the download */
        if( main_tx_line(base_addr+load_addr, buf, byte_cnt) )
          return 1;

        break;
      }

      /* end of file record */
      case 1: {
        return 0;
        break;
      }

      /* extended linear address record */
      case 4: {

        /* get address of data */
        base_addr = ascii2dec( fgetc(file) ) << 28L;
        base_addr += ascii2dec( fgetc(file) ) << 24L;
        base_addr += ascii2dec( fgetc(file) ) << 20L;
        base_addr += ascii2dec( fgetc(file) ) << 16L;

        /* discard checksum */
        fgetc(file);
        fgetc(file);

        break;
      }

      default: { 

        printf("error: invalid record\n");
        return 1;
      }
    }
  }

  return 0;
}
