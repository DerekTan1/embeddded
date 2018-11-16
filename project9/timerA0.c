#include "timerA0.h"
#include "DAC.h"
#include "spi.h"

extern DAC gDAC_A;
extern DAC gDAC_B;
extern DAC gDAC_C;
extern DAC gDAC_D;

void ConfigureTimerA0(void)
{
    SET_CLK_AS_AN_INPUT;

	// Stop the Timer A0 and clear it.
    TA0CTL = (MC_0 | TACLR);

    // Configure the timer, including input clock select, input clock divide,
    // and starting the timer in up mode.
    P1SEL |= BIT2;
    P2SEL &= ~BIT2;
    TA0CTL |= (TASSEL_2 | ID_3 | MC_1);

    // Initialize TA0CCR0.
    TA0CCR0 = 249;

	// Enable TA0CCR0 Compare/Capture Interrupt Flag (CCIFG0)
    TA0CCTL0 |= CCIE;
}

#pragma vector = TIMER0_A0_VECTOR
// Interrupt service routine for CCIFG0
__interrupt void TimerA0ISR(void)
{
    // 1 kHz
    SPISendByte(WRITE_TO_AND_UPDATE_N | DAC_D);
    int data = UpdateDACWithArrayValue(&gDAC_D);
    SPISendByte((data >> 8) & 0xFF);
    SPISendByte(data & 0xFF);
}


