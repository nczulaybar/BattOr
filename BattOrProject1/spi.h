#ifndef SPI_H
#define SPI_H

void spi_txrx(SPI_t* spi, void* txd, void* rxd, uint16_t len);

#endif