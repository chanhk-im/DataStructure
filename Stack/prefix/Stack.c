#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

stack *create_stack(int capacity, int unit)
{
	stack *newStack = (stack *)malloc(sizeof(stack));
	newStack->unit = unit;
	newStack->capacity = capacity;
	newStack->top = 0;
	newStack->buffer = (char *)calloc(newStack->capacity, newStack->unit);
	
	return newStack;
}

void delete_stack(stack *stack)
{
	if (stack->buffer != NULL)
		free(stack->buffer);

	free(stack);
}

int push(stack *stack, void *elem)
{
	if (is_full(stack))
		return FALSE;

	memcpy(stack->buffer + stack->top * stack->unit, elem, stack->unit);
	stack->top += 1;
	return TRUE;
}

int pop(stack *stack, void *elem)
{
	if (is_empty(stack))
		return FALSE;

	memcpy(elem, stack->buffer + (stack->top - 1) * stack->unit, stack->unit);
	stack->top -= 1;
	return TRUE;
}

int is_empty(stack *stack)
{
	return (stack->top == 0);
}

int is_full(stack *stack)
{
	return (stack->top == stack->capacity);
}

int get_size(stack *stack)
{
	return stack->top;
}

int get_element(stack *stack, int index, void *elem)
{
	if (stack->top <= index)
		return FALSE;

	memcpy(elem, stack->buffer + index * stack->unit, stack->unit);
	return TRUE;
}

