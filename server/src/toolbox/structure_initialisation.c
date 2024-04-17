/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** structure_initialisation
*/

#include "my.h"

int user_initialisation(user_t *user, char *name)
{
    if (name == NULL || user == NULL)
        return ERROR;
    user->username = strdup(name);
    user->uuid = generate_uuid();
    user->teams = NULL;
    user->personnal_messages = NULL;
    return OK;
}
