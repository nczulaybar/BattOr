void spi_txrx(SPI_t* spi, void* txd, void* rxd, uint16_t len){	
	
	// Case, want to both send and receive
	if(rxd != NULL && txd != NULL){
		for(int i = 0; i < len, i++){
			spi->DATA = *txd[i];
			while(spi->STATUS == false){
			}
			*rxd[i] = spi->DATA;
		}
	}
	
	//Case, just want to send
	else if(rxd == NULL){
		for(int i = 0; i < len, i++){
			spi->DATA = *txd[i];
			while(spi->STATUS == false){
			}
			spi->DATA;
		}
	}
	
	//Case, just want to receive
	else if(txd == NULL){
		for(int i = 0; i < len, i++){
			spi->DATA = 0x0;
			*rxd[i] = spi->DATA;
			while(spi->STATUS == false){
			}
		}
	}

}

