#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

#define TRUE 1
#define FALSE 0

typedef struct Tree
{
	int key;
	struct Tree  * left, * right;
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


tree_t* RightRotate(tree_t* tree)
{
	tree_t* tmp = tree->left;
	tree->left = tmp->right;
	tmp->right = tree;
	return tmp;
}

tree_t* LeftRotate(tree_t* tree)
{
	tree_t* tmp= tree->right;
	tree->right = tmp->left;
	tmp->left = tree;
	return tmp;
}

tree_t* Splay(tree_t* tree, int value)
{

	if (!tree)
		return tree;
	if (tree->key == value)
		return tree;
	if (tree->key > value)
	{
		if (!tree->left) 
			return tree;

		if (tree->left->key > value)
		{
			tree->left->left = Splay(tree->left->left, value);
			tree = RightRotate(tree);
		}
		else if (tree->left->key < value) 
		{
			tree->left->right = Splay(tree->left->right, value);

			if (tree->left->right)
				tree->left = LeftRotate(tree->left);
		}
		if (!tree->left)
			return tree;
		else
			return RightRotate(tree);
	}
	else 
	{
		if (!tree->right)
			return tree;

		if (tree->right->key > value)
		{
			tree->right->left = Splay(tree->right->left, value);

			if (tree->right->left)
				tree->right = RightRotate(tree->right);
		}
		else if (tree->right->key < value)
		{
			tree->right->right = Splay(tree->right->right, value);
			tree = LeftRotate(tree);
		}

		if (!tree->right)
			return tree;
		else
			return LeftRotate(tree);
	}
}

tree_t* Remove(tree_t* tree, int value)
{
	if (!tree)
		return NULL;
	tree_t* tmp;
	tree = Splay(tree, value);
	if (tree->key != value)
		return tree;
	tmp = tree;
	if (!tree->left)
	{
		tree = tree->right;
	}
	else
	{
		tree = Splay(tree->left, value);
		tree->right = tmp->right;
	}
	return tree;
}

tree_t* Find(tree_t* t, int key) {
	tree_t* temp = NULL;
	if (t == NULL)
		return NULL;
	if (t->key == key)
		return t;
	else {
		if (key < t->key)
			temp = Find(t->left, key);
		else
			temp = Find(t->right, key);
	}
	return temp;
}


void PrintTree(tree_t* tree, int x)
{
	int i;
	if (tree)
	{
		PrintTree(tree->right, x + 1);
		for (i = 0; i < x; i++)
			printf("       ");
		printf("%i\n", tree->key); 
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
	char func;
	int value; 
	tree_t* tree = NULL;
	while (fscanf(stdin, "%c %i", &func, &value))
	{
		switch(func)
		{
			case 'a':
				tree = Add(tree, value);
				break;
			case 'r':
				tree=Remove(tree, value);
				break;
			case 'f':
				tree = Splay(tree, value);
				if(tree->key==value)
					printf("yes\n");
				else
					printf("no\n");
				break;

		}

	
	}


	DestroyTree(tree);
}