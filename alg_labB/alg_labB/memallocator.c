#include"memallocator.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct Descriptor
{
	int size;
	char isFree; // 1- isFree, else 0
	struct Descriptor* next;
}descriptor_t;

descriptor_t* head = NULL;
descriptor_t* fromHere = NULL;

int memorySize = 0;

descriptor_t* GetPrevBlock(descriptor_t* block)
{
	if (block == NULL)
	{
		return NULL;
	}
	if (block == head)
	{
		return NULL;
	}
	if (head == NULL)
	{
		return NULL;
	}
	descriptor_t* desc = head;

	while (desc->next != NULL)
	{
		if (desc->next == block)
			return desc;
		desc = desc->next;
	}
	return NULL;
}

void MergeBlocks(descriptor_t* block)
{
	if (block && (block->isFree == 1) && block->next && (block->next->isFree == 1))
	{
		descriptor_t* secondBlock = block->next;
		block->next = secondBlock->next;
		block->size = block->size + sizeof(descriptor_t) + secondBlock->size;
		block->isFree = 1;
	}
}

descriptor_t* FindBlock(int size)
{
	descriptor_t* desc = fromHere;
	while (desc)
	{
		if ((desc->size >= size) && (desc->isFree == 1))
		{
			fromHere = desc->next;
			if (fromHere == NULL)
				fromHere = head;
			return desc;
		}
		desc = desc->next;
	}
	desc = head;
	while (desc != fromHere)
	{
		if ((desc->size >= size) && (desc->isFree == 1))
		{
			fromHere = desc->next;
			if (fromHere == NULL)
				fromHere = head;
			return desc;
		}
		desc = desc->next;
	}
	return NULL;
}

int meminit(void* pMemory, int size)
{
	if (!pMemory || size < sizeof(descriptor_t))
		return 1;

	head = (descriptor_t*)pMemory;
	head->next = NULL;
	head->size = size - sizeof(descriptor_t);
	head->isFree = 1;
	memorySize = size;
	fromHere = head;
	return 0;
}


void* memalloc(int size)
{
	if (size <= 0 || head == NULL)
	{
		return NULL;
	}
	int blockSize;
	descriptor_t* desc, * descLastBlock;

	desc = FindBlock(size);
	if (desc == NULL)
		return NULL;
	else
	{
		blockSize = desc->size;
		desc->size = size;
		desc->isFree = 0;
		if (blockSize - size > sizeof(descriptor_t)) {
			descLastBlock = (descriptor_t*)((char*)(desc + 1) + size);
			descLastBlock->next = desc->next;
			desc->next = descLastBlock;
			descLastBlock->size = blockSize - size - sizeof(descriptor_t);
			descLastBlock->isFree = 1;
		}
		else
		{
			desc->size = blockSize;
		}
		return (void*)(desc + 1);;
	}
}

void memfree(void* p)
{
	if (p == NULL)
	{
		return;
	}
	descriptor_t* descDeleteBlock = (descriptor_t*)p - 1;

	if (descDeleteBlock == NULL)
		return;
	if (descDeleteBlock->isFree != 0)
		return;

	descDeleteBlock->isFree = 1;

	descriptor_t* prevBlock = GetPrevBlock(descDeleteBlock);
	if (prevBlock && prevBlock->isFree == 1)
	{
		MergeBlocks(prevBlock);
		descDeleteBlock = prevBlock;
	}
	if (descDeleteBlock->next && descDeleteBlock->isFree == 1)
	{
		MergeBlocks(descDeleteBlock);
	}
}

void memdone()
{
	head = NULL;
	memorySize = 0;
}

int memgetminimumsize()
{
	return sizeof(descriptor_t);
}

int memgetblocksize()
{
	return sizeof(descriptor_t);
}
