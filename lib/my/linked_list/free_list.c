/*
** EPITECH PROJECT, 2023
** B-CPE-200-BDX-2-1-lemin-marc.mendia
** File description:
** free_list
*/

#include <stdlib.h>
#include <unistd.h>

#include "proto_lib.h"
#include "linked_list.h"

void free_node(list_t *node)
{
    if (node->str != NULL){
        free(node->str);
    }
    free(node);
}

void free_list(list_t *list)
{
    list_t *list_tmp = NULL;
    list_t *current = list;

    while (current != NULL) {
        list_tmp = current;
        current = current->next;
        free_node(list_tmp);
    }
    return;
}
