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

list_user_t *create_node(char *username, char *description, int uuid)
{
    list_user_t *new_node = malloc(sizeof(list_user_t));

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
    if (uuid != 0)
        my_strcpy("1\0", &(new_node)->uuid);
    else
        my_strcpy("0\0", &(new_node)->uuid);
    new_node->next = NULL;
    return new_node;
}
