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

list_t *create_message_node(char *message, char *sender_uuid,
    char *time_stamp)
{
    list_t *new_node = malloc(sizeof(list_t));

    if (!new_node)
        return NULL;
    if (message != NULL)
        my_strcpy(message, &(new_node)->message);
    else
        new_node->message = NULL;
    if (sender_uuid != NULL)
        my_strcpy(sender_uuid, &(new_node)->sender_uuid);
    else
        new_node->sender_uuid = NULL;
    if (time_stamp != NULL)
        my_strcpy(time_stamp, &(new_node)->time_stamp);
    else
        new_node->time_stamp = NULL;
    new_node->next = NULL;
    return new_node;
}
