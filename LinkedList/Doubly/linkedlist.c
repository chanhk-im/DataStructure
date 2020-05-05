#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

linkedlist_t *
linkedlist_alloc(int unit)
{
    linkedlist_t *new_list = (linkedlist_t *)malloc(sizeof(linkedlist_t));
    new_list->left = new_list;
    new_list->right = new_list;
    new_list->element = malloc(sizeof(int));
    *((int *)new_list->element) = unit;

    return new_list;
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
    node_t *curr;
    int len = 0;
    curr = l->right;
    while (curr != l)
    {
        curr = curr->right;
        len += 1;
    }

    return len;
}

void linkedlist_insert(node_t *left, void *e, int unit)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    node_t *right = left->right;

    new_node->element = malloc(unit);
    memcpy(new_node->element, e, unit);

    new_node->left = left;
    new_node->right = right;

    left->right = new_node;
    right->left = new_node;
}

void linkedlist_insert_first(linkedlist_t *l, void *e)
{
    linkedlist_insert(l, e, *((int *)l->element));
}

void linkedlist_insert_last(linkedlist_t *l, void *e)
{
    node_t *curr = l->right;

    while (curr->right != l)
        curr = curr->right;
    
    linkedlist_insert(curr, e, *((int *)l->element));
}

int linkedlist_remove(linkedlist_t *l, node_t *n)
{
    if (linkedlist_length(l) < 1)
        return 1;

    n->left->right = n->right;
    n->right->left = n->left;

    free(n->element);
    free(n);
    return 0;
}

int linkedlist_remove_first(linkedlist_t *l, void *e)
{
    memcpy(e, l->right->element, *((int *)l->element));
    return linkedlist_remove(l, l->right);
}

int linkedlist_remove_last(linkedlist_t *l, void *e)
{
    if (linkedlist_length(l) < 1)
        return 1;

    node_t *curr = l->right;

    while (curr->right != l)
        curr = curr->right;
    memcpy(e, curr->element, *((int *)l->element));
    return linkedlist_remove(l, curr);
}

int linkedlist_get(linkedlist_t *l, int pos, void *e)
{
    if (linkedlist_length(l) < pos)
        return 1;

    node_t *curr = l->right;
    for (int i = 0; i < pos; i++)
        curr = curr->right;
    
    memcpy(e, curr->element, *((int *)l->element));
    return 0;
}