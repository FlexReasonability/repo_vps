#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

struct node_chained_list *init_node_list(struct ast_node *node)
{
    struct node_chained_list *new_list =
        malloc(sizeof(struct node_chained_list));
    new_list->next = NULL;
    new_list->node = node;
    return new_list;
}

void node_push_back(struct node_chained_list *current, struct ast_node *node)
{
    struct node_chained_list *new_block = init_node_list(node);
    struct node_chained_list *head = current;
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = new_block;
}

size_t node_get_length(struct node_chained_list *current)
{
    size_t i = 0;
    while (current)
    {
        i++;
        current = current->next;
    }
    return i;
}

struct node_chained_list *node_remove_at(struct node_chained_list *current,
                                         size_t index)
{
    if (node_get_length(current) <= index)
    {
        fprintf(stderr, "myfind: debug: node_removing at a wrong index");
        exit(1);
    }

    if (index == 0)
    {
        struct node_chained_list *head = current->next;
        free(current);
        return head;
    }
    size_t i = 0;
    while (i < index - 1)
    {
        i++;
        current = current->next;
    }
    struct node_chained_list *to_delete = current->next;
    current->next = to_delete->next;

    free(to_delete);
    return current;
}

void free_node_list(struct node_chained_list *list)
{
    while (list)
    {
        struct node_chained_list *head = list;
        list = list->next;
        free(head);
    }
}

void print_node_list(struct node_chained_list *list)
{
    while (list)
    {
        printf("expr: %s", list->node->value);
        if (list->node->arg)
        {
            printf(" arg: %s\n", list->node->arg);
        }
        else
        {
            printf("\n");
        }
        list = list->next;
    }
}

struct stack *init_stack(void)
{
    struct stack *new_stack = malloc(sizeof(struct stack));
    if (!new_stack)
    {
        fprintf(stderr, "myfind: debug: error while creating stack");
        exit(1);
    }
    new_stack->head = NULL;
    new_stack->is_empty = 1;
    return new_stack;
}

void push(struct stack *stack, struct ast_node *node)
{
    struct node_chained_list *new_list =
        malloc(sizeof(struct node_chained_list));
    new_list->node = node;
    new_list->next = stack->head;
    stack->head = new_list;
    stack->is_empty = 0;
}

struct ast_node *pop(struct stack *stack)
{
    if (!stack->head)
    {
        return NULL;
    }

    struct node_chained_list *old_head = stack->head;
    stack->head = old_head->next;
    struct ast_node *node = old_head->node;
    free(old_head);
    if (!stack->head)
    {
        stack->is_empty = 1;
    }
    return node;
}
