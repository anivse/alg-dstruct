
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

#define TRUE 1
#define FALSE 0

typedef struct Tree
{
	int key;
	int nLeaves;  //количество листьев поддеревьев
	struct Tree* left, * right;
} tree_t;


tree_t* Add(tree_t* tree, int value)
{
	if (!tree)
	{
		tree = (tree_t*)malloc(sizeof(tree_t));
		if (!tree)
			return NULL;
		tree->key = value;
		tree->left = NULL;
		tree->right = NULL;
		tree->nLeaves = 0;
		return tree;
	}

	if (value < tree->key)
	{
		tree->left = Add(tree->left, value);
	}
	else
	{
		tree->right = Add(tree->right, value);
	}
	return tree;
}

tree_t* Max(tree_t* tree)
{
	while (tree->right)
		tree = tree->right;
	return tree;
}

int NumberLeaves(tree_t* tree)
{
	int number = 0;
	if (!tree)
		return 0;
	if ((tree->left == NULL) && (tree->right == NULL)) {
		number = 1;
	}
	else {
		if (tree->left)
			number += NumberLeaves(tree->left);
		if (tree->right)
			number += NumberLeaves(tree->right);
	}
	tree->nLeaves = number;
	return number;
}

void Remove(tree_t** tree, int value)
{
	if (*tree)
	{
		if (value < (*tree)->key)
			Remove(&((*tree)->left), value);
		else if (value >(*tree)->key)
			Remove(&((*tree)->right), value);
		else
		{
			if ((!(*tree)->right) && (!(*tree)->left))
			  *tree=NULL;
			else if ((!(*tree)->right) && (!(*tree)->left))
			{
				(*tree)=(*tree)->left;
			}
			else if ((!(*tree)->left) && (!(*tree)->right))
			{
				(*tree) = (*tree)->right;
			}
			else
			{
				tree_t* tmp = Max((*tree)->left);
				(*tree)->key = tmp->key;
				Remove(&((*tree)->left), tmp->key);
			}
		}
	}
}


int IsInTree(tree_t* tree, int value)
{
	int result;
	if (!tree)
		return FALSE;
	while (tree)
	{
		if (!tree)
			return FALSE;
		if (tree->key == value)
			return TRUE;
		if (tree->key < value)
			tree = tree->right;
		if (tree->key > value)
			tree = tree->left;
	}
}

void PrintTree(tree_t* tree, int x)
{
	int i;
	if (tree)
	{
		PrintTree(tree->right, x + 1);
		for (i = 0; i < x; i++) 
			printf("       ");
		printf("%i (%i)\n", tree->key, tree->nLeaves); //в скобках указывается количсетво листьев поддерьевьев
		PrintTree(tree->left, x + 1);
	}

}

void DestroyTree(tree_t* tree)
{
	if (!tree)
		return;
	if (tree)
	{
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}
}

int main()
{
	tree_t* tree=NULL;
	char op;
	int value;
	int n;
	int leaves;
	while (fscanf(stdin, "%c", &op) >= 1)
	{
		if ((op == 'a') || (op == 'r') || (op == 'f'))
			fscanf(stdin, "%i", &value);
		switch (op)
		{
		case'a':
			tree = Add(tree, value);
			leaves = NumberLeaves(tree);
			break;
		case 'r':
			Remove(&tree, value);
			leaves = NumberLeaves(tree);
			break;
		case 'f':
			n = IsInTree(tree, value);
			if (n == 1)
				printf("yes\n");
			else
				printf("no\n");
			break;
		}
	}
	PrintTree(tree, 0);
	DestroyTree(tree);
}
