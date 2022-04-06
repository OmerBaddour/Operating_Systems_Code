/*
 * Calculate pi using the Monte Carlo method.
 * Uses NUM_POINTS points.
 */

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_POINTS 1000000

int in_circle; /* store count of number of points in unit circle */

int main (void) {

	srand(time(NULL)); /* initialize seed */

	#pragma omp parallel for
	for (int i = 0; i < NUM_POINTS; i++) {
		/* generate (x, y)
		 * rand() returns an int whose range is [0, RAND_MAX]
		 * note that the computation results in the desired [-1, 1] bounds
		 * for x and y */
		double x = (rand() / (RAND_MAX / 2.0)) - 1;
		double y = (rand() / (RAND_MAX / 2.0)) - 1;
		
		if (sqrt(x * x + y * y) <= 1) {
			/* point is in the circle since its distance from (0, 0)
			 * is <= 1, and 1 is the radius of the unit circle */

			#pragma omp critical
			{
				in_circle++;
			}
		}
	}

	printf("Calculated value of pi: %f\n", 4.0 * in_circle / NUM_POINTS);

	return 0;
}
