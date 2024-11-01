#ifndef EVAL_H
#define EVAL_H

#include "../ast/ast.h"
#include "../chained_list/chained_list.h"

struct chained_list *eval(struct chained_list *all_files,
                          struct ast_node *root);

#endif /* EVAL_H */
