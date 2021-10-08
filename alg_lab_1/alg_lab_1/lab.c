#pragma once 
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"lab.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

void PrintStr(char* str) {
	int i = 0;
	while (str[i] != '\0') {
		printf("%c", str[i]);
		i++;
	}
}

void DestroyList(list_t* list) {
	list_t* delete = NULL;
	while (list != NULL) {
		delete = list;
		list = list->next;
		free(delete);
	}
}

int NumberMonth(char* month) {
	if (strcmp(month, "January") == 0)
		return 1;
	else if (strcmp(month, "February") == 0)
		return 2;
	else if (strcmp(month, "March") == 0)
		return 3;
	else if (strcmp(month, "April") == 0)
		return 4;
	else if (strcmp(month, "May") == 0)
		return 5;
	else if (strcmp(month, "June") == 0)
		return 6;
	else if (strcmp(month, "July") == 0)
		return 7;
	else if (strcmp(month, "August") == 0)
		return 8;
	else if (strcmp(month, "September") == 0)
		return 9;
	else if (strcmp(month, "October") == 0)
		return 10;
	else if (strcmp(month, "November") == 0)
		return 11;
	else if (strcmp(month, "December") == 0)
		return 12;
	else
		return 0;
}
 
int ItsName(char* fullName) {
	int length = strlen(fullName);
	int count = 0;
	while (count < length) {
		if ((fullName[count] >= 'A') && (fullName[count] <= 'Z') || (fullName[count] >= 'a') && (fullName[count] <= 'z') || (fullName[count] == ' '))
			count++;
		else
			return 0;
	}
	return 1;
}

int DateCompare(person_t p1, person_t p2) {
	int number = 1;
	if (p1.year > p2.year)
		return 1;
	if (p1.year < p2.year)
		return 0;
	if (p1.year == p2.year) {
		if (NumberMonth(p1.month) < NumberMonth(p2.month))
			return 1;
		if (NumberMonth(p1.month) == NumberMonth(p2.month)) {
			if (p1.day >= p2.day)
				return 1;
			else
				return 0;

		}
		if (NumberMonth(p1.month) > NumberMonth(p2.month))
			return 0;
	}
}

