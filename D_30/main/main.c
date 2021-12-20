#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "d30.h"

#pragma warning(disable:4996)

/**
*
* CPU: AMD Ryzen 3 3200U with Radeon Vega Mobile Gfx 2.60 GHz
* RAM: 4 GB
* SSD: 234 GB
*
* Number of tasks - 20000
*
* Result -  1.851627 s 
*
*/


void StressTest()
{
	LARGE_INTEGER start, end, counter;
	double time;

	int numTask = 20000;

	FILE* file = fopen("input.txt", "w");
	fprintf(file, "%i %i\n", numTask, 20001);

	for (int i = 0;i < numTask; i++)
	{
		fprintf(file, "%i ", 1);
	}

	fprintf(file, "\n");

	for (int i = 0;i < numTask-1;i++)
	{
		fprintf(file, "%i %i\n", i + 1, i + 2);
		fprintf(file, "%i %i\n", i + 2, i + 3);
	}

	fprintf(file, "0");
	fclose(file);

	QueryPerformanceFrequency(&counter);
	QueryPerformanceCounter(&start);

	MinMaxRates();

	QueryPerformanceCounter(&end);
	time = (double)((double)(end.QuadPart - start.QuadPart) / (double)counter.QuadPart);

	printf("%lf", time);

}

int main()
{
	StressTest();
}