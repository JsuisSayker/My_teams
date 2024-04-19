/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** structure_initialisation
*/

#include "server.h"

static int init_information(user_t **new_user, char *name)
{
    char *uuid = NULL;

    if (name == NULL || *new_user == NULL)
        return ERROR;
    if (strcpy((*new_user)->username, name) == NULL)
        return ERROR;
    if (strcpy((*new_user)->description, "No description\0") == NULL)
        return ERROR;
    uuid = generate_uuid();
    if (uuid == NULL)
        return ERROR;
    if (strcpy((*new_user)->uuid, uuid) == NULL){
        free(uuid);
        return ERROR;
    }
    free(uuid);
    return OK;
}

int user_initialisation(user_t **new_user, char *name, int socket)
{
    if (name == NULL || *new_user == NULL)
        return ERROR;
    if (strchr(name, '|') != NULL){
        write(socket, "500 Username can't contain '|'\a\n\0", 30);
        return ERROR;
    }
    if (init_information(new_user, name) == ERROR)
        return ERROR;
    (*new_user)->user_connected = 1;
    (*new_user)->entries.tqe_next = NULL;
    (*new_user)->entries.tqe_prev = NULL;
    (*new_user)->teams.tqh_first = NULL;
    (*new_user)->teams.tqh_last = NULL;
    (*new_user)->personnal_messages.tqh_first = NULL;
    (*new_user)->personnal_messages.tqh_last = NULL;
    return OK;
}

personnal_message_t *copy_message(personnal_message_t *message)
{
    personnal_message_t *new_message = malloc(sizeof(personnal_message_t));

    if (message == NULL)
        return new_message;
    if (strcpy(new_message->message, message->message) == NULL)
        return NULL;
    if (strcpy(new_message->sender_uuid, message->sender_uuid) == NULL)
        return NULL;
    if (strcpy(new_message->receiver_uuid, message->receiver_uuid) == NULL)
        return NULL;
    return new_message;
}