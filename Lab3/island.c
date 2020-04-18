#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    void *buffer;
    int unit;
    int capacity;
    int front;
    int rear;
    int full;
} queue;

typedef struct _task
{
    int x;
    int y;
    int m;
} Task;

int is_full(queue *que);
int is_empty(queue *que);

queue *
create_queue(int capacity, int unit)
{
    queue *que = malloc(sizeof(queue));
    que->capacity = capacity;
    que->unit = unit;
    que->buffer = calloc(capacity, unit);
    que->front = 0;
    que->rear = 0;
    que->full = 0;
    return que;
}

void delete_queue(queue *que)
{
    if (que->buffer != 0x0)
        free(que->buffer);
    free(que);
}

int enqueue(queue *que, void *elem)
{
    if (is_full(que))
        return 1;

    memcpy(que->buffer + ((que->rear) * (que->unit)), elem, que->unit);
    que->rear = (que->rear + 1) % que->capacity;

    if (que->rear == que->front)
        que->full = 1;

    return 0;
}

int dequeue(queue *que, void *elem)
{
    if (is_empty(que))
        return 1;

    memcpy(elem, que->buffer + que->front * que->unit, que->unit);
    que->front = (que->front + 1) % que->capacity;
    que->full = 0;

    return 0;
}

int is_empty(queue *que)
{
    return (que->front == que->rear) && (que->full == 0);
}

int is_full(queue *que)
{
    return que->full;
}

void print_queue(queue *que, void (*print_element)(void *elem))
{
    int i;
    if (que->front == que->rear && que->full == 0)
        return;

    for (i = que->front; i != que->rear; i = (i + 1) % (que->capacity))
    {
        printf("[");
        print_element(que->buffer + i * que->unit);
        printf("] ");
    }
    printf("\n");
}

int land[20][20];
int visited[20][20];

int main()
{
    int h, w;
    int i_cnt = 0;
    int area_cnt = 0, max_area = 0, min_area = 400;

    int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    scanf("%d %d", &w, &h);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
            scanf("%d", &land[i][j]);
    }

    queue *tasks = create_queue(h * w, sizeof(Task));

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (visited[i][j])
                continue;

            visited[i][j] = 1;
            if (land[i][j])
            {
                Task task_init;
                task_init.x = j;
                task_init.y = i;
                task_init.m = 0;
                enqueue(tasks, &task_init);

                area_cnt = 0;
                while (!is_empty(tasks))
                {
                    Task curr;
                    dequeue(tasks, &curr);
                    area_cnt += 1;

                    for (int k = 0; k < 4; k++)
                    {
                        Task next;
                        next.x = curr.x + d[k][1];
                        next.y = curr.y + d[k][0];

                        if (0 <= next.x && next.x < w)
                        {
                            if (0 <= next.y && next.y < h)
                            {
                                if (!visited[next.y][next.x] && land[next.y][next.x])
                                {
                                    visited[next.y][next.x] = 1;
                                    enqueue(tasks, &next);
                                }
                            }
                        }
                    }
                }

                i_cnt += 1;
                if (max_area < area_cnt)
                    max_area = area_cnt;
                
                if (area_cnt < min_area)
                    min_area = area_cnt;
            }
            
        }
    }
    printf("%d %d %d\n", i_cnt, min_area, max_area);
    delete_queue(tasks);
    return 0;
}