#include "digipot.h"
#include "gpio.h"
#include "spi.h"
#include <avr/io.h>
#include <stdio.h>
#include "led.h"

static void pot_high_impedance_sdo(uint8_t pot_cs_pin);

void digipot_init(){
	
	//Set chip select pins to output mode
	gpio_set_mode(&PORTC, DIGIPOT_AMP_CS_PIN_gm, 1);
	gpio_set_mode(&PORTC,DIGIPOT_FIL_CS_PIN_gm, 1);
	
	//Set mode to SSbar
	gpio_set_mode(&PORTC, 0b10100000, 1); // set mosi out
	gpio_set_mode(&PORTC, 0b01000000, 0); // Set miso in
	
	//Set output pin values to one
	gpio_set_out(&PORTC, DIGIPOT_AMP_CS_PIN_gm, 1);
	gpio_set_out(&PORTC, DIGIPOT_FIL_CS_PIN_gm, 1);
	
	//This line doesn't do anything important
	gpio_set_out(&PORTC, 0b1000000, 1);
	
	 //Enable register
	 //Turn to master mode
	 //Set to transmit least significant first
	SPIC_CTRL = 0b01010111; //Rising, setup and falling sample
	
	//Set miso to input again
	gpio_set_mode(&PORTC, 0b01000000, 0); 
	
	//Enable pullup resistor on MISO
	PORTC.PIN6CTRL |= 0b011000;
	
	pot_high_impedance_sdo(DIGIPOT_AMP_CS_PIN_gm);
	
	//Write enable, AMPOT
	gpio_set_out(&PORTC, DIGIPOT_AMP_CS_PIN_gm, 0);
	uint16_t writeEnable =  0b0001110000000010;
	spi_txrx(&SPIC, &writeEnable, NULL, 2);
	gpio_set_out(&PORTC, DIGIPOT_AMP_CS_PIN_gm, 1);
	pot_high_impedance_sdo(DIGIPOT_AMP_CS_PIN_gm);
	
	//Write enable, FILPOT
	gpio_set_out(&PORTC, DIGIPOT_FIL_CS_PIN_gm, 0);
	writeEnable =  0b0001110000000010;
	spi_txrx(&SPIC, &writeEnable, NULL, 2);
	gpio_set_out(&PORTC, DIGIPOT_FIL_CS_PIN_gm, 1);
	pot_high_impedance_sdo(DIGIPOT_FIL_CS_PIN_gm);
	
}

static void pot_high_impedance_sdo(uint8_t pot_cs_pin){
	gpio_set_out(&PORTC, pot_cs_pin, 0); //Pull down CS
	
	uint16_t dataword = 0b1000000000000001;
	spi_txrx(&SPIC, &dataword, NULL, 2);
	
	gpio_set_out(&PORTC, pot_cs_pin, 1); //Pull up CS
	gpio_set_out(&PORTC, pot_cs_pin, 0); //Pull down CS
	
	uint16_t dataword2 = 0b0000000000000000;
	spi_txrx(&SPIC, &dataword2, NULL, 2);
	
	gpio_set_out(&PORTC, pot_cs_pin, 1); //Pull up CS
}

//Read the wiper position (0 - 1023) of the potentiometer which has its CS pin connected to pot_cs_pin.
uint16_t pot_wiperpos_get(uint8_t pot_cs_pin){
	gpio_set_out(&PORTC, pot_cs_pin, 0); //Pull down CS

	uint16_t returnable = -1;
	uint16_t command = 0b00100000000000;
	//uint16_t command = 0x2000;
	spi_txrx(&SPIC, &command, NULL, 2);

	gpio_set_out(&PORTC, pot_cs_pin, 1); //Pull up CS

	uint16_t zeroes = 0b0000000000000000;
	
	gpio_set_out(&PORTC, pot_cs_pin, 0); //Pull down CS
	spi_txrx(&SPIC, &zeroes, &returnable, 2);
	gpio_set_out(&PORTC, pot_cs_pin, 1); //Pull up CS
	
	pot_high_impedance_sdo(pot_cs_pin); //Make it happen
	
	//printf("returnable: %d \n\r", returnable);
	return returnable;
}

//Write the wiper position (0 - 1023) of the potentiometer which has its CS pin connected to pot_cs_pin.
void pot_wiperpos_set(uint8_t pot_cs_pin, uint16_t pos){
	gpio_set_out(&PORTC, pot_cs_pin, 0); //Pull down CS

	uint16_t command = 0b00010000000000 | pos;
	spi_txrx(&SPIC, &command , NULL, 2);

	gpio_set_out(&PORTC, pot_cs_pin, 1); //Pull up CS
	
	pot_high_impedance_sdo(pot_cs_pin);
	
	//printf("hullo");
}
