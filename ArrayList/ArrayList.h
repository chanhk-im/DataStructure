#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#define TRUE 1
#define FALSE 0

typedef struct _arrayList
{
	int capacity;
	int length;
	int *elements;
} ArrayList;

ArrayList *ListInit();
void LInsert(ArrayList *plist, int data);
int LDelete(ArrayList *plist, int pos, int *e);
int LSearch(ArrayList *plist, int pos, int *e);
int ListLength(ArrayList *plist);

#endif