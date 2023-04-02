#define VNA_MSG_ACK          0      /* ack */
#define VNA_MSG_FA_J1939     1      /* pgn filter add */
#define VNA_MSG_FD_J1939     2      /* pgn filter delete */
#define VNA_MSG_FA_J1587     3      /* pid filter add */
#define VNA_MSG_FD_J1587     4      /* pid filter delete */
#define VNA_MSG_TX_J1939     5      /* pgn tx */
#define VNA_MSG_RX_J1939     6      /* pgn rx */
#define VNA_MSG_PX_J1939     7      /* pgn tx - periodic */
#define VNA_MSG_TX_J1587     8      /* pid tx */
#define VNA_MSG_RX_J1587     9      /* pid rx */
#define VNA_MSG_PX_J1587    10      /* pid tx - periodic */
#define VNA_MSG_RTC_SET     11      /* rtc set */
#define VNA_MSG_RTC_GET     12      /* rtc get */
#define VNA_MSG_LPW_ENA     13      /* low pwr mode enabled */
#define VNA_MSG_LPW_DIS     14      /* low pwr mode disabled */
#define VNA_MSG_CAN_SET     15      /* bus bits per second */
#define VNA_MSG_UART_SET    16      /* uart bits per second */
#define VNA_MSG_CPU_RESET   17      /* cpu reset */
#define VNA_MSG_PAMODE_SET  18      /* passall mode config */
#define VNA_MSG_TX_CAN      20      /* can rx */
#define VNA_MSG_RX_CAN      21      /* can rx */
#define VNA_MSG_RX_J1708    22      /* j1708 rx */
#define VNA_MSG_STATS       23      /* stat msg - 1 sec */
#define VNA_MSG_PSTATUS     30      /* patch status */
#define VNA_MSG_BLVER       31      /* bl version */
#define VNA_MSG_FA_I15765   40      /* pid filter add */
#define VNA_MSG_FD_I15765   41      /* pid filter delete */
#define VNA_MSG_TX_I15765   42      /* pid tx */
#define VNA_MSG_RX_I15765   43      /* pid rx */
#define VNA_MSG_PX_I15765   44      /* pid tx - periodic */
#define VNA_MSG_STATS_OBD   45      /* stat msg - 1 sec */



#if 0
VNA_MSG_ACK:
  8b-vmsg, 8b-vmsg_ack

VNA_MSG_FA_J1939:
  8b-vmsg, 8b-port, 24b-pgn

VNA_MSG_FD_J1939:
  8b-vmsg, 8b-port, 24b-pgn

VNA_MSG_FA_J1587
  8b-vmsg, 16b-pid

VNA_MSG_FD_J1587
  8b-vmsg, 16b-pid

VNA_MSG_TX_J1939:
  8b-vmsg, 8b-port, 24b-pgn, 8b-dst, 8b-src, 8b-pri, nB-data

VNA_MSG_RX_J1939:
  8b-vmsg, 8b-port, 24b-pgn, 8b-dst, 8b-src, 8b-pri, nB-data

VNA_MSG_PX_J1939:
  8b-vmsg, 8b-port, 24b-pgn, 8b-dst, 8b-src, 8b-pri, nB-data, 16b-rate(ms)

VNA_MSG_TX_J1587
  8b-vmsg, 8b-mid, 16b-pid, 8b-pri, nB-data

VNA_MSG_RX_J1587
  8b-vmsg, 8b-mid, 16b-pid, nB-data

VNA_MSG_TX_J1587
  8b-vmsg, 8b-mid, 16b-pid, 8b-pri, nB-data, 16b-rate(ms)

VNA_MSG_CAN_SET:
  8b-vmsg, 8b-port, 8b-brp, 8b-prseg, 8b-seg1ph, 8b-seg2ph

VNA_MSG_PAMODE_SET:
  8b-vmsg, 8b-port, 8b-mode17, 8b-mode15, 8b-modeca, 8b-modej19

VNA_MSG_CPU_RESET:
  8b-vmsg, 24b-key
#endif
