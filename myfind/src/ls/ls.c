#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "../chained_list/chained_list.h"

char *path_cat(const char *base, const char *other)
{
    if (base == NULL)
    {
        char *result = malloc((strlen(other) + 1) * sizeof(char));
        if (result == NULL)
        {
            fprintf(stderr, "myfind: debug: malloc failed\n");
            exit(1);
        }
        strcpy(result, other);
        return result;
    }

    size_t dest_len = strlen(base);
    size_t other_len = strlen(other);
    size_t total_len = dest_len + other_len + 2;
    char *result = malloc(total_len * sizeof(char));
    if (result == NULL)
    {
        fprintf(stderr, "myfind: debug: malloc failed\n");
        exit(1);
    }

    strcpy(result, base);
    if (dest_len > 0 && result[dest_len - 1] != '/')
    {
        strcat(result, "/");
    }
    strcat(result, other);

    return result;
}

void ls_rec(const char *starting_point, struct chained_list *all_files, int add_starting_point)
{
    DIR *dir = opendir(starting_point);
    struct dirent *ent;

    if (!dir)
    {
        fprintf(stderr, "myfind: couldn't open dir \"%s\". make sure it exists\n", starting_point);
        exit(1);
    }

    if (strcmp(starting_point, "./") == 0)
    {
        push_back(all_files, strdup("."));
    }
    else if (add_starting_point)
    {
        push_back(all_files, strdup(starting_point));
    }

    while ((ent = readdir(dir)) != NULL)
    {
        if (ent->d_name[0] != '.')
        {
            char *full_path = path_cat(starting_point, ent->d_name);
            push_back(all_files, strdup(full_path));  // Ajoute à la liste (full_path est libéré dans free_list)

            if (ent->d_type == 4)
            {
                ls_rec(full_path, all_files, 0);
            }

            free(full_path); // Libération immédiate de full_path
        }
    }

    closedir(dir);
}

struct chained_list *ls(const char *starting_point)
{
    struct chained_list *all_files = init_list(strdup("HEAD"));
    ls_rec(starting_point, all_files, 1);
    all_files = remove_at(all_files, 0);
    return all_files;
}