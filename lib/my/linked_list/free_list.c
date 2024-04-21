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

void free_node(list_user_t *node)
{
    if (node->username != NULL){
        free(node->username);
    }
    if (node->uuid != NULL){
        free(node->uuid);
    }
    if (node->is_connected != NULL){
        free(node->is_connected);
    }
    free(node);
}

void free_list(list_user_t *list)
{
    list_user_t *list_user_tmp = NULL;
    list_user_t *current = list;

    while (current != NULL) {
        list_user_tmp = current;
        current = current->next;
        free_node(list_user_tmp);
    }
    return;
}

void free_message_node(list_t *node)
{
    if (node->message != NULL){
        free(node->message);
    }
    if (node->sender_uuid != NULL){
        free(node->sender_uuid);
    }
    if (node->receiver_uuid != NULL){
        free(node->receiver_uuid);
    }
    free(node);
}

void free_message_list(list_t *list)
{
    list_t *list_tmp = NULL;
    list_t *current = list;

    while (current != NULL) {
        list_tmp = current;
        current = current->next;
        free_message_node(list_tmp);
    }
    return;
}
