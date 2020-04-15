#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Stack.h"

typedef enum
{
    VALUE,
    OPEARTOR
} token_type;

typedef struct
{
    int value;
    char operator;
    token_type type;
} token_t;

void print_stack(stack *st)
{
    int i;
    token_t t;
    for (i = 0; i < get_size(st); i++)
    {
        get_element(st, i, &t);
        if (t.type == VALUE)
            printf("[%d] ", t.value);
        else
            printf("[%c] ", t.operator);
    }
    printf("\n");
}

int main()
{
    
}