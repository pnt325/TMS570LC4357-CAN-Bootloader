#define CANID_BL_APP_ERASE       0x0CFFD000  /* app erase cmd */
#define CANID_BL_APP_ERASE_APOS  0x0CFFD001  /* ack positive */
#define CANID_BL_APP_ERASE_ANEG  0x0CFFD002  /* ack negative */

#define CANID_BL_STOP            0x0CFFD003  /* stop cmd */
#define CANID_BL_STOP_APOS       0x0CFFD004  /* ack positive */
#define CANID_BL_STOP_ANEG       0x0CFFD005  /* ack negative */

#define CANID_BL_CPU_RESET       0x0CFFD006  /* cpu reset cmd */
#define CANID_BL_CPU_RESET_APOS  0x0CFFD007  /* ack positive */

#define CANID_BL_VER_REQ         0x0CFFD008  /* req all version info */
#define CANID_BL_VER_REQ_RSP     0x0CFFD009  /* all ver response */

#define CANID_BL_MAP_REQ         0x0CFFD00A  /* req memory map info */
#define CANID_BL_MAP_REQ_RSP_ARM 0x0CFFD00B  /* memory map response */
#define CANID_BL_MAP_REQ_RSP_C2K 0x0CFFD00C

#define CANID_BL_ADDR            0x0CFFD020  /* 32-bit address */
#define CANID_BL_ADDR_APOS       0x0CFFD021  /* ack positive */
#define CANID_BL_ADDR_ANEG       0x0CFFD022  /* ack negative */
#define CANID_BL_DATA            0x0CFFD023  /* data */
#define CANID_BL_DATA_APOS       0x0CFFD024  /* ack positive */
#define CANID_BL_DATA_ANEG       0x0CFFD025  /* ack negative */
