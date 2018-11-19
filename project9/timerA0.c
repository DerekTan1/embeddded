#include "timerA0.h"
#include "DAC.h"
#include "spi.h"

extern DAC gDAC_A;
extern DAC gDAC_B;
extern DAC gDAC_C;
extern DAC gDAC_D;

unsigned int counterone;
unsigned int countertwo;
unsigned int counterthree;

void ConfigureTimerA0(void)
{
    SET_CLK_AS_AN_INPUT;

	// Stop the Timer A0 and clear it.
    TA0CTL = (MC_0 | TACLR);

    // Configure the timer, including input clock select, input clock divide,
    // and starting the timer in up mode.
    P1SEL |= BIT2;
    P2SEL &= ~BIT2;
    TA0CTL |= (TASSEL_2 | ID_0 | MC_1);

    // Initialize TA0CCR0.
    TA0CCR0 = 499;

	// Enable TA0CCR0 Compare/Capture Interrupt Flag (CCIFG0)
    TA0CCTL0 |= CCIE;

    counterone = 0;
    countertwo = 0;
    counterthree = 0;
}

#pragma vector = TIMER0_A0_VECTOR
// Interrupt service routine for CCIFG0
__interrupt void TimerA0ISR(void)
{
    counterone++;
    countertwo++;
    counterthree++;

    //Do this for all 4 DACs w/ global counters

    if(counterone == 2)
    {
        TURN_ON_CS;
        SPISendByte(WRITE_TO_INPUT_REGISTER_N | DAC_C);
        int data = UpdateDACWithArrayValue(&gDAC_C);
        SPISendByte((data >> 8));
        SPISendByte(data);
        //Disable CS
        TURN_OFF_CS;
        counterone=0;
    }

    if(countertwo == 4)
    {
        TURN_ON_CS;
        SPISendByte(WRITE_TO_INPUT_REGISTER_N | DAC_B);
        int data = UpdateDACWithArrayValue(&gDAC_B);
        SPISendByte((data >> 8));
        SPISendByte(data);
        //Disable CS
        TURN_OFF_CS;
        countertwo = 0;
    }

    if(counterthree == 2)
    {
        TURN_ON_CS;
        SPISendByte(WRITE_TO_INPUT_REGISTER_N | DAC_A);
        int data = UpdateDACWithArrayValue(&gDAC_A);
        SPISendByte((data >> 8));
        SPISendByte(data);
        //Disable CS
        TURN_OFF_CS;
        counterthree = 0;
    }
    // 1 kHz
    //Enable CS
    TURN_ON_CS;
    SPISendByte(WRITE_TO_INPUT_REGISTER_N_UPDATE_ALL_N | DAC_D);
    int data = UpdateDACWithArrayValue(&gDAC_D);
    SPISendByte((data >> 8));
    SPISendByte(data);
    //Disable CS
    TURN_OFF_CS;
}


