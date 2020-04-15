#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct
{
	char *buffer;
	int unit;
	int capacity;
	int top;
} stack;

int is_empty(stack *stack);
int is_full(stack *stack);

stack * 
create_stack (int capacity, int unit) 
{
	stack * st = malloc(sizeof(stack)) ;
	st->capacity = capacity ;
	st->unit = unit ;
	st->top = 0 ;
	st->buffer = calloc(capacity, unit) ;
	return st ;
}

void
delete_stack (stack * st) 
{
	if (st->buffer != 0x0)
		free(st->buffer) ;
	free(st) ;
}

int 
push (stack * st, void * elem)
{
	if (is_full(st))
		return 1 ;

	memcpy(st->buffer + ((st->top) * (st->unit)), elem, st->unit) ;
	st->top += 1 ;

	return 0 ;
}

int
pop (stack * st, void * elem)
{
	if (is_empty(st)) 
		return 1 ;
	
	memcpy(elem, st->buffer + (st->top - 1) * st->unit, st->unit) ;
	st->top -= 1 ;
	return 0;
}

int 
is_empty (stack * st) 
{
	return (st->top == 0) ;
}

int 
is_full (stack * st) 
{
	return (st->top == st->capacity) ;
}

int
get_size (stack * st) 
{
	return st->top ;
}

int
get_element (stack * st, int index, void * elem)
{
	if (st->top <= index)
		return 1 ;

	memcpy(elem, st->buffer + index * st->unit, st->unit) ;
	return 0 ;
}

int main()
{
	int n, c;
	scanf("%d %d", &n, &c);
	int num[n];
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);

	stack *start = create_stack(n, sizeof(int));
	stack *station = create_stack(c, sizeof(int));
	for (int i = n; i > 0; i--)
		push(start, &i);

	int start_c;
	int stati_c;
	int answer = 1;
	int i = 0;
	
	while (TRUE)
	{
		if (!is_empty(start))
		{
			get_element(start, get_size(start) - 1, &start_c);

			if (start_c == num[i])
			{
				pop(start, &start_c);
				i += 1;
				continue;
			}
			else if (!is_empty(station))
			{
				get_element(station, get_size(station) - 1, &stati_c);
				if (stati_c == num[i])
				{
					pop(station, &stati_c);
					i += 1;
					continue;
				}
				else if (stati_c > num[i])
				{
					answer = FALSE;
					break;
				}
				else if (is_full(station))
				{
					answer = FALSE;
					break;
				}
			}

			pop(start, &start_c);
			push(station, &start_c);
		}
		else
		{
			if (is_empty(station))
			{
				answer = TRUE;
				break;
			}
			else
			{
				get_element(station, get_size(station) - 1, &stati_c);
				if (stati_c == num[i])
				{
					pop(station, &stati_c);
					i += 1;
					continue;
				}
				else
				{
					answer = FALSE;
					break;
				}
			}
		}
	}
	
	if (answer)
		printf("true\n");
	else
		printf("false\n");

	return 0;
}
