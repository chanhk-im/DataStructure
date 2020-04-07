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

char b[101];

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
	stack *bracket = create_stack(100, sizeof(char));

	int max_dept = 0;
	int cur_dept = 0;
	int ans;
	char c;

	scanf("%s", b);
	for (int i = 0; i < strlen(b); i++)
	{
		if (b[i] == '(' || b[i] == '{' || b[i] == '[' || b[i] == '<')
		{
			cur_dept += 1;
			push(bracket, &b[i]);
			if (cur_dept > max_dept)
				max_dept = cur_dept;
		}
		else
		{
			if (is_empty(bracket))
			{
				ans = -1;
				break;
			}
			pop(bracket, &c);
			if (b[i] == ')')
			{
				if (c != '(')
				{
					ans = -1;
					break;
				}
				cur_dept -= 1;
			}
			if (b[i] == '}')
			{
				if (c != '{')
				{
					ans = -1;
					break;
				}
				cur_dept -= 1;
			}
			if (b[i] == ']')
			{
				if (c != '[')
				{
					ans = -1;
					break;
				}
				cur_dept -= 1;
			}
			if (b[i] == '>')
			{
				if (c != '<')
				{
					ans = -1;
					break;
				}
				cur_dept -= 1;
			}
		}
	}

	if (ans == -1 || cur_dept > 0)
		printf("invalid");
	else
		printf("%d", max_dept);

	return 0;
}
