#include <stdio.h>
#include <stdlib.h>
#define NUM_STEPS 8

typedef struct
{
	double r;
	double i;
}	complex_t;

int	main()
{
	int i;
	complex_t *complexArray;
	complex_t oddSum = {.0, .0}, evenSum = {.0, .0};

	complexArray = malloc (NUM_STEPS * sizeof (complex_t));
	for (i = 0; i != NUM_STEPS; ++i)
	{
		complexArray[i].r = i + 4;
		complexArray[i].i = 3 * i;
	}
	for (i = 0; i != NUM_STEPS; i += 2)
	{
		oddSum.r += complexArray[i].r;
		oddSum.i += complexArray[i].i;
		evenSum.r += complexArray[i].r;
		evenSum.i += complexArray[i].i;
	}
	printf ("Sums are: (%f, %f) & (%f, %f)\n", evenSum.r, evenSum.i, oddSum.r, oddSum.i);
	return 0;
}
