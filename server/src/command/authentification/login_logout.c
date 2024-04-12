/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** login_logout
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

int login(server_data_t *server, user_t *user)
{
    if (server == NULL || user == NULL)
        return ERROR;
    if (user->is_logged == true) {
        dprintf(user->socket, "401 Already logged in\n");
        return KO;
    }
    if (user->command[1] == NULL) {
        dprintf(user->socket, "500 Missing username\n");
        return KO;
    }
    user->username = strdup(user->command[1]);
    if (user->uuid != NULL)
    user->uuid = generate_uuid();
    user->is_logged = true;
    dprintf(user->socket, "200 Logged in\n");
    return OK;
}

int logout(server_data_t *server, user_t *user)
{
    
}