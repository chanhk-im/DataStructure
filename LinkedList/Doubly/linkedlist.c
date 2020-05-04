#include <stdio.h>
#include <stdlib.h>
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
    right->left - new_node;
}

void linkedlist_insert_first(linkedlist_t *l, void *e)
{
    linkedlist_insert(0, e, *((int *)l->element));
}