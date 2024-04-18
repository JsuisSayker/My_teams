/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** user_is_exist
*/

#include <stdbool.h>
#include "server.h"

bool user_is_exist(server_data_t *server, char *user_uuid)
{
    user_t *tmp = server->users.lh_first;

    while (tmp) {
        if (strcmp(tmp->uuid, user_uuid) == 0)
            return true;
        tmp = tmp->entries.le_next;
    }
    return false;
}