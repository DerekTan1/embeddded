#include "timerA0.h"

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
    static unsigned int resolution = 100;
    // 100 Hz
    static unsigned int delayA = 10;
    TimeDelay(delayA, resolution);

    // 250 Hz
    static unsigned int delayB = 4;
    TimeDelay(delayB, resolution);

    // 500 Hz
    static unsigned int delayC = 2;
    TimeDelay(delayC, resolution);
}

void TimeDelay(unsigned int delay, unsigned int resolution) {
    volatile int i, j;
    for (i = 0; i < delay; i++) {
        for (j = 0; j < resolution; j++);
    }
}

