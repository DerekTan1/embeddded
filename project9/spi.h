#ifndef USCI_SPI_H
#define USCI_SPI_H

#include <msp430.h>

void InitializeSPI();
void SPISendByte(unsigned char SendValue);
unsigned char SPIReceiveByte();

#endif
