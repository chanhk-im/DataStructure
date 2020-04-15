#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack.h"

void print_stack(stack *st)
{
    int i;
    for (i = 0; i < get_size(st); i++)
    {
        int num;
        get_element(st, i, &num);
        printf("[%d]", num);
    }
    printf(".\n");
}

int main()
{
    stack *st;
    st = create_stack(100, sizeof(int));

    char token[8];
    do
    {
        print_stack(st);

        scanf("%s", token);
        printf("> input %s\n", token);

        if (token[0] == ';')
            break;

        if (isdigit(token[0]))
        {
            int num = atoi(token);
            push(st, &num);
        }
        else
        {
            if (token[0] == '+')
            {
                int n1, n2, res;
                pop(st, &n2);
                pop(st, &n1);

                res = n1 + n2;
                push(st, &res);
            }
            else if (token[0] == '-')
            {
                int n1, n2, res;
                pop(st, &n2);
                pop(st, &n1);

                res = n1 - n2;
                push(st, &res);
            }
            else if (token[0] == '*')
            {
                int n1, n2, res;
                pop(st, &n2);
                pop(st, &n1);

                res = n1 * n2;
                push(st, &res);
            }
            else if (token[0] == '/')
            {
                int n1, n2, res;
                pop(st, &n2);
                pop(st, &n1);

                res = n1 / n2;
                push(st, &res);
            }
        }
        
        
    } while (token[0] != ';');

    int res;
    pop(st, &res);
    printf("%d", res);
    delete_stack(st);
    return 0;
}