#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define TRUE 1
#define FALSE 0

linkedlist_t *linkedlist_alloc(int unit)
{
    linkedlist_t *new_list;
    new_list = (linkedlist_t *)malloc(sizeof(linkedlist_t));

    new_list->element = malloc(sizeof(int));
    *((int *)new_list->element) = unit;
    new_list->next = NULL;
    return new_list;
}

void linkedlist_free(linkedlist_t *l)
{
    node_t *next, *curr;

    curr = l, next = curr->next;
    while (next != NULL)
    {
        curr = next;
        next = next->next;

        free(curr->element);
        free(curr);
    }

    free(l);
}

int linkedlist_length(linkedlist_t *l)
{
    int len = 0;
    node_t *curr = l;

    while (curr->next != NULL)
    {
        curr = curr->next;
        len += 1;
    }

    return len;
}

void linkedlist_insert_first(linkedlist_t *l, void *e)
{
    if (l == NULL)
        return;

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->element = malloc(*((int *)l->element));
    memcpy(new_node->element, e, *((int *)l->element));

    if (linkedlist_length(l) > 0)
        new_node->next = l->next;
    else
        new_node->next = NULL;

    l->next = new_node;
}

void linkedlist_insert_last(linkedlist_t *l, void *e)
{
    if (l == NULL)
        return;

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->element = malloc(*((int *)l->element));
    memcpy(new_node->element, e, *((int *)l->element));
    new_node->next = NULL;

    node_t *curr = l;
    
    while (curr->next != NULL)
        curr = curr->next;

    curr->next = new_node;
}

int linkedlist_remove(linkedlist_t *l, node_t *n)
{
    node_t *prev = l;
    node_t *curr = prev->next;

    while (curr != NULL && curr != n)
    {
        prev = prev->next;
        curr = curr->next;
    }

    if (curr == NULL)
        return FALSE;

    prev->next = curr->next;
    free(curr->element);
    free(curr);
    return TRUE;
}

int linkedlist_remove_first(linkedlist_t *l, void *e)
{
    if (linkedlist_length(l) == 0)
        return FALSE;

    node_t *del = l->next;
    memcpy(e, del->element, *((int *)l->element));
    l->next = del->next;

    free(del->element);
    free(del);
    return TRUE;
}

int linkedlist_remove_last(linkedlist_t *l, void *e)
{
    if (linkedlist_length(l) == 0)
        return FALSE;

    node_t *curr = l->next;
    node_t *prev = l;

    while (curr->next != NULL)
    {
        curr = curr->next;
        prev = prev->next;
    }

    memcpy(e, curr->element, *((int *)l->element));
    free(curr->element);
    free(curr);

    prev->next = NULL;
    return TRUE;
}

int linkedlist_get(linkedlist_t *l, int pos, void *e)
{
    if (pos < 0)
        return FALSE;

    int i = 0;
    node_t *n = l->next;

    while (i < pos && n != NULL)
    {
        n = n->next;
        i++;
    }

    if (n == NULL)
        return FALSE;

    memcpy(e, n->element, *((int *)l->element));
    return TRUE;
}
