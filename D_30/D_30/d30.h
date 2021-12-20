#pragma once 

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus



#include <stdio.h>
#include <stdlib.h>

typedef struct Pairs
{
	int one;
	int two;

}pairs_t;

typedef struct List
{
	int field;
	struct List* next;
} list_t;

typedef struct Queue
{
	struct List* head, * tail;
} queue_t;


void MinMaxRates();  
queue_t* QueueCreate(int value);  ////
void AddInQueue(queue_t* queue, int field);  //
void DeleteOutQueue(queue_t* queue);   //
void ShirtArray(pairs_t* pairs, int number);
int FoundNextTask(pairs_t* pairs, int numberT, int top); //
int IsInQueue(queue_t* queue, int value); //
pairs_t* PairsRead(int numberT, FILE* file, int* numPairs); ////
int IsInArr(int* arr, int size, int value); //
void QueueDestroy(queue_t* queue); ////
int* BuildSequence(int numberT, pairs_t* pairs, int numberPairs);
void Print(int* arr, int size, FILE* file); ////


#ifdef __cplusplus
}
#endif