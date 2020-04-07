#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

int get_x(int pos)
{
	return pos % 8;
}

int get_y(int pos)
{
	return pos / 8;
}

int is_conflict(stack *st, int pos)
{
	int curr;

	for (int i = 0; i < get_size(st); i++)
	{
		get_element(st, i, &curr);

		if (get_x(pos) == get_x(curr))
			return TRUE;
		if (get_y(pos) == get_y(curr))
			return TRUE;
		if (get_y(pos) - get_x(pos) == get_y(curr) - get_x(curr))
			return TRUE;
		if (get_y(pos) + get_x(pos) == get_y(curr) + get_x(curr))
			return TRUE;
	}

	return FALSE;
}

int main()
{
	const int CNT = 8;
	stack *sol = create_stack(CNT, sizeof(int));
	
	int curr = 0;

	while (get_size(sol) < CNT)
	{
		while (curr < 64)
		{
			if (!is_conflict(sol, curr))
			{
				push(sol, &curr);
				curr = 0;
				break;
			}

			curr += 1;
		}
		if (curr == 64)
		{
			pop(sol, &curr);
			curr += 1;
		}
	}

	if (get_size(sol) == 8)
	{
		for (int i = 0; i < 8; i++)
		{
			int e;
			get_element(sol, i, &e);
			printf("(%d %d)\n", get_x(e), get_y(e));
		}
	}

	return 0;
}
