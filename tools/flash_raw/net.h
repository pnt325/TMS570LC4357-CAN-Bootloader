#ifndef __NET_H__
/*
** Defines for MCONN_EXT and ACONN_EXT
*/
#define __NET_H__
#include "bits.h"

/* network type */
#define NET_TYPE_OBD2_11          (B0)
#define NET_TYPE_OBD2_29          (B1)
#define NET_TYPE_OBD2          (B1|B0)
#define NET_TYPE_J1939            (B2)
#define NET_TYPE_RAW_11           (B3)
#define NET_TYPE_RAW_29           (B4)
#define NET_TYPE_RAW           (B4|B3)
#define NET_TYPE_AUTOFAILED      (B31)

/* network speed */
#define NET_SPD_UNKNOWNERR       (B29)
#define NET_SPD_AUTOFAILED       (B30)
#define NET_SPD_INITSTATE        (B31)


#endif
