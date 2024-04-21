/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** get_team_by_uuid
*/

#include "server.h"

team_t *get_team_by_uuid(team_t *teams, char *uuid)
{
    team_t *tmp = teams;

    if (teams == NULL || uuid == NULL)
        return NULL;
    while (tmp) {
        printf("tmp->team_uuid: %s\n", tmp->team_uuid);
        if (strcmp(tmp->team_uuid, uuid) == 0)
            return tmp;
        tmp = tmp->entries.tqe_next;
    }
    return NULL;
}
