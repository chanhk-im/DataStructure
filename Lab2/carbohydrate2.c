#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int OPEN = -1;

typedef struct
{
    char *buffer;
    int unit;
    int capacity;
    int top;
} stack;

int is_empty(stack *stack);
int is_full(stack *stack);

char b[101];

stack *
create_stack(int capacity, int unit)
{
    stack *st = malloc(sizeof(stack));
    st->capacity = capacity;
    st->unit = unit;
    st->top = 0;
    st->buffer = calloc(capacity, unit);
    return st;
}

void delete_stack(stack *st)
{
    if (st->buffer != 0x0)
        free(st->buffer);
    free(st);
}

int push(stack *st, void *elem)
{
    if (is_full(st))
        return 1;

    memcpy(st->buffer + ((st->top) * (st->unit)), elem, st->unit);
    st->top += 1;

    return 0;
}

int pop(stack *st, void *elem)
{
    if (is_empty(st))
        return 1;

    memcpy(elem, st->buffer + (st->top - 1) * st->unit, st->unit);
    st->top -= 1;
    return 0;
}

int is_empty(stack *st)
{
    return (st->top == 0);
}

int is_full(stack *st)
{
    return (st->top == st->capacity);
}

int get_size(stack *st)
{
    return st->top;
}

int get_element(stack *st, int index, void *elem)
{
    if (st->top <= index)
        return 1;

    memcpy(elem, st->buffer + index * st->unit, st->unit);
    return 0;
}

void print_stack(stack *st)
{
    int i;
    for (i = 0; i < get_size(st); i++)
    {
        int num;
        get_element(st, i, &num);
        if (num == OPEN)
            printf("[(]");
        else
            printf("[%d]", num);
    }
    printf(".\n");
}

int main()
{
    stack *st = create_stack(101, sizeof(int));
    char formula[101];

    int o = OPEN;

    scanf("%s", formula);

    for (int i = 0; i < strlen(formula) + 1; i++)
    {
        int pre, res;
        if (isdigit(formula[i]))
        {
            
        }
    }
    
}