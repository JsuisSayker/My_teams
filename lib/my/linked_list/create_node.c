/*
** EPITECH PROJECT, 2023
** create_node
** File description:
** create_node
*/

#include <unistd.h>
#include <stdlib.h>

#include "proto_lib.h"
#include "linked_list.h"

list_t *create_node(char *str)
{
    list_t *new_node = malloc(sizeof(list_t));

    if (!new_node)
        return NULL;
    my_strcpy(str, &(new_node)->str);
    new_node->next = NULL;
    return new_node;
}
