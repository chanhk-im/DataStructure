#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

typedef enum
{
	UP, DOWN, LEFT, RIGHT, DONE
} dir;

enum cell {
	EMPTY, WALL, PATH
};

typedef struct {
	int x;
	int y;
	dir d;
} decision;

int X, Y;
int m[20][20];

void print_map()
{
	int i, j ;

	for (i = 0 ; i < X + 2 ; i++)
		printf("XX") ;
	printf("\n") ;
	for (i = 0 ; i < Y ; i++) {
		printf("XX") ;
		for (j = 0 ; j < X ; j++) {
			if (m[i][j] == WALL)
				printf("XX") ;
			else if (m[i][j] == PATH)
				printf("::") ;
			else
				printf("  ") ;
		}
		printf("XX\n") ;
	}
	for (i = 0 ; i < X + 2 ; i++)
		printf("XX") ;
	printf("\n") ;
}

int main()
{
	int i, j ;

	FILE * fp = fopen("maze2.txt", "r") ;
	fscanf(fp, "%d %d", &X, &Y) ;
	for (i = 0 ; i < Y ; i++) {
		for (j = 0 ; j < X ; j++) {
			fscanf(fp, "%d", &(m[i][j])) ;
		}
	}
	fclose(fp) ;

	stack *path = create_stack(400, sizeof(decision));

	decision curr, next;

	curr.x = 0;
	curr.y = 0;
	curr.d = UP;

	while (curr.x < X - 1 || curr.y < Y - 1)
	{
		if (curr.d == UP)
		{
			next.x = curr.x;
			next.y = curr.y - 1;
			next.d = UP;
		}
		else if (curr.d == DOWN)
		{
			next.x = curr.x;
			next.y = curr.y + 1;
			next.d = UP;
		}
		else if (curr.d == LEFT)
		{
			next.x = curr.x - 1;
			next.y = curr.y;
			next.d = UP;
		}
		else if (curr.d == RIGHT)
		{
			next.x = curr.x + 1;
			next.y = curr.y;
			next.d = UP;
		}
		else
		{
			pop(path, &curr);
			continue;
		}

		curr.d += 1;
		if (next.x >= 0 && next.y >= 0)
		{
			if (next.x < X && next.y < Y)
			{
				if (m[next.x][next.y] == EMPTY)
				{
					decision e;
					for (i = 0; i < get_size(path); i++)
					{
						get_element(path, i, &e);
						if (e.x == next.x && e.y == next.y)
							break;
					}
					if (i == get_size(path))
					{
						// printf("%d %d\n", curr.x, curr.y);
						push(path, &curr);
						curr = next;
					}
				}
			}
		}
	}
	curr.x = X - 1;
	curr.y = Y - 1;
	curr.d = DONE;
	push(path, &curr);

	for (i = 0; i < get_size(path); i++)
	{
		get_element(path, i, &curr);
		m[curr.x][curr.y] = PATH;
	}

	print_map();
	return 0;
}
