/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** get_user_by_uuid
*/

#include "server.h"

user_t *get_user_by_uuid(server_data_t *server, char *uuid)
{
    user_t *tmp;

    if (server == NULL || uuid == NULL)
        return NULL;
    tmp = server->users.tqh_first;
    TAILQ_FOREACH(tmp, &server->users, entries) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
    }
    return NULL;
}
