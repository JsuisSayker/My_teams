/*
** EPITECH PROJECT, 2023
** B-CPE-200-BDX-2-1-lemin-marc.mendia
** File description:
** add_node
*/

#include <unistd.h>
#include "proto_lib.h"
#include "linked_list.h"

list_t *add_node_in_list(list_t *list, char *str)
{
    list_t *node = create_node(str);
    list_t *next_list = list;

    if (next_list == NULL)
        return node;
    while (next_list->next != NULL)
        next_list = next_list->next;
    next_list->next = node;
    return list;
}
