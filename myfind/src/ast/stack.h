#ifndef STACK_H
#define STACK_H

#include <stddef.h>

#include "ast.h"

struct node_chained_list
{
    struct ast_node *node;
    struct node_chained_list *next;
};

struct stack
{
    struct node_chained_list *head;
    int is_empty;
};

struct stack *init_stack(void);
void push(struct stack *stack, struct ast_node *node);
struct ast_node *pop(struct stack *stack);
struct node_chained_list *init_node_list(struct ast_node *node);
void node_push_back(struct node_chained_list *current, struct ast_node *node);
size_t node_get_length(struct node_chained_list *current);
struct node_chained_list *node_remove_at(struct node_chained_list *current,
                                         size_t index);
void print_node_list(struct node_chained_list *list);
void free_node_list(struct node_chained_list *list);

#endif /* STACK_H */
