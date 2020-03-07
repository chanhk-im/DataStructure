#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

int main()
{
    ArrayList *list = ListInit();

    LInsert(list, 2);
    LInsert(list, 3);
    LInsert(list, 5);
    LInsert(list, 7);
    LInsert(list, 11);
    LInsert(list, 13);
    LInsert(list, 17);
    LInsert(list, 19);

    int e;
    if (!LSearch(list, 3, &e))
    {
        fprintf(stderr, "Error");
        return 1;
    }
    printf("%d\n", e);

    while (ListLength(list) > 0)
    {
        if (!LDelete(list, 0, &e))
        {
            fprintf(stderr, "Error");
            return 1;
        }
        printf("%d %d\n", e, list->capacity);
    }

    printf("\n");
    return 0;
}