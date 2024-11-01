#include <stdio.h>
#include <string.h>

#include "../ast/ast.h"
#include "../chained_list/chained_list.h"
#include "../expression/name.h"
#include "../expression/newer.h"
#include "../expression/type.h"

struct chained_list *eval_operand(struct chained_list *all_files,
                                  struct ast_node *operand)
{
    if (strcmp(operand->value, "-print") == 0)
    {
        return duplicate_list(all_files);
    }
    if (strcmp(operand->value, "-name") == 0)
    {
        return eval_name(all_files, operand->arg);
    }
    if (strcmp(operand->value, "-type") == 0)
    {
        return eval_type(all_files, operand->arg);
    }
    if (strcmp(operand->value, "-newer") == 0)
    {
        return eval_newer(all_files, operand->arg);
    }
    return NULL;
}

struct chained_list *eval(struct chained_list *all_files, struct ast_node *root)
{
    if (root->left && root->right)
    {
        struct chained_list *result_left =
            eval(duplicate_list(all_files), root->left);
        struct chained_list *result_right =
            eval(duplicate_list(all_files), root->right);

        struct chained_list *merge_result = NULL;
        if (strcmp(root->value, "-o") == 0)
        {
            if (!result_left)
            {
                free_list(result_left);
                free_list(all_files);
                return result_right;
            }
            free_list(result_right);
            free_list(all_files);
            return result_left;
        }
        if (strcmp(root->value, "-a") == 0)
        {
            merge_result =
                intersection_lists(duplicate_list(all_files), result_left, result_right);
            free_list(result_left);
            free_list(result_right);
        }
        free_list(all_files);
        return merge_result;
    }
    else
    {
        struct chained_list *result = eval_operand(all_files, root);
        free_list(all_files);
        return result;
    }
}
