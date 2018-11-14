#ifndef TIMER_A0_H
#define TIMER_A0_H

#include <msp430.h>

#define CLK_BIT                BIT2
#define CLK_PORT               P1IN
#define CLK_DDR                P1DIR
#define SET_CLK_AS_AN_INPUT    CLK_DDR &= ~CLK_BIT
#define TURN_ON_CLK            CLK_PORT |= CLK_BIT
#define TURN_OFF_CLK           CLK_PORT &= ~CLK_BIT

// Prototypes
void ConfigureTimerA0(void);

#endif
