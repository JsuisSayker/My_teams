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

list_t *create_node(char *username, char *description)
{
    list_t *new_node = malloc(sizeof(list_t));

    if (!new_node)
        return NULL;
    if (username != NULL)
        my_strcpy(username, &(new_node)->username);
    else
        new_node->username = NULL;
    if (description != NULL)
        my_strcpy(description, &(new_node)->description);
    else
        new_node->description = NULL;
    new_node->next = NULL;
    return new_node;
}
