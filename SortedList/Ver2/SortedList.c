#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SortedList.h"

sortedlist_t *sortedlist_alloc()
{
	sortedlist_t *new_list = (sortedlist_t *)malloc(sizeof(sortedlist_t));
	new_list->capacity = 10;
	new_list->length = 0;
	new_list->elements = (int *)calloc(new_list->capacity, sizeof(int));

	return new_list;
}

void sortedlist_insert(sortedlist_t *l, int e)
{
	if (l->length >= l->capacity)
	{
		l->capacity *= 2;
		l->elements = (int *)realloc(l->elements, sizeof(int) * l->capacity);
	}

	int i;
	l->elements[l->length] = e;
	
	for (i = l->length; i > 0; i--)
	{
		if (l->elements[i - 1] > l->elements[i])
		{
			int tmp;
			tmp = l->elements[i - 1];
			l->elements[i - 1] = l->elements[i];
			l->elements[i] = tmp;
		}
		else
			break;
	}
	l->length += 1;
}

int sortedlist_retrieve(sortedlist_t *l, int pos, int *e)
{
	if (l->length <= pos)
		return FALSE;
	
	*e = l->elements[pos];
	return TRUE;
}

int sortedlist_length(sortedlist_t *l)
{
	return l->length;
}

int sortedlist_pop(sortedlist_t *l, int *e)
{
	if (l->length == 0)
		return FALSE;

	*e = l->elements[0];
	l->length -= 1;

	for (int i = 1; i <= l->length; i++)
		l->elements[i - 1] = l->elements[i];

	if (l->length * 4 <= l->capacity)
	{
		l->capacity = l->length * 2;
		l->elements = (int *)realloc(l->elements, sizeof(int) * l->capacity);
	}

	return TRUE;
}

int sortedlist_lookup(sortedlist_t *l, int e)
{
	for (int i = 0; i < l->length; i++)
	{
		if (l->elements[i] == e)
			return i;
	}

	return -1;
}

sortedlist_t *sortedlist_merge(sortedlist_t *l1, sortedlist_t *l2)
{
	sortedlist_t *lm = (sortedlist_t *)malloc(sizeof(sortedlist_t));
	lm->capacity = l1->length + l2->length;
	lm->length = lm->capacity;
	lm->elements = (int *)calloc(lm->capacity, sizeof(int));

	memcpy((void *)lm->elements, (void *)l1->elements, sizeof(int) * l1->length);
	memcpy((void *)(lm->elements + l1->length), (void *)(l2->elements), sizeof(int) * l2->length);

	int i;
	for (i = l1->length; i < lm->length; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (lm->elements[i - 1] > lm->elements[i])
			{
				int tmp;
				tmp = lm->elements[i - 1];
				lm->elements[i - 1] = lm->elements[i];
			}
			else
				break;
		}
	}

	return lm;
}
