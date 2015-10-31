#include uart.h

void stdinout_init(){
  uart_init();

  static FILE uart_stream = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

  stdout = &uart_stream;
  stdin = &uart_stream;
}

int uart_putchar(char c, FILE* stream){
  uart_tx_byte(c);
  if(c == '\n') uart_tx_byte('\r');
  return 0;
}

int uart_getchar(FILE* stream){
  return uart_rx_byte();
}
