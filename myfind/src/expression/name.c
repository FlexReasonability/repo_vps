#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../chained_list/chained_list.h"

char *get_filename(char *path)
{
    char *filename = strrchr(path, '/');
    if (filename)
    {
        return filename + 1;
    }
    return path;
}

struct chained_list *eval_name(struct chained_list *all_files, char *pattern)
{
    if (!all_files)
    {
        return NULL;
    }
    struct chained_list *filtered_list = init_list("HEAD");

    while (all_files != NULL)
    {
        if (fnmatch(pattern, get_filename(all_files->path), 0) == 0)
        {
            push_back(filtered_list, strdup(all_files->path));
        }
        all_files = all_files->next;
    }
    return remove_at(filtered_list, 0);
}
