#ifndef DAC_DAC_H_
#define DAC_DAC_H_

#include <msp430.h>

typedef struct {
	int DACAddress;
	int CurrentArrayIndex;
	int ArrayLength;
	unsigned int * ArrayValuesPtr;
} DAC;

// Commands for DACs
#define WRITE_TO_INPUT_REGISTER_N               (0x00 << 4)
#define UPDATE_DAC_REGISTER_N                   (0x01 << 4)
#define WRITE_TO_INPUT_REGISTER_N_UPDATE_ALL_N  (0x02 << 4)
#define WRITE_TO_AND_UPDATE_N                   (0x03 << 4)
#define POWER_DOWN_N                            (0x04 << 4)
#define NO_OPERATION                            (0x0F << 4)

// Addresses for DACs
#define DAC_A       0x00
#define DAC_B       0x01
#define DAC_C       0x02
#define DAC_D       0x03
#define ALL_DACS    0x0F

//  DAC CS
#define DAC_CS 1
#define DAC_CS_BIT               BIT3
#define DAC_CS_PORT              P1OUT
#define DAC_CS_DDR               P1DIR
#define SET_DAC_CS_AS_AN_OUTPUT  DAC_CS_DDR |= DAC_CS_BIT
#define TURN_OFF_CS                    DAC_CS_PORT |= DAC_CS_BIT
#define TURN_ON_CS                        DAC_CS_PORT &= ~DAC_CS_BIT

//  DAC Clear
#define DAC_CLEAR 1
#define DAC_CLEAR_BIT               BIT4
#define DAC_CLEAR_PORT              P1OUT
#define DAC_CLEAR_DDR               P1DIR
#define SET_DAC_CLEAR_AS_AN_OUTPUT  DAC_CLEAR_DDR |= DAC_CLEAR_BIT
#define TURN_OFF_DAC_CLEAR                    DAC_CLEAR_PORT |= DAC_CLEAR_BIT
#define TURN_ON_DAC_CLEAR                        DAC_CLEAR_PORT &= ~DAC_CLEAR_BIT

/*
 * InitializeDACPins
 *
 * Set up the direction registers and initial states for the output pins used to interface with the DAC
 *
 * No arguments
 *
 * Return type: Void
 */
void InitializeDACPins(void);

/*
 * InitializeDACObject
 *
 * Define the initial values for the DAC struct, as demonstrated in main.c.
 *
 * Arguments:
 *  - DAC *Dac:                 Pointer to DAC struct in use
 *  - int DACNum:               Identifier for DAC output A through D
 *  - unsigned int * ArrayPtr   Pointer to the first element of sine table (array) associated with DAC
 *  - int ArrayLength           Variable for length of sine table associated with DAC
 *
 *  Return type: void
 */
void InitializeDACObject(DAC *Dac, int DACNum, unsigned int * ArrayPtr, int ArrayLength);

/*
 * UpdateDACWithArrayValue
 *
 * Function returns an integer that represents the value in the sinusoid array
 * located at Dac->CurrentArrayIndex.  Also, once the value has been obtained,
 * Dac->CurrentArrayIndex is incremented modulo Dac->ArrayLength; that is, if
 * Dac->CurrentArrayIndex is greater than Dac->ArrayLength after its incremented,
 * then reset Dac->CurrentArrayIndex to zero.
 *
 * Arguments:
 * - DAC *Dac               Pointer to DAC struct in use
 *
 * Return type: int
 */
int UpdateDACWithArrayValue(DAC *Dac);

#endif
