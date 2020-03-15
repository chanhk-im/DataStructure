#ifndef __LINKED_LIST_VER_1__
#define __LINKED_LIST_VER_1__

typedef struct _node
{
	int element;
	struct _node *tail;
} Node;

typedef Node *LinkedList;

LinkedList ListAlloc();
void ListPush(LinkedList *l, int e);
int ListRetrieve(LinkedList l, int pos, int *e);
int ListLength(LinkedList l);
int ListPop(LinkedList *l, int *e);
int ListRemove(LinkedList l, int e);

#endif
