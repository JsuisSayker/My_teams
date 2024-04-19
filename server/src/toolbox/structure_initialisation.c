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
    (*new_user)->entries.le_next = NULL;
    (*new_user)->entries.le_prev = NULL;
    (*new_user)->teams.lh_first = NULL;
    (*new_user)->personnal_messages.lh_first = NULL;
    return OK;
}
