#ifndef CHAINED_LIST_H
#define CHAINED_LIST_H

#include <stddef.h>

struct chained_list
{
    char *path;
    struct chained_list *next;
};

struct chained_list *init_list(char *path);
void push_back(struct chained_list *current, char *path);
size_t get_length(struct chained_list *current);
struct chained_list *remove_at(struct chained_list *current, size_t index);
struct chained_list *duplicate_list(struct chained_list *head);
struct chained_list *union_lists(struct chained_list *univers,
                                 struct chained_list *a,
                                 struct chained_list *b);
struct chained_list *intersection_lists(struct chained_list *univers,
                                        struct chained_list *a,
                                        struct chained_list *b);
void free_list(struct chained_list *head);
void print_list(struct chained_list *list);

#endif /* CHAINED_LIST_H */
