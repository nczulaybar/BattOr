#include uart.h
#include <avr/io.h>

void uart_init(){
  USARTD.CTRLB = 0b00011000; //Initialize UART
  USARTD.CTRLC = 0b00000011; //Set UART start, stop, parity, # data bits
  USARTD.BAUDCTRLA = 0b00000000; //This and next line set baud rate to f_clk/16, or 1MHz
  USARTD.BAUDCTRLB = 0b00000000;
}
