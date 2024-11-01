#include "chained_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct chained_list *init_list(char *path)
{
    struct chained_list *new_list = malloc(sizeof(struct chained_list));
    new_list->next = NULL;
    new_list->path = path;
    return new_list;
}

void push_back(struct chained_list *current, char *path)
{
    struct chained_list *new_block = init_list(path);
    struct chained_list *head = current;
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = new_block;
}

size_t get_length(struct chained_list *current)
{
    size_t i = 0;
    while (current)
    {
        i++;
        current = current->next;
    }
    return i;
}

struct chained_list *remove_at(struct chained_list *current, size_t index)
{
    if (get_length(current) <= index)
    {
        fprintf(stderr, "myfind: debug: remove_at at a wrong index");
        exit(1);
    }

    if (index == 0)
    {
        struct chained_list *head = current->next;
        free(current->path);
        free(current);
        return head;
    }
    size_t i = 0;
    while (i < index - 1)
    {
        i++;
        current = current->next;
    }
    struct chained_list *to_delete = current->next;
    current->next = to_delete->next;

    free(to_delete->path);
    free(to_delete);
    return current;
}

struct chained_list *duplicate_list(struct chained_list *head)
{
    if (head == NULL)
    {
        return NULL;
    }

    struct chained_list *new_head = malloc(sizeof(struct chained_list));
    if (new_head == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }
    new_head->path = strdup(head->path);
    new_head->next = NULL;

    struct chained_list *current_old = head->next;
    struct chained_list *current_new = new_head;

    while (current_old != NULL)
    {
        struct chained_list *new_node = malloc(sizeof(struct chained_list));
        if (new_node == NULL)
        {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(1);
        }
        new_node->path = strdup(current_old->path);
        new_node->next = NULL;

        current_new->next = new_node;
        current_new = new_node;
        current_old = current_old->next;
    }

    return new_head;
}

int is_in_list(struct chained_list *list, const char *value)
{
    while (list != NULL)
    {
        if (strcmp(list->path, value) == 0)
        {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

struct chained_list *union_lists(struct chained_list *univers,
                                 struct chained_list *a, struct chained_list *b)
{
    struct chained_list *result = init_list("HEAD");

    while (univers != NULL)
    {
        if (is_in_list(a, univers->path) || is_in_list(b, univers->path))
        {
            push_back(result, univers->path);
        }
        univers = univers->next;
    }
    return remove_at(result, 0);
}

struct chained_list *intersection_lists(struct chained_list *univers,
                                        struct chained_list *a,
                                        struct chained_list *b)
{
    struct chained_list *result = init_list("HEAD");

    while (univers != NULL)
    {
        if (is_in_list(a, univers->path) && is_in_list(b, univers->path))
        {
            push_back(result, univers->path);
        }
        univers = univers->next;
    }

    return remove_at(result, 0);
}

// Fonction pour libérer la mémoire d'une liste chaînée
void free_list(struct chained_list *head)
{
    if (head == NULL)
    {
        return;
    }
    free_list(head->next);
    free(head->path);
    free(head);
}

void print_list(struct chained_list *list)
{
    while (list)
    {
        printf("%s\n", list->path);
        list = list->next;
    }
}
