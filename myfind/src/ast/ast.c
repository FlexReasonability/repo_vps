#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_operand(char *value)
{
    if (strcmp(value, "-print") == 0)
    {
        return 1;
    }
    if (strcmp(value, "-name") == 0)
    {
        return 1;
    }
    if (strcmp(value, "-type") == 0)
    {
        return 1;
    }
    if (strcmp(value, "-newer") == 0)
    {
        return 1;
    }
    return 0;
}

int need_arg(char *value)
{
    if (strcmp(value, "-print") == 0)
    {
        return 0;
    }
    if (strcmp(value, "-name") == 0)
    {
        return 1;
    }
    if (strcmp(value, "-type") == 0)
    {
        return 1;
    }
    if (strcmp(value, "-newer") == 0)
    {
        return 1;
    }
    if (strcmp(value, "-o") == 0)
    {
        return 0;
    }
    if (strcmp(value, "-a") == 0)
    {
        return 0;
    }
    fprintf(stderr, "myfind: %s expression doesn't exist\n", value);
    exit(1);
    return 0;
}

struct ast_node *init_node(int argc, char **argv, int *cursor)
{
    char *current = argv[*cursor];

    struct ast_node *new_node = malloc(sizeof(struct ast_node));
    new_node->value = current;
    new_node->type = OPERATOR;
    if (is_operand(current))
    {
        new_node->type = OPERAND;
    }
    if (need_arg(current))
    {
        *cursor = *cursor + 1;
        if (*cursor >= argc)
        {
            fprintf(stderr, "myfind: missing argument after %s\n",
                    argv[*cursor - 1]);
            exit(1);
        }
        new_node->arg = argv[*cursor];
    }
    *cursor = *cursor + 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct ast_node *init_and_node(void)
{
    struct ast_node *new_node = malloc(sizeof(struct ast_node));
    new_node->value = "-a";
    new_node->type = OPERATOR;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void free_ast(struct ast_node *root)
{
    if (!root)
    {
        return;
    }
    free_ast(root->left);
    free_ast(root->right);
    free(root);
}