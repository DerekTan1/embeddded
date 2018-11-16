#include "DAC.h"

void InitializeDACPins(void)
{
    SPISendByte(POWER_DOWN_N);
    SPISendByte(ALL_DACS);
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
	Dac->CurrentArrayIndex += 1;
	//Modulo Increment, the easy way
	if(Dac->CurrentArrayIndex > Dac->ArrayLength){
	    Dac->CurrentArrayIndex = 0;
	}

	return ArrayValue;
}

