#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int d[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

typedef struct _pos
{
    int x;
    int y;
} Position;

typedef struct _task
{
    Position pos;
    int dept;
} Task;

int visited[8][8];
Position ancestor[8][8];

int main()
{
    Position start, end;
    scanf("%d %d", &start.y, &start.x);
    scanf("%d %d", &end.y, &end.x); 

    queue *tasks = create_queue(64, sizeof(Task));

    Task init;
    init.pos = start;
    init.dept = 0;
    enqueue(tasks, &init);

    while (!is_empty(tasks))
    {
        Task curr;
        dequeue(tasks, &curr);

        if (curr.pos.x == end.x && curr.pos.y == end.y)
        {
            printf("%d\n", curr.dept);
            printf("(%d, %d)\n", curr.pos.y, curr.pos.x);
            while (curr.dept > 0)
            {
                curr.pos = ancestor[curr.pos.y][curr.pos.x];
                curr.dept -= 1;
                printf("(%d, %d)\n", curr.pos.y, curr.pos.x);
            }
            return 0;
        }

        for (int i = 0; i < 8; i++)
        {
            Task next;
            next.pos.y = curr.pos.y + d[i][0];
            next.pos.x = curr.pos.x + d[i][1];
            next.dept = curr.dept + 1;

            if (0 <= next.pos.x && next.pos.x < 8)
            {
                if (0 <= next.pos.y && next.pos.y < 8)
                {
                    if (!visited[next.pos.y][next.pos.x])
                    {
                        enqueue(tasks, &next);
                        visited[next.pos.y][next.pos.x] = 1;
                        ancestor[next.pos.y][next.pos.x] = curr.pos;
                    }
                }
            }
        }
    }

    printf("unreachable\n");
    delete_queue(tasks);
    return 0;
}