#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

void spi_txrx(SPI_t* spi, void* txd, void* rxd, uint16_t len){	
	
	// Case, want to both send and receive
	if(rxd != NULL && txd != NULL){
		for(int i = len-1; i >= 0; i--){
			spi->DATA = ((uint8_t*)txd)[i];
			
			while(spi->STATUS == 0){
			}
			((uint8_t*)rxd)[i] = spi->DATA;
			
			
		}
	}
	
	//Case, just want to send
	else if(rxd == NULL){
		for(int i = len-1; i >= 0; i--){
			//printf("--> %d \n\r",((uint8_t*)txd)[i]);
			spi->DATA = ((uint8_t*)txd)[i];
			
			while(spi->STATUS == 0){
			}
			
			spi->DATA;
			
		}
	}
	
	//Case, just want to receive
	else if(txd == NULL){
		for(int i = 0; i < len; i++){
			spi->DATA = 0x0;
			((uint8_t*)rxd)[i] = spi->DATA;
			while(spi->STATUS == 0){
			}
		}
	}

}

