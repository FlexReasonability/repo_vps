#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../chained_list/chained_list.h"

int matches_type(const char *path, char type)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0)
    {
        fprintf(stderr,
                "myfind: debug: Erreur lors de l'obtention des informations du "
                "fichier\n");
        exit(1);
    }
    switch (type)
    {
    case 'b':
        return S_ISBLK(path_stat.st_mode); // Fichier spécial en mode bloc
    case 'c':
        return S_ISCHR(path_stat.st_mode); // Fichier spécial en mode caractère
    case 'd':
        return S_ISDIR(path_stat.st_mode); // Répertoire
    case 'f':
        return S_ISREG(path_stat.st_mode); // Fichier régulier
    case 'l':
        return S_ISLNK(path_stat.st_mode); // Lien symbolique
    case 'p':
        return S_ISFIFO(path_stat.st_mode); // Pipe nommé (FIFO)
    case 's':
        return S_ISSOCK(path_stat.st_mode); // Socket
    default:
        fprintf(stderr, "Type inconnu: %c\n", type);
        return 0;
    }
}

struct chained_list *eval_type(struct chained_list *all_files, char *type)
{
    struct chained_list *filtered_list = init_list("HEAD");
    if (type == NULL || strlen(type) != 1)
    {
        fprintf(stderr, "myfind: %s is an invalid type\n", type);
        exit(1);
    }

    while (all_files != NULL)
    {
        if (matches_type(all_files->path, type[0]))
        {
            push_back(filtered_list, all_files->path);
        }
        all_files = all_files->next;
    }

    return remove_at(filtered_list, 0);
}
