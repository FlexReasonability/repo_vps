#ifndef PARSE_H
#define PARSE_H

#include "../ast/ast.h"

struct ast_node *parse(int argc, char **argv, int *cursor);

#endif /* PARSE_H */
