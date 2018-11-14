#include "spi.h"

void InitializeSPI()
{
	// Software reset enabled. USCI B0 logic held in reset state.

	// Select USCI B0 SPI functionality.
	// SMCLK as source
	// divide clock by 1
	// initialize transmit buffer to 0

	// Configure port pin to receive output from USCI B0 clock.

	// Configure port pin to receive output from USCI B0 MOSI.

	// Configure port pin to receive output from USCI B0 MISO.

	// Software reset disabled. USCI B0 logic released for operation.
}


void SPISendByte(unsigned char SendValue)
{

}

unsigned char SPIReceiveByte()
{
	unsigned char ReceiveValue = 0;

	return ReceiveValue;
}

