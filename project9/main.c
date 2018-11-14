#include <msp430.h> 

#include "ArrayValues.h"
#include "timerA0.h"
#include "spi.h"
#include "DAC.h"

// Function Prototypes
void ConfigureClockModule();

// Global variables
DAC gDAC_A;
DAC gDAC_B;
DAC gDAC_C;
DAC gDAC_D;

void main(void)
{
	// Stop the watchdog timer, and configure the clock module.
	WDTCTL = WDTPW + WDTHOLD;
    ConfigureClockModule();

    // Initialize hardware and port pins.
	InitializeSPI();
	ConfigureTimerA0();
	InitializeDACPins();

	// Initialize the DAC variables
	InitializeDACObject(&gDAC_A, DAC_A, (unsigned int *) SinusoidArray, SinusoidArrayLength);
	InitializeDACObject(&gDAC_B, DAC_B, (unsigned int *) SinusoidArray, SinusoidArrayLength);
	InitializeDACObject(&gDAC_C, DAC_C, (unsigned int *) SinusoidArray, SinusoidArrayLength);
	InitializeDACObject(&gDAC_D, DAC_D, (unsigned int *) SinusoidArray, SinusoidArrayLength);

	_enable_interrupts();		// interrupts enabled

}

void ConfigureClockModule()
{
	// Configure Digitally Controlled Oscillator (DCO) using factory calibrations
	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}
