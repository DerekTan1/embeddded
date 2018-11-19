#include "DAC.h"

void InitializeDACPins(void)
{
    SET_DAC_CS_AS_AN_OUTPUT;
    SET_DAC_CLEAR_AS_AN_OUTPUT;
    TURN_OFF_DAC_CLEAR;
}

void InitializeDACObject(DAC *Dac, int DACNum, unsigned int * ArrayPtr, int ArrayLength)
{
	Dac->DACAddress = DACNum;
	Dac->CurrentArrayIndex = 0;
	Dac->ArrayLength = ArrayLength;
	Dac->ArrayValuesPtr = ArrayPtr;
}

int UpdateDACWithArrayValue(DAC *Dac)
{
	int ArrayValue = Dac->ArrayValuesPtr[Dac->CurrentArrayIndex];
	Dac->CurrentArrayIndex +=1;
	//Modulo Increment, the easy way
	if(Dac->CurrentArrayIndex > Dac->ArrayLength){
	    Dac->CurrentArrayIndex = 0;
	}

	return ArrayValue;
}

