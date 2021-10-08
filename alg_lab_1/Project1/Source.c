#include <stdio.h>
#include <stdlib.h>
#include "lab.h"
#pragma warning(disable:4996)
int main() {
	int day, year;
	char* month = malloc(sizeof(char) * 10);
	list_t* list = NULL;
	FILE* file = fopen("names.txt", "r");
	if (file) {
		person_t person;
		person = FileRead(file);
		while ((person.day != 0) && (person.fullName != '0') && (person.month != '0') && (person.year != 0)) {
			if ((person.day < 1) || (person.day > 31)) {
				printf("Ivalid value\n");
			}
			else {
				if (NumberMonth(person.month) == 0) {
					printf("Ivalid value\n");
				}
				else {
					if ((person.day != 0) && (person.fullName != '0') && (person.month != '0') && (person.year != 0)) {

						list = AddPerson(list, person);
						/*PrintList(list);
						printf("\n");*/
					}
				}
			}
			person = FileRead(file);
		}
		if (list) {
			PrintList(list);
			fclose(file);
		}
	}
	else {
		printf("File open error");
		return FILE_ERROR;
	}

	printf("\nInput Day: ");
	scanf("%i", &day);
	printf("\nInput Month: ");
	scanf("%s", month);
	printf("\nInput Year: ");
	scanf("%i", &year);
	int n = CheckList(list, day, month, year);
	DestroyList(list);
	free(month);
	return 0;
}