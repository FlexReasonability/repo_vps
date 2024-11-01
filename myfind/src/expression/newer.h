#ifndef NEWER_H
#define NEWER_H

#include "../chained_list/chained_list.h"

struct chained_list *eval_newer(struct chained_list *all_files,
                                char *file_path);
#endif /* NEWER_H */
