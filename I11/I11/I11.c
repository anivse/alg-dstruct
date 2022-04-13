#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct Tree
{
	struct Tree* parent; // родитель 
	struct Tree* sons[4]; // сыновья узла
	int keys[3];  // ключи узла
	int length;  // количество сыновей
} tree_t;


tree_t* root = NULL;

typedef struct List {
    struct List* next;
    struct List* prev;
    tree_t* value;
} list_t;


typedef struct Pair {
    tree_t* left;
    tree_t* right;
} pair_t;




tree_t* Find(int value, tree_t* root)
{
    tree_t* tmp = root;
    if (!tmp)
        return NULL;
    while (tmp->length > 0)
    {
        if (tmp->length == 2)
            if (tmp->keys[0] < value)
                tmp = tmp->sons[1];
            else
                tmp = tmp->sons[0];
        else if (tmp->keys[1] < value)
            tmp = tmp->sons[2];
        else if (tmp->keys[0] < value)
            tmp = tmp->sons[1];
        else
            tmp = tmp->sons[0];
    }
    return tmp;
}

int Compare(const void* a, const void* b) {
    tree_t** ax = (tree_t**)a;
    tree_t** bx = (tree_t**)b;
    return (*ax)->keys[0] - (*ax)->keys[0];
}

void SonsSort(tree_t* tree)
{
    if (!tree) 
        return;
    tree_t* tmp[4];
    for (int i = 0; i < tree->length; i++) {
        tmp[i] = tree->sons[i];
    }
    qsort(tmp, tree->length, sizeof(tree_t*), Compare);

    for (int i = 0; i < tree->length; i++) {
        tree->sons[i] = tmp[i];
    }

}

int Max(tree_t* tree)
{
    tree_t* tmp = tree;
    while (tmp->length != 1)
    {
        tmp = tmp->sons[tmp->length - 1];
    }
    return tmp->keys[0];
}

void UpdateKeys(tree_t* tree) {
    
    if (!tree)
        return;
    tree_t* parent = tree->parent;
    while (parent)
    {
        for (int i = 0; i < parent->length - 1;i++)
        {
            parent->keys[i] = Max(parent->sons[i]);
        }
        parent = parent->parent;
    }
          
}                         

void SplitParent(tree_t* tree) 
{
    if (tree)
    {
        if (tree->length > 3)
        {
            tree_t* tmp = (tree_t*)malloc(sizeof(tree_t));
            if (!tmp)
                return;
            tmp->sons[0] = tree->sons[2];
            tmp->sons[1] = tree->sons[3];
            tmp->sons[2] = NULL;
            tmp->sons[3] = NULL;
            tmp->parent = tree->parent;
            tmp->length = 2;
            tmp->keys[0] = tree->keys[2];
            tree->sons[2]->parent = tmp;
            tree->sons[3]->parent = tmp;
            tree->length = 2;
            tree->sons[2] = NULL;
            tree->sons[3] = NULL;
            if (tree->parent)
            {
                tree->parent->sons[tree->length] = tmp;
                tree->length++;
                SonsSort(tree->parent);
                UpdateKeys(tree);
                SplitParent(tree->parent);
            }
            else
            {
                tree_t* newroot = (tree_t*)malloc(sizeof(tree_t));
                if (!newroot)
                    return;
                newroot->sons[0] = tree;
                newroot->sons[1] = tmp;
                newroot->sons[2] = NULL;
                newroot->sons[3] = NULL;
                newroot->parent = NULL;
                newroot->length = 2;
                newroot->keys[0] = tree->keys[1];
                tree->parent = newroot;
                tmp->parent = newroot;
                SonsSort(newroot);
                root = newroot;
            }
        }
    }
}

tree_t* Add(tree_t* tree, int value) 
{
    tree_t* newelem = (tree_t*)malloc(sizeof(tree_t));
    if (!newelem)
        return NULL;
    newelem->length = 1;
    newelem->keys[0] = value;
    newelem->sons[0] = NULL;
    newelem->sons[1] = NULL;
    newelem->sons[2] = NULL;
    newelem->sons[3] = NULL;

    
    if (!root)
    {
        root = newelem;
        return root;
    }

    tree_t* tmp = Find(value, tree);
    if (tmp->keys[0] == value) 
        return root;
    if (!tmp->parent) {
        tree_t* newroot = (tree_t*)malloc(sizeof(tree_t));
        if (!newroot)
            return NULL;
        newroot->sons[0] = tmp;
        newroot->sons[1] = newelem;
        newroot->sons[2] = NULL;
        newroot->sons[3] = NULL;
        newroot->parent = NULL;
        newroot->length = 2;
        tmp->parent = newroot;
        newelem->parent = newroot;
        SonsSort(newroot);
        root = newroot;
    }
    else {
        tree_t* p = tmp->parent;
        p->sons[p->length] = newelem;
        newelem->parent = p;
        p->length++;
        SonsSort(p);
        UpdateKeys(newelem);
        SplitParent(p);
    }
    UpdateKeys(newelem);
    return root;
}

tree_t* FindBrother(tree_t* tree) {

    tree_t* parent = tree->parent;
    if (!parent || parent->length==1) {
        return NULL;
    }

    int pos = 4;
    for (int i = 0; i < parent->length; i++) {
        if (tree == parent->sons[i]) {
            pos = i;
            break;
        }
    }

    if (pos == 0 || pos == 2) {
        return parent->sons[1];
    }
    else {
        return parent->sons[0];
    }
}

