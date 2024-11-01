#ifndef AST_H
#define AST_H

enum node_type
{
    OPERAND,
    OPERATOR
};

struct ast_node
{
    enum node_type type;
    char *value;
    char *arg;
    char *arg2;
    struct ast_node *left;
    struct ast_node *right;
};

struct ast_node *init_node(int argc, char **argv, int *cursor);
struct ast_node *init_and_node(void);
void free_ast(struct ast_node *root);

#endif /* AST_H */
