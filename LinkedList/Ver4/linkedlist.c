#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define TRUE 1
#define FALSE 0

linkedlist_t *linkedlist_alloc(int unit)
{
    linkedlist_t *new_list = (linkedlist_t *)malloc(sizeof(linkedlist_t));
    new_list->unit = unit;
    new_list->last = NULL;

    return new_list;
}

void linkedlist_free(linkedlist_t *l)
{
    node_t *curr;
    node_t *next; 

    if (l->last)
    {
        curr = l->last->next;
        do
        {
            next = curr->next;
            free(curr->element);
            free(curr);
            curr = next;
        } while (curr != l->last);
        
    }

    free(l);
}

int linkedlist_length(linkedlist_t *l)
{
    int len = 0;
    if (l->last)
    {
        node_t *curr = l->last;

        do
        {
            curr = curr->next;
            len += 1;
        } while (curr != l->last);
    }
    return len;
}

void linkedlist_insert_first(linkedlist_t *l, void *e)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->element = malloc(l->unit);
    memcpy(new_node->element, e, l->unit);

    if (l->last)
    {
        new_node->next = l->last->next;
        l->last->next = new_node;
    }
    else
    {
        l->last = new_node;
        l->last->next = new_node;
    }
    
}

void linkedlist_insert_last(linkedlist_t *l, void *e)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->element = malloc(l->unit);
    memcpy(new_node->element, e, l->unit);

    if (l->last)
    {
        new_node->next = l->last->next;
        l->last->next = new_node;
        l->last = new_node;
    }
    else
    {
        l->last = new_node;
        l->last->next = new_node;
    }
    
}

int linkedlist_remove(linkedlist_t *l, node_t *n)
{
    if (l->last == NULL)
        return FALSE;
    
    node_t *prev = l->last;
    node_t *curr = prev->next;
    while (curr != n && curr != l->last)
    {
        prev = prev->next;
        curr = curr->next;
    }

    if (curr != n)
        return FALSE;

    if (prev != curr)
        prev->next = curr->next;
    else
        l->last = NULL;
    
    free(curr->element);
    free(curr);
    return TRUE;
}

int linkedlist_remove_first(linkedlist_t *l, void *e)
{
    if (l->last == NULL)
        return FALSE;

    node_t *del = l->last->next;
    memcpy(e, del->element, l->unit);
    linkedlist_remove(l, del);
    return TRUE;
}

int linkedlist_remove_last(linkedlist_t *l, void *e)
{
    if (l->last == NULL)
        return FALSE;

    node_t *del = l->last;
    memcpy(e, del->element, l->unit);
    
    if (l->last == l->last->next)
        l->last = NULL;
    else
    {
        node_t *n = l->last;
        while (n->next != l->last)
            n = n->next;
        n->next = l->last->next;
        l->last = n;
    }
    
    free(del->element);
    free(del);

    return TRUE;
}

int linkedlist_get(linkedlist_t *l, int pos, void *e)
{
    if (pos < 0 || l->last == NULL)
        return FALSE;

    int i = 0;
    node_t *curr = l->last->next;
    while (i < pos)
    {
        curr = curr->next;
        i++;
    }

    memcpy(e, curr->element, l->unit);
    return TRUE;
}