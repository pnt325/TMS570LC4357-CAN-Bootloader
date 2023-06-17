#include <stdio.h>
#include "stdint.h"
#include "main.h"
#include <stdbool.h>

uint32_t ihex_addr_start;
uint32_t ihex_addr_end;
uint32_t ihex_size;

#define IHEX_IMAGE_SIZE (1024UL * 1024UL)
uint8_t ihex_image[IHEX_IMAGE_SIZE];
static uint16_t ihex_checksum_calculated;

static const uint16_t crc16_table[] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

/* Private function prototypes ---------------------------------------- */
static uint16_t util_crc16_incremental(uint16_t crc, uint8_t *data, uint32_t len);
static uint16_t util_crc16(uint8_t *data, uint32_t len);
static uint8_t util_ascii2dec(int a);

/* Function definitions ----------------------------------------------- */
void ihex_cksum_calc(uint32_t addr, uint8_t *buf, uint8_t buf_len)
{
  static bool first_called = true;

  ihex_size = ihex_size + buf_len;

  if (first_called)
  {
    ihex_checksum_calculated = util_crc16(buf, buf_len);
    first_called = false;
  }
  else
  {
    ihex_checksum_calculated = util_crc16_incremental(ihex_checksum_calculated, buf, buf_len);
  }
}

uint16_t ihex_cksum_get(void)
{
  if (ihex_addr_end <= ihex_addr_start)
  {
    printf("The memory map receive is not correct. Size %d\n", ihex_size);
    printf("Checksum failed \n");
    return 0;
  }

  printf("Check sum: %d\n", ihex_checksum_calculated);
  printf("Hex size: %d\n", ihex_size);

  return ihex_checksum_calculated;
}

/*
** Reads in a hex file and sends it out over ISO 15765-4
** RETURN: 0 - success
**         1 - failure
*/
uint8_t ihex_ftx(FILE *file, uint32_t start, uint32_t end)
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
  for (cnt = 0; cnt < IHEX_IMAGE_SIZE; cnt++)
    ihex_image[cnt] = 0xFFFF;

  /* assume a base address of zero */
  base_addr = 0;

  /* read character from file. if end of file, return ok. */
  while ((tmp = fgetc(file)) != EOF)
  {
    /* if end of line read again */
    if (tmp == 10)
      continue;

    /* if not ':' then error */
    if (tmp != ':')
    {
      printf("error: invalid start of line\n");
      return 1;
    }

    /* get number of bytes */
    byte_cnt = util_ascii2dec(fgetc(file)) << 4;
    byte_cnt += util_ascii2dec(fgetc(file));

    /* get load address */
    load_addr = util_ascii2dec(fgetc(file)) << 12L;
    load_addr += util_ascii2dec(fgetc(file)) << 8L;
    load_addr += util_ascii2dec(fgetc(file)) << 4L;
    load_addr += util_ascii2dec(fgetc(file)) << 0L;

    /* get record type */
    rec_type = util_ascii2dec(fgetc(file)) << 4;
    rec_type += util_ascii2dec(fgetc(file));

    /* get record */
    switch (rec_type)
    {
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
    case 0:
    {
      /* if not ':' then error */
      if (byte_cnt & 1)
      {
        printf("error: byte count must be even\n");
        return 1;
      }

      /* get data. there are twice the number of characters than bytes */
      for (cnt = 0; cnt < byte_cnt; cnt++)
      {
        buf[cnt] = util_ascii2dec(fgetc(file)) << 4;
        buf[cnt] += util_ascii2dec(fgetc(file));
      }

      /* discard checksum */
      fgetc(file);
      fgetc(file);

      ihex_cksum_calc(base_addr + load_addr, buf, byte_cnt);

      /* if sending data fails, we stop the download */
      if (main_tx_line(base_addr + load_addr, buf, byte_cnt))
        return 1;

      break;
    }

    /* end of file record */
    case 1:
    {
      return 0;
      break;
    }

    /* extended linear address record */
    case 4:
    {
      /* get address of data */
      base_addr = util_ascii2dec(fgetc(file)) << 28L;
      base_addr += util_ascii2dec(fgetc(file)) << 24L;
      base_addr += util_ascii2dec(fgetc(file)) << 20L;
      base_addr += util_ascii2dec(fgetc(file)) << 16L;

      /* discard checksum */
      fgetc(file);
      fgetc(file);

      break;
    }

    default:
    {
      printf("error: invalid record\n");
      return 1;
    }
    }
  }

  return 0;
}

/* Private function definitions ---------------------------------------- */
static uint16_t util_crc16_incremental(uint16_t crc, uint8_t *data, uint32_t len)
{
  const unsigned char *d = (const unsigned char *)data;
  unsigned int tbl_idx;

  // Ensure that the length is not too long, else we'd try to read data that is not accessible.
  // This would lead to a memory access error / data abort.
  if (len > 0xA0000)
    return 0;

  while (len--)
  {
    tbl_idx = ((crc >> 8) ^ *d) & 0xff;
    crc = (crc16_table[tbl_idx] ^ (crc << 8)) & 0xffff;
    d++;
  }

  return crc & 0xffff;
}

static uint16_t util_crc16(uint8_t *data, uint32_t len)
{
  return util_crc16_incremental(0, data, len);
}

static uint8_t util_ascii2dec(int a)
{
  unsigned ret = 0;

  if ((a >= 'A') && (a <= 'F'))
  {
    ret = a - 'A' + 10;
  }
  else if ((a >= 'a') && (a <= 'f'))
  {
    ret = a - 'a' + 10;
  }
  else if ((a >= '0') && (a <= '9'))
  {
    ret = a - '0';
  }

  return ret;
}