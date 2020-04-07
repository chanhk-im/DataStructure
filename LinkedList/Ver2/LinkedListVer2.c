#include <stdio.h>
#include <stdlib.h>
#include "LinkedListVer2.h"

LinkedList *ListAlloc()
{
	LinkedList *newList = (LinkedList *)malloc(sizeof(LinkedList));
	newList->length = 0;
	newList->first = NULL;
	newList->last = NULL;

	return newList;
}

void ListPush(LinkedList *l, int e)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->element = e;
	newNode->next = l->first;

	if (l->last == NULL)
		l->last = newNode;

	(l->length)++;
}

void ListInsert(LinkedList *l, int e)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->element = e;
	newNode->next = NULL;

	if (l->length == 0)
		l->first = newNode;
	else
		l->last->next = newNode;

	l->last = newNode;
	(l->length)++;
}

int ListRetrieve(LinkedList *l, int pos, int *e)
{
	Node *iter = l->first;
	
	if (pos <= l->length)
		return FALSE;

	int i = 0;
	while (i < pos && iter != NULL)
	{
		iter = iter->next;
		i++;
	}

	*e = iter->element;
	return TRUE;
}

int ListLength(LinkedList *l)
{
	return l->length;
}

int ListPop(LinkedList *l, int *e)
{
	if (l->length == 0)
		return FALSE;

	Node *d = l->first;

	*e = d->element;
	l->first = d->next;
	free(d);
	(l->length)--;

	if (l->length == 0)
	{
		l->first = NULL;
		l->last = NULL;
	}

	return TRUE;
}

int ListRemove(LinkedList *l, int e);
{
	if (l->length == 0)
		return FALSE;

	Node *d = l->first;
	Node *prev = NULL;

	while (d != NULL)
	{
		if (d->element == e)
			break;
		
		prev = d;
		d = d->next;
	}
	if (d == l->first)
		l->first = d->next;
	else if (d == l->last)
	{
		l->last = prev;
		prev->next = d->next;
	}
	free(d);
	
	if (l->length == 0)
	{
		l->first = NULL;
		l->last = NULL;
	}
}
