#ifndef STDINOUT1_H
#define STDINOUT1_H

#include <stdio.h>

//Initialize the UART bus, then create a new file stream based off of the wrapper
//UART functions uart_putchar()and uart_getchar()
//void stdinout_init1();

//Transmit the character c over the UART. Ignore the stream parameter, as this function only works with one UART device. Note that if a newline (‘\n’) character is being transmitted, this will happen when you have a newline in your printf() string, you also need to transmit a carriage return (‘\r’) character to tell the console on the PC that it should not just advance to a new line, but also start writing the next characters from the beginning of the line. This function should return 0 on success, -1 on failure.
int uart_putchar(char c, FILE* stream);

//Receive the character c from the UART. Ignore the stream parameter as this function only works with one UART device. This function should return the character on success, -1 on failure.
int uart_getchar(FILE* stream);

#endif
