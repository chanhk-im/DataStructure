#ifndef __LINKED_LIST_VER_2__
#define __LINKED_LIST_VER_2__

#define TRUE 1
#define FALSE 0

typedef struct _node
{
	int element;
	struct _node *next;
} Node;

typedef struct _linkedList
{
	int length;
	Node *first;
	Node *last;
} LinkedList;

LinkedList *ListAlloc();
void ListPush(LinkedList *l, int e);
void ListInsert(LinkedList *l, int e);
int ListRetrieve(LinkedList l, int pos, int *e);
int ListLength(LinkedList *l);
int ListPop(LinkedList *l, int *e);
int ListRemove(LinkedList *l, int e);

#endif
