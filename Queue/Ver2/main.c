#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"

void print_int(void *p)
{
    int *elem = (int *)p;
    printf("%d", *elem);
}

int main()
{
    int data;
    queue *que;

    que = create_queue(4, sizeof(int));

    data = 1;
    enqueue(que, &data);
    print_queue(que, print_int);

    data = 2;
    enqueue(que, &data);
    print_queue(que, print_int);

    data = 3;
    enqueue(que, &data);
    print_queue(que, print_int);

    data = 4;
    enqueue(que, &data);
    print_queue(que, print_int);

    dequeue(que, &data);
    print_queue(que, print_int);

    dequeue(que, &data);
    print_queue(que, print_int);

    data = 5;
    enqueue(que, &data);

    print_queue(que, print_int);

    delete_queue(que);
    return 0;
}