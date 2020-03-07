#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

typedef struct _arrayList
{
	int capacity;
	int length;
	int *elements;
} ArrayList;

ArrayList *ListInit();
int LInsert(ArrayList *plist, int data);
int LDelete(ArrayList *plist, int data);
int LSearch(ArrayList *plist, int pos, int *e);
int ListLength(ArrayList *plist);
int LDeleteFirst(ArrayList *plist, int *e);

#endif
