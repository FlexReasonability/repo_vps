#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../chained_list/chained_list.h"

#ifdef __APPLE__
#    define ST_MTIMESPEC st_mtimespec
#else // POSIX
#    define ST_MTIMESPEC st_mtim
#endif

int is_newer(struct timespec t1, struct timespec t2)
{
    if (t1.tv_sec > t2.tv_sec)
        return 1;
    if (t1.tv_sec < t2.tv_sec)
        return 0;
    return t1.tv_nsec > t2.tv_nsec;
}

struct timespec get_modification_time(const char *path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0)
    {
        perror("Erreur lors de l'obtention des informations du fichier");
        exit(1);
    }
    return path_stat.ST_MTIMESPEC;
}

struct chained_list *eval_newer(struct chained_list *all_files, char *file_path)
{
    struct chained_list *filtered_list = init_list("HEAD");

    // Obtenir le temps de modification de file_path avec précision nanoseconde
    struct timespec reference_time = get_modification_time(file_path);

    // Parcourir la liste all_files
    while (all_files != NULL)
    {
        // Obtenir le temps de modification du fichier actuel avec précision
        // nanoseconde
        struct timespec file_time = get_modification_time(all_files->path);

        // Si le fichier actuel est plus récent que file_path, l'ajouter à la
        // liste filtrée
        if (is_newer(file_time, reference_time))
        {
            push_back(filtered_list, all_files->path);
        }

        all_files = all_files->next;
    }

    return remove_at(filtered_list, 0);
}
