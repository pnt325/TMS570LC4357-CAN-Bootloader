#include <stdio.h>
#include "stdint.h"
#include "main.h"
#include "vna.h"
#include "vna_232.h"
#include "uart.h"

/* SLIP byte stuffing */
#define VNA_BS_FLAG           0xC0
#define VNA_BS_ESCAPE         0xDB
#define VNA_BS_ESCAPE_FLAG    0xDC
#define VNA_BS_ESCAPE_ESCAPE  0xDD

/*
** Calculates and returns 2's complement checksum.
*/
uint8_t vna_232_cksum(uint8_t *buf, uint16_t size)
{
  uint8_t ret = 0;

  /* checksum data */
  while (size--)
    ret += buf[size];

  return ((~ret) + 1);
}

/*
** Byte stuff the stream.
*/
uint16_t vna_232_bs(uint8_t *dst, uint8_t *src, uint16_t buf_len)
{
  uint16_t cnt;
  uint8_t *prev = dst;

  /* byte stuff stream */
  for (cnt = 0; cnt < buf_len; cnt++, src++)
  {
    /* 0xC0 is sent as 0xDB, 0xDC
       0xDB is sent as 0xDB, 0xDD */
    if (*src == VNA_BS_FLAG)
    {
      *dst++ = VNA_BS_ESCAPE;
      *dst++ = VNA_BS_ESCAPE_FLAG;
    }
    else if (*src == VNA_BS_ESCAPE)
    {
      *dst++ = VNA_BS_ESCAPE;
      *dst++ = VNA_BS_ESCAPE_ESCAPE;
    }
    else
    {
      *dst++ = *src;
    }
  }

  return (dst - prev);
}

/*
** Transmits a RS-232 message.  This function sends the start of message byte,
** adds the 2-byte length field and checksum to the message.  It then byte
** stuffs the length field, data, and checksum and transmits it.
*/
void vna_232_tx_msg(uint8_t *buf, uint16_t buf_len)
{
  uint16_t cnt;
  uint8_t msg[1000];
  uint8_t msg_bs[2000];

  /* is the msg larger than our example supports? */
  if (buf_len >= 2000)
    return;

  /* start of message (raw - unstuffed) */
  msg_bs[0] = VNA_BS_FLAG;

  /* stuff msg length, adding a byte for chksum */
  msg[0] = (uint8_t)((buf_len + 1) >> 8);
  msg[1] = (uint8_t)(buf_len + 1);

  /* copy over message */
  for (cnt = 0; cnt < buf_len; cnt++)
    msg[2 + cnt] = buf[cnt];

  /* checksum and place at end of message */
  msg[2 + buf_len] = vna_232_cksum(msg, (uint16_t)(buf_len + 2));

  /* byte stuff */
  buf_len = vna_232_bs(&msg_bs[1], msg, (uint16_t)(buf_len + 3));

  /* transmit message */
  for (cnt = 0; cnt < (buf_len + 1); cnt++)
    uart_tx(msg_bs[cnt]);
}

/*
** Receives a message, unstuffing the data, and validating the checksum.
** All completed messages are returned in msg.
** INPUT:  msg - pointer to buffer for new message
** OUTPUT: size of message
*/
uint16_t vna_232_rx_msg(uint8_t *msg, uint16_t msg_size)
{
  uint8_t val;
  uint16_t cnt;
  static uint16_t i = 0;
  static uint16_t r232_len = 0;
  static uint16_t buf_len = 0;
  static uint16_t msg_len = 0;
  static uint8_t is_stuffed = 0;
  static uint8_t is_invalid = 0;
  static uint8_t buf_232[1000];
  static uint8_t buf_unstf[500];

  do
  {
    for (; i < r232_len; i++)
    {
      /* is it start of message? */
      if (buf_232[i] == VNA_BS_FLAG)
      {
        /* start */
        buf_len = 0;
        is_invalid = 0;
      }
      else if (is_invalid == 0)
      {
        /* if it's an escape, skip and unstuff next byte */
        if (buf_232[i] == VNA_BS_ESCAPE)
        {
          is_stuffed = 1;
        }
        else
        {
          /* if prev byte was an escape, then decode current byte */
          if (is_stuffed)
          {
            is_stuffed = 0;

            /* it can only be two things, else invalid stream */
            if (buf_232[i] == VNA_BS_ESCAPE_FLAG)
              buf_232[i] = VNA_BS_FLAG;
            else if (buf_232[i] == VNA_BS_ESCAPE_ESCAPE)
              buf_232[i] = VNA_BS_ESCAPE;
            else
              is_invalid = 1;
          }

          /* at this point data is always unstuffed */
          if (buf_len < sizeof(buf_unstf))
            buf_unstf[buf_len++] = buf_232[i];

          /* at 2 bytes, we have enough info to calc a real msg length */
          if (buf_len == 2)
            msg_len = ((buf_unstf[0] << 8) | buf_unstf[1]) + 2;

          /* have we received the entire msg, is it big enough? */
          if ((buf_len == msg_len) && (buf_len > 2) && (msg_len <= msg_size))
          {
            /* subtract off cksum, validate, and pass back new msg to application */
            buf_len--;
            if (buf_unstf[buf_len] == vna_232_cksum(&buf_unstf[0], buf_len))
            {
              msg_len = (uint16_t)(buf_len - 2);
              for (cnt = 0; cnt < msg_len; cnt++)
                msg[cnt] = buf_unstf[cnt + 2];
              return msg_len;
            }
          }
        }
      }
    }

    /* read all data from uart and reset our index */
    r232_len = 0;
    while ((uart_rx(&val) == 0) && (r232_len < sizeof(buf_232)))
      buf_232[r232_len++] = val;

    i = 0;

  } while (r232_len);

  return 0;
}
