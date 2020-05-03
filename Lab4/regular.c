#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node
{
    void *element;
    struct node *left;
    struct node *right;
};

typedef struct node node_t;
typedef struct node linkedlist_t;

linkedlist_t *linkedlist_alloc(int unit);
void linkedlist_free(linkedlist_t *l);
int linkedlist_length(linkedlist_t *l);
void linkedlist_insert_first(linkedlist_t *l, void *e);
void linkedlist_insert_last(linkedlist_t *l, void *e);
int linkedlist_remove(linkedlist_t *l, node_t *n);
int linkedlist_remove_first(linkedlist_t *l, void *e);
int linkedlist_remove_last(linkedlist_t *l, void *e);
int linkedlist_get(linkedlist_t *l, int pos, void *e);

linkedlist_t *linkedlist_alloc(int unit)
{
    linkedlist_t *l = (linkedlist_t *)malloc(sizeof(linkedlist_t));
    l->left = l;
    l->right = l;
    l->element = malloc(sizeof(int));
    int *u = (int *)l->element;
    *u = unit;

    return l;
}

void linkedlist_free(linkedlist_t *l)
{
    node_t *curr;
    node_t *next;

    curr = l->right;
    while (curr != l)
    {
        next = curr->right;
        free(curr->element);
        free(curr);
        curr = next;
    }
    free(l->element);
    free(l);
}

int linkedlist_length(linkedlist_t *l)
{
    int len = 0;

    node_t *curr = l->right;
    while (curr != l)
    {
        len += 1;
        curr = curr->right;
    }
    return len;
}

void linkedlist_insert(node_t *left, void *e, int unit)
{
    node_t *_new = (node_t *)malloc(sizeof(node_t));
    _new->element = malloc(unit);
    memcpy(_new->element, e, unit);

    node_t *right = left->right;

    _new->left = left;
    _new->right = right;

    left->right = _new;
    right->left = _new;
}

void linkedlist_insert_first(linkedlist_t *l, void *e)
{
    linkedlist_insert(l, e, *((int *)(l->element)));
}

void linkedlist_insert_last(linkedlist_t *l, void *e)
{
    linkedlist_insert(l->left, e, *((int *)(l->element)));
}

int linkedlist_remove(linkedlist_t *l, node_t *n)
{
    if (l->left == l)
        return 1;

    n->left->right = n->right;
    n->right->left = n->left;

    free(n->element);
    free(n);
    return 0;
}

int linkedlist_remove_first(linkedlist_t *l, void *e)
{
    if (l->right == l)
        return 1;

    memcpy(e, l->right->element, *((int *)(l->element)));
    linkedlist_remove(l, l->right);
    return 0;
}

int linkedlist_remove_last(linkedlist_t *l, void *e)
{
    if (l->left == l)
        return 1;

    memcpy(e, l->left->element, *((int *)(l->element)));
    linkedlist_remove(l, l->left);
    return 0;
}

int linkedlist_get(linkedlist_t *l, int pos, void *e)
{
    if (pos < 0)
        return 1;

    int unit = *((int *)l->element);
    int i = 0;
    node_t *curr = l->right;
    while (i < pos && curr != l)
    {
        curr = curr->right;
        i += 1;
    }
    if (i != pos)
        return 1;

    memcpy(e, curr->element, unit);
    return 0;
}

/*-----------------------*/

typedef enum
{
    ALPHA,
    ASTAR,
    QUEST,
    EXCLA,
    BRACK,
} pattern_kind;

typedef struct _pattern
{
    pattern_kind kind;
    char characters[30];
} pattern_t;

typedef struct _task
{
    char string[129];
    int m;
} task_t;

char pattern_str[129];
char str[5][129];

void print_pattern(linkedlist_t *l)
{
    for (int i = 0; i < linkedlist_length(l); i++)
    {
        pattern_t pk;
        linkedlist_get(l, i, &pk);
        if (pk.kind == ALPHA)
            printf("[%c] ", pk.characters[0]);
        else if (pk.kind == ASTAR)
            printf("[*] ");
        else if (pk.kind == QUEST)
            printf("[?] ");
        else if (pk.kind == EXCLA)
            printf("[!] ");
        else
            printf("[%s] ", pk.characters);
    }
    printf("\n");
}

