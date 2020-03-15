#include <stdio.h>
#include <stdlib.h>
#include "LinkedListVer1.h"

LinkedList ListAlloc()
{
	return NULL;
}

void ListPush(LinkedList *l, int e)
{
	LinkedList newList = (LinkedList)malloc(sizeof(Node));

	newList->element = e;
	newList->tail = *l;
	*l = newList;
}

int ListRetrieve(LinkedList l, int pos, int *e)
{
	LinkedList t = l;

	for (int i = 0; i < pos; i++)
	{
		if (t->tail == NULL)
			return 0;

		t = t->tail;
	}

	*e = t->element;
	return 1;
}

int ListLength(LinkedList l)
{
	int count = 0;
	LinkedList t = l;

	while (t != NULL)
	{
		t = t->tail;
		count++;
	}

	return count;
}
int ListPop(LinkedList *l, int *e)
{
	if (*l == NULL)
		return 0;

	LinkedList t = (*l)->tail;

	*e = (*l)->element;
	free(*l);
	*l = t;
	return 1;
}
int ListRemove(LinkedList l, int e)
{
	LinkedList t = l;

	while (t->tail != NULL)
	{
		if (t->tail->element == e)
		{
			LinkedList r = t->tail;
			t->tail = t->tail->tail;
			free(r);
			return 1;
		}
		t = t->tail;	
	}

	return 0;
}
