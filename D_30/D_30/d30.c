#include <stdio.h>
#include <stdlib.h>
#include "d30.h"

#pragma warning(disable:4996)
#pragma warning (disable:6031)

queue_t* QueueCreate(int value)
{
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	if (!queue)
		return NULL;
	queue->head = (list_t*)malloc(sizeof(list_t));
	if (!queue->head)
		return NULL;
	queue->head->field = value;
	queue->head->next = NULL;
	queue->tail = queue->head;
	return queue;
}

void AddInQueue(queue_t* queue, int field)
{
	if (!queue->tail)
	{
		QueueCreate(field);
		return;
	}
	queue->tail->next = (list_t*)malloc(sizeof(list_t));
	if (!queue->tail->next)
	{
		perror("Memory error");
		return;
	}
	queue->tail = queue->tail->next;
	queue->tail->field = field;
	queue->tail->next = NULL;
}

void DeleteOutQueue(queue_t* queue)
{
	if (queue)
	{
		list_t* temp;
		temp = queue->head;
		queue->head = queue->head->next;
		free(temp);
	}
}

void ShirtArray(pairs_t* pairs, int number)
{
	int i = number;
	while ((pairs[i].one != 0) || (pairs[i].two != 0))
	{
		pairs[i] = pairs[i + 1];
		i++;
	}
	pairs[i].one = 0;
	pairs[i].two = 0;
}

int FoundNextTask(pairs_t* pairs, int numberT, int top)
{
	int i = 0;
	int nextTask = numberT+1, count;
	while ((pairs[i].one != 0) || (pairs[i].two != 0))
	{
		if (pairs[i].one == top)
		{
			nextTask = pairs[i].two;
			count = i;
			ShirtArray(pairs, count);
			return nextTask;
		}
		i++;
	}
	return 0;
}

int IsInQueue(queue_t* queue, int value)
{
	list_t* tmp = queue->head;
	while (tmp != NULL)
	{
		if (tmp->field == value)
		{
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

pairs_t* PairsRead(int numberT, FILE* file, int* numPairs)
{
	int MaxNumPairs = numberT * (numberT + 1) * 0.5;
	pairs_t* pairs = (pairs_t*)malloc(sizeof(pairs_t) * MaxNumPairs);
	if (!pairs)
		return NULL;
	int i = 0;
	while ((fscanf(file, "%i", &pairs[i].one) != EOF) && (fscanf(file, "%i", &pairs[i].two) != EOF))
	{
		if (pairs[i].one == 0)
			break;
		i++;
	}
	*numPairs = MaxNumPairs;
	pairs[i].one = 0;
	pairs[i].two = 0;
	fclose(file);
	return pairs;
}

int IsInArr(int* arr, int size, int value)
{
	for (int i = 0; i < size; i++) {
		if (arr[i] == value) {
			return 1;
		}
	}
	return 0;
}

void QueueDestroy(queue_t* queue)
{
	list_t* delete = NULL;
	while (queue->head != NULL) {
		delete = queue->head;
		queue->head = queue->head->next;
		free(delete);
	}
}

int* BuildSequence(int numberT, pairs_t* pairs, int numberPairs)
{
	queue_t* queue = QueueCreate(1);
	int* sequence = (int*)malloc(sizeof(int) * numberT);
	if (!sequence)
		return NULL;
	int count = 0;
	while (count < numberT)
	{
		if (queue->head == NULL)
			break;
		int tmp = queue->head->field;
		int task = FoundNextTask(pairs, numberT, tmp);
		while (task != 0)
		{
			if ((IsInQueue(queue, task) == 0) && (IsInArr(sequence, count + 1, task) == 0))
			{
				AddInQueue(queue, task);
			}
			task = FoundNextTask(pairs, numberT, tmp);
		}
		DeleteOutQueue(queue);
		sequence[count] = tmp;
		count++;
	}
	if (count < numberT)
		return NULL;
	QueueDestroy(queue);
	free(pairs);
	return sequence;
}

void Print(int* arr, int size, FILE* file)
{
	for (int i = 0;i < size;i++)
	{
		fprintf(file, "%i ", arr[i]);
	}
}

void MinMaxRates()
{
	FILE* input = fopen("input.txt", "r");
	FILE* output = fopen("output.txt", "w");
	if (!input)
		return;
	int numberT;
	int K;
	fscanf(input, "%i", &numberT);
	fscanf(input, "%i", &K);
	int sum = 0, ct;
	for (int i = 0;i < numberT;i++)
	{
		fscanf(input, "%i", &ct);
		sum += ct;
	}

	if (sum > K)
	{
		fprintf(output, "0");
		fclose(input);
		fclose(output);
		return;
	}

	int numberPairs = 0;
	pairs_t* pairs = PairsRead(numberT, input, &numberPairs);
	if (!pairs)
	{
		fprintf(output, "0");
		fclose(output);
		return;
	}
	int* sequence = BuildSequence(numberT, pairs, numberPairs);
	if (!sequence)
	{
		fprintf(output, "0");
		fclose(output);
		return;
	}
	Print(sequence, numberT, output);
	free(sequence);
	fclose(output);
}