void print_strings(linkedlist_t *l)
{
    for (int i = 0; i < linkedlist_length(l); i++)
    {
        task_t t;
        linkedlist_get(l, i, &t);
        printf("[%s %d]\n", t.string, t.m);
    }
    printf(".\n");
}

int main()
{
    linkedlist_t *pattern_list = linkedlist_alloc(sizeof(pattern_t));
    scanf("%s", pattern_str);

    int in_bracket = 0;
    int bracket_count = 0;
    pattern_t bracket_pattern;
    for (int i = 0; i < strlen(pattern_str); i++)
    {
        if (in_bracket)
        {
            if (pattern_str[i] == ']')
            {
                bracket_pattern.characters[bracket_count] = '\0';
                linkedlist_insert_last(pattern_list, &bracket_pattern);
                in_bracket = 0;
                bracket_count = 0;
            }
            else
            {
                bracket_pattern.characters[bracket_count] = pattern_str[i];
                bracket_count += 1;
            }
            continue;
        }
        pattern_t new_pattern;
        if (isalpha(pattern_str[i]))
        {
            new_pattern.characters[0] = pattern_str[i];
            new_pattern.kind = ALPHA;
        }
        else if (pattern_str[i] == '*')
        {
            new_pattern.kind = ASTAR;
        }
        else if (pattern_str[i] == '?')
        {
            new_pattern.kind = QUEST;
        }
        else if (pattern_str[i] == '!')
        {
            new_pattern.kind = EXCLA;
        }
        else if (pattern_str[i] == '[')
        {
            bracket_pattern.kind = BRACK;
            in_bracket = 1;
            continue;
        }

        linkedlist_insert_last(pattern_list, &new_pattern);
    }

    for (int i = 0; i < 5; i++)
        scanf("%s", str[i]);

    for (int i = 0; i < 5; i++)
    {
        int is_match;
        linkedlist_t *strings = linkedlist_alloc(sizeof(task_t));
        task_t get_task, t;
        get_task.m = 0;
        strcpy(get_task.string, str[i]);
        linkedlist_insert_last(strings, &get_task);
        pattern_t p;

        int curr = 0;
        while (curr < linkedlist_length(pattern_list) && 0 < linkedlist_length(strings))
        {
            linkedlist_remove_first(strings, &get_task);
            if (curr != get_task.m)
                curr = get_task.m;

            if (linkedlist_length(pattern_list) <= curr)
            {
                linkedlist_insert_last(strings, &get_task);
                break;
            }

            linkedlist_get(pattern_list, curr, &p);

            switch (p.kind)
            {
            case ALPHA:
                if (p.characters[0] == get_task.string[0])
                {
                    strcpy(t.string, get_task.string + 1);
                    t.m = get_task.m + 1;
                    linkedlist_insert_last(strings, &t);
                }
                break;

            case ASTAR:
                t.m = get_task.m + 1;
                for (int j = 0; j < strlen(get_task.string) + 1; j++)
                {
                    strcpy(t.string, get_task.string + j);
                    linkedlist_insert_last(strings, &t);
                }
                break;

            case QUEST:
                if (0 < strlen(get_task.string))
                {
                    strcpy(t.string, get_task.string + 1);
                    t.m = get_task.m + 1;
                    linkedlist_insert_last(strings, &t);
                }
                break;

            case EXCLA:
                t.m = get_task.m + 1;
                strcpy(t.string, get_task.string);
                linkedlist_insert_last(strings, &t);

                if (0 < strlen(get_task.string))
                {
                    strcpy(t.string, get_task.string + 1);
                    linkedlist_insert_last(strings, &t);
                }
                break;

            case BRACK:
                if (0 < strlen(get_task.string))
                {
                    if (strchr(p.characters, get_task.string[0]) != NULL)
                    {
                        t.m = get_task.m + 1;
                        strcpy(t.string, get_task.string + 1);
                        linkedlist_insert_last(strings, &t);
                    }
                }
                break;
            }
        }
        if (0 < linkedlist_length(strings))
        {
            task_t t;
            int answer = 0;
            for (int j = 0; j < linkedlist_length(strings); j++)
            {
                linkedlist_get(strings, j, &t);
                if (strlen(t.string) == 0)
                {
                    answer = 1;
                    break;
                }
            }

            if (!answer)
                printf("false\n");
            else
                printf("true\n");
        }
        else
            printf("false\n");

        linkedlist_free(strings);
    }

    linkedlist_free(pattern_list);
    return 0;
}