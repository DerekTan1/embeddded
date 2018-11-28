#include "filter.h"

extern int y;
int x[NUMBER_OF_SAMPLES];
unsigned int n;
unsigned int CurrentSample;
unsigned int CumulativeSum;

void filter()
{
	// Update the sample array, x.
    CumulativeSum=CumulativeSum+(CurrentSample-x[n]);
    x[n] = CurrentSample;
    n=(n+1)&(NUMBER_OF_SAMPLES-1);
	// Generate the filter output.
	y = CumulativeSum>>6;
}

