#ifndef UART_H
#define UART_H

//Configure the USART D0 peripheral to operate at 1 Mbit/s baud, with 8 bit characters, one start bit and one stop bit, and no parity bits.
void uart_init();

//Transmit the specified byte called data over the UART bus. This function will complete when the byte has been fully transmitted.
inline void uart_tx_byte(uint8_t data){
  while(!(USARTD.STATUS & USART_DREIF_bm)){} //Pause until RTS bit goes high

  USARTD.DATA = data;
}

//Receive the specified byte called data over the UART bus. This function will complete when one byte has been fully received.
inline uint8_t uart_rx_byte(){
  while(!(USART.STATUS & USART_RXCIF_bm)){} //Pause until data ready bit goes high

  return USART.DATA;
}

#endif
