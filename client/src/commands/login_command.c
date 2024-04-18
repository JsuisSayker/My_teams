/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** login_command
*/

#include "client.h"

int login_command(char *message, char **command, client_t *client)
{
    client->user_name = strdup(command[2]);
    client->is_logged = true;
    client->uuid = strdup(command[3]);
    client_event_logged_in(client->uuid, client->user_name);
    return OK;
}
