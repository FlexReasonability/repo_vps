#include <stdio.h>
#include <stdlib.h>

#include "../ast/ast.h"
#include "../ast/stack.h"

struct node_chained_list *infix_to_rpn(int argc, char **argv, int *cursor)
{
    struct node_chained_list *head = init_node_list(NULL);
    struct stack *stack = init_stack();
    int was_last_operand = 0;
    while (*cursor < argc)
    {
        struct ast_node *new_node = init_node(argc, argv, cursor);
        if (new_node->type == OPERAND)
        {
            if (was_last_operand)
            {
                struct ast_node *and_node = init_and_node();
                if (!stack->is_empty)
                {
                    node_push_back(head, pop(stack));
                }
                push(stack, and_node);
            }
            node_push_back(head, new_node);
            was_last_operand = 1;
        }
        else if (new_node->type == OPERATOR)
        {
            if (!stack->is_empty)
            {
                node_push_back(head, pop(stack));
            }
            push(stack, new_node);
            was_last_operand = 0;
        }
    }

    struct ast_node *node = NULL;
    do
    {
        node = pop(stack);
        if (node)
        {
            node_push_back(head, node);
        }
    } while (node);
    free(stack);
    return node_remove_at(head, 0);
}

struct ast_node *rpn_to_ast(struct node_chained_list *rpn)
{
    struct stack *stack = init_stack();
    while (rpn)
    {
        if (rpn->node->type == OPERAND)
        {
            push(stack, rpn->node);
        }
        else
        {
            struct ast_node *right = pop(stack);
            struct ast_node *left = pop(stack);
            rpn->node->left = left;
            rpn->node->right = right;
            push(stack, rpn->node);
        }
        rpn = rpn->next;
    }
    struct ast_node *root = pop(stack);
    free(stack);
    return root;
}

struct ast_node *parse(int argc, char **argv, int *cursor)
{
    struct node_chained_list *rpn = infix_to_rpn(argc, argv, cursor);
    if (rpn)
    {
        struct ast_node *root = rpn_to_ast(rpn);
        free_node_list(rpn);
        return root;
    }
    return NULL;
}
