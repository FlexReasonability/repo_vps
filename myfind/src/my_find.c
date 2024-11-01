#include <stdio.h>

#include "ast/ast.h"
#include "chained_list/chained_list.h"
#include "eval/eval.h"
#include "ls/ls.h"
#include "parse/parse.h"

char *find_starting_point(int argc, char **argv, int *cursor)
{
    if (argc == 1 || argv[1][0] == '-')
    {
        return "./";
    }
    *cursor = *cursor + 1;
    return argv[1];
}

int my_find(int argc, char **argv)
{
    int cursor = 1;
    char *starting_point = find_starting_point(argc, argv, &cursor);
    struct chained_list *all_files = ls(starting_point);
    struct ast_node *root = parse(argc, argv, &cursor);
    if (root)
    {
        struct chained_list *result = eval(all_files, root);
        print_list(result);
        free_list(result);
        free_ast(root);
        return 0;
    }
    print_list(all_files);
    free_list(all_files);
    return 0;
}
