#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

/*****************/

int main()
{
    stack *st;
    st = create_stack(100, sizeof(int));

    char tok[8];
    do
    {
        scanf("%s", tok);

        if (tok[0] == ';')
            break;

        if (isdigit(tok[0]))
        {
            int num = atoi(tok);
            push(st, &num);
        }
        else /* operator */
        {
            if (get_size(st) <= 1)
            {
                printf("invalid\n");
                return 0;
            }

            switch (tok[0])
            {
            case '+':
            {
                int n1, n2, res;
                pop(st, &n2);
                pop(st, &n1);
                res = n1 + n2;
                push(st, &res);
                break;
            }

            case '-':
            {
                int n1, n2, res;
                pop(st, &n2);
                pop(st, &n1);
                res = n1 - n2;
                push(st, &res);
                break;
            }

            case '*':
            {
                int n1, n2, res;
                pop(st, &n2);
                pop(st, &n1);
                res = n1 * n2;
                push(st, &res);
                break;
            }

            case '/':
            {
                int n1, n2, res;
                pop(st, &n2);
                pop(st, &n1);

                if (n2 == 0)
                {
                    printf("undefined\n");
                    return 0;
                }

                res = n1 / n2;
                push(st, &res);
                break;
            }
            case '^':
            {
                int n1, n2, res;
                pop(st, &n2);
                pop(st, &n1);

                if (n2 < 0)
                {
                    printf("undefined\n");
                    return 0;
                }

                res = 1;
                for (int i = 0; i < n2; i++)
                    res *= n1;
                
                push(st, &res);
                break;
            }
            case '~':
            {
                int n, res;
                pop(st, &n);

                res = -n;
                push(st, &res);
                break;
            }
            default:
            {
                printf("invalid\n");
                return 0;
            }
            }
        }
    } while (tok[0] != ';');

    if (get_size(st) > 1)
    {
        printf("invalid\n");
        return 0;
    }

    int result;
    pop(st, &result);
    printf("%d\n", result);

    delete_stack(st);
    return 0;
}