#pragma once 

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_ERROR -1
#define FILE_ERROR -2
#define INVALID_VALUE -3
#define MAX_SIZE 50


typedef struct Person {
	char* fullName;
	int day;
	char* month;
	int year;
} person_t;
typedef struct List {
	person_t person;
	struct List* next;
} list_t;

void PrintStr(char* str);
void DestroyList(list_t* list);
int NumberMonth(char* month);
int ItsName(char* fullName);
int DateCompare(person_t p1, person_t p2);
char* WithoutFirst(char* str);
person_t StructureFromString(char* arr);
person_t FileRead(FILE* file);
int SearchPosition(list_t* list, person_t person);
list_t* AddPerson(list_t* list, person_t person);
void PrintList(list_t* list);
int CheckPerson(person_t person, int day, char* month, int year);
int CheckList(list_t* list, int day, char* month, int year);

#ifdef __cplusplus
}
#endif