char* WithoutFirst(char* str) {
	int i = 0;
	while (str[i] != '\0') {
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
	return str;
}

person_t StructureFromString(char* arr) {
	person_t person;
	person_t error = { NULL,NULL,NULL,NULL };
	char* temp = (char*)malloc(sizeof(char) * 100);
	person.month = (char*)malloc(sizeof(char) * MAX_SIZE);
	if (!person.month) {
		perror("Memory allocation error");
		return error;
	}
	person.fullName = (char*)malloc(sizeof(char) * MAX_SIZE * 3);
	if (!person.fullName) {
		perror("Memory allocation error");
		return error;
	}
	if (temp) {
		strcpy(temp, arr);
		char* help = (char*)malloc(sizeof(char) * 100);
		help = strchr(temp, ' ');
		if (!help) {
			perror("Invalid value");
			return error;
		}
		int lengthSurName = help - temp + 1;
		temp = WithoutFirst(help);
		help = strchr(temp, ' ');
		if (!help) {
			perror("Invalid value");
			return error;
		}
		int lengthName = help - temp + 1;
		temp = WithoutFirst(help);
		help = strchr(temp, ' ');
		int lengthPatronymic = help - temp + 1;
		temp = WithoutFirst(help);
		help = strchr(temp, ' ');
		if (!help) {
			perror("Invalid value");
			return error;
		}
		int count = 0;
		int countM = 0;
		int lengthMonth = help - temp + 1;
		while (countM < lengthMonth) {
			person.month[countM] = temp[count];
			countM++;
			count++;
		}
		person.month[countM-1] = '\0';
		if (((temp[count + 1] & 0x0F) >= 0) && ((temp[count + 1] & 0x0F) <= 9) && ((temp[count] & 0x0F) >= 0) && ((temp[count] & 0x0F) <= 9)) {
			person.day = (temp[count] & 0x0F) * 10 + (temp[count + 1] & 0x0F);
			count += 4;
		}
		else if (((temp[count] & 0x0F) >= 0) && ((temp[count] & 0x0F) <= 9)) {
			person.day = (temp[count] & 0x0F);
			count += 3;
		}
		else {
			printf("Invalid value");
			return error;
		}
		person.year = (temp[count] & 0x0F) * 1000 + (temp[count + 1] & 0x0F) * 100 + (temp[count + 2] & 0x0F) * 10 + (temp[count + 3] & 0x0F);
		if ((person.year <= 0) && (person.year >= 3000)) {
			printf("Invalid value");
			return error;
		}
		int lengthFullName = lengthSurName + lengthName + lengthPatronymic;
		int countF = 0;
		count = 0;
		while (countF < lengthFullName) {
			person.fullName[countF] = arr[count];
			countF++;
			count++;
		}
		person.fullName[countF-1] = '\0';
		if (NumberMonth(person.month) == 0) {
			printf("Invalid value");
			return error;
		}
		if (ItsName(person.fullName) == 0) {
			printf("Invalid value");
			return error;
		}
		return person;
	}
	else {
		perror("Memory allocation error");
		return error;
	}
}

person_t FileRead(FILE* file) { //считывание одной строки 
	char* arr, * help;
	int a;
	person_t MemoryError = { '-1',-1,'-1',-1 };
	arr = malloc(sizeof(char));
	if (arr) {
		person_t null = { '0',0,'0',0 };
		person_t person;
		//person_t person = { '1', '1', 1, 1 };
		int i = 0;
		a = fscanf(file, "%c", (arr + i));
		if (a == EOF) {
			return null;
		}
		do {
			i++;
			help = realloc(arr, (i + 10) * sizeof(char));
			if (help != NULL)
			{
				arr = help;
			}
			else {
				printf("Memory allocation error");
				return MemoryError;
			}
			a = fscanf(file, "%c", (arr + i));
		} while ((*(arr + i) != '\n') && (a != EOF));
		person = StructureFromString(arr);
		free(arr);
		_CrtDumpMemoryLeaks();
		return person;
	}
	else {
		printf("Memory allocation error");
		return MemoryError;
	}
}


int SearchPosition(list_t* list, person_t person) {
	list_t* temp = list;
	int n = 1;
	while (temp) {
		if (DateCompare(person, temp->person) == 0)
			return n;
		else
			n++;
		temp = temp->next;
	}
	return n;
}

list_t* AddPerson(list_t* list, person_t person) {
	int position = SearchPosition(list, person);
	list_t* newPerson = malloc(sizeof(list_t));
	newPerson->person = person;
	newPerson->next = NULL;
	if (newPerson == NULL)
	{
		perror("Memory allocation error");
		return MEMORY_ERROR;
	}
	if (list == NULL)
	{
		list = newPerson;
		return list;
	}
	list_t* temp = list;
	for (int i = 2;i < position;i++) {
		temp = temp->next;
		if (temp == NULL)
			break;
	}
	if (position == 1) {
		newPerson->next = temp;
		temp = newPerson;
		return temp;
	}
	if ((temp != NULL) && (position != 1)) {
		newPerson->next = temp->next;
		temp->next = newPerson;
		return list;
	}
}

void PrintList(list_t* list) {
	if (list) {
		PrintStr(list->person.fullName);
		printf(" ");
		PrintStr(list->person.month);
		printf(" %i", list->person.day);
		printf(", %i \n", list->person.year);
		PrintList(list->next);
	}
}

int CheckPerson(person_t person, int day, char* month, int year) {
	if (person.day == day) {
		if (strcmp(person.month,month)==0) {
			if (person.year == year) {
				return 1;
			}
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}

int CheckList(list_t* list, int day, char* month, int year) {
	list_t* temp = list;
	int n = 0;
	if (list == NULL) {
		printf("Empty list");
	}
	printf("These person have a birthday on this day: \n");
	while (temp) {
		if (CheckPerson(temp->person, day, month, year) == 1) {
			PrintStr(temp->person.fullName);
			printf("\n");
			n++;
		}
		temp = temp->next;
	}
	if (n == 0) {
		printf(":(");
	}
	return n;
}