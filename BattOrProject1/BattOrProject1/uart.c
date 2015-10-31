//#include "uart.h"
#include "gpio.h"
#include <avr/io.h>
#include <stdio.h>

void uart_init(){
  gpio_set_mode(&PORTD, 0b100, 0);
  gpio_set_mode(&PORTD, 0b1000, 1);
  gpio_set_out(&PORTD, 0b1000, 1);
  USARTD0.CTRLB = 0b00011000; //Initialize UART
  USARTD0.CTRLC = 0b00000011; //Set UART start, stop, parity, # data bits
  USARTD0.BAUDCTRLA = 0b00000000; //This and next line set baud rate to f_clk/16, or 1MHz
  USARTD0.BAUDCTRLB = 0b00000000;
}
