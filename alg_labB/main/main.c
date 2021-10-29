#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include"memallocator.h"

#pragma warning(disable:4996)

#define MAX_MEMORY_SIZE 10000
#define MAX_ITERATION_SIZE 1000
#define MAX_NUMBER_OF_ITERATION 10000

double mallocTest(int iteration)
{
	LARGE_INTEGER start, end, counter; //время 
	double time;
	QueryPerformanceFrequency(&counter);
	QueryPerformanceCounter(&start);
	for (int i = 0;i < iteration;i++)
	{
		void* ptr = malloc((rand() % MAX_ITERATION_SIZE));
		free(ptr);
	}
	QueryPerformanceCounter(&end);
	time = (double)((double)(end.QuadPart - start.QuadPart) / (double)counter.QuadPart * 1000);
	return time;
}

double memallocTest(int iteration)
{
	LARGE_INTEGER start, end, counter; //время 
	double time;
	QueryPerformanceFrequency(&counter);
	QueryPerformanceCounter(&start);
	for (int i = 0;i < iteration;i++)
	{
		void* ptr = memalloc((rand() % MAX_ITERATION_SIZE));
		memfree(ptr);
	}
	QueryPerformanceCounter(&end);
	time = (double)((double)(end.QuadPart - start.QuadPart) / (double)counter.QuadPart * 1000);
	return time;
}

int main() 
{
	void* p1 = 0, * p2 = 0, * p3 = 0;
	void* ptr = malloc(10000);
	int a = meminit(ptr,10000);
	double mallocTime[MAX_NUMBER_OF_ITERATION], memallocTime[MAX_NUMBER_OF_ITERATION];
	for (int i = 0;i < MAX_NUMBER_OF_ITERATION;i++)
	{
		mallocTime[i] = mallocTest(i);
		memallocTime[i] = memallocTest(i);
	}
	FILE* file = fopen("result.txt", "w");
	for (int i = 0;i < MAX_NUMBER_OF_ITERATION;i++)
	{
		fprintf(file, "%lf ", mallocTime[i]);
	}
	fprintf(file, "\n\n");
	for (int i = 0;i < MAX_NUMBER_OF_ITERATION;i++)
	{
		fprintf(file, "%lf ", memallocTime[i]);
	}
	fclose(file);
	/*p1 = memalloc(100);
	p2 = memalloc(1000);
	memfree(p1);
	p3 = memalloc(96);
	memfree(p3);
	memfree(p2);*/
	memdone();
	free(ptr);
}