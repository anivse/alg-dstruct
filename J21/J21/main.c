#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

typedef struct Node
{
	char* str;
	int key;
} node;


#define EMPTY 0 
#define NOT_EMPTY 1


node* map = NULL;
const int size = 15420;

void MakeMap()
{
	map = (node*)malloc(size * sizeof(node));

	if (!map)
		return;

	for (int i = 0; i < size;i++)
	{
		map[i].key = EMPTY;
		map[i].str = NULL;
	}

}

int Hash(char* str)
{
	int h = 0;

	for (int i = 0; str[i] != '\0'; i++)
		h += str[i];

	h = h % size;
	return h;
}

int LinearProb(int h, int i)
{
	return (int)(h + i) % size;
}


void Add(char* str)
{
	if (!str)
		return;
	int hash = Hash(str);

	int h;

	for (int i = 0; i < size; i++)
	{
		h = LinearProb(hash, i);

		if (map[h].key == NOT_EMPTY)
		{
			if (!strcmp(str, map[h].str))
				return;
		}
		if (!map[h].str)
		{
			int len = strlen(str);
			map[h].str = (char*)malloc((len + 1) * sizeof(char));

			if (!map[h].str)
				return;

			map[h].str[len] = '\0';
			strcpy(map[h].str, str);
			map[h].key = NOT_EMPTY;
			return;
		}

	}

	
}

int Find(char* str)
{
	if (!str)
		return 0;
	int hash = Hash(str);

	int h;

	for (int i = 0; i < size; i++)
	{
		h = LinearProb(hash, i);

		if (map[h].key == NOT_EMPTY)
		{
			if (!strcmp(str, map[h].str))
				return 1;
		}

	}

	return 0;
}

void Remove(char* str)
{
	if (!str)
		return;
	int hash = Hash(str);

	int h;

	for (int i = 0; i < size; i++)
	{
		h = LinearProb(hash, i);

		if (map[h].key == NOT_EMPTY)
		{
			if (!strcmp(str, map[h].str))
			{
				map[h].key = EMPTY;
				free(map[h].str);
				map[h].str = NULL;
				return;
			}

		}

	}
}

void DestroyMap()
{
	for (int i = 0;i < size;i++)
	{
		if (map[i].key == NOT_EMPTY)
		{
			free(map[i].str);
		}
	}
	free(map);
}

int main()
{
	MakeMap();
	char func;
	char str[1000];
	while (fscanf(stdin, "%c", &func)) {
		switch (func) {
		case 'a':
			scanf("%s", &str);
			Add(str);
			break;
		case 'r':
			scanf("%s", &str);
			Remove(str);
			break;
		case 'f':
			scanf("%s", &str);
			if (Find(str)) {
				puts("yes");
			}
			else {
				puts("no");
			}
			break;
		}
	}
	DestroyMap();
}