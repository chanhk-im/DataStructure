#include <stdio.h>
#include <stdlib.h>
#include "LinkedListVer1.h"

int main()
{
	LinkedList list = ListAlloc();

	ListPush(&list, 1);
	ListPush(&list, 2);
	ListPush(&list, 3);
	ListPush(&list, 4);
	ListPush(&list, 6);
	ListPush(&list, 12);

	int value;
	if (ListRetrieve(list, 2, &value))
		printf("2 %d\n", value);
	else
		printf("The index 2 is not exist!\n");

	if (ListRetrieve(list, 4, &value))
		printf("4 %d\n", value);
	else
		printf("The index 4 is not exist!\n");

	if (ListRetrieve(list, 7, &value))
		printf("7 %d\n", value);
	else
		printf("The index 7 is not exist!\n");

	if (!ListPop(&list, &value))
		return 1;

	for (int i = 0; i < ListLength(list); i++)
	{
		if (!ListRetrieve(list, i, &value))
			return 1;

		printf("%d ", value);
	}
	printf("\n");

	if (!ListRemove(list, 3))
		return 1;

	for (int i = 0; i < ListLength(list); i++)
	{
		if (!ListRetrieve(list, i, &value))
			return 1;

		printf("%d ", value);
	}
	printf("\n");

	return 0;
}
