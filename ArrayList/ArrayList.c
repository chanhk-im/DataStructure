#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

ArrayList *ListInit()
{
    ArrayList *plist = (ArrayList *)malloc(sizeof(ArrayList));

    plist->capacity = 10;
    plist->length = 0;
    plist->elements = (int *)calloc(plist->capacity, sizeof(int));

    return plist;
}

void LInsert(ArrayList *plist, int data)
{
    if (plist->capacity <= plist->length)
    {
        plist->capacity *= 2;
        realloc(plist->elements, sizeof(int) * (plist->capacity));
    }

    plist->elements[plist->length] = data;
    plist->length++;
}

int LDelete(ArrayList *plist, int pos, int *e)
{
    if (plist->length <= pos)
        return FALSE;
    
    *e = plist->elements[pos];

    for (int i = pos; i < plist->length - 1; i++)
        plist->elements[i] = plist->elements[i + 1];
    
    plist->length--;

    if ((plist->capacity) / 2 > plist->length && plist->capacity > 10)
    {
        plist->capacity /= 2;
        realloc(plist->elements, sizeof(int) * (plist->capacity));
    }

    return TRUE;
}

int LSearch(ArrayList *plist, int pos, int *e)
{
    if (plist->length <= pos)
        return FALSE;

    *e = plist->elements[pos];
    return TRUE;
}

int ListLength(ArrayList *plist)
{
    return plist->length;
}