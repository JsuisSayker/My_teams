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

list_user_t *create_node(char *username, char *uuid, int is_connected)
{
    list_user_t *new_node = malloc(sizeof(list_user_t));

    if (!new_node)
        return NULL;
    if (username != NULL)
        my_strcpy(username, &(new_node)->username);
    else
        new_node->username = NULL;
    if (uuid != NULL)
        my_strcpy(uuid, &(new_node)->uuid);
    else
        new_node->uuid = NULL;
    if (is_connected != 0)
        my_strcpy("1\0", &(new_node)->is_connected);
    else
        my_strcpy("0\0", &(new_node)->is_connected);
    new_node->next = NULL;
    return new_node;
}
