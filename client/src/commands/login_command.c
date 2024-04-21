/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** login_command
*/

#include "client.h"

int login_command(char *message, char **command, client_t *client)
{
    if (client->user_name != NULL && client->uuid != NULL) {
        free(client->user_name);
        free(client->uuid);
        client->user_name = NULL;
        client->uuid = NULL;
    }
    client->user_name = strdup(command[2]);
    client->is_logged = true;
    client->uuid = strdup(command[3]);
    client_event_logged_in(client->uuid, client->user_name);
    return OK;
}
