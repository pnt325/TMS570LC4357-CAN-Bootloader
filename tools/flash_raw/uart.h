extern uint8_t uart_setup(uint8_t port, uint8_t rate);

extern void uart_close(void);

extern uint8_t uart_rx(uint8_t *val);

extern uint8_t uart_tx(uint8_t val);

extern uint8_t uart_tx_bytes(uint8_t *buf, uint16_t len);

extern uint32_t uart_rx_bytes(uint8_t *val, int max_bytes);