void DeleteNode(tree_t* node) {
    tree_t* parent = node->parent;
    int pos = 4;

    for (int i = 0; i < parent->length; i++) {
        if (node == parent->sons[i]) {
            pos = i;
            free(parent->sons[i]);
        }
        if (i > pos) {
            parent->sons[i - 1] = parent->sons[i];
        }
    }
    parent->length--;
    UpdateKeys(parent->sons[0]);
}

tree_t* Remove(tree_t* tree, int value) {

    if (!tree)
        return NULL;
    tree_t* tmp = Find(value, tree);
    if (!tmp) 
        return NULL;

    if (tmp->keys[0] != value) 
        return root;

    tree_t* parent = tmp->parent;

    if (!parent) {
        free(tree);
        root = NULL;
    }
    else {
        if (parent->length == 2) {
            tree_t* brotherparent = FindBrother(parent);
            if (!brotherparent) {
                DeleteNode(tmp);
                parent->sons[0]->parent = NULL;
                root = parent->sons[0];
            }
            else {
                tree_t* brother = FindBrother(tmp);
                brotherparent->sons[brotherparent->length] = brother;
                brother->parent = brotherparent;
                brotherparent->length++;
                parent->length = 1;
                parent->keys[0] = value;
                SonsSort(brotherparent);
                Remove(tree, value);
                UpdateKeys(brother);
                SplitParent(brotherparent);
                UpdateKeys(brother);
            }
        }
        if (parent->length > 2) {
            DeleteNode(tmp);
            return root;
        }
    }
    return root;
}

int Height(tree_t* tree) {
    int height = 0;
    while (tree->length != 1) {
        height++;
        tree = tree->sons[0];
    }
    return height;
}


tree_t* Merge(tree_t* left, tree_t* right) {
    
    if (!left) 
        return right;
    
    if (!right) 
        return left;
    
    int heightr = Height(right);
    int heightl = Height(left);

    if (heightr == heightl) {
        tree_t* newroot = (tree_t*)malloc(sizeof(tree_t));
        if (!newroot)
            return NULL;
        newroot->length = 2;
        newroot->sons[0] = left;
        left->parent = newroot;
        newroot->sons[1] = right;
        right->parent = newroot;
        UpdateKeys(right);
        return newroot;
    }

    tree_t* tmp;
    if (heightr > heightl) {
        tmp = right;
        while (abs(heightr - Height(tmp)) > 1) {
            tmp = tmp->sons[0];
        }
        right->sons[right->length] = left;
        right->length++;
        left->parent = right;
        SonsSort(right);
        UpdateKeys(left);
        tree_t* newroot = right;
        SplitParent(right);
        return newroot;
    }
    else {
        tmp = left;
        while (abs(heightl - Height(tmp)) > 1) {
            tmp = tmp->sons[0];
        }
        left->sons[left->length] = right;
        left->length++;
        right->parent = left;
        SonsSort(left);
        UpdateKeys(right);
        tree_t* newroot = left;
        SplitParent(left);
        return newroot;
    }

}

list_t* AddInList(list_t* list, tree_t* value) {
    list_t* node = (list_t*)malloc(sizeof(list_t));
    if (!node)
        return NULL;
    list->next = node;
    node->next = NULL;
    node->prev = list;
    node->value = value;
    return node;
}


pair_t Split(tree_t* tree, int value) {


    list_t* leftlist = (list_t*)malloc(sizeof(list_t));
    list_t* rightlist = (list_t*)malloc(sizeof(list_t));

    pair_t null = { NULL,NULL };
    if (!leftlist || !rightlist)
        return null;

    list_t* leftptr = leftlist;
    list_t* rightptr = rightlist;

    while (tree->length != 1) {
        if (tree->length == 2) {
            if (value <= tree->keys[0]) {
                rightptr = AddInList(rightptr, tree->sons[1]);
                tree = tree->sons[0];
            }
            else {
                leftptr = AddInList(leftptr, tree->sons[0]);
                tree = tree->sons[1];
            }
        }
        else if (value <= tree->keys[0]) {
            rightptr = AddInList(rightptr, tree->sons[1]);
            rightptr = AddInList(rightptr, tree->sons[2]);
            tree = tree->sons[0];
        }
        else if (value <= tree->keys[1]) {
            leftptr = AddInList(leftptr, tree->sons[0]);
            rightptr = AddInList(rightptr, tree->sons[2]);
            tree = tree->sons[1];
        }

        else {
            leftptr = AddInList(leftptr, tree->sons[0]);
            leftptr = AddInList(leftptr, tree->sons[1]);
            tree = tree->sons[2];
        }
    }
    leftptr = AddInList(leftptr, tree);

    tree_t* left = NULL;
    tree_t* right = NULL;
    leftptr = leftlist->next;

    while (rightptr != rightlist) {
        right = Merge(right, rightptr->value);
        rightptr = rightptr->prev;
    }
    while (leftptr) {
        left = Merge(left, leftptr->value);
        leftptr = leftptr->next;
    }
    
    pair_t pair;
    pair.left = left;
    pair.right = right;
    return pair;
}

int main()
{
    char func;
    int value;
    tree_t* tree = NULL;
    tree_t* node = NULL;
    while (fscanf(stdin, "%c %i", &func, &value))
    {
        switch (func)
        {
        case 'a':
            tree = Add(tree, value);
            break;
        case 'r':
            tree = Remove(tree, value);
            break;
        case 'f':
            node = Find(value, tree);
            if (node->keys[0] == value)
                printf("yes\n");
            else
                printf("no\n");
            break;

        }

    }
}