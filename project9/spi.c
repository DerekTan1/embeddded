#include "spi.h"

void InitializeSPI()
{
// Software reset enabled. USCI B0 logic held in reset state.
    UCB0CTL1 |= UCSWRST;
	// Select USCI B0 SPI functionality.
    UCB0CTL0 |= UCCKPH | UCMSB | UCMST | UCSYNC | UCMODE_0;
	// SMCLK as source
    UCB0CTL1 |= UCSSEL_2;
	// Divide clock by 1
    UCB0BR0 = 1;
    UCB0BR1 = 0;
	// Initialize transmit buffer to 0
    UCB0TXBUF = 0x0;

	// Configure port pin to receive output from USCI B0 clock.
    P1SEL |= BIT5;
    P1SEL2 |= BIT5;
	// Configure port pin to receive output from USCI B0 MOSI.
    P1SEL |= BIT6;
    P1SEL2 |= BIT6;
	// Configure port pin to receive output from USCI B0 MISO.
    P1SEL |= BIT7;
    P1SEL2 |= BIT7;
	// Software reset disabled. USCI B0 logic released for operation.
    UCB0CTL1 &= ~UCSWRST;
}

void SPISendByte(unsigned char SendValue)
{
    UCB0TXBUF = SendValue;
    while (UCB0STAT & UCBUSY);
}


unsigned char SPIReceiveByte()
{
	unsigned char ReceiveValue = 0;

	return ReceiveValue;
}
