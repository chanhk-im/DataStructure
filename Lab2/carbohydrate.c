#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
    NUM,
    ELEMENT,
    OPEN,
    DONE
} token_type;

typedef struct
{
    char *buffer;
    int unit;
    int capacity;
    int top;
} stack;

typedef struct
{
    int n;
    token_type type;
} token_t;

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
        token_t t;
        get_element(st, i, &t);
        if (t.type == NUM || t.type == DONE)
            printf("[%d]", t.n);
        else if (t.type == ELEMENT)
            printf("[%c]", (t.n == 1) ? 'H' : ((t.n == 12) ? 'C' : 'O'));
        else
            printf("[(]");
    }
    printf(".\n");
}

int main()
{ 
    stack *st = create_stack(101, sizeof(token_t));
    char formula[101];

    token_t o;
    o.type = OPEN;
    push(st, &o);

    scanf("%s", formula);

    for (int i = 0; i < strlen(formula) + 1; i++)
    {
        if (isdigit(formula[i]))
        {
            if (is_empty(st))
                return 1;

            token_t t;
            token_t new_t;
            int num = formula[i] - '0';
            pop(st, &t);

            if (t.type == NUM)
            {
                t.n *= 10;
                t.n += num;
                push(st, &t);
            }
            else
            {
                new_t.n = num;
                new_t.type = NUM;
                push(st, &t);
                push(st, &new_t);
            }
            
        }
        else
        {
            if (formula[i] == '(')
            {
                token_t new_t;
                new_t.type = OPEN;
                push(st, &new_t);
            }
            else if (formula[i] == ')' || formula[i] == '\0')
            {
                token_t res, top, sub_top, ssub_top;

                do
                {
                    pop(st, &top);
                    
                    if (top.type == NUM)
                    {
                        pop(st, &sub_top);
                        if (sub_top.type == NUM)
                            return 1;

                        res.n = sub_top.n * top.n;
                        res.type = DONE;
                    }
                    else if (top.type == ELEMENT || top.type == DONE)
                    {
                        pop(st, &sub_top);
                        if (sub_top.type == OPEN)
                        {
                            res = top;
                            push(st, &sub_top);
                        }
                        else
                        {
                            if (sub_top.type == NUM)
                            {
                                pop(st, &ssub_top);
                                if (ssub_top.type != ELEMENT && ssub_top.type != DONE)
                                    return 1;

                                sub_top.n = ssub_top.n * sub_top.n;
                                sub_top.type = DONE;
                            }

                            res.n = sub_top.n + top.n;
                            res.type = DONE;
                        }
                    }
                    else
                        return 1;
                    
                    pop(st, &top);
                    if (top.type != OPEN)
                        push(st, &top);

                    push(st, &res);
                } while (top.type != OPEN); 
                
            }
            else if (formula[i] == 'C')
            {
                token_t new_t;
                new_t.n = 12;
                new_t.type = ELEMENT;
                push(st, &new_t);
            }
            else if (formula[i] == 'H')
            {
                token_t new_t;
                new_t.n = 1;
                new_t.type = ELEMENT;
                push(st, &new_t);
            }
            else if (formula[i] == 'O')
            {
                token_t new_t;
                new_t.n = 16;
                new_t.type = ELEMENT;
                push(st, &new_t);
            }
        }
    }
    token_t result;
    pop(st, &result);
    printf("%d\n", result);

    delete_stack(st);
    return 0;
}